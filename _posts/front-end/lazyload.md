---
title: 延迟加载(Lazyload)三种实现方式
date: 2018-04-20 00:33:12
tags: ['延迟加载','lazyload']
categories: 
 - 开发语言
 - HTML/JS/CSS
---

# 延迟加载(Lazyload)

注明:文章转载于 [有酒 - 知乎](https://zhuanlan.zhihu.com/p/25455672)

>定义：延迟加载也称为惰性加载，即在长网页中延迟加载图像。用户滚动到它们之前，视口外的图像不会加载。这与图像预加载相反，在长网页上使用延迟加载将使网页加载更快。在某些情况下，它还可以帮助减少服务器负载。

举个例子来说明，当打开淘宝首页的时候，只有在浏览器窗口里的图片才会被加载，当你滚动首页向下滑的时候，进入视口内的图片才会被加载，而其它从未进入视口的图像不会也不会加载。
那么延迟加载有什么好处：

首先它能提升用户的体验，试想一下，如果打开页面的时候就将页面上所有的图片全部获取加载，如果图片数量较大，对于用户来说简直就是灾难，会出现卡顿现象，影响用户体验。
有选择性地请求图片，这样能明显减少了服务器的压力和流量，也能够减小浏览器的负担。
那么下面就介绍延迟加载的三种实现方式：

## 方式1

首先将页面上的图片的 src 属性设为 loading.gif，而图片的真实路径则设置在 data-src 属性中，页面滚动的时候计算图片的位置与滚动的位置，当图片出现在浏览器视口内时，将图片的 src 属性设置为 data-src 的值，这样，就可以实现延迟加载。

下面是具体的实现代码：

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Lazyload 1</title>
    <style>
        img {
	    display: block;
	    margin-bottom: 50px;
	    height: 200px;
	}
    </style>
</head>
<body>
    <img src="images/loading.gif" data-src="images/1.png">
    <img src="images/loading.gif" data-src="images/2.png">
    <img src="images/loading.gif" data-src="images/3.png">
    <img src="images/loading.gif" data-src="images/4.png">
    <img src="images/loading.gif" data-src="images/5.png">
    <img src="images/loading.gif" data-src="images/6.png">
    <img src="images/loading.gif" data-src="images/7.png">
    <img src="images/loading.gif" data-src="images/8.png">
    <img src="images/loading.gif" data-src="images/9.png">
    <img src="images/loading.gif" data-src="images/10.png">
    <img src="images/loading.gif" data-src="images/11.png">
    <img src="images/loading.gif" data-src="images/12.png">
    <script>
        function lazyload() {
	    var images = document.getElementsByTagName('img');
	    var len    = images.length;
	    var n      = 0;      //存储图片加载到的位置，避免每次都从第一张图片开始遍历		
	    return function() {
		var seeHeight = document.documentElement.clientHeight;
		var scrollTop = document.documentElement.scrollTop || document.body.scrollTop;
		for(var i = n; i < len; i++) {
		    if(images[i].offsetTop < seeHeight + scrollTop) {
		        if(images[i].getAttribute('src') === 'images/loading.gif') {
			     images[i].src = images[i].getAttribute('data-src');
			}
			n = n + 1;
		     }
		}
	    }
	}
	var loadImages = lazyload();
	loadImages();          //初始化首页的页面图片
	window.addEventListener('scroll', loadImages, false);
    </script>
</body>
</html>
```

比较 image 的 offsetTop 与 seeHeight + scrollTop 的大小，当小于时则说明图片已经出现过在视口中，这时候继续判断图片是否已经替换过，如果没有替换过，则进行替换。

你可以拷贝我的代码去进行实验，但是请确保 HTML 同目录下有 images 目录并且含有 1~12.png 和 loading.gif。

需要提及的是变量 n 是用来保存已经加载的图片数量，避免每次都从第一张图片开始遍历，提升性能。上面的代码用到了 JS 闭包的知识，如果你不太熟悉的话，可以自行百度一下。

## 方式2


上面的代码是没什么问题，但是性能偏差。如果直接将函数绑定在 scroll 事件上，当页面滚动时，函数会被高频触发，这非常影响浏览器的性能。我粗略地估计一下，当简单地滚动一下页面，函数至少触发了十来次，这显然是十分没必要的。
所以在做事件绑定的时候，可以对 lazyload 函数进行函数节流（throttle）与函数去抖（debounce）处理。
这里我并不再另外介绍这两种方案，如果你想了解的话可以阅读：[JS魔法堂：函数节流（throttle）与函数去抖（debounce） - ^_^肥仔John](https://link.zhihu.com/?target=http://www.cnblogs.com/fsjohnhuang/p/4147810.html)

简单说来：

Debounce：一部电梯停在某一个楼层，当有一个人进来后，20秒后自动关门，这20秒的等待期间，又一个人按了电梯进来，这20秒又重新计算，直到电梯关门那一刻才算是响应了事件。
Throttle：好比一台自动的饮料机，按拿铁按钮，在出饮料的过程中，不管按多少这个按钮，都不会连续出饮料，中间按钮的响应会被忽略，必须要等这一杯的容量全部出完之后，再按拿铁按钮才会出下一杯。
下面就是经过 throttle 处理后的代码：

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Lazyload 2</title>
    <style>
	img {
	    display: block;
	    margin-bottom: 50px;
	    height: 200px;
	}
    </style>
</head>
<body>
    <img src="images/loading.gif" data-src="images/1.png">
    <img src="images/loading.gif" data-src="images/2.png">
    <img src="images/loading.gif" data-src="images/3.png">
    <img src="images/loading.gif" data-src="images/4.png">
    <img src="images/loading.gif" data-src="images/5.png">
    <img src="images/loading.gif" data-src="images/6.png">
    <img src="images/loading.gif" data-src="images/7.png">
    <img src="images/loading.gif" data-src="images/8.png">
    <img src="images/loading.gif" data-src="images/9.png">
    <img src="images/loading.gif" data-src="images/10.png">
    <img src="images/loading.gif" data-src="images/11.png">
    <img src="images/loading.gif" data-src="images/12.png">
    <script>
	function throttle(fn, delay, atleast) {
	    var timeout = null,
		startTime = new Date();
	    return function() {
		var curTime = new Date();
		clearTimeout(timeout);
		if(curTime - startTime >= atleast) {
		    fn();
		    startTime = curTime;
		}else {
		    timeout = setTimeout(fn, delay);
		}
	    }
	}
	function lazyload() {
	    var images = document.getElementsByTagName('img');
	    var len    = images.length;
	    var n      = 0;      //存储图片加载到的位置，避免每次都从第一张图片开始遍历		
	    return function() {
		var seeHeight = document.documentElement.clientHeight;
		var scrollTop = document.documentElement.scrollTop || document.body.scrollTop;
		for(var i = n; i < len; i++) {
		    if(images[i].offsetTop < seeHeight + scrollTop) {
		        if(images[i].getAttribute('src') === 'images/loading.gif') {
			     images[i].src = images[i].getAttribute('data-src');
		        }
			n = n + 1;
		     }
		}
	    }
	}
	var loadImages = lazyload();
	loadImages();          //初始化首页的页面图片
	window.addEventListener('scroll', throttle(loadImages, 500, 1000), false);
    </script>
</body>
</html>
```

设置了 500ms 的延迟，和 1000ms 的间隔，当超过 1000ms 未触发该函数，则立即执行该函数，不然则延迟 500ms 执行该函数。


参考链接：[实现图片懒加载(lazyload)](https://link.zhihu.com/?target=http://i.jakeyu.top/2016/11/26/%25E5%25AE%259E%25E7%258E%25B0%25E5%259B%25BE%25E7%2589%2587%25E6%2587%2592%25E5%258A%25A0%25E8%25BD%25BD/)

## 方式3 

使用 IntersectionObserver API

目前有一个新的 IntersectionObserver API，可以自动"观察"元素是否可见，Chrome 51+ 已经支持。

这里不过多介绍 IntersectionObserver API 的详细使用，感兴趣可以另外阅读下面的文章：


>[IntersectionObserver API 使用教程](https://link.zhihu.com/?target=http://www.ruanyifeng.com/blog/2016/11/intersectionobserver_api.html)
[Intersection Observer API](https://link.zhihu.com/?target=https://developer.mozilla.org/en-US/docs/Web/API/Intersection_Observer_API)

实现代码：简洁，但是浏览器尚未全部实现。

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Lazyload 3</title>
	<style>
	    img {
		display: block;
		margin-bottom: 50px;
		width: 800px;
	    }
    </style>
</head>
<body>
    <img src="images/loading.gif" data-src="images/1.png">
    <img src="images/loading.gif" data-src="images/2.png">
    <img src="images/loading.gif" data-src="images/3.png">
    <img src="images/loading.gif" data-src="images/4.png">
    <img src="images/loading.gif" data-src="images/5.png">
    <img src="images/loading.gif" data-src="images/6.png">
    <img src="images/loading.gif" data-src="images/7.png">
    <img src="images/loading.gif" data-src="images/8.png">
    <img src="images/loading.gif" data-src="images/9.png">
    <img src="images/loading.gif" data-src="images/10.png">
    <img src="images/loading.gif" data-src="images/11.png">
    <img src="images/loading.gif" data-src="images/12.png">
    <script>
	function query(selector) {
	    return Array.from(document.querySelectorAll(selector));
	}
	var io = new IntersectionObserver(function(items) {
	    items.forEach(function(item) {
		var target = item.target;
		if(target.getAttribute('src') == 'images/loading.gif') {
		    target.src = target.getAttribute('data-src');
		}
	    })
	});
	query('img').forEach(function(item) {
	    io.observe(item);
	});
    </script>
</body>
</html>
```

IntersectionObserver 传入一个回调函数，当其观察到元素集合出现时候，则会执行该函数。
io.observe 即要观察的元素，要一个个添加才可以。io 管理的是一个数组，当元素出现或消失的时候，数组添加或删除该元素，并且执行该回调函数。