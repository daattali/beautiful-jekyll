---
layout: post
title: Number bases - Essential math
subtitle: In order to understand crypto, let's deep dive into number bases
# cover-img: /assets/img/banditlogo.png
thumbnail-img: /assets/img/crypto/crypto.png
# share-img: /assets/img/path.jpg
tags: [Number bases, cryto, computer basics]
comments: true
author: Lantana Park
---

# Why I care about number bases?

Since number bases are fundamental concept in computer science that underpins everything from **the basic operation of computers** to advanced topics in software development.

# How to count the bases(Base 2, Base 4 and Base 10)?

## How to count numbers in Base 2 and covert to decimal

It is a numeric method of representing numbers using only two numbers **0, 1.** This is foundational to digital computing and eletronics, as it reflects state of computer hardware conponents, which can be either off(0) or on (1).

- Base 2: 0 -- Base 10: 0
- Base 2: 1 -- Base 10: 1
- Base 2: 10 -- Base 10: 2
- Base 2: 11 -- Base 10: 3
- Base 2: 100 -- Base 10: 4
- Base 2: 101 -- Base 10: 5
- Base 2: 110 -- Base 10: 6
- Base 2: 111 -- Base 10: 7
- Base 2: 1000 -- Base 10: 8
- Base 2: 1001 -- Base 10: 9
- Base 2: 1010 -- Base 10: 10
- **Base 2: 1011 -- Base 10: 11**
- Base 2: 1100 -- Base 10: 12

In order to convert Base 2 into Decimal, I can multiply each digit by its place value and sum the results.

For example,

If I convert `1011` into decimal

- 1 X 2^0 = 1
- 1 X 2^1 = 2
- 0 X 2^2 = 0
- 1 X 2^3 = 8

---

1 + 2 + 0 + 8 = 11

In other notation of Base 2,

I can represent like 1011<sub>2</sub> = 11

## How to count numbers in Base 4 and convert to decimal

It is a numertic method of representing numbers using four different numbers **0, 1, 2, 3**.

- Base 4: 0 -- Base 10: 0
- Base 4: 1 -- Base 10: 1
- Base 4: 2 -- Base 10: 2
- Base 4: 3 -- Base 10: 3
- Base 4: 10 -- Base 10: 4
- Base 4: 11 -- Base 10: 5
- Base 4: 12 -- Base 10: 6
- Base 4: 13 -- Base 10: 7
- Base 4: 20 -- Base 10: 8
- Base 4: 21 -- Base 10: 9
- Base 4: 22 -- Base 10: 10
- **Base 4: 23 -- Base 10: 11**
- Base 4: 30 -- Base 10: 12

In order to convert Base 4 into Decimal, I can multiply each digit by its place value and sum the results.

For example,

If I convert `23` into decimal

- 3 X 4^0 = 3 X 1 = 3
- 2 X 4^1 = 2 X 4 = 8

---

3 + 8 = 11

In other notation of Base 4,

I can represent like 23<sub>4</sub> = 11

# Binary and computers

Computers represent and process all information using just two digits: 0, 1. These digits, known as bits, correspond to low (0) and high (1) voltage states in the computer hardware, enabling data storage and processing.

- 1 Kilobyte(1KB) 2^10 = 1,024
- 1 Megabyte(1MB) 2^20 = 1,048,576
- 1 Gigabyte(1GB) 2^30 = 1,073,741,824
- 1 Terabyte(1TB) 2^40 = 1,099,511,627,776

# Hexadecimal

It is Base 16.

# The modulo operator

# Converting from decimal to other bases

# Bicimals: fractional quantities in binary

# Binary cannot store all decimal numbers
