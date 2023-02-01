# startActivity

```kotlin
inline fun <reified T: Activity> startActivity(context: Context){
	context.startActivity(Intent(context,T::class.java))
}
//use
startActivity<UserDetailsActivity>(context
```

(java)

```java
startActivity(Intent(this, ProductActivity::class.java))
```

메소드를 올바르게 사용하려면 시작되는 액티비티(Bundle)로 매개변수를 전달하는 방법

```kotlin
startActivity<ProductActivity>("id"to 123,"extended" to true)
```

인수가 to 인라인 함수로 정의되는 pair의 키와 값으로 채워진다.

코틀린은 자바와 달리 원시 형식(형식 인수로 매개변수화하지 않은 제네릭 형식)의 선언을 허용하지 않는다

```kotlin
simpleList<> // 자바 가능
simpleList<> // 코틀린 불가능
```

코틀린은 누락되거나 중요하지 않은 형식 인수에 대한 정보를 알려줄 수 있는 별표 프로젝션을 지원

```kotlin
class Box<T>

val anyBox = Box<Any>()
val intBox = Box<Int>()
val stringBox = Box<String>()
var unkownBox : Box<*>

unknownBox = anyBox // Ok
unknownBox = intBox // Ok
unknownBox = stringBox // Ok
```

```kotlin
val anyBox: Box<Any> = Box<Int> // error 형식 불일치
```

한 제네릭이 여러 형식 매개변수를 정의할 때

```kotlin
class Container<T,T2>
val container: Container<*,*>
```