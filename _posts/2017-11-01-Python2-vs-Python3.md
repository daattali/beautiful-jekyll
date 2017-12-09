---
layout: post
title: Một vài điểm khác biệt Python2 và Python3
image: /img/2017-06-01-Python/python.png
tags: [Python, lap-trinh, program-language]
categories: [Dev-Python]
date: 2017-11-01
---


Python2 đã dừng lại ở Python 2.7; Python3 thì vẫn đang tiếp tục phát triển. Phiên bản RC gần nhất là 3.6 và tiếp tục đang phát triển 3.7 beta. Python2 và Python3 có nhiều điểm khác biệt về syntax. Vậy nên học phiên bản nào Python 2 hay Python3 ?

Chắc chắn là một lập trình viên hay công ty sản xuất phần mềm thì chúng ta dễ dàng lựa chọn sử dụng Python3 thay cho Python2. Nhưng nếu là một newbie thì nên dùng bản nào để học ? 

Dưới đây là một số khác biệt cơ bản giữa Python2 và Python3:

1. Print statement vs. print function
2. Differences between range and xrange functions
2. Raising and handling Exceptions
3. Comparison of unorderable types
4. bytes vs string
5. Integer division
6. Unicode
7. dictionary method
8. Data Input


## print statement vs. print function

Khác biệt lớn nhất là: 

Python2 dùng `print`

Python3 dùng `print()`


<table class="table">
<tbody>
<tr>
<td>Python 2 </td>
<td>Python 3 </td>
</tr>
<tr>
<td><pre name="code" class="python">>>> print "Hello World"
Hello World</pre></td>
<td>
<pre name="code" class="python">>>> print("Hello World")
Hello World
</pre></td>
</tr>
<tr>
<td>
<pre name="code" class="python">>>> #print a newline
>>> print

</pre></td>
<td>
<pre name="code" class="python">>>> #print a newline,
>>> #using parentheses
>>> print()
  
</pre></td>
</tr>
<tr>
<td>
<pre name="code" class="python">>>> #add trailing comma to
>>> #remove newline
>>> print "No newline", 
    No newline
</pre></td>
<td><pre name="code" class="python">>>> #Appends nothing 
>>> #instead of a newline
>>> print("No newline", end="")
 No newline
>>> </pre></td>
</tr>
<tr>
<td>
<pre name="code" class="python">>>> #print to stderr
>>> print >>sys.stderr, "Error"   
  Traceback (most recent call last):
File "&lt;stdin>", line 1, in &lt;module>
NameError: name 'sys' is not defined</pre></td>
<td><pre name="code" class="python">>>> #Specifies the 
>>> #output buffer
>>>print("Error", file=sys.stderr)
>>> 
Traceback (most recent call last):
File "C:/Python34/test.py", 
 line 1, in &lt;module>
 print("Error", file=sys.stderr)
 NameError: name 'sys' 
 is not defined
>>></pre></td>
</tr>
<tr>
<td>&nbsp;</td>
<td><pre name="code" class="python">>>> #sep specifies the separator
>>> #here ',' is used as a separator
>>> print("Python", "JS", sep=",")
          Python,JS</pre></td>
</tr>
<tr>
<td>&nbsp;</td>
<td><pre name="code" class="python">>>> #prints as XYZ, there
>>> #is nothing in sep
>>> print("X", "Y", "Z", sep="")
    XYZ</pre></td>
</tr>
<tr>
<td>&nbsp;</td>
<td><pre name="code" class="python">>>> #flush the output buffer
>>> print("Python", flush=True)
  Python</pre></td>
</tr>
</tbody></table>
<hr>


## Differences between range and xrange functions
<hr>
<table class="table table-bordered">
<tbody><tr>
<th>Python 2</th>
<th>Python 3</th>
</tr>
<tr>
<td><pre name="code" class="python">>>> range(1, 10)
   [1, 2, 3, 4, 5, 6, 7, 8, 9]
</pre></td>
<td><pre name="code" class="python">>>> range(1, 10)
   range(1, 10)
>>> 
</pre></td>
</tr>
<tr>
<td><pre name="code" class="python">>>> xrange(1, 10)
xrange(1, 15)</pre></td>
<td><pre name="code" class="python">>>> xrange(1, 10)
  Traceback (most recent call last):
File "&lt;pyshell#9>", 
line 1, in &lt;module>
xrange(1, 10)
NameError: name 'xrange' 
is not defined
      </pre></td>
</tr>
<tr>
<td><pre name="code" class="python">>>> isinstance(xrange(1, 15), xrange)
True
>>>
</pre></td>
<td><pre name="code" class="python">>>> isinstance(range(1, 15), range)
True
>>> </pre></td>
</tr>
</tbody></table>
<hr>

## Raising and handling Exceptions
<hr/>
<table class="table table-bordered">
<tbody><tr>
<th>Python 2</th>
<th>Python 3</th>
</tr>
<tr>
<td><pre name="code" class="python">>>> 3 &lt; 5.5
    True
>>></pre></td>
<td><pre name="code" class="python">>>> 3 &lt; 5.5
True
>>></pre></td>
</tr>
<tr>
<td>
<pre name="code" class="python">>>> [3, 5] > 'xyz'
      False
>>>
</pre></td>
<td>
<pre name="code" class="python">>>> [3, 5] > 'xyz'
 Traceback (most recent call last):
 File "&lt;pyshell#14>", 
 line 1, in &lt;module>
 [3, 5] > 'xyz'
TypeError: unorderable types: 
list() > str()
>>>
</pre></td>
</tr>
<tr>
<td><pre name="code" class="python">>>> (3, 5) > 'xyz'
   True
>>></pre></td>
<td>
<pre name="code" class="python">>>> (3, 5) > 'xyz'
Traceback (most recent call last):
File "&lt;pyshell#15>", 
line 1, in &lt;module>
(3, 5) > 'xyz'
TypeError: unorderable types: 
tuple() > str()>>> 
</pre></td>
</tr>
<tr>
<td>
<pre name="code" class="python">>>> [3, 5] > (3, 5)
      False
>>>
</pre></td>
<td>
<pre name="code" class="python">>>> [3, 5] > (3, 5)
  Traceback (most recent call last):
File "&lt;pyshell#21>", 
line 1, in &lt;module>
[3, 5] > (3, 5)
TypeError: unorderable types: 
list() > tuple()
>>>
</pre></td>
</tr>
<tr>
<td>
<pre name="code" class="python">>>> 50 &lt; [2, 'x'] &lt; 'xyz' &lt; (2, 'x')
	   True
>>>
</pre></td>
<td>
<pre name="code" class="python">>>> 50 &lt; [2, 'x'] &lt; 'xyz' &lt; (2, 'x')
  Traceback (most recent call last):
File "&lt;pyshell#23>", 
line 1, in &lt;module>
50 &lt; [2, 'x'] &lt; 'xyz' &lt; (2, 'x')
TypeError: unorderable types: 
int() &lt; list()
>>></pre></td>
</tr>
</tbody></table>

<hr>

## Comparison of unorderable types
<hr>
<table class="table table-bordered">
<tbody><tr>
<th>Python 2</th>
<th>Python 3</th>
</tr>
<tr>
<td><pre name="code" class="python">>>> print "[2, 3]>'xyz'= ", [2, 3]>'xyz'
[2, 3]>'xyz' =  False
>>> print "(2, 3)>'xyz' = ", (2, 3)>'xyz'
(2, 3)>'xyz' =  True
>>> print "[2, 3]>(2, 3) = ", [2, 3]>(2, 3)
[2, 3] > (2, 3) =  False
</pre></td>
<td><pre name="code" class="python">print("[1, 2]>'foo' = ", [1, 2]>'foo')
print("(1, 2)>'foo' = ", (1, 2)>'foo')
print("[1, 2]>(1, 2) = ", [1, 2]>(1, 2))
Traceback (most recent call last):
  File "C:/Python34/test.py", line 1, 
  in <module>
    print("[1, 2] > 'foo' = ", 
	[1, 2] > 'foo')
TypeError: unorderable types: 
list() > str()
</module></pre></td>
</tr>
</tbody></table>
<hr>

## bytes vs string
<hr>
<table class="table table-bordered">
<tbody><tr>
<th>Python 2</th>
<th>Python 3</th>
</tr>
<tr>
<td>
<pre name="code" class="python">>>> a = "Python"
>>> len(a)
    6
>>> a[0]
    'P'
>>>
</pre></td>
<td><pre name="code" class="python">>>> a = "Python"
>>> len(a)
   6
>>> a[0]
   'P'
>>></pre></td>
</tr>
<tr>
<td>&nbsp;</td>
<td><pre name="code" class="python">>>> 
#To treat a string as a 
#sequence of bytes, 
#you need to cast:
>>> a = bytes("Python", "utf-8")
>>> a
   b'Python'
>>> a[0]
   80
>>>
</pre></td>
</tr>
<tr>
<td>&nbsp;</td>
<td><pre name="code" class="python">>>> #bytes(foo, 'utf-8') means to encode&nbsp;&lt;em>foo&lt;/em>
>>> #in UTF-8. treat the result as a 
>>> #sequence of unsigned  8bit integers. You can 
>>> #also convert bytes to a string,
>>> #as following
>>> a = bytes("Python", "utf-8")
>>> b = str(a, "utf-8")
>>> b
    'Python'
>>></pre></td>
</tr>
</tbody></table>
<hr>

## Integer division

<hr>
<table class="table table-bordered">
<tbody><tr>
<th>Python 2</th>
<th>Python 3</th>
</tr>
<tr>
<td><pre name="code" class="python">>>> import sys
>>> print(sys.version)
       2.7.9 (default, Apr  2 2015, 
	   15:33:21)[GCC 4.9.2]
>>> print "6/3 =", 6/3
    6/3 = 2
>>> print "6//3 =", 6//3
    6//3 = 2
>>> print "6/3.0 =", 6/3.0
    6/3.0 = 2.0
>>> print "6//3.0 =", 6//3.0
    6//3.0 = 2.0
>>>
</pre></td>
<td><pre name="code" class="python">>>> import sys
>>> print(sys.version)
       3.4.2 (v3.4.2:ab2c023a9432, 
	    Oct  6 2014, 22:15:05)
	    [MSC v.1600 32 bit (Intel)]
>>>
>>> print("6/3 =", 6/3)
    6/3 = 2.0
>>> print("6//3 =", 6//3)
    6//3 = 2
>>> print("6/3.0 =", 6/3.0)
    6/3.0 = 2.0
>>> print("6//3.0 =", 6//3.0)
    6//3.0 = 2.0
>>> </pre></td>
</tr>
</tbody></table>
<hr>

## Unicode 

Python2 không hỗ trợ Unicode, muốn in ra Unicode phải làm nhiều bước khác nhau.

<table class="table table-bordered">
<tbody><tr>
<th>Python 2</th>
<th>Python 3</th>
</tr>
<tr>
<td><pre name="code" class="python">>>> import sys
>>> print(sys.version)
   2.7.9 (default, Apr  2 2015, 
   15:33:21) GCC 4.9.2]
>>> print type(unicode
("Python Unicode"))
&lt;type 'unicode'>
>>>
</pre></td>
<td><pre name="code" class="python">>>> import sys
>>> print(sys.version)
  3.4.2 (v3.4.2:ab2c023a9432,
   Oct  6 2014, 22:15:05) 
   MSC v.1600 32 bit (Intel)]
>>></pre></td>
</tr>
<tr>
<td><pre name="code" class="python">>>> print type(b"Python")
   &lt;type 'str'>
>>></pre></td>
<td>&nbsp;</td>
</tr>
<tr>
<td><pre name="code" class="python">>>> print "Python" + b" Unicode"
Python Unicode
>>></pre></td>
<td><pre name="code" class="python">>>> print(" Python", type(b" Unicode"))
Python &lt;class 'bytes'>
>>></pre></td>
</tr>
</tbody></table>
<hr>

## dictionary method

<hr>
In Python 2 
dict.iteritems(): Return an iterator over the dictionary's (key, value) pairs.

In Python 3 
dict.items(): Return a copy of the dictionary’s list of (key, value) pairs.

<table class="table table-bordered">
<tbody><tr>
<th>Python 2</th>
<th>Python 3</th>
</tr>
<tr>
<td><pre name="code" class="python">>>> x = {1: "red", 2: "blue"}
>>> print(x)
   {1: 'red', 2: 'blue'}
>>> print(x.items())
dict_items([(1, 'red'), (2, 'blue')])
>>> print(x.iteritems())
    Traceback (most recent call last):
File "&lt;stdin>", line 1, in &lt;module>
AttributeError: 'dict' object has no 
attribute 'iteritems'
>>> print([i for i in x.iteritems()])
 [(1, 'red'), (2, 'blue')]
>>></pre></td>
<td><pre name="code" class="python">>>> x = {1: "red", 2: "blue"}
>>> print(x)
  {1: 'red', 2: 'blue'}
>>> print(x.items)
&lt;built-in method items of dict object 
at 0x7fe191a89748>
>>> print(x.items())
dict_items([(1, 'red'), (2, 'blue')])
>>> print([i for i in x.items()])
  [(1, 'red'), (2, 'blue')]
>>>
</pre></td>
</tr>
<tr>
<td>&nbsp;</td>
<td>&nbsp;</td>
</tr>
</tbody></table>

Trong Python2: dict.keys, dict.values, dict.items trả về một list. 
Python3 không trả về một list mà trả về object dict_items. Muốn chuyển về list cần thực hiện convert sang dạng list

<table class="table table-bordered">
<tbody><tr>
<td><pre name="code" class="python">>>> #In Python 2&nbsp;dict.has_key()
&nbsp;is used to test.
>>> #whether the dict has 
a certain key.
>>> x = {1: "red", 2: "blue"}
>>> print(x.has_key(1))
True
>>>
</pre></td>
<td>
<pre name="code" class="python">>>> #But this method has been
>>> #removed in Python 3.
>>> #Instead, the&nbsp;in&nbsp;operator
>>> #Is used.
>>> x = {1: "red", 2: "blue"}
>>> print(a.has_key(1))
 #Don't run it, unless you want this:
 Traceback (most recent call last):
 File "&lt;stdin>", line 1, in &lt;module> 
 AttributeError: 'dict' object has
 no attribute 'has_key'
>>> print(1 in x)
        True
>>>
</pre></td>
</tr>
</tbody></table>

<hr>

## Data Input
<hr>


<table class="table table-bordered">
<tbody><tr>
<th>Python2</th>
<th>Python3</th>
</tr>
<tr>
<td><pre name="code" class="python">>>>data_input2 = raw_input()
</pre></td>
<td><pre name="code" class="python">>>>data_input3 = input()</pre></td>
</tr>
</tbody></table>

