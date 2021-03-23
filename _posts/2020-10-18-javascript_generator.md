---
layout: post
title: javascript
subtitle: generator
tags: [javascript]
---


## Nguồn 

<a href= 'https://www.youtube.com/watch?v=JYd8eWId5gU'>


# Generator là gì: 

- Generator là object tạo ra từ Generator function  ??? ( má như cái qq)
- Generator không thể tạo ra trực tiếp, chỉ có thể tạo ra từ Generator function 

Ví dụ cho dễ hiểu: 

```javascrpit
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

**Kết quả:**
```sh
first value :
{ value: 1, done: false }
continue to run:
{ value: 2, done: false }
remuse:
{ value: 3, done: true }
```

Như ở trên có thể thấy Generator function có thể thực thi nhiều lần, nhìn thì giống như vòng lặp nhưng khác cái là có thể dừng lại và tiếp tục thực thi.
Chúng ta sẽ găp nhiều Generator function trong Redux Saga - thư viện được sử dụng để xử lý các side effects trong redux.


# Callback là gì?

Nói một cách đơn giản: Callback là một hàm sẽ được thực hiện sau khi một hàm khác đã thực hiện xong - vì thế nó có tên là callback.
