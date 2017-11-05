---
layout: post
title: "Celery queue 에 중요한 데이터를 보내지 마라"
author: ianstream
description: "Celery queue 에 중요한 데이터를 보내지 마라"
date: 2017-11-01
tags: [queue,python,celery]
comments: true
---

이 글은 다음 [원문](https://www.caktusgroup.com/blog/2016/10/18/dont-keep-important-data-your-celery-queue/) 을 번역한 글 입니다.
<br />

Celery 라이브러리 ( 이전 게시물 )를 사용하면 나중에 함수를 호출 할 때 실행할 task 를 쉽게 스케줄 할 수 있다.
다음과 같은 task 를 :

```python
send_welcome_email('dan@example.com ')
```

이렇게 변경하라:

```python
send_welcome_email.apply_async('dan@example.com ')
```

그러면, Celery 를 통해 비동기로 실행된다.

하지만 이로 인해 애플리케이션이 실패할 수 있는 경우가 생긴다.
Celery 가 해당 작업을 추적하고 실행하지 않으면, 사용자가 보내려는 이메일을 받지 못하게 된다.

예를 들어 Celery 큐를 호스팅하는 서버가 손상된 경우 이런 일이 발생할 수 있다.
큐 서버에 hot 백업 서버를 설정할 수는 있지만, 이는 많은 작업을 필요로 한다.

Celery 큐를 캐시처럼 다루면 더 간단하다 -- 캐시는 데이터를 유지하는데 유용하다.
설령 캐시가 손실되더라도 작업은 마무리 된다.

Ed :이 게시물의 code snippets 은 포스트의 아이디어와 함께 사용하기위한 예제로만 사용되며, 이러한 아이디어를 프로덕션 환경에서 구현하는 방법의 예가 될 수는 없다.

이는 백그라운드에서 작업을 수행하기 위한 패턴을 변경함으로써 할 수 있다.
핵심 아이디어는 중요한 데이터와 함께 데이터베이스에서 수행해야 하는 작업에 대한 정보를 유지하는 것이다.

예를 들어 다음 작업을 보자 :

```python
send_welcome_email.apply_async('dan@example.com')
```

모델에 needs_welcome_email boolean 필드를 추가하고 다음과 같이 저장할 수 있다.

```python
user.needs_welcome_email = True
user.save()
```

이제 우리는 데이터베이스에서 이 사용자가 Celery 대기열과 관계없이 welcome email 을 받아야한다는 것을 알고 있다.

그런 다음 정기적인 작업을 설정하여 필요한 이메일을 보낸다.

```python
@task
def send_background_emails():
    for user in User.objects.filter(needs_welcome_email=True):
        send_welcome_email(user.email)
        user.needs_welcome_email = False
        user.save()
```

위와 같은 작업을 5 분 마다 실행할 수도 있다.
작업을 수행하기 위한 별도의 일이 없다면 실행하기가 아주 쉬울 것이며 발송되야 하는 "queued" 된 welcome email 을 모두 처리 할 것이다.

사용자가 이메일을 더 빨리 받길 원한다면, 즉시 다른 백그라운드 작업을 예약 할 수 있다.

```pyhton
user.needs_welcome_email = True
user.save()
send_background_emails.apply_async()
```

그리고 사용자는 이전의 방식과 같이 빠르게 이메일을 받을 수 있게 된다.

대기 중인 task 가 모두 종료된 경우 백그라운드 작업을 정기적으로 실행하기를 원할 수 있다
그러나 실행할 taks 가 거의 없는 경우에는 잦은 빈도로 실행할 필요가 없다.

제 동료 인 Karen 의 코드에 대한 [코드 리뷰](https://www.caktusgroup.com/blog/2014/07/28/culture-code-reviews/) 를 하면서 이것을 배웠다.
지속적으로 학습할 수 있다는 것은 팀단위 작업에서 내가 제일 좋아하는 부분이다.
<br />

#### task 종료하기

이제 이러한 변화를 만들었고, 이제 더 개선할 수 있는 기회가 주어졌다.

다음과 같이 주기적으로 작업을 예약한다고 가정해보자.

```python
CELERYBEAT_SCHEDULE = {
    'process_new_work': {
        'task': 'tasks.send_background_emails',
        'schedule': timedelta(minutes=15),
    },
}
```

매 15 분마다 Celery 는 백그라운드 작업을 다시 실행하도록 예약하고, 모든 상태가 정상이면 거의 즉시 실행된다.

그러나 Celery worker 가 잠시 동안 이용할 수 없다고 가정해보자.(일시적으로 연결이 끊어 질 수도 있다.) 
Celery 는 15 분마다 작업을 계속 queuing 시킨다. worker 가 하루 동안 다운 된 경우 살아날 경우 24 * 4 = 96 회의 예약 된 작업이 표시되며 96 번 작업을 실행할 것이다.

우리는 모든 작업을 자주 스케줄링 하지 않으며 작업은 매우 가볍다. 
그러나 수천 개의 작업이 대기하고 있는 경우를 겪어보았다. worker 가 작업을 재개 할 수 있게 되어서 모든 작업을 실행하려고 할 때 서버는 다운되었다.

실행하지 못한 작업을 위해서 한 번만 작업을 수행하면 된다. 우리는 수동으로 대기열을 비우고 다음 예약 된 작업이 처리하도록 할 수 있다. 
Celery 가 다음 작업이 예정되기 전에 실행되지 않으면 작업을 버릴 수도 있다는 것을 알수 있다면 더 간단하지 않겠는가?

Celery 에는 만료 옵션이 있어서 스케줄링할 때 사용 할 수 있다.

```python
CELERYBEAT_SCHEDULE = {
    'process_new_work': {
        'task': 'tasks.send_background_emails',
        'schedule': timedelta(minutes=15),
        'options': {
            'expires': 10*60, # 10 minutes
        }
    },
}
```

위 옵션은 Celery 가 스케줄을 정한 후 10 분 이내에 작업이 실행되지 않았다면 전혀 실행하지 않아도 되고 버려도 된다는 것을 알려준다. 
이렇게 하더라도 5 분 안에 또 다른 스케줄이 예약 될 것이므로 문제 없다.

만약 실행되는 workers 를 멈추면 어떻게 될까? 대기열에 작업을 계속 추가하지만 worker 를 다시 시작할 때 대부분의 작업이 만료(expired) 된다. 
worker 가 대기열의 작업이 만료 될 때마다 작업을 종료한다. 
이를 통해 작업을 낭비하지 않고 매우 신속하게 백로그를 따라 잡을 수 있다.
<br />

#### 결론

언제나 그렇듯이, 모든 경우에 적절할 기술은 없다. 
그러나 필요한 때에 쉽게 도움을 받을 수 있도록 당신의 툴박스에 넣어두는 것이 좋을 것이다.


