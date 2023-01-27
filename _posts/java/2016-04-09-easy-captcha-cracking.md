---
title: Java实现简单的验证码破解
date: 2016-04-09 14:10:12
updated: 2016-04-09 14:10:12
tags: ['验证码', '破解']
categories: 
 - 开发语言
 - Java
---

 
功能仅限验证码规则的图片，有噪音或者文字倾斜均不实用


```java
package image;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

public class ImageDemo {
  // 定义数字
  int[][] number = {
    { 7, 11, 13, 8, 4, 4, 4, 8, 13, 11, 7 }, //0
    { 4, 4, 4, 15, 15, 15, 2, 2, 2 }, //1
    { 5, 6, 7, 7, 7, 7, 8, 9, 8, 6 }, //2
    { 4, 6, 6, 6, 6, 10, 14, 11, 7 }, //3
    { 3, 4, 4, 4, 5, 5, 4, 15, 15, 15, 2, 2 }, //4
    { 9, 9, 6, 6, 7, 8, 10, 9, 6 }, //5
    { 7, 11, 13, 8, 6, 6, 6, 8, 11, 10, 5 }, //6
    { 2, 4, 6, 8, 7, 7, 6, 6, 4, 3 }, //7
    { 4, 9, 13, 12, 7, 7, 7, 13, 12, 9, 4 }, //8
    { 4, 10, 11, 8, 6, 6, 7, 8, 13, 11, 7 }, //9
  };

  public int[][] grayImage() throws IOException {
    // 图片文件的路径
    File file = new File(
      "C:\\Users\\user\\Desktop\\DeCheckCode\\checkCode\\check9.jpg"
    );
    BufferedImage image = ImageIO.read(file);

    int width = image.getWidth();
    int height = image.getHeight();

    int box[][] = new int[height][width];
    for (int i = 0; i < width; i++) {
      int[] sum = new int[width];
      for (int j = 0; j < height; j++) {
        int rgb[][] = new int[height][width];

        rgb[j][i] = image.getRGB(i, j);
        int r = (rgb[j][i] & 16711680) >> 16;
        int g = (rgb[j][i] & 65280) >> 8;
        int b = (rgb[j][i] & 255);
        int black = (0 << 16) | (0 << 8) | 0;
        int white = (255 << 16) | (255 << 8) | 255;
        if (r * r + g * g + b * b < 3 * 128 * 128) {
          rgb[j][i] = black;
          box[j][i] = 1;
        } else {
          rgb[j][i] = white;
          box[j][i] = 0;
        }
        sum[i] += box[j][i];
        image.setRGB(i, j, rgb[j][i]);
      }
    }
    return box;
  }

  public int[] delNoise() throws IOException {
    int box[][] = grayImage();
    int box1[][] = box;
    for (int i = 0; i < box.length; i++) {
      for (int j = 0; j < box[i].length; j++) {
        if (j == box[i].length - 1) {
          System.out.println(box[i][j]);
        } else System.out.print(box[i][j]);
      }
    }
    int x = box1.length;
    int y = box1[0].length;
    int sum[] = new int[y];
    for (int m = 0; m < y; m++) {
      for (int n = 0; n < x; n++) {
        sum[m] += box1[n][m];
      }
    }
    return sum;
  }

  public void getDegital() throws IOException {
    int sum[] = delNoise();
    int[] m = new int[4];
    int[] n = new int[4];
    int i = 0;
    for (int z = 0; z < sum.length; z++) {
      if (z != 0 && sum[z - 1] == 0 && sum[z] != 0) {
        m[i] = z;
        //System.out.println("m["+i+"]="+m[i]);
      }
      if (sum[z] != 0) {
        n[i] = n[i] + 1;
        //System.out.println("n["+i+"]="+n[i]);
      }
      if (z != 0 && sum[z] == 0 && sum[z - 1] != 0) {
        i = i + 1;
      }
    }

    int[][] Degital = new int[4][];
    int[] code = new int[4];
    for (int b = 0; b < 4; b++) {
      Degital[b] = new int[n[b]];
      System.arraycopy(sum, m[b], Degital[b], 0, n[b]);

      for (int a = 0; a < 10; a++) {
        boolean e = true;
        if (Degital[b].length == number[a].length) {
          for (int d = 0; d < Degital[b].length; d++) {
            if (Degital[b][d] != number[a][d]) {
              e = e & false;
            } else e = e & true;
          }
          if (e) {
            code[b] = a;
            System.out.print(a + " ");
          }
        }
      }
    }
  }

  public static void main(String[] args) throws IOException {
    ImageDemo demo = new ImageDemo();
    //demo.grayImage();
    demo.getDegital();
  }
}
```
基本思路: 二值化，黑点转为1 白点转为0

![验证码图片](https://cdn.jsdelivr.net/gh/amosnothing/cdn/image/easy-captcha-cracking/2561.jpg)

000000000000000000000000000000000000000000000000000000000000
000000000000000000011111111100000000000000000000111000000000
000000000000000000011111111100000000000000000111111000000000
000000000000000000011000000000000000000000000111111000000000
000000000000000000011000000000000000000000000000111000000000
000000111111000000011000000000000001111100000000111000000000
000001111111110000011111000000000111111110000000111000000000
000001000001111000011111110000001111000010000000111000000000
000000000000111000000001111000001110000000000000111000000000
000000000000111000000000111100011100000000000000111000000000
000000000000111000000000011100011100111100000000111000000000
000000000001110000000000011100011111111110000000111000000000
000000000011100000000000011100011110001111000000111000000000
000000000111000000010000111000011100000111000000111000000000
000000001110000000011111111000011100000111000111111111000000
000000011100000000001111100000011100000111000111111111000000
000000111000000000000000000000001100000111000000000000000000
000001110000000000000000000000001110001110000000000000000000
000001111111111000000000000000000111111110000000000000000000
000001111111111000000000000000000011111000000000000000000000
2 5 6 1 

功力有限，暂时只研究出来了简单的破解，复杂点的需要日后慢慢研究，欢迎交流！