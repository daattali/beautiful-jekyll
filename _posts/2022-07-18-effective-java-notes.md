---
layout: post
title: "Effective Java Notes"
date: 2022-07-18 09:57:00 +0800
categories: Java
---
# Effective Java Notes

[TOC]

## Creating and Destroying Objects

### Item 1: Static factory methods instead of constructors

Pros: 

1. have names
2. not required to create a new object each time they’re invoked
    1. flyweight pattern
    2. singleton pattern
    ![48fd0356f3db1ec3699581b3010e663e.jpeg](evernotecid://576B7A0F-9DD7-4927-B83B-40B311D24856/appyinxiangcom/1074526/ENResource/p3044)
    
```java
import java.util.HashMap;
 
public class ShapeFactory {
   private static final HashMap<String, Shape> circleMap = new HashMap<>();
 
   public static Shape getCircle(String color) {
      Circle circle = (Circle)circleMap.get(color);
 
      if(circle == null) { // lazy creation
         circle = new Circle(color);
         circleMap.put(color, circle);
         System.out.println("Creating circle of color : " + color);
      }
      return circle;
   }
}
```

3. they can return an object of any subtype of their return type
4. returned object can vary from call to call as a function of the input parameters
5. returned object need not exist when the class containing the method is written
    * bridge pattern

```csharp
namespace BridgePattern
{
    abstract class HandsetSoft
    {
        public abstract void Run();
    }
}

using System;

namespace BridgePattern
{
    class HandsetGame : HandsetSoft
    {
        public override void Run()
        {
            Console.WriteLine("运行手机游戏");
        }
    }
}

namespace BridgePattern
{
    //手机品牌
    abstract class HandsetBrand
    {
        protected HandsetSoft soft;
        //设置手机软件
        public void SetHandsetSoft(HandsetSoft soft)
        {
            this.soft = soft;
        }
        //运行
        public abstract void Run();
    }
}

namespace BridgePattern
{
    //手机品牌N
    class HandsetBrandN : HandsetBrand
    {
        public override void Run()
        {
            soft.Run();
        }
    }
}
```

Cons:

1. classes without public or protected constructors cannot be subclassed
2. factory methods is that they are hard for programmers to find

### Item 2: Consider a builder when faced with many constructor parameters

**Builder pattern**:

1. no setter methods
2. private constructors
3. private final fields
4. builder's setter methods may be *chained*

The Builder pattern is well suited to class hierarchies.

```java
// Builder pattern for class hierarchies
public abstract class Pizza {
    public enum Topping { HAM, MUSHROOM, ONION, PEPPER, SAUSAGE }
    final Set<Topping> toppings;
    abstract static class Builder<T extends Builder<T>> {
        EnumSet<Topping> toppings = EnumSet.noneOf(Topping.class);
        public T addTopping(Topping topping) {
            toppings.add(Objects.requireNonNull(topping));
            return self();
        }
        // build method
        abstract Pizza build();
        // Subclasses must override this method to return "this"
        protected abstract T self();
    }
    Pizza(Builder<?> builder) {
        toppings = builder.toppings.clone(); // See Item 50
    }
}
```

```java
public class NyPizza extends Pizza {
    public enum Size { SMALL, MEDIUM, LARGE }
    private final Size size;
    // concrete builder class
    public static class Builder extends Pizza.Builder<Builder> {
        private final Size size;
        public Builder(Size size) {
            this.size = Objects.requireNonNull(size);
        }
        @Override public NyPizza build() {
            return new NyPizza(this);
        }
        @Override protected Builder self() { return this; }
    }
    private NyPizza(Builder builder) {
        super(builder);
        size = builder.size;
    }
}
```

```java
NyPizza pizza = new NyPizza.Builder(SMALL).addTopping(SAUSAGE).addTopping(ONION).build();
```

### Item 3: singleton property with private constructor or enum type

### Item 4: enforce noninstantiability with a private constructor

### Item 5: prefer dependency injection to hardwiring resources

**Dependency injection pattern**: Pass the resource into the constructor when creating a new instance

```java
// Dependency injection provides flexibility and testability
public class SpellChecker {
    private final Lexicon dictionary;
    public SpellChecker(Lexicon dictionary) {
        this.dictionary = Objects.requireNonNull(dictionary);
    }
    public boolean isValid(String word) { ... }
    public List<String> suggestions(String typo) { ... }
}
```

Java 8: supplier<T> interface

```java
Mosaic create(Supplier<? extends Tile> tileFactory) { ... }
```

### Item 6: avoid creating unnecessary objects

### Item 7: eliminate obsolete object references

```java
public Object pop() {
    if (size == 0)
        throw new EmptyStackException();
    Object result = elements[--size];
    elements[size] = null; // Eliminate obsolete reference
    return result;
}
```

Sources of memory leak:

1. obsolete references
2. caches 
3. listeners and other callbacks


### Item 8: avoid finalizers

### Item 9: prefer try-with-resources to try-finally

```java
// try-with-resources on multiple resources - short and sweet
static void copy(String src, String dst) throws IOException {
    try (InputStream in = new FileInputStream(src);
    OutputStream out = new FileOutputStream(dst)) {
        byte[] buf = new byte[BUFFER_SIZE];
        int n;
        while ((n = in.read(buf)) >= 0)
            out.write(buf, 0, n);
    }
}
```

Resources must implement `AutoClosable` interface

If exceptions are thrown by both the readLine call and the (invisible) close, the latter exception is *suppressed* in favor of the former.

## Methods common to all objects

### Item 10: Obey the general contract when overriding `equals`

The easiest way to avoid problems is not to override the `equals` method

* Each instance of the class is inherently unique
* There is no need for the class to provide a “logical equality” test
* A superclass has already overridden equals, and the superclass behavior
is appropriate for this class
* The class is private or package-private, and you are certain that its equals
method will never be invoked

```java
@Override public boolean equals(Object o) {
    throw new AssertionError(); // Method is never called
}
```

Properties
* Reflexive: for any non-null value x, `x.equal(x)` must be true;
* Symmetric: `x.equals(y) <=> y.equals(x)`
* Transitive: be aware of class inheritance
* Consistent
* Non-nullity

**Liskov substitution principle**: any important property of a type should also hold for all its subtypes so that any method written for the type should work equally well on its subtypes

There is no way to extend an instantiable class and add a value component while **preserving the equals contract**

1. Use the `==` operator to check if the argument is a reference to this object (performance optimization).
2. Use the `instanceof` operator to check if the argument has the correct type.
3. Cast the argument to the correct type.
4. For each “significant” field in the class, check if that field of the argument
matches the corresponding field of this object.

```java
// Class with a typical equals method
public final class PhoneNumber {
    private final short areaCode, prefix, lineNum;
    public PhoneNumber(int areaCode, int prefix, int lineNum) {
        this.areaCode = rangeCheck(areaCode, 999, "area code");
        this.prefix = rangeCheck(prefix, 999, "prefix");
        this.lineNum = rangeCheck(lineNum, 9999, "line num");
    }
    private static short rangeCheck(int val, int max, String arg) {
        if (val < 0 || val > max)
            throw new IllegalArgumentException(arg + ": " + val);
        return (short) val;
    }
    @Override public boolean equals(Object o) {
        if (o == this) // check if it is the object itself
            return true;
        if (!(o instanceof PhoneNumber)) // check the type
            return false;
        PhoneNumber pn = (PhoneNumber)o; // cast 
        return pn.lineNum == lineNum && pn.prefix == prefix && pn.areaCode == areaCode; // check each field
}
... // Remainder omitted
}
```

* Always override `hashCode` when you override `equals`
* Don’t substitute another type for `Object` in the equals declaration

### Item 11: Always override `hashCode` when you override `equals`

You *must* override hashCode in every class that overrides equals.

* When the hashCode method is invoked on an object repeatedly during an execution of an application, it must consistently return the same value.
* If two objects are equal according to the equals(Object) method, then calling `hashCode` on the two objects *must* produce the same integer result.
* If two objects are unequal according to the equals(Object) method, it is *not* required that calling hashCode on each of the objects must produce distinct results.

Notes for writing a proper `hashCode` method: 
1. Declare an int variable named result
2. For every remaining significant field `f` in your object, do the following
    1. Compute an int hash code `c` for the field
        1. If the field is of a *primitive type*, compute Type.hashCode(f), where Type is the boxed primitive class corresponding to f’s type.
        2. If the field is an object reference and this class’s equals method compares the field by recursively invoking `equals`, recursively invoke `hashCode` on the field.
        3. If the field is an array, treat it as if each significant element were a
separate field. If all elements are significant, use `Arrays.hashCode`.
    2. Combine the hash code c computed in step 2.1. `result = 31 * result + c;`
3. Return `result`.

```java
// Typical hashCode method
@Override public int hashCode() {
    int result = Short.hashCode(areaCode);
    result = 31 * result + Short.hashCode(prefix);
    result = 31 * result + Short.hashCode(lineNum);
    return result;
}
```

```java
// One-line hashCode method - mediocre performance
@Override public int hashCode() {
    return Objects.hash(lineNum, prefix, areaCode);
}
```

Only if the object is *immutable*

```java
// hashCode method with lazily initialized cached hash code
private int hashCode; // Automatically initialized to 0
@Override public int hashCode() {
    int result = hashCode;
    if (result == 0) {
        result = Short.hashCode(areaCode);
        result = 31 * result + Short.hashCode(prefix);
        result = 31 * result + Short.hashCode(lineNum);
        hashCode = result;
    }
    return result;
}
```

### Item 12: Always override `toString`

When practical, the toString method should return all of the interesting information contained in the object.

### Item 13: Override `clone` judiciously

In practice, a class implementing `Cloneable` is expected to provide a properly functioning public clone method.

### Item 14: Considering implementing `Comparable`


## Classes and interfaces

### Item15: Minimize the accessibility

make each class or member as *inaccessible* as possible

* Top-level classes and interfaces: package-private or public
If a package-private top-level class or interface is used *by only one class*,
consider making the top-level class a *private static nested class* of the sole class
that uses it.

* Members (fields, methods, *nested classes*, and *nested interfaces*): private, package-private, protected, public

If a method overrides a superclass method, it *cannot have a more restrictive access level* in the subclass than in the superclass. (Liskov substitution principle)

Nonzero-length array is *always mutable*.

```java
// Potential security hole!
public static final Thing[] VALUES = { ... }; // always mutable

// Approach 1
private static final Thing[] PRIVATE_VALUES = { ... };
public static final List<Thing> VALUES =
Collections.unmodifiableList(Arrays.asList(PRIVATE_VALUES));

// Approach 2
private static final Thing[] PRIVATE_VALUES = { ... };
public static final Thing[] values() {
    return PRIVATE_VALUES.clone();
}
```

### Item 16: In public classes, use method accessors, not public fields

### Item 17: Minimize mutability
1. Don’t provide methods that modify the object’s state (known as mutators).
2. Ensure that the class can’t be extended. *final class*
3. Make all fields final.
4. Make all fields private.
5. Ensure exclusive access to any mutable components. *defensive copy*

* Classes should be **immutable** unless there’s a very good reason to make them mutable
* Declare every field **private final** unless there’s a good reason to do otherwise.
* Constructors should create **fully initialized objects** with all of their invariants established.

### Item 18: Favor composition over inheritance

Unlike method invocation, **inheritance violates encapsulation**

Instead of extending an existing class, give your new class a private field that references an
instance of the existing class (*composition*)
* forwarding and forwarding methods

**Decorator pattern**

### Item 19: Design and document for inheritance or prohibit it

### Item 20: Prefer interfaces to abstract classes

### Item 21: Design interfaces for posterity

### Item 22: Use interfaces only to define types 

```java
// Constant interface antipattern - do not use!
public interface PhysicalConstants {
    // Avogadro's number (1/mol)
    static final double AVOGADROS_NUMBER = 6.022_140_857e23;
    // Boltzmann constant (J/K)
    static final double BOLTZMANN_CONSTANT = 1.380_648_52e-23;
    // Mass of the electron (kg)
    static final double ELECTRON_MASS = 9.109_383_56e-31;
}
```

The constant interface pattern is a **poor use of interfaces**.
Use `enum` type or *noninstantiable utility class*.

```java
// Constant utility class
package com.effectivejava.science;

public class PhysicalConstants {
    private PhysicalConstants() { } // Prevents instantiation
    public static final double AVOGADROS_NUMBER = 6.022_140_857e23;
    public static final double BOLTZMANN_CONST = 1.380_648_52e-23;
    public static final double ELECTRON_MASS = 9.109_383_56e-31;
}
```

### Item 23: Prefer class hierarchies to tagged classes

```java
// Tagged class - vastly inferior to a class hierarchy!
class Figure {
    enum Shape { RECTANGLE, CIRCLE };
    // Tag field - the shape of this figure
    final Shape shape;
    // These fields are used only if shape is RECTANGLE
    double length;
    double width;
    // This field is used only if shape is CIRCLE
    double radius;
    // Constructor for circle
    Figure(double radius) {
        shape = Shape.CIRCLE;
        this.radius = radius;
    }
    // Constructor for rectangle
    Figure(double length, double width) {
        shape = Shape.RECTANGLE;
        this.length = length;
        this.width = width;
    }
    double area() {
        switch(shape) {
            case RECTANGLE:
                return length * width;
            case CIRCLE:
                return Math.PI * (radius * radius);
            default:
                throw new AssertionError(shape);
        }
    }
}
```

```java
// Class hierarchy replacement for a tagged class
abstract class Figure {
    abstract double area();
}
class Circle extends Figure {
    final double radius;
    Circle(double radius) { this.radius = radius; }
    @Override double area() { return Math.PI * (radius * radius); }
}

class Rectangle extends Figure {
    final double length;
    final double width;
    Rectangle(double length, double width) {
        this.length = length;
        this.width = width;
    }
    @Override double area() { return length * width; }
}
```

### Item 24: Favor static member classes over nonstatic

Four types of nested classes:

* static memebr class
* nonstatic member class
* anonymous class
* local class

### Item 25: Limit source files to a single top-level class

Never put multiple top-level classes or interfaces in a single source file.

## Generics

### Item 26: Don't use raw types

### Item 27: Eliminate unchecked warnings

### Item 28: Prefer Lists to Arrays

Arrays are *covariant* and *reified*; generics are *invariant* and *erased*

**covariant**: C[] is a subclass of P[] if C is a subclass of P
**invariant**: Collection<C> is **NOT** a subclass of Collection<P> even if C is a subclass of P

**Reified**: arrays know and enforce their element type at *runtime*
**Erased**: generics enforce their type constraints *only at compile time* and discard (or **erase**) their element type information at runtime. Runtime representation contains less information than compile-time representation.

### Item 29: Favor generic types

### Item 30: Favor generic methods

Static utility methods that operate on parameterized types are usually generic.

**Recursive type bound**: 

```java
// Builder pattern for class hierarchies
public abstract class Pizza {
    public enum Topping {HAM, MUSHROOM, ONION, PEPPER, SAUSAGE}

    final Set<Topping> toppings;

    abstract static class Builder<T extends Builder<T>> { // recursive type bound
        EnumSet<Topping> toppings = EnumSet.noneOf(Topping.class);

        public T addTopping(Topping topping) {
            toppings.add(Objects.requireNonNull(topping));
            return self();
        }

        abstract Pizza build();

        // Subclasses must override this method to return "this"
        protected abstract T self();
    }

    Pizza(Builder<?> builder) {
        toppings = builder.toppings.clone(); // See Item 50
    }
}
```

```java
// Returns max value in a collection - uses recursive type bound
public static <E extends Comparable<E>> E max(Collection<E> c) {
    if (c.isEmpty())
        throw new IllegalArgumentException("Empty collection");
    E result = null;
    for (E e : c)
        if (result == null || e.compareTo(result) > 0)
            result = Objects.requireNonNull(e);
    return result;
}
```

### Item 31: Use *bounded wildcards* to increase API flexibility

**Bounded wildcard type**: 

```java
public class Stack<E> {
    private Object[] elements;
    private int size = 0;
    private static final int DEFAULT_INITIAL_CAPACITY = 16;

    public Stack() {
        elements = new Object[DEFAULT_INITIAL_CAPACITY];
    }

    public void push(E e) {
        ensureCapacity();
        elements[size++] = e;
    }

    public E pop() {
        if (size == 0)
            throw new EmptyStackException();
        @SuppressWarnings("unchecked")
        E result = (E) elements[--size];
        elements[size] = null; // Eliminate obsolete reference
        return result;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    private void ensureCapacity() {
        if (elements.length == size)
            elements = Arrays.copyOf(elements, 2 * size + 1);
    }

    //producer
    public void pushAll(Iterable<? extends E> src) {
        for (E e : src) {
            push(e);
        }
    }
    
    //consumer
    public void popAll(Collection<? super E> dst) {
        while (!isEmpty()) {
            dst.add(pop());
        }
    }
    
    public static void main(String[] args) {
        Stack<Number> numberStack = new Stack<>();
        Iterable<Integer> integers = List.of(1, 2, 3);
        numberStack.pushAll(integers);
        
        Collection<Object> objects = new ArrayList<>();
        numberStack.popAll(objects);
    }
}
```

For maximum flexibility, use **wildcard types** on input parameters that represent producers (extends) or consumers (super). 

**PECS** stands for producer-extends, consumer-super.

**Do not use bounded wildcard types as return types**.

Comparables are always consumers, so you should generally use `Comparable<? super T>` in preference to `Comparable<T>`.

### Item 32: Combine generics and varargs judiciously

Varargs is a *leaky abstraction*: when you invoke a varargs method, an array is created to hold the varargs parameters; that array, which should be an implementation detail, is visible.

*Heap pollution*: when a variable of a parameterized type refers to an object that is not of that type

```java
// Mixing generics and varargs can violate type safety!
static void dangerous(List<String>... stringLists) {
    List<Integer> intList = List.of(42);
    Object[] objects = stringLists;
    objects[0] = intList; // Heap pollution
    String s = stringLists[0].get(0); // ClassCastException
}
```


This cast fails, demonstrating that type safety has been compromised, and it is unsafe to store a value **in a generic varargs array parameter**.

```java
// UNSAFE - Exposes a reference to its generic parameter array!
static <T> T[] toArray(T... args) {
    return args;
}
```

```java
@SafeVarargs
static <T> List<T> flatten(List<? extends T>... lists) {
    System.out.println(lists.getClass());
    List<T> result = new ArrayList<>();
    for (List<? extends T> list : lists) {
        result.addAll(list);
    }
    return result;
}
```

As a reminder, a generic varargs methods is safe if:
1. it doesn’t store anything in the varargs parameter array, and
2. it doesn’t make the array (or a clone) visible to untrusted code.

varargs and generics do not interact well because the varargs
facility is a leaky abstraction built atop arrays, and arrays have different type rules
from generics. (Item 28)

### Item 33: Consider typesafe heterogeneous containers

When a class literal is passed among methods to communicate both compile-time and runtime type information, it is called a *type token*.

```java
public class Favorites {
    private Map<Class<?>, Object> favorites = new HashMap<>();

    private <T> void putFavorite(Class<T> type, T instance) {
        favorites.put(Objects.requireNonNull(type), instance);
    }

    private <T> T getFavorite(Class<T> type) {
        return type.cast(favorites.get(type)); //dynamic cast
    }
}
```

```java
@SuppressWarnings("unchecked")
public T cast(Object obj) {
    if (obj != null && !isInstance(obj))
        throw new ClassCastException(cannotCastMsg(obj));
    return (T) obj;
}
```

**Bounded type token**: a type token that places a bound on what type can be represented,
using a *bounded type parameter* (Item 30, `E extends Comparable`) or a *bounded wildcard* (Item 31, `? extends Comparable`, sometimes you need more flexibility than invariant typing can provide).

## Enums and annotations

### Item 34: Use enums instead of int constants

To associate data with enum constants, declare **instance fields** and write a **constructor** that takes the data and stores it in the fields. All fields should be `final`.

**Constant-specific method implementations**:

```java
public enum Operation {
    PLUS("+") {
        public double apply(double x, double y) {
            return x + y;
        }
    },
    MINUS("-") {
        public double apply(double x, double y) {
            return x - y;
        }
    },
    TIMES("*") {
        public double apply(double x, double y) {
            return x * y;
        }
    },
    DIVIDE("/") {
        public double apply(double x, double y) {
            return x / y;
        }
    };
    private final String symbol;

    Operation(String symbol) {
        this.symbol = symbol;
    }

    @Override
    public String toString() {
        return symbol;
    }

    public abstract double apply(double a, double b);
}
```

```java
public enum Operation {
  PLUS("+", (x, y) -> x + y),
  MINUS("-", (x, y) -> x - y),
  MULTIPLY("*", (x, y) -> x * y),
  DIVIDE("/", (x, y) -> x / y);
  
  private final String symbol;
  private final DoubleBinaryOperator op;

  @Override
  public String toString() {
    return this.symbol;
  }

  Operation(String symbol, DoubleBinaryOperator op) {
    this.symbol = symbol;
    this.op = op;
  }

  public double apply(double x, double y) {
    return op.applyAsDouble(x, y);
  }
}

```

Use enums any time you need a set of constants whose members are **known at compile time**.
It is not necessary that the set of constants in an enum type stay fixed for all time.

### Item 35: Use instance fields instead of ordinals

```java
// Abuse of ordinal to derive an associated value - DON'T DO THIS
public enum Ensemble {
    SOLO, DUET, TRIO, QUARTET, QUINTET,
    SEXTET, SEPTET, OCTET, NONET, DECTET;
    public int numberOfMusicians() { return ordinal() + 1; }
}
```

Never derive a value associated with an enum from its **ordinal**; store it in an **instance field** instead.

### Item 36: Use EnumSet instead of bit fields
```java
// Bit field enumeration constants - OBSOLETE!
public class Text {
    public static final int STYLE_BOLD = 1 << 0; // 1
    public static final int STYLE_ITALIC = 1 << 1; // 2
    public static final int STYLE_UNDERLINE = 1 << 2; // 4
    public static final int STYLE_STRIKETHROUGH = 1 << 3; // 8
    // Parameter is bitwise OR of zero or more STYLE_ constants
    public void applyStyles(int styles) { ... }
}
```

```java
// EnumSet - a modern replacement for bit fields
public class Text {
    public enum Style { BOLD, ITALIC, UNDERLINE, STRIKETHROUGH }
    // Any Set could be passed in, but EnumSet is clearly best
    public void applyStyles(Set<Style> styles) { ... }
}

text.applyStyles(EnumSet.of(Style.BOLD, Style.ITALIC));
```

### Item 37: Use EnumMap instead of ordinal indexing 

```java
// Using an EnumMap to associate data with an enum
Map<Plant.LifeCycle, Set<Plant>> plantsByLifeCycle = new EnumMap<>(Plant.LifeCycle.class);
for (Plant.LifeCycle lc : Plant.LifeCycle.values())
    plantsByLifeCycle.put(lc, new HashSet<>()); // create a set for each value of LifeCycle
for (Plant p : garden)
    plantsByLifeCycle.get(p.lifeCycle).add(p);
System.out.println(plantsByLifeCycle);
```

```java
public enum Phase {
    SOLID, LIQUID, GAS;

    public enum Transition {
        MELT(SOLID, LIQUID), FREEZE(LIQUID, SOLID),
        BOIL(LIQUID, GAS), CONDENSE(GAS, LIQUID),
        SUBLIME(SOLID, GAS), DEPOSIT(GAS, SOLID);
        private final Phase from;
        private final Phase to;

        Transition(Phase from, Phase to) {
            this.from = from;
            this.to = to;
        }

        private static final Map<Phase, Map<Phase, Transition>>
                m = Stream.of(values()).collect(groupingBy(t -> t.from,
                () -> new EnumMap<>(Phase.class),
                toMap(t -> t.to, t -> t,
                        (x, y) -> y, () -> new EnumMap<>(Phase.class))));

        public static Transition from(Phase from, Phase to) {
            return m.get(from).get(to);
        }
    }
}
```

It is rarely appropriate to use ordinals to index into arrays: use EnumMap instead.

### Item 38: Emulate extensible enums with interfaces

```java
public interface Operation {
    double apply(double x, double y);
}
public enum BasicOperation implements Operation {
    PLUS("+") {
        public double apply(double x, double y) { return x + y; }
    },
    MINUS("-") {
        public double apply(double x, double y) { return x - y; }
    },
    TIMES("*") {
        public double apply(double x, double y) { return x * y; }
    },
    DIVIDE("/") {
        public double apply(double x, double y) { return x / y; }
    };
    private final String symbol;
    BasicOperation(String symbol) {
        this.symbol = symbol;
    }
    @Override public String toString() {
        return symbol;
    }
}
```

### Item 39: Prefer annotations to naming patterns

### Item 40: Consistency use the @Override annotation

The compiler can protect you from a great many errors if you use the Override annotation on every method declaration that you believe to override a supertype declaration.

### Item 41: Use marker interfaces to define types

A marker interface is an interface that contains no method declarations but merely designates (or “marks”) a class that implements the interface **as having some property** (`Serializable` interface)

Marker interfaces have two advantages over marker annotations. 
1. marker interfaces define a **type** that is implemented by instances of the marked class; marker annotations do not.
2. they can be targeted more precisely.

## Lambdas and Streams

### Item 42: Prefer lambdas to anonymous classes

Interfaces (or, rarely, abstract classes) with a single abstract method were used as *function types*.
Their instances, known as *function objects*, represent functions or actions.
*Anonymous class* was the primary means of creating *function objects*.

```java
// Anonymous class instance as a function object - obsolete!
Collections.sort(words, new Comparator<String>() {
    public int compare(String s1, String s2) {
        return Integer.compare(s1.length(), s2.length());
    }
});
```

```java
// Lambda expression as function object (replaces anonymous class)
Collections.sort(words, (s1,s2)->Integer.compare(s1.length(),s2.length()));
```

*Type inference*: The compiler **deduces** these types from context. Omit the types of all lambda parameters unless their presence makes your program clearer.

By way of example, the code snippet above won’t compile if the variable words is declared to
be of the *raw type* `List` instead of the *parameterized type* `List<String>`. (Item 26)

*comparator construction method*: 
```java
Collections.sort(words, comparingInt(String::length));
```
```java
words.sort(comparingInt(String::length));
```

* Lambdas cannot obsoletes constant-specific method bodies: lambdas lack names and documentation; if a computation isn’t self-explanatory, or exceeds a few lines, don’t put it in a lambda. One line is ideal for a lambda, and three lines is a reasonable maximum.
* Lambdas cannot obsoletes anonymous classes: Lambdas are limited to functional interfaces. 
    * If you want to create *an instance of an abstract class*, you can do it with an anonymous class, but not a lambda. 
    * A lambda cannot obtain a reference to *itself*.

As of Java 8, lambdas are by far the best way to represent **small function objects**. Don’t use anonymous classes for function objects unless you have to create instances of types that aren’t functional interfaces.

### Item 43: Prefer method reference to lambdas

Java provides a way to generate function objects even more succinct than lambdas: *method references*.

```java
map.merge(key, 1, (count, incr) -> count + incr);
```

```java
map.merge(key, 1, Integer::sum);
```


| Method Ref Type | Example | Lambda Equivalent |
| --- | --- | --- |
| Static | `Integer::parseInt` | `str -> Integer.parseInt(str)` |
| Bound | `Instant.now()::isAfter` | `Instant then = Instant.now(); t -> then.isAfter(t)` |
| Unbound | `String::toLowerCase` | `str -> str.toLowerCase()` |
| Class Constructor | `TreeMap<K,V>::new` | `() -> new TreeMap<K,V>` |
| Array Constructor | `int[]::new` | `len -> new int[len]` |

### Item 44: Favor the use of standard functional interfaces

If one of the standard functional interfaces does the job, you should generally use it in preference to a purpose-built functional interface.

* The `Operator` interfaces represent functions whose result and argument types are the **same**.
* The `Predicate` interface represents a function that takes **an argument** and returns a `boolean`.
* The `Function` interface represents a function whose argument and return types **differ**.
* The `Supplier` interface represents a function that takes **no arguments** and **returns (or “supplies”) a value**.
* The `Consumer` represents a function that takes **an argument** and **returns
nothing**, essentially *consuming* its argument.

| Interface | Function Signature | Example |
| --- | --- | --- |
| `UnaryOperator<T>` | `T apply(T t)` | `String::toLowerCase` | 
| `BinaryOperator<T>` | `T apply(T t1, T t2)` | `BigInteger::add` |
| `Predicate<T>` | `boolean test(T t)` | `Collection::isEmpty` |
| `Function<T,R>` |  `R apply(T t)` |  `Arrays::asList` |
| `Supplier<T>` | `T get()` |  `Instant::now` |
| `Consumer<T>` | `void accept(T t)` | `System.out::println` | 

**Don’t be tempted to use basic functional interfaces with boxed primitives instead of primitive functional interfaces**

### Item 45: Use streams judiciously

A stream pipeline consists of a source stream followed by zero or more *intermediate operations* and one *terminal operation*.

Stream pipelines are evaluated *lazily*.
The streams API is *fluent*.

### Item 46: Prefer side-effect-free methods in streams

**Pure function**: A pure function is one whose result depends only on its input: it does not depend on any mutable state, nor does it update any state.

```java
// Uses the streams API but not the paradigm--Don't do this!
Map<String, Long> freq = new HashMap<>();
try (Stream<String> words = new Scanner(file).tokens()) {
    words.forEach(word -> {
        freq.merge(word.toLowerCase(), 1L, Long::sum);
    });
}
```

```java
// Proper use of streams to initialize a frequency table
Map<String, Long> freq;
try (Stream<String> words = new Scanner(file).tokens()) {
    freq = words.collect(groupingBy(String::toLowerCase, counting()));
}
```

The `forEach` operation should be used only to report the result of a stream computation, not to perform the computation.

*collector*: You can ignore the Collector interface and think of a collector as an opaque object that encapsulates a *reduction* strategy.
The collectors for gathering the elements of a stream into a true `Collection`
are straightforward.

* There are three such collectors: `toList()`, `toSet()`, and `toCollection(collectionFactory)`.

```java
// Pipeline to get a top-ten list of words from a frequency table
List<String> topTen = freq.keySet().stream()
    .sorted(comparing(freq::get).reversed())
    .limit(10) //SQL?
    .collect(toList());
```

* `toMap` collector:

```java
// Using a toMap collector to make a map from string to enum
private static final Map<String, Operation> stringToEnum =
Stream.of(values()).collect(toMap(Object::toString, e -> e));
```

The three-argument form of toMap is also useful to make a map from a key to a chosen element associated with that key. 

```java
// Collector to generate a map from key to chosen element for key
Map<Artist, Album> topHits = albums.collect(
toMap(Album::artist, a->a, maxBy(comparing(Album::sales))));
```

Another use of the three-argument form of toMap is to produce a collector that imposes a *last-write-wins policy* when there are collisions.

```java
// Collector to impose last-write-wins policy
toMap(keyMapper, valueMapper, (v1, v2) -> v2);
```

* `groupingBy` method, which returns collectors to produce maps that group elements into
categories based on a *classifier* function. The classifier function **takes an element**
and **returns the category** into which it falls. 

```java
words.collect(groupingBy(word -> alphabetize(word)));
```

If you want groupingBy to return a collector that produces a map **with values other than lists**, you can specify a *downstream collector* in addition to a classifier.

```java
Map<String, Long> freq = words.collect(groupingBy(String::toLowerCase, counting()));
```

### Item 47: Prefer Collection to Stream as a return type

* Stream<E> to Iterable<E>:

```java
// Won't compile, due to limitations on Java's type inference
for (ProcessHandle ph : ProcessHandle.allProcesses()::iterator) {
// Process the process
}
```

```java
// Adapter from Stream<E> to Iterable<E>
public static <E> Iterable<E> iterableOf(Stream<E> stream) {
    return stream::iterator;
}

for (ProcessHandle p : iterableOf(ProcessHandle.allProcesses())) {
// Process the process
}
```

* Iterable<E> to Stream<E>:
```java
// Adapter from Iterable<E> to Stream<E>
public static <E> Stream<E> streamOf(Iterable<E> iterable) {
    return StreamSupport.stream(iterable.spliterator(), false);
}
```

### Item 48: Use caution when making streams parallel

Parallelizing a pipeline is *unlikely to increase its performance* if the source is from `Stream.iterate`, or the intermediate operation `limit` is used.

Performance gains from parallelism are best on streams over `ArrayList`, `HashMap`, `HashSet`, and `ConcurrentHashMap` instances; arrays; `int` ranges; and `long` ranges.

## Methods

### Item 49: Check parameters for validity

```java
/**
* Returns a BigInteger whose value is (this mod m). This method
* differs from the remainder method in that it always returns a
* non-negative BigInteger.
*
* @param m the modulus, which must be positive
* @return this mod m
* @throws ArithmeticException if m is less than or equal to 0
*/
public BigInteger mod(BigInteger m) {
    if (m.signum() <= 0)
        throw new ArithmeticException("Modulus <= 0: " + m);
        ... // Do the computation
}
```


The `Objects.requireNonNull` method, added in Java 7, is flexible and convenient, so there’s no reason to perform null checks manually anymore.

```java
// Inline use of Java's null-checking facility
this.strategy = Objects.requireNonNull(strategy, "strategy");
```

You should **document** these restrictions and **enforce them with explicit checks** at the beginning of the method body.

### Item 50: Make defensive copies when needed

You must program **defensively**, with the assumption that clients of your class will do their best to destroy its invariants.

It is essential to make a **defensive copy** of each mutable parameter to the constructor

```java
// Attack the internals of a Period instance
Date start = new Date();
Date end = new Date();
Period p = new Period(start, end);
end.setYear(78); // Modifies internals of p!
```

```java
// Repaired constructor - makes defensive copies of parameters
public Period(Date start, Date end) {
    this.start = new Date(start.getTime()); //defensive copy
    this.end = new Date(end.getTime());
    if (this.start.compareTo(this.end) > 0)
        throw new IllegalArgumentException(
    this.start + " after " + this.end);
}
```

Defensive copies are made *before* checking the validity of the parameters, and the validity check is performed on the copies rather than on the originals.
It protects the class against changes to the parameters from another thread during the *window of vulnerability* between the time the parameters are *checked* and the time they are *copied*. In the computer security community, this is known as a *time-of-check/time-of-use* or *TOCTOU* attack.

Do not use the `clone` method to make a defensive copy of a parameter whose type is subclassable by untrusted parties.

```java
// Second attack on the internals of a Period instance
Date start = new Date();
Date end = new Date();
Period p = new Period(start, end);
p.end().setYear(78); // Modifies internals of p!
```

Return defensive copies of mutable internal fields.

```java
// Repaired accessors - make defensive copies of internal fields
public Date start() {
    return new Date(start.getTime());
}
public Date end() {
    return new Date(end.getTime());
}
```

Non-zero length arrays are always mutable.

```java
private static final Thing[] PRIVATE_VALUES = { ... };
public static final List<Thing> VALUES = Collections.unmodifiableList(Arrays.asList(PRIVATE_VALUES));
```

```java
private static final Thing[] PRIVATE_VALUES = { ... };
public static final Thing[] values() {
    return PRIVATE_VALUES.clone();
}
```

### Item 51: Design method signatures carefully

* Choose method names carefully
* Don’t go overboard in providing convenience methods
* Avoid long parameter lists. Long sequences of identically typed parameters are especially
harmful, like `method(int, int, int, int)`
    * **Break the method** up to multiple methods
    * Create **helper classes** to hold groups of parameters
    * Adapt the **Builder pattern** from object construction to method invocation
* For parameter types, favor interfaces over classes
* Prefer two-element enum types to `boolean` parameters.

### Item 52: Use overloading judiciously

The choice of *which overloading to invoke* is made at **compile time**: no dynamic binding.

Selection among **overloaded** methods is **static**, while selection among **overridden** methods is **dynamic**.

A safe, conservative policy is never to export two overloadings **with the same number of parameters**.

### Item 53: Use varargs judiciously

```java
// The WRONG way to use varargs to pass one or more arguments!
static int min(int... args) {
    if (args.length == 0)
        throw new IllegalArgumentException("Too few arguments");
    int min = args[0];
    for (int i = 1; i < args.length; i++)
        if (args[i] < min)
            min = args[i];
    return min;
}
```

```java
// The right way to use varargs to pass one or more arguments
static int min(int firstArg, int... remainingArgs) {
    int min = firstArg;
    for (int arg : remainingArgs)
        if (arg < min)
            min = arg;
    return min;
}
```

### Item 54: Return empty collections or arrays, not nulls

```java
//The right way to return a possibly empty collection
public List<Cheese> getCheeses() {
    return new ArrayList<>(cheesesInStock);
}

// Optimization - avoids allocating empty collections
public List<Cheese> getCheeses() {
    return cheesesInStock.isEmpty() ? Collections.emptyList()
        : new ArrayList<>(cheesesInStock);
}

//The right way to return a possibly empty array
public Cheese[] getCheeses() {
    return cheesesInStock.toArray(new Cheese[0]);
}

// Optimization - avoids allocating empty arrays
private static final Cheese[] EMPTY_CHEESE_ARRAY = new Cheese[0];
public Cheese[] getCheeses() {
    return cheeseInStock.toArray(EMPTY_CHEESE_ARRAY);
}
```

In the optimized version, we pass the **same empty array** into every toArray call, and this array will be returned from getCheeses whenever cheesesInStock is empty.

Reference:

`public <T> T[] toArray(T[] a)`

Returns an array containing *all of the elements in this collection*; the runtime type of the returned array is that of the specified array. If the collection *fits in* the specified array, it is returned therein. Otherwise, *a new array is allocated* with the runtime type of the specified array and the size of this collection.
If this collection *fits in the specified array with room to spare* (i.e., the array has more elements than this collection), *the element in the array immediately following the end of the collection is set to null*. (This is useful in determining the length of this collection only if the caller knows that this collection does not contain any null elements.)

### Item 55: Return optionals judiciously

## 10 Exceptions

### Item 70: Use checked exceptions for recoverable conditions and runtime exceptions for programming errors

Three kinds of throwables: `checked exceptions`, `runtime exceptions`, `errors`.

* Use **checked exceptions** for conditions from which the caller can reasonably be expected to *recover*.
* Runtime exceptions and errors need not and should not be caught.
* Use **runtime exceptions** to indicate programming errors.
* Provide methods on your checked exceptions to aid in recovery.

### Item 71: Avoid unnecessary use of checked exceptions

* The easiest way to eliminate a checked exception is to return an optional of the desired result type.
* Break the method that throws the exception into two methods, the first of which returns a `boolean` indicating whether the exception would be thrown.

```java
// Invocation with checked exception
try {
    obj.action(args);
} catch (TheCheckedException e) {
    ... // Handle exceptional condition
}
```

```java
// Invocation with state-testing method and unchecked exception
if (obj.actionPermitted(args)) {
    obj.action(args);
} else {
    ... // Handle exceptional condition
}
```

* If callers won’t be able to recover from failures, throw *unchecked exceptions*.
* If recovery may be possible and you want to *force* callers to handle exceptional conditions, first consider returning an *optional*.
* Only if this would provide insufficient information in the case of failure should you throw a checked exception.

### Item 72: Favor the use of standard exceptions

The most commonly reused exception type is `IllegalArgumentException`. This is generally the exception to throw when the caller passes in an argument whose value is inappropriate.

Another commonly reused exception is `IllegalStateException`. This is generally the exception to throw if the invocation is illegal because of the state of the receiving object.

Another reusable exception is `ConcurrentModificationException`. It should be thrown if an object that was designed for use by a single thread (or with external synchronization) detects that it is being modified concurrently.

A last standard exception of note is `UnsupportedOperationException`. This is the exception to throw if an object does not support an attempted operation. Its use is rare because most objects support all of their methods.

Do not reuse Exception, RuntimeException, Throwable, or Error **directly**.


| Exception | Occasion for Use |
| --- | --- |
| IllegalArgumentException | Non-null parameter value is inappropriate |
| IllegalStateException | Object state is inappropriate for method invocation |
| NullPointerException | Parameter value is null where prohibited |
| IndexOutOfBoundsException | Index parameter value is out of range |
| ConcurrentModificationException | Concurrent modification of an object has been detected where it is prohibited |
| UnsupportedOperationException | Object does not support method |

Throw `IllegalStateException` if no argument values would have worked, otherwise throw `IllegalArgumentException`.

### Item 73: Throw exceptions appropriate to the abstraction

Exception translation: higher layers should catch lower-level exceptions and, in their place, throw exceptions that can be explained *in terms of the higher-level abstraction*.

```java
// Exception Translation
try {
    ... // Use lower-level abstraction to do our bidding
} catch (LowerLevelException e) {
    throw new HigherLevelException(...);
}
```

```java
/**
* Returns the element at the specified position in this list.
* @throws IndexOutOfBoundsException if the index is out of range
* ({@code index < 0 || index >= size()}).
*/
public E get(int index) {
    ListIterator<E> i = listIterator(index);
    try {
        return i.next();
    } catch (NoSuchElementException e) {
        throw new IndexOutOfBoundsException("Index: " + index);
    }
}
```

```java
// Exception Chaining
try {
... // Use lower-level abstraction to do our bidding
} catch (LowerLevelException cause) {
    throw new HigherLevelException(cause);
}
```

```java
// Exception with chaining-aware constructor
class HigherLevelException extends Exception {
    HigherLevelException(Throwable cause) {
        super(cause);
    }
}
```

While exception translation is superior to mindless propagation of exceptions from lower layers, it should not be overused.

### Item 74: Document all exceptions thrown by each method

Always declare checked exceptions individually, and document precisely the conditions under which each one is thrown using the Javadoc `@throws` tag.

### Item 79: Avoid Excessive Synchronization

* To avoid liveness and safety failures, never cede control to the client within a synchronized method or block.
* As a rule, you should do as little work as possible inside synchronized regions.

Two options for a mutable class:
1. omit all synchronization and allow the client to synchronize externally (`java.util.*`)
2. synchronize internally, making the class *thread-safe* (`java.util.concurrent.*`)

If you do synchronize your class internally, you can use various techniques to
achieve high concurrency, such as *lock splitting*, *lock striping*, and *nonblocking concurrency control*.

### Item 80: Prefer executors, tasks, and streams to threads

```java
ExecutorService exec = Executors.newSingleThreadExecutor();
exec.execute(runnable);
exec.shutdown();
```

```java
ExecutorService service = Executors.newCachedThreadPool();
ExecutorService service2 = Executors.newFixedThreadPool(10);
```

Not only should you refrain from writing your own work queues, but you
should generally refrain from working directly with threads.

### Item 81: Prefer concurrency utilities to wait and notify

* Executor Framework
* concurrent collections
* synchronizers

```java
// The standard idiom for using the wait method
synchronized (obj) {
    while (<condition does not hold>)
        obj.wait(); // (Releases lock, and reacquires on wakeup)
... // Perform action appropriate to condition
}
```

### Item 82: Document thread safety

A class must clearly document what level of thread safety it supports
* Immutable
* Unconditionally thread safe
* Conditionally thread safe
* Not thread-safe
* Thread-hostile 

### Item 83: Use lazy initialization judiciously

If you need to use lazy initialization for performance on an instance field, use the *double-check idiom*.

```java
// Double-check idiom for lazy initialization of instance fields
private volatile FieldType field;
private FieldType getField() {
    FieldType result = field;
    if (result == null) { // First check (no locking)
        synchronized(this) {
            if (field == null) // Second check (with locking)
            field = result = computeFieldValue();
        }
    }
    return result;
}
```

> The value of this variable will never be cached thread-locally: all reads and writes will go straight to "main memory";
> Access to the variable acts as though it is enclosed in a synchronized block, synchronized on itself.

### Item 84: Do not depend on thread scheduler

Threads should not *busy-wait*, repeatedly checking a shared object waiting for its state to change.

The resulting program will be neither robust nor portable.

## Chapter 12. Serialziation

### Item 84: Prefer alternatives to Java serialization

The best way to avoid serialization exploits is never to deserialize anything. There is no reason to use Java serialization in any new system you write.

*cross-platform structured-data representations*: JSON, Protobuf 