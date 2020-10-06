---
categories:
  - blog
title: Reverse Engineering Crypto Keys - WIP Notes
subtitle: A rudimentary guide as to how you could find a HEX crypto key in a sample - Work in Progress
tags: [programming, reverse_engineering, debug]
comments: false
---

# Preface
I am by no means a programming, or RE expert. But I'm going to have a go at explaining the issue of finding the needle in a haystack of an XOR key used to obfuscate files in a sample.

# Introduction
Find that needle in the haystack... I had a collegue ask for some help finding a crypto key for a challenge they were doing, I had no idea i'd be rehashing some of the basics of CompSCI and C Programming. 

## Background
According to DI Management, in cryptography programming, binary data is usually inputed to, or outputed from, as a bit string.

A bit string, might help you find the key. In this instance, we were given a hint about the function. Normally, it needs to be found as a needle in a haystack. Not fun... For finding it purely, I dont have a methodoly just yet, but, if you can find the reference to the key hopefully this provides and explination.

The second peice of background you might need, is to figure out how a "bit string" might be stored. For all intensive purposes a bit string in this case appears to be an array of hexidecimal characters that could be stored in one of two ways

### Local Variables
Local varibles, are those that exist only inside a function within C. In assembly this means the array is stored in the stack and appears to be stored as a dword. 

This means that your varible likely only exists inside that function, and therefore, any processing is likely to not show the exact reference to the data.

### Global Variables
Global variables are those that are available to any function within C. In assembly, this appears to mean they are pushed as a byte_reference on the stack.

This means, a key is likely poped back off the stack, so you can refer to it as 0xFFFFFFFF (with F being the reference to the original byte_reference) when decompiling. This means when an indivual function wants to process this data, it is likely to leave a reference to the location in the stack or the (.data) part of the object.

## Software Used
IDA - To follow through the code

Snowman - To look at the code rudimentally

Borland C++ 5.5.1 - To Compile

## Code

To find these results, I used the following code (The comments, refer to what I found in the disassembler)
```c

/*
Author: Samuel Freeman
Date: 16/06/20
Purpose: To decompile and show a simple prog
*/

#include <stdio.h>
#include <iostream>
//sub_401150
//global variable
unsigned char key3[4]={0xFA, 0xCE, 0xBE, 0xAD}; //push offset byte_40A128

int main()
{
	int num1 = 1 ; //ebx
	int char1 = 'A' ; //edi
	unsigned int key=0xFACE ; //edp + 4
        //local variable
        unsigned char key2[4]={0xFA, 0xCE, 0xBE, 0xED}; //mov eax, dword_40A12C
   		
	printf("This program uses local variables as a demo example for reverse engineering \n\n\n ");
			
	printf("Your integer (2 or 4 bytes (Number)) is: \n DECIMAL: %d \n HEX: 0x%X \n\n",num1, num1);		
	printf("Your char (ASCII Number (A in ASCII 65)) is: \n DECIMAL: %d \n HEX: 0x%X \n\n" ,char1, char1);		
	printf("Your key (Raw hex) is: \n DECIMAL:  %d \n HEX: 0x%X \n\n", key, key);
        printf("Long Key (Array of ASCII HEX Bites) (Raw hex) is: \n DECIMAL:  %d \n HEX: 0x%X \n\n", key2, key2);
        printf("note, the above item has just printed the address of the array... lets now print it\n HEX:0x");

        for (int i=0; i < sizeof(key2); ++i)
        {
            printf("%X",key2[i]);
        }		
		

        printf("\n\n Long Key (Array of ASCII HEX Bites) (Raw hex) is: \n DECIMAL:  %d \n HEX: 0x%X \n\n", key3, key3);
        printf("note, the above item has just printed the address of the array... lets now print it\n HEX:0x");

        for (int i=0; i < sizeof(key2); ++i)
        {
            printf("%X",key3[i]);
        }		
		return(0);
}

```



