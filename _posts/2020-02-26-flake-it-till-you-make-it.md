---
layout: post
title: 06월 03일
subtitle: //변수 ,자료형, 함수, 조건문 ,반복문
cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/thumb.png
share-img: /assets/img/path.jpg
tags: [books, test]
---

U//변수 ,자료형, 함수, 조건문 ,반복문
undefined

/*자료형*/

undefined
let a_list =['수박',참외','배']
VM961:1 Uncaught SyntaxError: Unexpected string
let a_list =['수박','참외','배']
undefined
a_list
(3) ["수박", "참외", "배"]
a_list(1)
VM1021:1 Uncaught TypeError: a_list is not a function
    at <anonymous>:1:1
a_list[0]
"수박"
a_list.push('감')
4
a_list.pop('감')
"감"
a_list.pop('수박')
"배"
a_list
(2) ["수박", "참외"]
// pop 은 LIFO 룰에 따름
undefined

﻿/*사전형*/
​let a_dic = {'name':'bob','age':27}
undefined
let a_dict = {'name':'bob','age':27}
undefined
let a_dict['name']
VM1836:1 Uncaught SyntaxError: Unexpected token '['
a_dict['name']
"bob"
a_dict['age']
27
a_dict['height']= 180
180
a_dict
{name: "bob", age: 27, height: 180}
a_dict['fruits']=a_list
(2) ["수박", "참외"]
a_dict
{name: "bob", age: 27, height: 180, fruits: Array(2)}age: 27fruits: (2) ["수박", "참외"]height: 180name: "bob"__proto__: Object
//이중리스트
a != 100
false
let myemail= 'dpdtydz@donga.ac.kr'
undefined
myemail.split('@')
(2) ["dpdtydz", "donga.ac.kr"]
myemail.split('@')[1]
"donga.ac.kr"
myemail.split('@')[1].split('.')
(3) ["donga", "ac", "kr"]
myemail.split('@')[1].split('.')[10]
undefined
myemail.split('@')[1].split('.')[0]
"donga"

/* 함수*/

숙제햇음
