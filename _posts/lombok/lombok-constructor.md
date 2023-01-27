---
title: 【lombok】@NoArgsConstructor/@RequirArgsConstructor/@AllArgsConstructor - 生成指定参数的构造器
date: 2019-02-12 08:00:46
updated: 2019-02-12 08:00:46
tags: ['lombok']
categories: 
 - 开发语言
 - Java
 - lombok
---

这三个注解的集合接受某些字段的一个参数，简单的用于分配这个参数给这个字段。

`@NoArgsConstructor`生成的构造器无参数。如果这是不可能的（因为有final字段），则会导致编译错误。除非使用`@NoArgsConstructor(force=true)`，然后将所有的final字段都初始化为`0`/`false`/`null`。

对于有约束的字段，比如`@NonNull`，不会生成任何检查，所以请注意直到这些字段都适当的被初始化后，才会满足这些约束条件。某些java构造器，比如hibernate和服务提供接口需要无参构造器。这个注解主要同`@Data`或者其他生成构造器的注解一起使用。

`@RequirArgsConstructor`为每个需要特殊处理的字段生成一个字段与参数对应的构造器。所有未初始化的final字段都获得一个参数，以及标识为`@NonNull`的任何字段，这些字段在申明它们时未初始化。对于这些标记为`@NonNull`的字段，明确的Null检查也会跟着生成。

如果任意标记`@NonNull`字段的参数包含`null`，则构造器会抛出空指针异常。这些参数的排序同这些字段在类里出现的顺序一致。

`@AllArgsConstructor`在你的类中生成一个将所有字段作为参数的构造器。标记为`@NonNull`的字段将生成对应的null检查。

所有的这些注解都支持替换格式，生成的构造器都是私用的，然后会生成一个额外的封装私有构造器的静态工厂方法。这个模式通过在注解内使用`staticName`开启，比如`@RequiredArgsConstructor(staticName="of")`。和普通构造器不一样，该静态工厂方法可以推断泛型。也就是说你的API调用方可以使用`MapEntry.of("foo", 5)`而不是`new MapEntry<String, Integer>("foo", 5)`。

想要将注解放置在生成的构造器上，可以通过使用`onConstructor=@__({@AnnotationsHere})`，但是请小心，这只是一个实验阶段功能。
更多的信息请参考文档的`onX`功能。 

上述的这些注解会跳过静态字段。

同其他lombok注解不一样的是，指定构造器的出现不会阻碍这些注解生成它们自己的构造器。这也意味着你可以编写你自己专门的构造器，并让lombok生成样板文件。如果出现冲突（专门的构造器和lombok生成的签名一致），会引发编译错误。

使用Lombok

```java
import lombok.AccessLevel;
import lombok.RequiredArgsConstructor;
import lombok.AllArgsConstructor;
import lombok.NonNull;

@RequiredArgsConstructor(staticName = "of")
@AllArgsConstructor(access = AccessLevel.PROTECTED)
public class ConstructorExample<T> {
  private int x, y;
  @NonNull private T description;
  
  @NoArgsConstructor
  public static class NoArgsExample {
    @NonNull private String field;
  }
}

```

不使用Lombok

```java
public class ConstructorExample<T> {
  private int x, y;
  @NonNull private T description;
  
  private ConstructorExample(T description) {
    if (description == null) throw new NullPointerException("description");
    this.description = description;
  }
  
  public static <T> ConstructorExample<T> of(T description) {
    return new ConstructorExample<T>(description);
  }
  
  @java.beans.ConstructorProperties({"x", "y", "description"})
  protected ConstructorExample(int x, int y, T description) {
    if (description == null) throw new NullPointerException("description");
    this.x = x;
    this.y = y;
    this.description = description;
  }
  
  public static class NoArgsExample {
    @NonNull private String field;
    
    public NoArgsExample() {
    }
  }
}
```