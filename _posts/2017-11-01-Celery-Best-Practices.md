---
layout: post
title: "Celery Best Practices"
author: ianstream
description: "Celery Best Practices"
date: 2017-11-01
tags: [queue,python,celery]
comments: true
---

이 글은 다음 [원문](https://denibertovic.com/posts/celery-best-practices/) 을 번역한 글 입니다.
<br />

참고 : 원문이 2014년 글 이기 때문에 celery 사용법은 상이할 수 있습니다. 컨셉만 이해하고 버전에 맞게 적용하세요.
<br />

[Django](https://www.djangoproject.com/) 를 사용하고 있다면, 긴 시간이 걸리는 작업을 백그라운드로 처리할 필요성을 느꼈을 것이다.
[Celery](http://www.celeryproject.org/) 는 파이썬 생태계에서 비동기 처리에 관해 가장 유명한 프로젝트이다.

Celery 를 task queue 로 사용하는 프로젝트들을 수행하는 동안 모범사례들을 수집해 문서화 하기로 했다.
그럼에도 불구하고, 나는 작업을 수행하는데 더 적절한 방법이라고 생각하는 것들과 Celery 생태계가 제공하는 몇몇 불충분한 기능들에 대해 말하려고 한다.
<br />


#### No 1. database 를 AMQP broker 로 사용하지 마라.

이게 왜 틀린 것인지 설명해보겠다.

데이터베이스는 RabbitMQ와 같은 AMQP 브로커와 같이 동작하도록 만들어지 지지 않았다.
그리 크지 않은 트래픽/사용자 기반의 프러덕션 환경에서도 망가질 것이다.

데이터베이스를 사용하기로 결정하는 가장 보편적인 이유는 웹 애플리케이션을 위해 이미 데이터베이스가 설치되어 있기 때문일 것이다.
그러니 사용하지 않을 이유가 있을까? 세팅도 쉽고 RabbitMQ 와 같은 다른 컴포넌트에 대해 걱정할 필요도 없다.

다음은 가상의 시나리오가 아니다: 데이터베이스에 태스크를 넣는 4개의 백그라운드 worker 가 있다고 하자.
즉, 4개의 worker 가 새로운 작업을 위해 꽤 자주 데이터베이스를 폴링하는 프로세스 4개가 동작하게 된다.
4개의 worker 각각이 multiple concurrent threads 를 가진다는 것을 의미하지는 않는다.
어떤 시점이 오면, 완료되는 것보다 더 많은 task가 입력되고 있음을 알아차리게 될 것이다.
자연스럽게 당신은 task 처리를 위한 worker 수를 늘릴 것이다.
갑자기 많은 수의 worker 가 새로운 tasks 를 위해 데이터베이스를 폴링기 시작하고 데이터베이스의 성능이 떨어지기 시작한다.
디스크 입출력은 최고치를 기록하게 되며 worker 가 데이터베이스를 DDoS 공격하는 것과 같이 되기 때문에 웹 응용 프로그램에 영향을 주기 시작한다.

[RabbitMQ](http://www.rabbitmq.com/) 와 같은 적절한 AMQP를 사용한다면 이런 현상은 발생하지 않는다.
디스크에 부하가 가지 않도록 queue 가 메모리에 상주하기 때문이다.
consumer(worker) 는 queue 가 새로운 task 를 consumer 에게 강요하는 방법으로 polling 할 필요가 없다.
만약 AMQP 이 다른 이유로 망가지더라도 웹 애플리케이션에 영향을 주진 않는다.

나는 개발환경에서라도 데이터베이스를 broker 로 사용해서는 안된다고 말하고 싶다.

첨언 : AMQP 표준에 대해서는 다음 [링크](https://en.wikipedia.org/wiki/Advanced_Message_Queuing_Protocol)를 참고하자.
<br />


#### No 2. 큐는 기본값인 한개보다 많이 사용하라.

설정은 설정하기가 매우 간단하며, 특정 큐에 작업을 수행하지 않는 한 모든 작업을 수행하는 기본 큐가 제공된다.
가장 일반적인 모습은 다음과 같다.

```python
@app.task()
def my_taskA(a, b, c):
    print("doing something here...")

@app.task()
def my_taskB(x, y):
    print("doing something here...")
```

여기서 발생하는 작업은 두 작업은 모두 동일한 queue 에서 끝난다(celeryconfig.py 파일에 명시되지 않은 경우).
단 하나의 decorator 만이 여러분 자신만의 백그라운드 task 를 수행하기 때문에 이렇게 처리하는것에 대한 매력을 느낄 수 있다.
나의 관심사는 taskA와 taskB가 다른 것들을 하고 있을지도 모른다는 것다.
아마도 둘 중 하나는 다른 것보다 훨씬 더 중요할 수도 있다.
그렇다면 왜 같은 공간에서 동작하도록 하는가? 비록 worker 가 두가지 작업을 모두 처리하고 있다고 해도, 중요하지 않은 taskB가 너무 많기 때문에 더 중요한 taskA가 worker 에게 중요치 않게 처리되도 괜찮다고 생각하는가?
이 시점에서 worker 의 숫자를 늘리는 것만으로는 문제를 해결하지 못한다.
모든 worker 들이 여전히 두 tasks 를 다 처리할 필요가 있을 것이고 taskB 의 작업수가 크기 때문에 taskA 는 덜 중요한것처럼 여겨질 것이기 때문이다.
이제 다음을 살펴보자.
<br />


#### No 3. 우선순위 worker 를 사용하자.
위의 문제를 해결하기 위한 방법은 하나의 큐(Q1) 에 taskA 를 할당하는 것이다.
그리고 taskB 는 다른 큐(Q2) 에 할당한다.
더 많은 작업이 이루어질 수 있도록 x 개의 worker 는 'Q1'에 할당하고 다른 모든 worker 는 좀더 중요한 Q2 를 처리하도록 하자.
이렇게 하면, 처리하는 동안 오래 대기할 필요 없이 taskB 에는 충분한 worker 가 할당되게 하고 taskA 에는 우선순위를 가지는 worker 를 할당해 작업을 처리할 수 있다.
이제 queue 를 정의해보자:

```python
CELERY_QUEUES = (
    Queue('default', Exchange('default'), routing_key='default'),
    Queue('for_task_A', Exchange('for_task_A'), routing_key='for_task_A'),
    Queue('for_task_B', Exchange('for_task_B'), routing_key='for_task_B'),
)
```

이제 route 설정이 task 가 어디로 가야할지 지정할 것이다

```python
CELERY_ROUTES = {
    'my_taskA': {'queue': 'for_task_A', 'routing_key': 'for_task_A'},
    'my_taskB': {'queue': 'for_task_B', 'routing_key': 'for_task_B'},
}
```

다음 명령을 통해 각각의 task 를 worker 가 실행하도록 할 수 있다.

```bash
celery worker -E -l INFO -n workerA -Q for_task_A
celery worker -E -l INFO -n workerB -Q for_task_B
```
<br />


#### No 4. Celery 의 에러 제어 방식을 사용하라.

task 를 사용하는 실례에서 예외를 처리하는 것을 보지 못했다.
그러나, 몇몇 경우에는 에러가 발생해도 문제가 되지 않는다.
내가 봤던 대부분의 task 는 서드파티 API 를 호출하는 경우였고, 네트웍 장애나 "resource availability" 에러와 같은 문제로 실패하는 경우였다.
이러한 종류의 오류를 해결할 수 있는 가장 간단한 방법은 단순히 작업을 재시도하는 것이다.
서드파티 API는 간혹 서버/네트워킹 문제가 발생할 수 있고, 단기간에 복구될 것이이다.
그러니, 왜 재시도하지 않을 이유가 없다.

```python
@app.task(bind=True, default_retry_delay=300, max_retries=5)
def my_task_A():
    try:
        print("doing stuff here...")
    except SomeNetworkException as e:
        print("maybe do some clenup here....")
        self.retry(e)
```

작업을 재시도하기 전에 task 에 얼마나 오래 있다가 재시도 하는지, 얼마나 많이 재시도 하는지 등을 정의한다(default_retry_delay 및 max_retries 매개 변수).
이것은 내가 생각할 수 있는 오류 처리의 가장 기본적인 형태이지만, 거의 사용하는 경우를 거의 보지 못했다.
물론 celery 는 오류 처리에 대해 더 많은 것을 제공한다. 더 자세한 것은 doc 를 참고하자.
<br />


#### No 5. Flower 를 사용하자.

Flower 프로젝트는 Celery task, worker 를 모니터링하는 좋은 도구이다.
웹 기반이며 task process 및 상세내용, worker 상태, 새로운 worker 등록 및 기타 관련된 기능을 제공해준다.
다음 링크에서 상세한 내용을 확인해보자.
<br />


#### No 6. 정말 필요한 경우만 결과를 저장하자

task 는 작업의 성공여부에 대한 정보를 가진다.
나중에 결과정보를 집계하고자 하는경우 유용하게 쓰일 수 있다.
주목해야할 것은 작업의 종료정보가 task 가 수행한 작업에 대한 결과가 아니라는 것이다.
내가 봐왔던 대부분의 프로젝트에서는 task 의 종료 후 상태를 지속적으로 추적하고 있지는 않았다.
하지만 대부분의 경우에는 sqlite, postgres, 혹은 다른 database 를 사용하여 이 정보들을 저장하고 있었다.
왜 이런식으로 웹 애플리케이션의 데이터베이스에 부하를 주고 있나? celeryconfig.py 파일에 CELERY_IGNORE_RESULT = True 옵션을 사용해서 결과를 기록하지 말기 바란다.

첨언 : Celery 4.1 기준은 [링크](http://docs.celeryproject.org/en/latest/userguide/tasks.html#ignore-results-you-don-t-want)를 참고하자.
<br />


#### No 7. database/ORM 객체를 task 에 보내지 마라.

강연 이후에 사람들은 이 내용을 추가할 것을 제한했다.
어떻게 된 일일까? 직렬화된 데이터는 과거의 정보를 가지고 있을수 있기 때문에 백그라운드 task 에 전달해서는 안된다.
원하는 정보의 키가 될수 있는 값을 task 에 전달해야 하며 key 정보로 부터 최신의 정보를 얻어야만 한다.
