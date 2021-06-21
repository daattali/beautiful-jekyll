---
layout: post
title: 0. 모각코 전 블로그 생성
subtitle: 모각코 대표 블로그 생성
gh-repo: fullop2/fullop2.github.io
#gh-badge: [star, fork, follow]
tags: [dev]
comments: true
---

마크다운을 활용한 **github page**를 통해서 대표 블로그를 생성하였습니다


## 헤더 예시

테이블 작성 예시:

| Number | Next number | Previous number |
| :------ |:--- | :--- |
| Five | Six | Four |
| Ten | Eleven | Nine |
| Seven | Eight | Six |
| Two | Three | One |


그림 및 스타일 예시

![Crepe](https://s3-media3.fl.yelpcdn.com/bphoto/cQ1Yoa75m2yUFFbY2xwuqw/348s.jpg)

![Crepe](https://s3-media3.fl.yelpcdn.com/bphoto/cQ1Yoa75m2yUFFbY2xwuqw/348s.jpg){: .mx-auto.d-block :}

코드 청크 예시:

~~~
var foo = function(x) {
  return(x + 5);
}
foo(3)
~~~

구문 강조 예시:

```javascript
var foo = function(x) {
  return(x + 5);
}
foo(3)
```

라인을 포함한 예시:

{% highlight javascript linenos %}
var foo = function(x) {
  return(x + 5);
}
foo(3)
{% endhighlight %}

## 박스 예시
quote처럼 활용할 수 있음:

### Notification

{: .box-note}
**Note:** This is a notification box.

### Warning

{: .box-warning}
**Warning:** This is a warning box.

### Error

{: .box-error}
**Error:** This is an error box.
