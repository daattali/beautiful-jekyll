---
layout: post
title: Number bases - Essential math
subtitle: In order to understand basic crypto, let's deep dive into number bases
# cover-img: /assets/img/banditlogo.png
thumbnail-img: /assets/img/crypto/crypto.png
# share-img: /assets/img/path.jpg
tags: [number bases, crypto, computer basics]
comments: true
author: Lantana Park
---

# Why I care about number bases?

Since number bases are fundamental concept in computer science that underpins everything from **the basic operation of computers** to advanced topics in software development.

# How to count the bases(Base 2, Base 4 and Base 10)?

## What is bit and byte?

- **Bit** is a binary digit because it is alway on one of two states(0 - low voltage, 1 - high voltage).

- **Byte** is a group of binary digits or bits, consisting 8 digits in binary.

![difference](/assets/img/crypto/bits-and-bytes-units-of-data_1_en.jpeg)

## How to count numbers in Binary(Base 2) and covert to Decimal(Base10)

**Base 2** is a numeric method of representing numbers using only two numbers, **0** and **1**. This is foundational to digital computing and eletronics, as it reflects state of computer hardware conponents, which can be either **off(0)** or **on(1)**. knowing binary helps programmers understand how a computer "thinks" and processes information at the most fundamental level. It's especially used in creating and optimizing programs that work closely with the computer's hardware.

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

1 X 2<sup>0</sup> = 1<br/>
1 X 2<sup>1</sup> = 2<br/>
0 X 2<sup>2</sup> = 0<br/>
1 X 2<sup>3</sup> = 8

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

In order to convert Quaternary(Base 4) into Decimal(Base 10), I can multiply each digit by its place value and sum the results.

For example,

If I convert `23` into decimal

3 X 4<sup>0</sup> = 3 X 1 = 3<br/>
2 X 4<sup>1</sup> = 2 X 4 = 8

---

3 + 8 = 11

In other notation of Quaternary(Base 4),

I can represent like 23<sub>4</sub> = 11

# Binary and computers

Computers represent and process all information using just two digits: 0, 1. These digits, known as bits, correspond to low (0) and high (1) voltage states in the computer hardware, enabling data storage and processing.

1 Kilobyte(1KB) 2<sup>10</sup> = 1,024<br/>
1 Megabyte(1MB) 2<sup>20</sup> = 1,048,576<br/>
1 Gigabyte(1GB) 2<sup>30</sup> = 1,073,741,824<br/>
1 Terabyte(1TB) 2<sup>40</sup> = 1,099,511,627,776

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

Hexadecimal is particularly useful in computer science and digital electronics because it provides a more human-friendly way of representing binary data. Since 16 is a power of 2 (specifically, 2<sup>4</sup>), each hexadecimal digit can represent four binary digits (bits). This makes conversion between binary and hexadecimal straightforward and much easier than converting between binary and decimal.

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

1 (hexadecimal) = 0001 (binary)<br/>
A (hexadecimal) = 1010 (binary)<br/>
3 (hexadecimal) = 0011 (binary)<br/>
F (hexadecimal) = 1111 (binary)

Therefore, **1A3F** in hexadecimal is **0001101000111111** in binary.

Furthermore, hexadecimal can be translated into text string using ASCII (American Standard Code for Information Interchange) table.

1.  Break down the hexadecimal code

    - Each pair of hexadecimal digits represents one byte (8 bits), and in the context of text, one byte usually corresponds to one character in the ASCII table. For example, in **4D 61 69 6E**:

    **4D** is one byte<br/>
    **61** is one byte<br/>
    **69** is one byte<br/>
    **6e** is one byte

    2<sup>4</sup> = 8 bits

2.  Convert hexadecimal to decimal

    4D → 77<br/>
    61 → 97<br/>
    69 → 105<br/>
    6E → 110

3.  Look up each decimal value in the ASCII table below to get the corresponding character

    77 → M<br/>
    97 → a<br/>
    105 → i<br/>
    110 → n

Thus, **4D 61 69 6E** in hexadecimal is **Main** in text string based on ASCII

![ASCII](/assets/img/crypto/Screenshot%202024-04-07%20at%2011.42.23.png)

# What is Base 64?

Base 2, 4, and 10 are used for numerical representation and arithmetic operations. Base 64, however, is used for encoding binary data into a textual format, serving as a bridge between binary data and systems that handle text.

To show how it encode binary data, I am going to encode `lantana` using base64

1. Convert Characters to ASCII values

![ASCII](/assets/img/crypto/Screenshot%202024-04-07%20at%2011.42.23.png)

l = 108</br>
a = 97</br>
n = 110</br>
t = 116</br>
a = 97</br>
n = 110</br>
a = 97

2. Convert ASCII values to binary

I used arithmetic method to convert the ASCII values to binary

For instance, in the `108` value

108 / 2 = 54 remainder 0
54 / 2 = 27 remainder 0
27 / 2 = 13 remainder 1
13 / 2 = 6 remainder 1
6 / 2 = 3 remainder 0
3 / 2 = 1 remainder 1
1 / 2 = 0 remainder 1

And then appended `0` to represent this converted binary value as a full byte(8 bits)

`108` can be converted into `01101100`

108 = 01101100</br>
97 = 01100001</br>
110 = 01101110</br>
116 = 01110100</br>
97 = 01100001</br>
110 = 01101110</br>
97 = 01100001

3. Concatenate Binary Values

I concatenated the binary strings into one long string.

`01101100 01100001 01101110 01110100 01100001 01101110 01100001`

4. Divide into 6-bit Groups

I divide this concatenated binary string into 6-bit groups. If the total number of bits isn't a multiple of 6 digits, I padded it with zeros on the right

`011011 000110 000101 101110 011101 000110 000101 101110 011000 01` (Division)

`011011 000110 000101 101110 011101 000110 000101 101110 011000 010000` (Padding to ensure 6 digits in wach group)

5. Convert Each 6-bit Group to a Base64 Value

Using the Base64 index talbe, I converted each 6-digit group to its corresponding Base64 character.

011011 = b</br>
000110 = G</br>
000101 = F</br>
101110 = u</br>
011101 = t</br>
000110 = G</br>
000101 = F</br>
101110 = u</br>
011000 = Y</br>
010000 = Q

`bGFudGFuYQ`

6. Padding the Base64 encoded string

Since the original binary string didn't divide evenly into 6-bit groups, I added two "=" characters to the end of the Base64 string to indicate the padding.

`bGFudGFuYQ==`

# The modulo operator

With modular arithmetic, we can convert freely each numeral method.

The picture below is to understand what is modular arithmetic.

![modular](/assets/img/crypto/Screenshot%202024-04-07%20at%2013.28.07.png)

# Converting from decimal to other bases

If I convert **11(decimal)** into **binary(base2)**

11/2 = 5R**1**<br/>
5/2 = 2r**1**<br/>
2/2 = 1r**0**<br/>
1/2 = 0r**1**<br/>

And then I can read off by reading **backwards** along the remainders

**11** in Decimal **1011<sub>2</sub>**

Moreover, if I change 11(Decimal) into Quaternary(Base 4)

11/4 = 2R**3**<br/>
2/4 = 0R**2**<br/>

And then I can read off by reading **backwards** along the remainders

**11** in Decimal is converted into <sub>23</sub>4

# Bicimals: fractional quantities in binary

The concept of "Bicimals", refers to the way fractional numbers are represented in binary (Base2).

In short, the digits after the decimal point are called "bicimals"

For example, when we represent 12.75(adding decimals after the decimal point) === 1275/100

in Base 10(decimal),

(1 X 10) + (2 X 1) + (7 X 0.1) + (5 X 0.01) = 12.75

in Base 2(binary) 1100.11 can be calculated to 12.75

(1 X 8) + (1 X 4) + (0 X 2) + (0 X 1) + (1 X 1/2) + (1 X 1/4)

= 8 + 4 + 0.5 + 0.25

= 12 + 0.75

= 12.75

So, the binary coding of 12.75 is 1100.11<sub>2</sub>

# Binary cannot store all decimal numbers

When I try to represent 0.3 (or 3/10) in binary, I ended up with a series that goes on forever: 0.30000000000000004... and so on. This series is binary's attempt to get as close as possible to 0.3 but it never quite gets there, just like we cannot never perfectly fill a square box with round oranges.

I made an example using javaScript because it uses binary floating-point for numeric values, which leads to the same kind of precision issues.

![greatExample](/assets/img/crypto/Screenshot%202024-04-07%20at%2014.56.13.png)

However, computer represent 0.5 precisely. Because, to perfectly represent 0.5 (which is half of 1) in binary, we only need one digit after the decimal point, making the binary number 0.1. This shows us that binary 0.1 is exactly equal to decimal 0.5, hence the answer to the question is 1.

![greatExample2](/assets/img/crypto/Screenshot%202024-04-07%20at%2016.18.35.png)
