---
layout: post
title: Number bases - Essential math
subtitle: In order to understand basic crypto, let's deep dive into number bases
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

## How to count numbers in Binary(Base 2) and covert to Decimal(Base10)

**Base 2** is a numeric method of representing numbers using only two numbers **0, 1.** This is foundational to digital computing and eletronics, as it reflects state of computer hardware conponents, which can be either off(0) or on (1). knowing binary helps programmers understand how a computer "thinks" and processes information at the most fundamental level. It's especially used in creating and optimizing programs that work closely with the computer's hardware.

**Base 10** is a nummeric method of representting numbers using 10 digit numbers from **0 to 9**. Even though computers naturally "speak" and "think" in binary, they need to interact with humans who use the decimal numeral system. So, when we're making software that people will use, such as apps on a phone or computer programs, we often work in decimal to make inputs (like typing numbers into a calculator app) and outputs (like seeing your bank balance) understandable.

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

1 X 2^0 = 1<br/>
1 X 2^1 = 2<br/>
0 X 2^2 = 0<br/>
1 X 2^3 = 8

---

1 + 2 + 0 + 8 = 11

In other notation of Base 2,

I can represent like 1011<sub>2</sub> = 11

## How to count numbers in Quanternary(Base 4) and convert to decimal (Base 10)

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

3 X 4^0 = 3 X 1 = 3..
2 X 4^1 = 2 X 4 = 8

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

Hexadecimal, also known as **base 16**, is a numeral method that extends beyond the familiar decimal (base 10) method by using sixteen distinct symbols for its digits instead of ten. While the decimal system uses the digits 0 through 9, the hexadecimal system uses 0 through 9 to represent values zero to nine, and then it uses the letters A through F to represent values ten to fifteen. Hexadecimal acts as a bridge between the binary world of computers and the more understandable decimal system for humans. It's much easier to read and write for us, especially when dealing with large amounts of binary data, because it makes a compact way to write longer binary sequences.

Here's how the digits in hexadecimal correspond to decimal values:

- 0-9 are the same as in decimal
- A represents 10(decimal)
- B represents 11(decimal)
- C represents 12(decimal)
- D represents 13(decimal)
- E represents 14(decimal)
- F represents 15(decimal)

Hexadecimal is particularly useful in computer science and digital electronics because it provides a more human-friendly way of representing binary data. Since 16 is a power of 2 (specifically, 2^4), each hexadecimal digit can represent four binary digits (bits). This makes conversion between binary and hexadecimal straightforward and much easier than converting between binary and decimal. For instance, the binary sequence 1010 1101 is easily broken down into two groups of four (1010 and 1101), which directly convert to hexadecimal digits AD.

## Translate binary into hexadecimal vice versa

Translating between binary (base 2) and hexadecimal (base 16) is a straightforward process because each hexadecimal digit exactly corresponds to four binary digits (bits). Here I can show you how these can be traslated each other.

From Binary to Hexadecimal,

- **0000 (Binary) = 0 (Hexadecimal) = 0 (Decimal)**
- 0001 = 1 = 1
- 0010 = 2 = 2
- 0011 = 3 = 3
- 0100 = 4 = 4
- 0101 = 5 = 5
- 0110 = 6 = 6
- 0111 = 7 = 7
- 1000 = 8 = 8
- 1001 = 9 = 9
- 1010 = A = 10
- 1011 = B = 11
- 1100 = C = 12
- 1101 = D = 13
- 1110 = E = 14
- 1111 = F = 15
- 10000 = 10 = 16
- 10001 = 11 = 17
- 11010 = 1A = 26
- 11011 = 1B = 27
- 100000 = 20 = 32
- 100001 = 21 = 33
- 100010 = 22 = 34

Binary: **110101101011**

1. Group into four: **11 0101 1010 1011**
2. Add leading zeros to the leftmost group: **0011 0101 1010 1011**
3. Convert each group: **3(0011) 5(0101) A(1010) B(1011)**

So, the binary number 110101101011 is 35AB in hexadecimal.

From Hexdecimal to Binary,

Hexadecimal: **1A3F**

1. Convert each hexadecimal digit to binary:

1 (hexadecimal) = 0001 (binary)..
A (hexadecimal) = 1010 (binary)..
3 (hexadecimal) = 0011 (binary)..
F (hexadecimal) = 1111 (binary)

Therefore, **1A3F** in hexadecimal is **0001101000111111** in binary.

Furthermore, hexadecimal can be translated into text string using ASCII (American Standard Code for Information Interchange) table.

1.  Break down the hexadecimal code

    - Each pair of hexadecimal digits represents one byte (8 bits), and in the context of text, one byte usually corresponds to one character in the ASCII table. For example, in **4D 61 69 6E**:

      **4D** is one byte..
      **61** is one byte..
      **69** is one byte..
      **6e** is one byte

      2^4 = 8 bits

2.  Convert hexadecimal to decimal

        4D → 77..
        61 → 97..
        69 → 105..
        6E → 110

3.  Look up each decimal value in the ASCII table below to get the corresponding character

        77 → M..
        97 → a..
        105 → i..
        110 → n

Thus, **4D 61 69 6E** in hexadecimal is **Main** in text string based on ASCII

![ASCII](/assets/img/crypto/Screenshot%202024-04-07%20at%2011.42.23.png)



# The modulo operator

# Converting from decimal to other bases

# Bicimals: fractional quantities in binary

# Binary cannot store all decimal numbers
