---
layout: post
title: Functional programming
subtitle: Practice for concept of functional programming
# cover-img: /assets/img/Blackboard.png
# thumbnail-img: /assets/img/designathon/coverdesginathon.png
# share-img: /assets/img/path.jpg
tags: [concept of programming, functional programming, javascript, python]
comments: true
author: Lantana Park
---

## What is functional programming?

- It is a declarative programming paradigm style and takes an input value and produces an output value.

- It is an **immutable data structures and algorithms.**

- It is higher-order functions.

![functionalDiagram](/assets/img/functionalProgramming/Function_machine.png)

## what is declarative vs imperative programming?

- Imperative programming describes a step-by-step process for a program's execution, detailing the steps required to solve a problem. (such as Object-Oriented Programming)

- In the declarative paradigm, I need to define the results I want a program to accomplish wihout describing its control flow. (such as Functional Programming)

- JavaScript is supporting both paradigms, declarative and imperative programming.

- Python is considered an imperative programming language.

## What is immutability in functional programming?

- Once a variable is assigned a value, that value cannot be changed throughout the course of its existence. In short, data structures, once created, cannot be changed.

```javascript
function incrementAge(user) {
  return { ...user, age: user.age + 1 };
}

const originalUser = { name: "Mark", age: 25 };
const newUser = incrementAge(originalUser);

console.log(originalUser); // {name: "Mark", age: 25}
console.log(newUser); // {name: "Mark", age: 26}
```

Here, `incrementAge` returns a new user object with the age property incremented, leaving the original `originalUser` object unmodified.

Let's look at my source code where I used immutability concept.

![immutabilitymycode](/assets/img/functionalProgramming/immutable.png)

I used React's `useState` hook to manage component state updating state variables immutably.

To explain with my source code(client side),

First, the `useState` hook initializes the `perks` state as an object with multiple properties, each representing a different category and initially set to an empty string.

```javascript
const [perks, setPerks] = useState({
  food: "",
  transportation: "",
  beverage: "",
  alcohol: "",
  equipment: "",
  others: "",
});
```

Second, the `handlePerksChange` function is designed to update the `perks` state when a change event occurs from the input field.

```javascript
const handlePerksChange = (e) => {
  const { name, value } = e.target;
  // In the line 66, it extracts the `name` and `value` from the event's target from the input field. The `name` corresponds to the specific perk being updated, and `value` is the new value for that perk.
  setPerks((prevPerks) => ({
    // `setPerks` is called with a function as its argument rather than a direct new state value. This function receives the previous state as its parameter.
    ...prevPerks,
    // Here is where immutability is applied.
    // `...prevPerks` creates a new object that is a shallow copy of `prevPerks`. By spreading `prevPerks`, all existing properties and their values are included in the new state object, ensuring that I am building on the latest state withoug mutating it.
    [name]: value,
    // This syntax dynamically updates the property of the object that corresponds to the input's name attribute.
    // The property's value is set to the new value from the input.
    // This part of the expression is key to immutability because it doesn't alter an existing property directly; instead, it specifies the updated value in the new object being created.
  }));
};

<textarea
  type="text"
  id="transportation"
  name="transportation"
  value={perks.transportation}
  onChange={handlePerksChange}
  autoComplete="off"
  className="mt-2 block w-full rounded-md border-0 py-1.5 text-gray-900 shadow-sm ring-1 ring-inset ring-gray-300 placeholder:text-gray-400 focus:ring-2 focus:ring-inset focus:ring-red-600 sm:text-sm sm:leading-6"
/>;
```

## Functional Programming Concepts

1. Pure function

- It always returns the same output for the same input (name) without causing any side effects.

```javascript
function greet(name) {
  return `Hi, ${name}`;
}
console.log(greet("lantana"));
// Hi, lantana
```

2. Higher Order Functions

- Higher-order functions are a concept in functional programming. They are functions that can take other functions as arguments or return function as their results. It characteristic allows for a higher level of abstraction in programming, enabling more flexible and reusable code.

  1. In javaScript, `map` is a higher-order function that transforms an array by applying a function to all of its elements and returning a new array with the results.

```javascript
const numbers = [1, 2, 3, 4];
const squares = numbers.map((x) => x * x); // Applying a function to square each element
console.log(numbers); // [1, 2, 3, 4]
console.log(squares); // [1, 4, 9, 16]
```

2. `filter` is another higher-order function that creates a new array with all elements that pass the test implemented by the provided function.

```javascript
const numbers = [1, 2, 3, 4];
const evens = numbers.filter((x) => x % 2 === 0); // Filtering even numbers
console.log(numbers); // [1, 2, 3, 4]
console.log(evens); // [2, 4]
```

3. `reduce` method is a higher-order function. It operates on arrays and takes a callback function as an argument, applying this callback to reduce the array to a single value.

```javascript
let numbers = [5, 20, 100, 60, 1];
const maxValue = numbers.reduce((max, curr) => {
  if (curr > max) max = curr;
  return max;
});
console.log(numbers); // [5, 20, 100, 60, 1]
console.log(maxValue); // 100
```

To explain with my source code,

in this express.js server code, middleware functions are used to process requests. The `authenticateUser` middleware checks if the user is anthenticated before processing to the route handler. Middleware functions in this code below are higher-order functions because they take three arguments: `req` (the request object), `res` (the response object), and `next` (a function to call the next middleware in the stack).

The `next` argument is particularly significant because it allows `authenticateUser` to control the flow of the application by deciding whether to proceed to the next piece of middleware in the stack or terminate the chain based on authentication logic. Since `next` function has the potential to call this function depending on the outcome of its internal logic, the ability to take and invoke functions makes middleware inherently higher-order.

```javascript
// middleware
const authenticateUser = async (req, res, next) => {
  try {
    const authAccessToken = req.cookies["accessToken"];
    if (!authAccessToken) {
      return res.status(401).json("Access token not found!");
    }

    const payload = jwt.verify(authAccessToken, process.env.ACCESS_SECRET);

    if (!payload) {
      return res.status(401).json("Unauthorized!");
    }

    const user = await User.findById(payload.id);
    if (!user || (!user.isVerified && !user.isActive)) {
      return res.status(401).json("Unauthorized!");
    }

    req.user = user;
    next();
  } catch (error) {
    next(error);
  }
};
```

Additionally, in the route handler `router.get("/:id", authenticateUser, async (req, res) => {})`, the use of `authenticateUser` as middleware before the asynchronous route handler also illustrates the use of higher-order functions. The middleware preprocesses the request, applying authentication logic, before passing control to the route handler.

```javascript
// server code to get the user's profile data
router.get("/:id", authenticateUser, async (req, res) => {
  try {
    const user = await User.findById(req.params.id);

    if (!user) {
      return res.status(404).json("User not found");
    }

    if (user.id !== req.user.id) {
      return res.status(404).json("User not found");
    }

    res.status(200).json(user);
  } catch (error) {
    res.status(500).json({ error: "Server Error!" });
  }
});
```

3. Currying

-  Currying is a functional programming concept where a function that takes multiple arguments is transformed into a sequence of nested functions, each taking a single argument. For example, `function(a, b, c)` can be `function (a) (b) (c)`.

```javascript
// The function applyShipCost takes three arguments sequentially
// 
const applyShippingCost = (country) => (flatRate) => (order) => {
  if (order.shipTo === country) {
    return {
      ...order,
      shippingCost: flatRate,
    };
  }
  return order;
};

const applyShippingToUSA = applyShippingCost('USA')(10); 
const order = { item: 'Book', shipTo: 'USA', price: 15 };
console.log(applyShippingToUSA(order));
```



4. Recursion

```javascript
const buildTree = (list, parent) => {
  let tree = {};
  list
    .filter((items) => items.parent === parent)
    .forEach((items) => {
      tree[items.id] = buildTree(list, items.id);
    });
  return tree;
};
```

![recursion](/assets/img/functionalProgramming/Screenshot%202024-03-04%20at%2022.00.51.png)

5. Functors

6. Monads
