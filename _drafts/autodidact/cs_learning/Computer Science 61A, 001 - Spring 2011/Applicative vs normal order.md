[[cs_learning]]

A lambda expression is said to be in _normal form_ if it cannot be reduced any further, meaning that the expression no longer contains any function applications. More formally, a reducible expression is called a _redex_, and a lambda expression is in normal form when it contains no more redexes.

Redex
A reducible function expression.

Normal Form
A lambda expression that contains no redexes.

Given a lambda expression, there are two primary strategies for reducing it to normal form: normal-order evaluation, or applicative-order evaluation. This article discusses both methods, their pros and cons, and an alternative evaluation strategy that combines the pros from both — lazy evaluation.

## Normal-Order Evaluation

Normal-order evaluation of a lambda expression is the repeated application of the leftmost reducible function application. In other words, normal order evaluation is the strategy that always reduces the left-most outer-most redex first. You can think about normal-order evaluation as traversing the lambda expression and evaluating every function you find _before_ evaluating any function arguments.

The most noticeable effect of using normal-order evaluation is that, since we evaluate the leftmost function first, arguments to that function are not evaluated. If those arguments are themselves functions, we may pass unevaluated functions as function arguments. Speaking in terms of lambda calculus, an expression with an unevaluated function application as argument will replace all bound variables with the unevaluated function application.

## Applicative-Order Evaluation

Applicative-order evaluation means that a function’s arguments are evaluated before the function is _applied_. In other words, with applicative-order evaluation, internal reductions are applied first, and only after all internal reductions are complete, the left-most redex is reduced. More formally, we evaluate the left-most redex free of any internal redexes.

The most noticeable effect of applicative-order evaluation is that recursive functions may not terminate. For example, if an argument to a function must be evaluated before calling the function, and if that argument is recursive, the function will never terminate.

To illustrate the differences between normal and applicative order reduction, let’s walk through a few examples.

## Comparison

Consider a function `double` that doubles two numbers, and a function `average` that takes the average of two numbers.

```
def double x = (plus x x)
def average x y = (divide (plus x y) 2)
```

Now let’s use these functions to create a lambda expression that we can evaluate in normal order:

### Normal-Order Evaluation

```
(double (average 2 4)) =>
(plus (average 2 4) (average 2 4)) =>
(plus (divide (plus 2 4) 2) (average 2 4)) =>
(plus (divide 6 2) (average 2 4)) =>
(plus 3 (average 2 4)) =>
(plus 3 (divide (plus 2 4) 2)) =>
(plus 3 (divide 6 2)) =>
(plus 3 3) =>
6
```

### Applicative-Order Evaluation

We can evaluate that same function in applicative order:

```
double (average 2 4) =>
double (divide (plus 2 4) 2) =>
double (divide 6 2) =>
double 3 =>
plus 3 3 =>
6
```

Notice how, under normal-order evaluation, the left-most function application is always evaluated first, and with applicative-order evaluation, the inner-most functions are evaluated first. Also notice how normal-order evaluation applies the `(average 2 4)` function more than once.

Now consider an `if` function with an argument that is an illegal operation. Semantically, the `if` function takes three arguments, and if the first argument evaluates to `True` return the second argument, otherwise, return the third argument. For example:

```
if True x y = x
if False x y = y
```

### Normal-Order Evaluation

With normal-order evaluation, we derive the value `10`.

```
if (less 3 4) (plus 5 5) (divide 1 0) =>
if True (plus 5 5) (divide 1 0) =>
(plus 5 5) =>
10
```

### Applicative-Order Evaluation

With applicative-order evaluation, we end up with an error because we evaluate the illegal argument before applying the function.

```
if (less 3 4) (plus 5 5) (divide 1 0) =>
if True (plus 5 5) (divide 1 0) =>
if True 10 (divide 1 0) =>
Error — Divide by Zero
```

In this case, the applicate-order evaluation results in a run-time error, while the normal-order evaluation completes.

## Lazy Evaluation

While normal-order evaluation may result in doing extra work by requiring function arguments to be evaluated more than once, applicative-order evaluation may result in programs that do not terminate where their normal-order equivalents do. In practise, most functional programming languages solve this problem using _lazy evaluation_.

With lazy evalution, we delay function evaluation in a way that avoids multiple evaluations of the same function — thus combining the benefits of normal-order and applicative-order evaluation. **With lazy evaluation, we evaluate a value when it is needed, and after evaluation all copies of that expression are updated with the new value.** In effect, a parameter passed into a function is stored in a single location in memory so that the parameter need only be evaluated once. That is, we remember all of the locations where we a certain argument will be used, and when we evaluate a function, we replace the argument with the value. As a result, with lazy evaluation, every parameter is evaluated at most once.

## Summary

This article briefly covered the differences between normal-order and applicative-order evaluation, with special care given to the degenerative cases for both. In particular, normal-order evaluation may result in duplicate function applications, whereas applicative-order evaluation may increase the chance of non-termination (due to infinite recursion), or errors (due to evaluating all potential paths). In practise, no programming language uses normal-order evaluation because of the performance penalty, and it is also difficult to use strict applicative-order evaluation because of the increase in non-terminating cases. Rather, programming languages tend to use _lazy-evaluation_ as a means of enabling the performance benefit of applicative-order evaluation without the risk.

https://sookocheff.com/post/fp/evaluating-lambda-expressions/