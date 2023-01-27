---
title: 【基础】Java抽象类与接口的区别与使用场合
date: 2020-04-18 19:06:00
tags: ['java','抽象类','接口','编程语言']
categories: 
 - 开发语言
 - Java
---

## 区别

- 最重要的区别是：接口的方法不可以有实现，并且是绝对的抽象方法。抽象类可以有实例方法用来实现默认行为
- 接口中的变量申明默认是`final`, 而抽象类中变量申明可以是非`final`
- 接口中的成员默认是`public`修饰，而抽象类中成员可以是`private`, `protected`等等
- 接口通过关键字`implements`被其他类实现，而抽象类则是通过`extends`关键字被其他类扩展
- 接口可以扩展（extends）另外一个/或多個接口，抽象类可以扩展（extends）另一个Java类并(或)实现（implements）多个Java接口
- Java类可以实现多个接口但是只能扩展一个抽象类
- 接口是绝对抽象而且无法实例化，抽象类也无法实例化但是如果类中有main()方法是可以被调用的
- 与抽象类相比，接口更慢，因为它需要额外的间接寻址

## 使用场合

接口用来定义契约行为，也可作为两个系统间的契约进行交互。而抽象类主要用来为子类定义默认行为，也就是说所有的继承子类都需要运行相同的功能。

{% tabs useage %}
<!-- tab 抽象类 -->
- 如果我们使用继承概念，那么抽象类是个不错的选择。因为它为派生类提供了一个通用基类实现。
- 当定义非`public`成员时，抽象类也是不错的选择，而接口内，所有的方法都必须是`public`的
- 在未来需要添加新方法时，选择抽象类更为合适。因为当我们在接口内添加新的方法时，所有实现该接口的类都需要添加新的方法
- 如果想创建多版本的组件，那么使用抽象类。抽象类提供一个简单且方便的方式来版本转换我们的组件。通过更新基类，所有继承子类都自动被更新为新的。另一方面，若使用接口则一旦创建则无法修改。如果我们需要新版本的接口只能创建一个全新的接口。
- 抽象类具有更佳的向后兼容性，我们可以添加新的行为而不影响原有代码，但是如果调用方使用的是接口，我们则无法修改它。
- 如果想为组件的所有实现中提供公共的且已实现的功能，那么使用抽象类，它允许我们部分实现类。而接口不为任何成员提供任何实现。

### 抽象类示例

```java
abstract class Car {
   public void accelerate() {
      System.out.println("Do something to accelerate");
   }
   public void applyBrakes() {
      System.out.println("Do something to apply brakes");
   }
   public abstract void changeGears();
}
```

现在任意的`Car`类想要实例化必须实现`changeGears()`方法.

```java
class Alto extends Car {
   public void changeGears() {
      System.out.println("Implement changeGears() method for Alto Car");
   }
}
class Santro extends Car {
   public void changeGears() {
      System.out.println("Implement changeGears() method for Santro Car");
   }
}
```
<!-- endtab -->
<!-- tab 接口 -->
- 如果我们实现的功能是对迥然不同的对象都很有用，那么使用接口。抽象类主要用作紧密相关的对象之间，然而在给非相关的类提供通用方法时，接口是更好的选择。
- 在我们认为API在短期内不会修改时，接口是更好的选择。
- 当我们有一些相似的多重继承时考虑使用接口，因为我们可以实现多重接口。
- 如果我们设计小巧而简单的功能时使用接口，如果我们设计庞大的功能单元，使用抽象类。

### 接口示例

```java
public interface Actor {
   void perform();
}
public interface Producer {
   void invest();
}
```

现在大多数演员都很有钱，可以制作自己的电影。如果我们使用接口而不是抽象类，那么我们可以同时实现Actor和Producer。另外，我们可以定义一个新的ActorProducer接口来扩展两者。

```java
public interface ActorProducer extends Actor, Producer{
   // some statements
}
```
<!-- endtab -->
{% endtabs %}

## 参考

- [When to use an abstract class and when to use an interface in Java?](https://www.tutorialspoint.com/when-to-use-an-abstract-class-and-when-to-use-an-interface-in-java)
- [Difference Between Interface and Abstract Class](https://javapapers.com/core-java/abstract-and-interface-core-java-2/difference-between-a-java-interface-and-a-java-abstract-class/)
