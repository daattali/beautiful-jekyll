---
layout: post
title: javascript
subtitle: generator
tags: [javascript]
---


## Nguồn 

https://www.youtube.com/watch?v=JYd8eWId5gU


# Generator là gì: 

- Generator là object tạo ra từ Generator function  ??? ( má như cái qq)
- Generator không thể tạo ra trực tiếp, chỉ có thể tạo ra từ Generator function 

```
function* gen() {
	console.log('first value :');
	yield 1;

	console.log('continue to run:');
	yield 2;
	
	console.log('remuse:');
	return 3;
}

const newId = gen();

console.log(newId.next()); 
console.log(newId.next()); 
console.log(newId.next()); 
```

```sh
first value :
{ value: 1, done: false }
continue to run:
{ value: 2, done: false }
remuse:
{ value: 3, done: true }
```
