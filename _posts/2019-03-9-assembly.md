---
layout: post
title: অ্যাসেম্বলি ? পাশ করার ছোট প্রয়াস ! 
tags: [Assembly]
permalink: /_asm_/
---

# `কেন এটা ?`
অ্যাসেম্বলি এর ঝামেলা মুক্ত করার উপায় বের করার জন্য ! `কোড` নিয়েই কথা হবে । 

# যোগ এর প্রোগ্রাম দিয়ে শুরু হোক
```asm
INCLUDE 'EMU8086.INC'   ;
.MODEL SMALL            ;
.STACK 100H             ;  এগুলু ফরয ! মুখস্ত করে নেন ।
.CODE                   ;
MAIN PROC               ; 

    PRINT 'ENTER X : '      ;  PRINT SIMPLY PRINT WHICH IS GIVEN BY YOU 
1   MOV AH,1                ;
2   INT 21H                 ;   INPUT X
3   MOV BL,AL
    
    PRINTN 
    PRINT 'ENTER Y : '
4   MOV AH,1                ;  
5   INT 21H                 ;   INPUT Y
6   MOV BH,AL
    
7   ADD BL,BH               ; ADD means BL = BL + BH 
8   SUB BL,30H              ; SUB means BL = BL - 30H
    
    PRINTN                  ; PRINTN REFERS TO NEW LINE
    PRINT 'RESULT : '
9     MOV AH,2              ;   OUTPUT 
10    MOV DL,BL             ;   OUTPUT 
11    INT 21H
```
> হাবিজাবি কি এসব ? 
 
>> দেখি কি হয় । 

*1-3 ইনপুট নেয়ার জন্য ।* 
MOV AH,1 এটা ব্যাবহার হয়  ইনপুট  জন্য INT 21H ঐ ইনপুটটা পর্দায় দেখায় ।
আবার MOV ? KENO ? একবার ইনপুট নেয়ার পড় জায়গাটা পূর্ণ আছে তাই ওটাকে সরিয়ে নিয়ে আবার পুনরায় ইনপুট নেয়ার জন্য জায়গা খালী করলাম ;
এতটুক জানলে পাশ করে ফেলবেন । [[ আরও বলতে গেলে AH ,AL থেকে যোগসহ অনেক কাজ করা যাবে না । ]]
 
*4-6 একী কাজ হইসে ।*

*7 এ BH,BL যোগ করলাম ।*

*8 এ বিয়োগ করলাম কারণ অ্যাসেম্বলি ASCI নিয়ে কাজ করে । বেশী জানতে চাইলে হবে না ?*

*9 আউটপুট দেখানোর জন্য ।*

*10 BL থেকে প্রিন্ট করানো যায় না তাই DL এ MOV ।*

*INT 21H আপনার প্রত্যাশিত  আউটপুট পর্দায় দেখাবে ।*

*আজ খতম । বূঝে থাকলে বিয়োগটা চেষ্টা করেন ।*
