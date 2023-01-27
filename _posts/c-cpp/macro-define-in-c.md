---
title: 【C语言】宏定义的使用
date: 2019-12-24 09:24:13
tags: ['c语言','宏定义','c基础']
categories: 
 - 开发语言
 - C/C++
---

# 宏定义形式和使用

宏定义格式

```c
#define your_macro_name the_replacement
```

对于#define中的名字`your_macro_name`, 和变量名的命名方式相同, 替换文本`the_replacement` 可以是任意字符串.
通常define指令只占用一行, 如果被替换文本比较长, 可以是用反斜杠`\`换行.

## 定义常量
```c
#define e 2.71828
```
## 任意文本
```c
#define forever for( ; ; )
```
使用宏forever
```c
int main() {
    forever{
        printf(1);
    }
    return 1;
}
```

## 带参数宏定义

```c
#define max(a,b) ((a)>(b)?(a):(b))
```

使用宏max
```c
int main() {
    int x = max(1, 2);
    printf("%d",x);
    return 1;
}
```

## 实参即是实参字符

形参是不可以用带引号的字符串替换, 但是如果想达到传入实参就是所对应的实参字符(即给实参自动加上引号)呢?
比如实参传入 `amos`（不带引号）,  而我实际想用的是`"amos"`

```c
#define dprintf("hello " #str)
```

使用dprint
```c
int main() {
    dprint(amos);
    return 1;
}
```
调用该宏的时候, 该宏被扩展为:

```c
printf("hello " "amos")  
```
等价于
```c  
printf("hello amos")  
```
## 连接实参

```c
#define paste(name) char_##name
```
```c
int main() {
     char paste(a);
     char paste(b);
     // char_a char_b 无需定义, 定义已经在宏内完成
     char_a = 'x';
     char_b = 'y';
     printf("%c%c\n", char_a, char_b) ;
     return 1;
}
```

## 多行宏替换

```c
#define loop(a, b) for(int i=0;i<(b);++i)\
{\
(a)+=i;\
}\
```

loop宏的使用:

```c
int main() {
    int a = 100, b = 100;
    loop(a, b);
    printf("%d\n", a);
    return 1;
}
```
打印为 `5050`

# 注意事项

## 尽可能为每个形参加上括号
```c
#define square(x) x*x

int main() {
    printf("%d\n", square(1 + 5));
    return 1;
}
```
上面这段代码, 感觉上应该打印 `36`, 实际上不是的
因为宏替换为:

```c
printf("%d\n", 1+5*1+5)
```
结果是`11`, 所以尽可能的加上括号.

## 取消宏定义
```c
#define square(x) x*x
#undef square
```