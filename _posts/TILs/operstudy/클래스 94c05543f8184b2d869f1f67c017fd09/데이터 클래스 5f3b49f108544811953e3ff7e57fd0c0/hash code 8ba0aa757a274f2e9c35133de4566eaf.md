# hash code

```kotlin
public class Product{
	private String name;
	private Double price;

	public Product(String name, Double price){
		this.name=name;
		this.price=price;
}

@Override
public int hashCode(){
	int result = name != null? name.hashCode() : 0;
	result =31* result+(price.hashCode():0);
	return result;
}

@Override
public boolean equals(Object o){
	if (this ==o){
		return true;
	}
	if(o==null ||getClass() != o.getClass(){
		return false;
	}

	Product product = (Product) o;

	if(name!=null? !name.equals(product.name):
		product.name!=null){
		return false;
	}
	return price != null? prict.equals(product.name):
		product.price == null;
}
public String getName(){
		return name;
}

public void setName(String name){
	this.name =name;
}
public Double getPrice(){
	return price;
}
public void setPrice(Double price){
	tihs.price=price;
}
}
	
```

자바를 비롯한 OOP 프로그래밍 언어에서 널리 사용되는 방식으로, 코틀린에서 데이터 클래스를 사용하면 이러한 메소드가 컴파일러에 의해 자동으로 생성된다.

```kotlin
DATA CALSS Product(var name: String, var price:Double)
```

```kotlin
data class Product(var name:String,var price:Double)
	
val productA=Product("Spoon",30.2)
val productB=Product("Spoon",30.2)
val productC=Product("Fork",17.2)
```

1. A==A  → true
2. A==B → true
3. B==A → true
4. A==C → false
5. B==C → false