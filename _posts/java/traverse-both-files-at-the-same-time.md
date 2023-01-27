---
title: JAVA while同时遍历两个文件的坑
date: 2019-01-25 17:30:11
updated: 2019-01-25 17:30:11
tags: ['java','java文件遍历','while嵌套']
categories: 
 - 开发语言
 - Java
---

# 背景

有两个文件，第一个文件长这样：
>110000,北京市
110101,东城区
...

第二个文件长这样：
>沪L,上海市
京M,北京市
...



需求：遍历两个文件，第1个文件内的城市名如果在第2个文件里找到，那么在第1个文件内行后添加上车牌号，比如：
>110000,北京市,京M
...

代码使用的是两个while循环，同时遍历每一行，若是城市名一致，则将车牌号加到一个文件行后。直到两个文件遍历完毕。问题是，每一次都只遍历到了第1个文件的第一行。象这种有成千上万行的文件，如果要调试的话，也比较麻烦，问题找到好久都没有找到。具体代码省略，可以看下面的示例代码。

# 发现问题

先创建两个文件`one.txt`,`two.txt`
文件内容如下：
>A in file1
B in file1
C in file1

>α in file2
β in file2
γ in file2
θ in file2

```java
package com.amos.learn;

import java.io.*;
import java.net.URL;
import java.text.MessageFormat;

/**
 * @author chenjun
 */
public class TraverseFile {

    private static File fileInResourceInstance(String fileName) {

        URL url = TraverseFile.class.getClassLoader().getResource(fileName);
        if (null == url) {
            throw new IllegalArgumentException(MessageFormat.format("file-[{0}] not found", fileName));
        }
        return new File(url.getPath());
    }


    private static BufferedReader readerResourcesFile(String fileName) throws FileNotFoundException {
        // 读取源文件
        File file = fileInResourceInstance(fileName);
        BufferedReader reader;
        reader = new BufferedReader(new FileReader(file));
        return reader;
    }

	// 重点看这一个方法
    private static void testTwoFileTraverse() throws IOException {

        BufferedReader reader1 = readerResourcesFile("one.txt");
        BufferedReader reader2 = readerResourcesFile("two.txt");

        String tmpStr1;
        String tmpStr2;

        // 遍历第一个文件 一共3行
        while (( tmpStr1 = reader1.readLine()) != null) {
            System.out.println("file1:" + tmpStr1);
            // 遍历第二个文件 一共4行
            while ((tmpStr2 = reader2.readLine()) != null) {
                // 3 * 4 = 12 行
                System.out.println(tmpStr1 + " * " + tmpStr2);
            }
        }
    }

    public static void main(String[] args) throws IOException {
        testTwoFileTraverse();
    }
}
```

打印结果：
>file1:A in file1
A in file1 * α in file2
A in file1 * β in file2
A in file1 * γ in file2
A in file1 * θ in file2
file1:B in file1
file1:C in file1

可以看出来，在第一个文件遍历到第二行的时候，第二个while循环就已经没有再执行了！因为`reader2.readLine()`已经遍历完，结果为null了！

# 解决问题

修改`testTwoFileTraverse`方法，读取文件1, while每循环一次都要遍历一次文件2.

```java
private static void testTwoFileTraverse() throws IOException {

    BufferedReader reader1 = readerResourcesFile("one.txt");
    String tmpStr1;
    // 遍历第一个文件 一共3行
    while ((tmpStr1 = reader1.readLine()) != null) {
        System.out.println("file1:" + tmpStr1);

        BufferedReader reader2 = readerResourcesFile("two.txt");
        String tmpStr2;
        // 遍历第二个文件 一共4行
        while ((tmpStr2 = reader2.readLine()) != null) {
            // 3 * 4 = 12 行
            System.out.println(tmpStr1 + " * " + tmpStr2);
        }
    }
}
```
打印结果：
>file1:A in file1
A in file1 * α in file2
A in file1 * β in file2
A in file1 * γ in file2
A in file1 * θ in file2
file1:B in file1
B in file1 * α in file2
B in file1 * β in file2
B in file1 * γ in file2
B in file1 * θ in file2
file1:C in file1
C in file1 * α in file2
C in file1 * β in file2
C in file1 * γ in file2
C in file1 * θ in file2
