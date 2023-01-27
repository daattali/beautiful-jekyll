---
title: 【lombok】@Data - @ToString,@EqualsAndHashCode,@Getter,@Setter,@RequiredArgsConstructor多个注解的组合快捷方法
date: 2019-02-13 10:20:46
updated: 2019-02-13 10:20:46
tags: ['lombok']
categories: 
 - 开发语言
 - Java
 - lombok
---

# 概述

`@Data`是将`@ToString`,`@EqualsAndHashCode`,`@Getter`/`@Setter`和`RequiredArgsConstructor`功能捆绑在一起的方便快捷方式。

也就是说，`@Data`生成通常与简单POJO(普通旧JAVA对象)和组件相关联的所有样板代码：所有字段的getter方法，所有非final字段的setter方法，涉及类字段的相应`toString`,`equals`和`hashCode`实现，还有所有final字段已初始化的构造器，以及被`@NonNull`标记且未初始化的所有非final字段，以确保该字段始终不会为null。

`@Data`就像是在类上隐含`@Getter`, `@Setter`, `@ToString`, `@EqualsAndHashCode` and `@RequiredArgsConstructor`注解一样（除非没有构造器生成，如果任何明确的构造器已存在）。然而这些注解的参数（比如`callSuper`,`includeFieldNames`和`exclude`）不能通过`@Data`设置。如果你想为这些参数设置非默认数值，只需要明确的添加注解，`@Data`足够智能来满足这些注解。

所有的getter和setter方法作用域都是`public`。可以通过在类或者字段上添加明确的`@Getter`和/或`@Setter`注解来覆盖访问级别。你还可以使用此注解（同`AccessLevel.NONE`组合使用）来完全禁止生成getter/setter。

所有标记为`transient`的字段将不被`hashCode`和`equals`处理。所有的静态字段将彻底跳过（任何生成的方法都不会包含，且不会为他们生成setter/getter方法）。

如果类里已经包含某一个方法和即将生成的方法的方法名和参数个数一致，则该将要生成的方法不会被生成，且没有任何警告和错误出现。打个比方，如果已有一个方法签名为`equals(AnyType param)`，即使从技术上来说，由于具有不同的参数类型，它可能是完全不同的方法，依然不会再生成`equals`方法。同样的规则也适用于构造器（任何明确的构造器都会阻止`@Data`生成一个新的），`toString`，`equals`，和所有的getter/setter方法。你可以在构造器或者方法上标记`@lombok.experimental.Tolerate`注解来从lombok隐藏它们。

`@Data`正好也可以处理泛型参数。为了减少构造泛型类对象的样板代码，你可以使用`staticConstructor`参数来生成私有的构造器，同返回一个新实例的静态方法一样。这个方法，javac会推断变量类型，因此通过这样申明：

```java
@Data(staticConstructor="of") 
class Foo<T> { 
  private T x;
}
```

你可以通过如此写法来创建新的实例：

```java
Foo.of(5);
```

而不是：

```java
new Foo<Integer>(5);
```

## 使用lombok

```java
import lombok.AccessLevel;
import lombok.Setter;
import lombok.Data;
import lombok.ToString;

@Data public class DataExample {
  private final String name;
  @Setter(AccessLevel.PACKAGE) private int age;
  private double score;
  private String[] tags;
  
  @ToString(includeFieldNames=true)
  @Data(staticConstructor="of")
  public static class Exercise<T> {
    private final String name;
    private final T value;
  }
}
```

## 不使用lombok
```java
import java.util.Arrays;

public class DataExample {
  private final String name;
  private int age;
  private double score;
  private String[] tags;
  
  public DataExample(String name) {
    this.name = name;
  }
  
  public String getName() {
    return this.name;
  }
  
  void setAge(int age) {
    this.age = age;
  }
  
  public int getAge() {
    return this.age;
  }
  
  public void setScore(double score) {
    this.score = score;
  }
  
  public double getScore() {
    return this.score;
  }
  
  public String[] getTags() {
    return this.tags;
  }
  
  public void setTags(String[] tags) {
    this.tags = tags;
  }
  
  @Override public String toString() {
    return "DataExample(" + this.getName() + ", " + this.getAge() + ", " + this.getScore() + ", " + Arrays.deepToString(this.getTags()) + ")";
  }
  
  protected boolean canEqual(Object other) {
    return other instanceof DataExample;
  }
  
  @Override public boolean equals(Object o) {
    if (o == this) return true;
    if (!(o instanceof DataExample)) return false;
    DataExample other = (DataExample) o;
    if (!other.canEqual((Object)this)) return false;
    if (this.getName() == null ? other.getName() != null : !this.getName().equals(other.getName())) return false;
    if (this.getAge() != other.getAge()) return false;
    if (Double.compare(this.getScore(), other.getScore()) != 0) return false;
    if (!Arrays.deepEquals(this.getTags(), other.getTags())) return false;
    return true;
  }
  
  @Override public int hashCode() {
    final int PRIME = 59;
    int result = 1;
    final long temp1 = Double.doubleToLongBits(this.getScore());
    result = (result*PRIME) + (this.getName() == null ? 43 : this.getName().hashCode());
    result = (result*PRIME) + this.getAge();
    result = (result*PRIME) + (int)(temp1 ^ (temp1 >>> 32));
    result = (result*PRIME) + Arrays.deepHashCode(this.getTags());
    return result;
  }
  
  public static class Exercise<T> {
    private final String name;
    private final T value;
    
    private Exercise(String name, T value) {
      this.name = name;
      this.value = value;
    }
    
    public static <T> Exercise<T> of(String name, T value) {
      return new Exercise<T>(name, value);
    }
    
    public String getName() {
      return this.name;
    }
    
    public T getValue() {
      return this.value;
    }
    
    @Override public String toString() {
      return "Exercise(name=" + this.getName() + ", value=" + this.getValue() + ")";
    }
    
    protected boolean canEqual(Object other) {
      return other instanceof Exercise;
    }
    
    @Override public boolean equals(Object o) {
      if (o == this) return true;
      if (!(o instanceof Exercise)) return false;
      Exercise<?> other = (Exercise<?>) o;
      if (!other.canEqual((Object)this)) return false;
      if (this.getName() == null ? other.getValue() != null : !this.getName().equals(other.getName())) return false;
      if (this.getValue() == null ? other.getValue() != null : !this.getValue().equals(other.getValue())) return false;
      return true;
    }
    
    @Override public int hashCode() {
      final int PRIME = 59;
      int result = 1;
      result = (result*PRIME) + (this.getName() == null ? 43 : this.getName().hashCode());
      result = (result*PRIME) + (this.getValue() == null ? 43 : this.getValue().hashCode());
      return result;
    }
  }
}
```