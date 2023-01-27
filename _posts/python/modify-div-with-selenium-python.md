---
title: Python-Selenium修改div元素的方法
date: 2017-10-13 18:43:12
updated: 2017-10-13 18:43:12
tags: ['python','自动化','selenium','修改div']
categories: 
 - 开发语言
 - Python
---

# 背景
在做UI自动化的时候，做好了登陆，但是进入到个人页，一直定位不到某个元素。很奇怪的是，手动操作完全没问题。经过调试了发现，进入个人页面后，<font color=#DC143C>需要点击的元素上面有2层div给挡住了</font>。

## 方法1

手动操作时元素可以点击，代码操作不可以。可以通过代码将这层div给点掉。

## 方法2

通过代码将这两层div的display属性改为none
我的代码如下：

```python
class OpenAccountLocators:
    # 这里有一层隐藏div 有点坑哈
    ACCOUNT_POP_JS1 = "document.getElementsByClassName('home-pop')[0].style.display='none'"
    # 大层的div
    ACCOUNT_POP_JS2 = "document.getElementsByClassName('g-mask-layer gray')[0].style.display='none'"
    # 填写开户信息页面元素
	... 此处省略一些代码


class OpenAccount(BasePage):
    def input_account_info(self, real_name, id_card, bank_card_no, bank_phone):
        # 进入我的账户页面
        time.sleep(2)
        # 第一层div
        self.driver.execute_script(OpenAccountLocators.ACCOUNT_POP_JS1)
        time.sleep(2)
        # 第二层div
        self.driver.execute_script(OpenAccountLocators.ACCOUNT_POP_JS2)
```

说明：<font color=#DC143C>还有一个比较坑的地方是，我设置2s的延时，偶尔还是会出现无法定位到我需要点击的那个元素，我猜测有两种可能性：</font>

1. 因为执行js的时候selenium需要去查找定位到这个div，再将div的display强制改为none，但是2s时间内未找到此div。（可能性不大）
2. 自动执行时，此元素xpath路径是{"method":"xpath","selector":"/html/body/div[8]/div[3]/div[1]/ul/li[1]/a"}，可能因为页面元素的变化而导致此元素的xpath改变了。为什么这么说？因为在手动操作的时候此元素的xpath路径是{"method":"xpath","selector":"/html/body/div[7]/div[3]/div[1]/ul/li[1]/a"}

后面抽时间细细研究一下这个问题。


## 总结

```python
# 如果div有id根据id来定位
driver.execute_script("document.getElementById('home-pop').style.display='none'")

# 如果div没有id根据className来定位 请注意获取到的是一个数组
driver.execute_script("document.getElementsByClassName('home-pop')[0].style.display='none'")
```