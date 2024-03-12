---
layout: post
title: Functional programming
subtitle: Practice for concept of functional programming
# cover-img: /assets/img/Blackboard.png
# thumbnail-img: /assets/img/designathon/coverdesginathon.png
# share-img: /assets/img/path.jpg
tags: [concept of programming, functional programming]
comments: true
author: Lantana Park
---

## What is functional programming?

1. Pure function

```javascript
function greet(name) {
  return `Hi, ${name}`;
}
```

![pure](/assets/img/functionalProgramming/Screenshot%202024-03-04%20at%2022.00.51.png)

2.  Higher Order Functions

    - isPrime.js

    ```javascript
    /*
    The cart is an array of objects like this:
    var cart=[
    {"name":"Biscuits", "type":"regular", "category":"food", "price": 2.0},
    {"name":"Monitor", "type":"prime", "category":"tech", "price": 119.99},
    {"name":"Mouse", "type":"prime", "category":"tech", "price": 25.50},
    {"name":"dress", "type":"regular", "category":"clothes", "price": 49.90},
    ]
    \*/
    function isPrime(item) {
      return item.type === "prime";
    }

    function primeItems(cart) {
      // write your code here
      return cart.filter(isPrime);
    }
    ```

    ![isPrime](/assets/img/functionalProgramming/Screenshot%202024-03-02%20at%2019.39.40.png)

    - isNotPrime.js

    ```javascript
    const _ = require("underscore");
    const isPrime = require("./isPrime.js");

    function notPrimeItems(cart) {
      // Using _.reject to filter out items where type is not 'prime'
      return _.reject(cart, (item) => item.type === "prime");
    }
    ```

    ![inNotPrime](/assets/img/functionalProgramming/Screenshot%202024-03-11%20at%2021.41.00.png)

    - coupons.js

    ```javascript
    function applyCoupon(cart) {
      return cart.map((items) => {
        if (items.category === "tech") {
          return {
            price: items.price * 0.8,
          };
        }
        return items;
      });
    }
    ```

    ![coupons](/assets/img/functionalProgramming/Screenshot%202024-03-02%20at%2021.35.19.png)

    - totalCost.js

    ```javascript
    function totalCost(cart) {
      // write your code here
      return cart.reduce(
        (accumulator, currentValue) => accumulator + currentValue.price,
        0
      );
    }
    ```

    ![totalCost](/assets/img/functionalProgramming/Screenshot%202024-03-02%20at%2021.38.18.png)

3.  Currying

```javascript
const applyCoupon = (category) => (discount) => (items) => {
  if (items.category === category) {
    return {
      price: items.price * (1 - discount),
    };
  }
  return items;
};
```

![currying](/assets/img/functionalProgramming/Screenshot%202024-03-02%20at%2022.36.45.png)

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
