## The Edge Cases - AT END

Methods that do not return values.

``` csharp
public static void Main()
{
  Foo();
  Foo();
  Foo();
}

public static void Foo()
{
  Console.WriteLine("test");

}
```

- Method called multiple times with different parameters.
- Method called multiple times with pairs of equal parameters
  
Example:

``` csharp
var x = Foobar("Foo");
var y = Foobar("Foo");
var z = Foobar("Bar");
var w = Foobar("Bar");
```


