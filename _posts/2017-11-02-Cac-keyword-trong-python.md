---
layout: post
title: Các keyword trong Python
subtile: Python coding like a Pythonista
image: /img/2017-06-10-coding-style/CodingBia.png
tags: [Python, lap-trinh, programming-language, pep8, Pythonista]
categories: [Dev-Python]
date: 2017-11-02
---

Tiếp tục phần 1 đã [Cách code Python như một lập trình viên chuyên nghiệp](/2017-06-10-Python-coding-style/), phần 2 sẽ nói về các keyword trong Python.

Khi đặt tên biến (name) trong chương trình Python, cần chú ý không đặt trùng với các keyword trên.

Số lượng keyword rất ít nên cố nhớ và không vi phạm vào.

<table class="table">
<tbody><tr>
<td>False</td>
<td>class</td>
<td>finally</td>
<td>is</td>
<td>return</td>
</tr>
<tr>
<td>None</td>
<td>continue</td>
<td>for</td>
<td>lambda</td>
<td>try</td>
</tr>
<tr>
<td>True</td>
<td>def</td>
<td>from</td>
<td>nonlocal</td>
<td>while</td>
</tr>
<tr>
<td>and</td>
<td>del</td>
<td>global</td>
<td>not</td>
<td>with</td>
</tr>
<tr>
<td>as</td>
<td>el</td>
<td>if</td>
<td>or</td>
<td>yield</td>
</tr>
<tr>
<td>assert</td>
<td>else</td>
<td>import</td>
<td>pass</td>
<td>&nbsp;</td>
</tr>
<tr>
<td>break</td>
<td>except</td>
<td>in</td>
<td>raise</td>
<td>&nbsp;</td>
</tr>
</tbody></table>


Keywords trong Python có thể xem được qua các lệnh sau:

```Python
import keyword
print(keyword.kwlist)
['False', 'None', 'True', 'and', 'as', 'assert', 'break', 'class', 'continue', 'def', 'del', 'elif', 'else', 'except', 'finally', 'for', 'from', 'global', 'if', 'import', 'in', 'is', 'lambda', 'nonlocal', 'not', 'or', 'pass', 'raise', 'return', 'try', 'while', 'with', 'yield']
```

Ngoài ra còn một số từ khóa là built-in function của Python. Không nên đặt tên trùng với các từ khóa này.

Các từ khóa này có thể tham khảo tại [https://docs.python.org/3/library/functions.html](https://docs.python.org/3/library/functions.html)



<table border="1" class="docutils">
<colgroup>
<col width="21%">
<col width="19%">
<col width="20%">
<col width="18%">
<col width="22%">
</colgroup>
<thead valign="bottom">
<tr class="row-odd"><th class="head"></th>
<th class="head"></th>
<th class="head">Built-in Functions</th>
<th class="head"></th>
<th class="head"></th>
</tr>
</thead>
<tbody valign="top">
<tr class="row-even"><td><a class="reference internal" href="#abs" title="abs"><code class="xref py py-func docutils literal"><span class="pre">abs()</span></code></a></td>
<td><a class="reference internal" href="#func-dict"><code class="docutils literal"><span class="pre">dict()</span></code></a></td>
<td><a class="reference internal" href="#help" title="help"><code class="xref py py-func docutils literal"><span class="pre">help()</span></code></a></td>
<td><a class="reference internal" href="#min" title="min"><code class="xref py py-func docutils literal"><span class="pre">min()</span></code></a></td>
<td><a class="reference internal" href="#setattr" title="setattr"><code class="xref py py-func docutils literal"><span class="pre">setattr()</span></code></a></td>
</tr>
<tr class="row-odd"><td><a class="reference internal" href="#all" title="all"><code class="xref py py-func docutils literal"><span class="pre">all()</span></code></a></td>
<td><a class="reference internal" href="#dir" title="dir"><code class="xref py py-func docutils literal"><span class="pre">dir()</span></code></a></td>
<td><a class="reference internal" href="#hex" title="hex"><code class="xref py py-func docutils literal"><span class="pre">hex()</span></code></a></td>
<td><a class="reference internal" href="#next" title="next"><code class="xref py py-func docutils literal"><span class="pre">next()</span></code></a></td>
<td><a class="reference internal" href="#slice" title="slice"><code class="xref py py-func docutils literal"><span class="pre">slice()</span></code></a></td>
</tr>
<tr class="row-even"><td><a class="reference internal" href="#any" title="any"><code class="xref py py-func docutils literal"><span class="pre">any()</span></code></a></td>
<td><a class="reference internal" href="#divmod" title="divmod"><code class="xref py py-func docutils literal"><span class="pre">divmod()</span></code></a></td>
<td><a class="reference internal" href="#id" title="id"><code class="xref py py-func docutils literal"><span class="pre">id()</span></code></a></td>
<td><a class="reference internal" href="#object" title="object"><code class="xref py py-func docutils literal"><span class="pre">object()</span></code></a></td>
<td><a class="reference internal" href="#sorted" title="sorted"><code class="xref py py-func docutils literal"><span class="pre">sorted()</span></code></a></td>
</tr>
<tr class="row-odd"><td><a class="reference internal" href="#ascii" title="ascii"><code class="xref py py-func docutils literal"><span class="pre">ascii()</span></code></a></td>
<td><a class="reference internal" href="#enumerate" title="enumerate"><code class="xref py py-func docutils literal"><span class="pre">enumerate()</span></code></a></td>
<td><a class="reference internal" href="#input" title="input"><code class="xref py py-func docutils literal"><span class="pre">input()</span></code></a></td>
<td><a class="reference internal" href="#oct" title="oct"><code class="xref py py-func docutils literal"><span class="pre">oct()</span></code></a></td>
<td><a class="reference internal" href="#staticmethod" title="staticmethod"><code class="xref py py-func docutils literal"><span class="pre">staticmethod()</span></code></a></td>
</tr>
<tr class="row-even"><td><a class="reference internal" href="#bin" title="bin"><code class="xref py py-func docutils literal"><span class="pre">bin()</span></code></a></td>
<td><a class="reference internal" href="#eval" title="eval"><code class="xref py py-func docutils literal"><span class="pre">eval()</span></code></a></td>
<td><a class="reference internal" href="#int" title="int"><code class="xref py py-func docutils literal"><span class="pre">int()</span></code></a></td>
<td><a class="reference internal" href="#open" title="open"><code class="xref py py-func docutils literal"><span class="pre">open()</span></code></a></td>
<td><a class="reference internal" href="#func-str"><code class="docutils literal"><span class="pre">str()</span></code></a></td>
</tr>
<tr class="row-odd"><td><a class="reference internal" href="#bool" title="bool"><code class="xref py py-func docutils literal"><span class="pre">bool()</span></code></a></td>
<td><a class="reference internal" href="#exec" title="exec"><code class="xref py py-func docutils literal"><span class="pre">exec()</span></code></a></td>
<td><a class="reference internal" href="#isinstance" title="isinstance"><code class="xref py py-func docutils literal"><span class="pre">isinstance()</span></code></a></td>
<td><a class="reference internal" href="#ord" title="ord"><code class="xref py py-func docutils literal"><span class="pre">ord()</span></code></a></td>
<td><a class="reference internal" href="#sum" title="sum"><code class="xref py py-func docutils literal"><span class="pre"><span class="highlighted">sum</span>()</span></code></a></td>
</tr>
<tr class="row-even"><td><a class="reference internal" href="#func-bytearray"><code class="docutils literal"><span class="pre">bytearray()</span></code></a></td>
<td><a class="reference internal" href="#filter" title="filter"><code class="xref py py-func docutils literal"><span class="pre">filter()</span></code></a></td>
<td><a class="reference internal" href="#issubclass" title="issubclass"><code class="xref py py-func docutils literal"><span class="pre">issubclass()</span></code></a></td>
<td><a class="reference internal" href="#pow" title="pow"><code class="xref py py-func docutils literal"><span class="pre">pow()</span></code></a></td>
<td><a class="reference internal" href="#super" title="super"><code class="xref py py-func docutils literal"><span class="pre">super()</span></code></a></td>
</tr>
<tr class="row-odd"><td><a class="reference internal" href="#func-bytes"><code class="docutils literal"><span class="pre">bytes()</span></code></a></td>
<td><a class="reference internal" href="#float" title="float"><code class="xref py py-func docutils literal"><span class="pre">float()</span></code></a></td>
<td><a class="reference internal" href="#iter" title="iter"><code class="xref py py-func docutils literal"><span class="pre">iter()</span></code></a></td>
<td><a class="reference internal" href="#print" title="print"><code class="xref py py-func docutils literal"><span class="pre">print()</span></code></a></td>
<td><a class="reference internal" href="#func-tuple"><code class="docutils literal"><span class="pre">tuple()</span></code></a></td>
</tr>
<tr class="row-even"><td><a class="reference internal" href="#callable" title="callable"><code class="xref py py-func docutils literal"><span class="pre">callable()</span></code></a></td>
<td><a class="reference internal" href="#format" title="format"><code class="xref py py-func docutils literal"><span class="pre">format()</span></code></a></td>
<td><a class="reference internal" href="#len" title="len"><code class="xref py py-func docutils literal"><span class="pre">len()</span></code></a></td>
<td><a class="reference internal" href="#property" title="property"><code class="xref py py-func docutils literal"><span class="pre">property()</span></code></a></td>
<td><a class="reference internal" href="#type" title="type"><code class="xref py py-func docutils literal"><span class="pre">type()</span></code></a></td>
</tr>
<tr class="row-odd"><td><a class="reference internal" href="#chr" title="chr"><code class="xref py py-func docutils literal"><span class="pre">chr()</span></code></a></td>
<td><a class="reference internal" href="#func-frozenset"><code class="docutils literal"><span class="pre">frozenset()</span></code></a></td>
<td><a class="reference internal" href="#func-list"><code class="docutils literal"><span class="pre">list()</span></code></a></td>
<td><a class="reference internal" href="#func-range"><code class="docutils literal"><span class="pre">range()</span></code></a></td>
<td><a class="reference internal" href="#vars" title="vars"><code class="xref py py-func docutils literal"><span class="pre">vars()</span></code></a></td>
</tr>
<tr class="row-even"><td><a class="reference internal" href="#classmethod" title="classmethod"><code class="xref py py-func docutils literal"><span class="pre">classmethod()</span></code></a></td>
<td><a class="reference internal" href="#getattr" title="getattr"><code class="xref py py-func docutils literal"><span class="pre">getattr()</span></code></a></td>
<td><a class="reference internal" href="#locals" title="locals"><code class="xref py py-func docutils literal"><span class="pre">locals()</span></code></a></td>
<td><a class="reference internal" href="#repr" title="repr"><code class="xref py py-func docutils literal"><span class="pre">repr()</span></code></a></td>
<td><a class="reference internal" href="#zip" title="zip"><code class="xref py py-func docutils literal"><span class="pre">zip()</span></code></a></td>
</tr>
<tr class="row-odd"><td><a class="reference internal" href="#compile" title="compile"><code class="xref py py-func docutils literal"><span class="pre">compile()</span></code></a></td>
<td><a class="reference internal" href="#globals" title="globals"><code class="xref py py-func docutils literal"><span class="pre">globals()</span></code></a></td>
<td><a class="reference internal" href="#map" title="map"><code class="xref py py-func docutils literal"><span class="pre">map()</span></code></a></td>
<td><a class="reference internal" href="#reversed" title="reversed"><code class="xref py py-func docutils literal"><span class="pre">reversed()</span></code></a></td>
<td><a class="reference internal" href="#__import__" title="__import__"><code class="xref py py-func docutils literal"><span class="pre">__import__()</span></code></a></td>
</tr>
<tr class="row-even"><td><a class="reference internal" href="#complex" title="complex"><code class="xref py py-func docutils literal"><span class="pre">complex()</span></code></a></td>
<td><a class="reference internal" href="#hasattr" title="hasattr"><code class="xref py py-func docutils literal"><span class="pre">hasattr()</span></code></a></td>
<td><a class="reference internal" href="#max" title="max"><code class="xref py py-func docutils literal"><span class="pre">max()</span></code></a></td>
<td><a class="reference internal" href="#round" title="round"><code class="xref py py-func docutils literal"><span class="pre">round()</span></code></a></td>
<td>&nbsp;</td>
</tr>
<tr class="row-odd"><td><a class="reference internal" href="#delattr" title="delattr"><code class="xref py py-func docutils literal"><span class="pre">delattr()</span></code></a></td>
<td><a class="reference internal" href="#hash" title="hash"><code class="xref py py-func docutils literal"><span class="pre">hash()</span></code></a></td>
<td><a class="reference internal" href="#func-memoryview"><code class="docutils literal"><span class="pre">memoryview()</span></code></a></td>
<td><a class="reference internal" href="#func-set"><code class="docutils literal"><span class="pre">set()</span></code></a></td>
<td>&nbsp;</td>
</tr>
</tbody>
</table>

