# Copy

기본적으로 코틀린 컴파일러는 객체를 손쉽게 복사하기 위한 copy 메소드도 자동으로 생성한다.

```kotlin
data class Product(var name:String, var price :Double)
val productA = Product("Spoon,30.2)
print(productA) // -> Product(name=Spoon, price=30.2)
val productB = ProductA.copy()
print(productB)// -> Product(name=Spoon, price=30.2)
```

정적 팩토리

```kotlin
val productB=ProductFactory.newInstance(productA)
```

Copy 생성자

```kotlin
val productB= Product(productA)
```

copy 메소드는 주 생성자에 선언된 모든 속성에 해당하는 인수를 받고, 기본 인수 구문을 함께 이용하면 모든 속성, 그중 일부를 지정해 수정도니 인스턴스 복사본을 생성

```kotlin
data class Product(var name:String, var price :Double)

val productA = Product("Spoon,30.2)
print(productA) // -> Product(name=Spoon, price=30.2)
val productB = ProductA.copy(price=24.0)
print(productB)// -> Product(name=Spoon, price=24.0)
val productC = Product(price,30.2)
print(productA) // -> Product(name=Spoon, price=30.2)
```

멀티스레드 애플리케이션에서 데이터 동기화의 필요성 이와 연관된 잠재적 오류를 줄이는방법

```kotlin
// 가변객체 - 객체 상태 수정
data class Product(var name:String, var price:Double)

var productA = Product("Spoon",30.2)
productA.name ="Knife"

//불변객체 - 새로운 객체 인스턴스 생성
data class Product(val name:String, val price:Double)

var productA=Product("Spoon", 30.2)
productA = productA.copy(name="Knife)
```

→가변 속성을 정의하고 객체 상태를 수정하는 대신, 불변 속성을 정의하고, 객체를 불변으로 만든 다음, 변경된 값을 갖는 복사본을 얻고 이를 대상으로 필요한 작업을 한다.

불변객체는 스레드간에 자유롭게 공유할 수 있어 멀티스레드→ 데이터 동기화 부분에 기여를한다.