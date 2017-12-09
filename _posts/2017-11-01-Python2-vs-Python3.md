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
<td><pre name="code" class="python">&gt;&gt;&gt; print "Hello World"
Hello World</pre></td>
<td>
<pre name="code" class="python">&gt;&gt;&gt; print("Hello World")
Hello World
</pre></td>
</tr>
<tr>
<td>
<pre name="code" class="python">&gt;&gt;&gt; #print a newline
&gt;&gt;&gt; print

</pre></td>
<td>
<pre name="code" class="python">&gt;&gt;&gt; #print a newline,
&gt;&gt;&gt; #using parentheses
&gt;&gt;&gt; print()
  
</pre></td>
</tr>
<tr>
<td>
<pre name="code" class="python">&gt;&gt;&gt; #add trailing comma to
&gt;&gt;&gt; #remove newline
&gt;&gt;&gt; print "No newline", 
    No newline
</pre></td>
<td><pre name="code" class="python">&gt;&gt;&gt; #Appends nothing 
&gt;&gt;&gt; #instead of a newline
&gt;&gt;&gt; print("No newline", end="")
 No newline
&gt;&gt;&gt; </pre></td>
</tr>
<tr>
<td>
<pre name="code" class="python">&gt;&gt;&gt; #print to stderr
&gt;&gt;&gt; print &gt;&gt;sys.stderr, "Error"   
  Traceback (most recent call last):
File "&lt;stdin&gt;", line 1, in &lt;module&gt;
NameError: name 'sys' is not defined</pre></td>
<td><pre name="code" class="python">&gt;&gt;&gt; #Specifies the 
&gt;&gt;&gt; #output buffer
&gt;&gt;&gt;print("Error", file=sys.stderr)
&gt;&gt;&gt; 
Traceback (most recent call last):
File "C:/Python34/test.py", 
 line 1, in &lt;module&gt;
 print("Error", file=sys.stderr)
 NameError: name 'sys' 
 is not defined
&gt;&gt;&gt;</pre></td>
</tr>
<tr>
<td>&nbsp;</td>
<td><pre name="code" class="python">&gt;&gt;&gt; #sep specifies the separator
&gt;&gt;&gt; #here ',' is used as a separator
&gt;&gt;&gt; print("Python", "JS", sep=",")
          Python,JS</pre></td>
</tr>
<tr>
<td>&nbsp;</td>
<td><pre name="code" class="python">&gt;&gt;&gt; #prints as XYZ, there
&gt;&gt;&gt; #is nothing in sep
&gt;&gt;&gt; print("X", "Y", "Z", sep="")
    XYZ</pre></td>
</tr>
<tr>
<td>&nbsp;</td>
<td><pre name="code" class="python">&gt;&gt;&gt; #flush the output buffer
&gt;&gt;&gt; print("Python", flush=True)
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
<td><pre name="code" class="python">&gt;&gt;&gt; range(1, 10)
   [1, 2, 3, 4, 5, 6, 7, 8, 9]
</pre></td>
<td><pre name="code" class="python">&gt;&gt;&gt; range(1, 10)
   range(1, 10)
&gt;&gt;&gt; 
</pre></td>
</tr>
<tr>
<td><pre name="code" class="python">&gt;&gt;&gt; xrange(1, 10)
xrange(1, 15)</pre></td>
<td><pre name="code" class="python">&gt;&gt;&gt; xrange(1, 10)
  Traceback (most recent call last):
File "&lt;pyshell#9&gt;", 
line 1, in &lt;module&gt;
xrange(1, 10)
NameError: name 'xrange' 
is not defined
      </pre></td>
</tr>
<tr>
<td><pre name="code" class="python">&gt;&gt;&gt; isinstance(xrange(1, 15), xrange)
True
&gt;&gt;&gt;
</pre></td>
<td><pre name="code" class="python">&gt;&gt;&gt; isinstance(range(1, 15), range)
True
&gt;&gt;&gt; </pre></td>
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
<td><pre name="code" class="python">&gt;&gt;&gt; 3 &lt; 5.5
    True
&gt;&gt;&gt;</pre></td>
<td><pre name="code" class="python">	&gt;&gt;&gt; 3 &lt; 5.5
True
&gt;&gt;&gt;</pre></td>
</tr>
<tr>
<td>
<pre name="code" class="python">&gt;&gt;&gt; [3, 5] &gt; 'xyz'
      False
&gt;&gt;&gt;
</pre></td>
<td>
<pre name="code" class="python">&gt;&gt;&gt; [3, 5] &gt; 'xyz'
 Traceback (most recent call last):
 File "&lt;pyshell#14&gt;", 
 line 1, in &lt;module&gt;
 [3, 5] &gt; 'xyz'
TypeError: unorderable types: 
list() &gt; str()
&gt;&gt;&gt;
</pre></td>
</tr>
<tr>
<td><pre name="code" class="python">&gt;&gt;&gt; (3, 5) &gt; 'xyz'
   True
&gt;&gt;&gt;</pre></td>
<td>
<pre name="code" class="python">&gt;&gt;&gt; (3, 5) &gt; 'xyz'
Traceback (most recent call last):
File "&lt;pyshell#15&gt;", 
line 1, in &lt;module&gt;
(3, 5) &gt; 'xyz'
TypeError: unorderable types: 
tuple() &gt; str()&gt;&gt;&gt; 
</pre></td>
</tr>
<tr>
<td>
<pre name="code" class="python">&gt;&gt;&gt; [3, 5] &gt; (3, 5)
      False
&gt;&gt;&gt;
</pre></td>
<td>
<pre name="code" class="python">&gt;&gt;&gt; [3, 5] &gt; (3, 5)
  Traceback (most recent call last):
File "&lt;pyshell#21&gt;", 
line 1, in &lt;module&gt;
[3, 5] &gt; (3, 5)
TypeError: unorderable types: 
list() &gt; tuple()
&gt;&gt;&gt;
</pre></td>
</tr>
<tr>
<td>
<pre name="code" class="python">&gt;&gt;&gt; 50 &lt; [2, 'x'] &lt; 'xyz' &lt; (2, 'x')
	   True
&gt;&gt;&gt;
</pre></td>
<td>
<pre name="code" class="python">&gt;&gt;&gt; 50 &lt; [2, 'x'] &lt; 'xyz' &lt; (2, 'x')
  Traceback (most recent call last):
File "&lt;pyshell#23&gt;", 
line 1, in &lt;module&gt;
50 &lt; [2, 'x'] &lt; 'xyz' &lt; (2, 'x')
TypeError: unorderable types: 
int() &lt; list()
&gt;&gt;&gt;</pre></td>
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
<td><pre name="code" class="python">&gt;&gt;&gt; print "[2, 3]&gt;'xyz'= ", [2, 3]&gt;'xyz'
[2, 3]&gt;'xyz' =  False
&gt;&gt;&gt; print "(2, 3)&gt;'xyz' = ", (2, 3)&gt;'xyz'
(2, 3)&gt;'xyz' =  True
&gt;&gt;&gt; print "[2, 3]&gt;(2, 3) = ", [2, 3]&gt;(2, 3)
[2, 3] &gt; (2, 3) =  False
</pre></td>
<td><pre name="code" class="python">print("[1, 2]&gt;'foo' = ", [1, 2]&gt;'foo')
print("(1, 2)&gt;'foo' = ", (1, 2)&gt;'foo')
print("[1, 2]&gt;(1, 2) = ", [1, 2]&gt;(1, 2))
Traceback (most recent call last):
  File "C:/Python34/test.py", line 1, 
  in <module>
    print("[1, 2] &gt; 'foo' = ", 
	[1, 2] &gt; 'foo')
TypeError: unorderable types: 
list() &gt; str()
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
<pre name="code" class="python">&gt;&gt;&gt; a = "Python"
&gt;&gt;&gt; len(a)
    6
&gt;&gt;&gt; a[0]
    'P'
&gt;&gt;&gt;
</pre></td>
<td><pre name="code" class="python">&gt;&gt;&gt; a = "Python"
&gt;&gt;&gt; len(a)
   6
&gt;&gt;&gt; a[0]
   'P'
&gt;&gt;&gt;</pre></td>
</tr>
<tr>
<td>&nbsp;</td>
<td><pre name="code" class="python">&gt;&gt;&gt; 
#To treat a string as a 
#sequence of bytes, 
#you need to cast:
&gt;&gt;&gt; a = bytes("Python", "utf-8")
&gt;&gt;&gt; a
   b'Python'
&gt;&gt;&gt; a[0]
   80
&gt;&gt;&gt;
</pre></td>
</tr>
<tr>
<td>&nbsp;</td>
<td><pre name="code" class="python">&gt;&gt;&gt; #bytes(foo, 'utf-8') means to encode&nbsp;&lt;em&gt;foo&lt;/em&gt;
&gt;&gt;&gt; #in UTF-8. treat the result as a 
&gt;&gt;&gt; #sequence of unsigned  8bit integers. You can 
&gt;&gt;&gt; #also convert bytes to a string,
&gt;&gt;&gt; #as following
&gt;&gt;&gt; a = bytes("Python", "utf-8")
&gt;&gt;&gt; b = str(a, "utf-8")
&gt;&gt;&gt; b
    'Python'
&gt;&gt;&gt;</pre></td>
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
<td><pre name="code" class="python">&gt;&gt;&gt; import sys
&gt;&gt;&gt; print(sys.version)
       2.7.9 (default, Apr  2 2015, 
	   15:33:21)[GCC 4.9.2]
&gt;&gt;&gt; print "6/3 =", 6/3
    6/3 = 2
&gt;&gt;&gt; print "6//3 =", 6//3
    6//3 = 2
&gt;&gt;&gt; print "6/3.0 =", 6/3.0
    6/3.0 = 2.0
&gt;&gt;&gt; print "6//3.0 =", 6//3.0
    6//3.0 = 2.0
&gt;&gt;&gt;
</pre></td>
<td><pre name="code" class="python">&gt;&gt;&gt; import sys
&gt;&gt;&gt; print(sys.version)
       3.4.2 (v3.4.2:ab2c023a9432, 
	    Oct  6 2014, 22:15:05)
	    [MSC v.1600 32 bit (Intel)]
&gt;&gt;&gt;
&gt;&gt;&gt; print("6/3 =", 6/3)
    6/3 = 2.0
&gt;&gt;&gt; print("6//3 =", 6//3)
    6//3 = 2
&gt;&gt;&gt; print("6/3.0 =", 6/3.0)
    6/3.0 = 2.0
&gt;&gt;&gt; print("6//3.0 =", 6//3.0)
    6//3.0 = 2.0
&gt;&gt;&gt; </pre></td>
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
<td><pre name="code" class="python">&gt;&gt;&gt; import sys
&gt;&gt;&gt; print(sys.version)
   2.7.9 (default, Apr  2 2015, 
   15:33:21) GCC 4.9.2]
&gt;&gt;&gt; print type(unicode
("Python Unicode"))
&lt;type 'unicode'&gt;
&gt;&gt;&gt;
</pre></td>
<td><pre name="code" class="python">&gt;&gt;&gt; import sys
&gt;&gt;&gt; print(sys.version)
  3.4.2 (v3.4.2:ab2c023a9432,
   Oct  6 2014, 22:15:05) 
   MSC v.1600 32 bit (Intel)]
&gt;&gt;&gt;</pre></td>
</tr>
<tr>
<td><pre name="code" class="python">&gt;&gt;&gt; print type(b"Python")
   &lt;type 'str'&gt;
&gt;&gt;&gt;</pre></td>
<td>&nbsp;</td>
</tr>
<tr>
<td><pre name="code" class="python">&gt;&gt;&gt; print "Python" + b" Unicode"
Python Unicode
&gt;&gt;&gt;</pre></td>
<td><pre name="code" class="python">&gt;&gt;&gt; print(" Python", type(b" Unicode"))
Python &lt;class 'bytes'&gt;
&gt;&gt;&gt;</pre></td>
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
<td><pre name="code" class="python">&gt;&gt;&gt; x = {1: "red", 2: "blue"}
&gt;&gt;&gt; print(x)
   {1: 'red', 2: 'blue'}
&gt;&gt;&gt; print(x.items())
dict_items([(1, 'red'), (2, 'blue')])
&gt;&gt;&gt; print(x.iteritems())
    Traceback (most recent call last):
File "&lt;stdin&gt;", line 1, in &lt;module&gt;
AttributeError: 'dict' object has no 
attribute 'iteritems'
&gt;&gt;&gt; print([i for i in x.iteritems()])
 [(1, 'red'), (2, 'blue')]
&gt;&gt;&gt;</pre></td>
<td><pre name="code" class="python">&gt;&gt;&gt; x = {1: "red", 2: "blue"}
&gt;&gt;&gt; print(x)
  {1: 'red', 2: 'blue'}
&gt;&gt;&gt; print(x.items)
&lt;built-in method items of dict object 
at 0x7fe191a89748&gt;
&gt;&gt;&gt; print(x.items())
dict_items([(1, 'red'), (2, 'blue')])
&gt;&gt;&gt; print([i for i in x.items()])
  [(1, 'red'), (2, 'blue')]
&gt;&gt;&gt;
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
<td><pre name="code" class="python">&gt;&gt;&gt; #In Python 2&nbsp;dict.has_key()
&nbsp;is used to test.
&gt;&gt;&gt; #whether the dict has 
a certain key.
&gt;&gt;&gt; x = {1: "red", 2: "blue"}
&gt;&gt;&gt; print(x.has_key(1))
True
&gt;&gt;&gt;
</pre></td>
<td>
<pre name="code" class="python">&gt;&gt;&gt; #But this method has been
&gt;&gt;&gt; #removed in Python 3.
&gt;&gt;&gt; #Instead, the&nbsp;in&nbsp;operator
&gt;&gt;&gt; #Is used.
&gt;&gt;&gt; x = {1: "red", 2: "blue"}
&gt;&gt;&gt; print(a.has_key(1))
 #Don't run it, unless you want this:
 Traceback (most recent call last):
 File "&lt;stdin&gt;", line 1, in &lt;module&gt; 
 AttributeError: 'dict' object has
 no attribute 'has_key'
&gt;&gt;&gt; print(1 in x)
        True
&gt;&gt;&gt;
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
<td><pre name="code" class="python">&gt;&gt;&gt;data_input2 = raw_input()
</pre></td>
<td><pre name="code" class="python">&gt;&gt;&gt;data_input3 = input()</pre></td>
</tr>
</tbody></table>

