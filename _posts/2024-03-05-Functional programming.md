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

```JavaScript
function greet(name) {
  return `Hi, ${name}`
}
```

![pure](/assets/img/functionalProgramming/Screenshot%202024-03-04%20at%2022.00.51.png)

2.  Higher Order Functions

    - isPrime.js
    ```JavaScript
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
    return item.type === "prime"
    }

    function primeItems(cart) {
    // write your code here
    return cart.filter(isPrime)
    }
    ```
    ![isPrime](/assets/img/functionalProgramming/Screenshot%202024-03-02%20at%2019.39.40.png)

    - isNotPrime.js
    ```JavaScript
    const _ = require('underscore'); 
    const isPrime = require('./isPrime.js');

    function notPrimeItems(cart) {
    // Using _.reject to filter out items where type is not 'prime'
    return _.reject(cart, (item) => item.type === 'prime');
    }
    ```
    ![inNotPrime](/assets/img/functionalProgramming/Screenshot%202024-03-11%20at%2021.41.00.png)

    - coupons.js
    ```JavaScript
    function applyCoupon(cart) {
        return cart.map((items) => {
            if (items.category === 'tech') {
                return {
                    price: items.price * 0.8
                };
            }
            return items;
        });
    }
    ```
    ![coupons](/assets/img/functionalProgramming/Screenshot%202024-03-02%20at%2021.35.19.png)

    - 
