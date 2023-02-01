# LINQ 스타일

LINQ는 Language Integrate Query의 약자로써 **통합 질의 언어**
 라고 말할 수 있습니다.. 기존의 Query는 Database의 데이터를 다루기 위해 사용하는 언어쯤으로 여겨 졌습니다.

```kotlin
strings.filter { it.length ==5 }.map {it.toUpperCase() }
```

→ 마지막 람다식 인수 규칙을 이용하지 않은 표기법

```kotlin
strings.({s->s.length ==5}).map({s -> s.toUpperCase()})
```

매개변수를 받아 연결하는걸 it으로 한번에 하기 때문에 코드가 알아보기 쉽다.