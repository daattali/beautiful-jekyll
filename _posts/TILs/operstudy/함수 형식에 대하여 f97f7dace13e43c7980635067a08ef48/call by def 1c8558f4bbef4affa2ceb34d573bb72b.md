# call by def

인수로서 전달하려는 함수가 이미 별도의 함수로 정의된 경우

```kotlin
fun isOdd(i:Int) = i%2 ==1
list.filter{isOdd(it)}
```

함수를 값으로 전달

```kotlin
list.filter(::

isOdd)
```