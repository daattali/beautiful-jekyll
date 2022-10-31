---
layout: post
title: Flake it till you make it
subtitle: 摘自Jeff Brown的Soulshaping。
cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/thumb.png
share-img: /assets/img/path.jpg
tags: [books, test]
---
jQuery学习笔记  
jQuery语法

    // 完整版语法
    $(document).ready(function(){
    })

    // 简写语法
    $(function(){
        
    })

    例子：点击事件在某个 <p> 元素上触发时，隐藏当前的 <p> 元素：

    <p>如果你点我，我就会消失。</p>
    <p>点我消失!</p>
    <p>点我也消失!</p>

    <script>
    $(document).ready(function(){
        $("p").click(function(){
            $(this).hide();
        });
    });
    </script>

    click() 方法是当按钮点击事件被触发时会调用一个函数