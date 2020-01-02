---
layout: post
title: What is different TypeAssertion and TypeCasting in Typescript
tags: [dev, typescript]
---

According to my experience, When learning new technology or concepts, Reading articles in english is better than korean ones. Because most of technology terms came from English.  I have some experiences that I was confused terms which I've already learned in korean, but It dose not match english terms. After that I've decided I should be familiar with english terms.

Today I want get deep insights of Type Assertion and Type Casting in Typescript.

# What is Type Assertion?
Type Assertion is let Typescript compiler know that 'I know what type is it for this variable.'. It's done by declaring forced Type.
E.g
```typescript
interface Foo {
    bar: number;
    bas: string;
}
var foo = {} as Foo;
foo.bar = 123;
foo.bas = 'hello';
```

Originally the syntax for is `<Foo>` but, It conflicts with JSX syntax. so We can use `as Foo` as well with tsx files.
It's different from `Casting`. Because `Casting` is generally runtime operation. But `Type Assertion` is compile time operation to provide hint to compiler.

## What is Type Casting?
In Typescript, Type Casting is not used.

[more details](https://basarat.gitbooks.io/typescript/docs/types/type-assertion.html)