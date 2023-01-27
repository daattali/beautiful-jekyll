---
title: JS实现动态添加和删除div（基于bootstrap）
date: 2018-10-29 16:21:39
tags: ['添加div','删除div','添加删除元素','添加删除div','javascript']
categories: 
 - 开发语言
 - HTML/JS/CSS
---

## 背景
需要做一个页面，页面表单可以输入参数，点击确认按钮可以发请求给某个接口。但是接口的某个字段是数组类型，所以在页面上需要实现添加或者删除元素的功能。
## 实现
### html
前端是基于`bootstrap4.0`.
!-- more -->
```html
<form id="form" role="form" method="post" class="custom-control">
        <div class="form-inline">
        <label for="details" class="custom-control-label col-md-2">还款明细</label>
        <button type="button" class="button btn-light" id="add-btn" onclick="add_div()">添加明细</button>
        <button type="button" class="button btn-light" id="del-btn" onclick="del_div()">删除明细</button>
    </div>
    <div class="form-group" id="details">
        <div class="form-inline">
            <label for="receivable" class="custom-control-label col-md-3">应收金额</label>
            <input type="text" class="form-control" id="receivable" value="" placeholder="应收金额 单位分"/>
        </div>
        <div class="form-inline">
            <label for="period" class="custom-control-label col-md-3">还款期数</label>
            <input type="text" class="form-control" id="period" value="" placeholder="还款期数"/>
        </div>
        <div class="form-inline">
            <label for="kind" class="custom-control-label col-md-3">还款科目</label>
            <input type="text" class="form-control" id="kind" value="" placeholder="还款科目"/>
        </div>
    </div>
</form>
```

### JS

```javascript
<script type="text/javascript">
    var detail_div = 1;
    function add_div() {
        var e = document.getElementById("details");
        var div = document.createElement("div");
        div.className = "form-group";
        div.id = "details" + detail_div;
        div.innerHTML = e.innerHTML;
        document.getElementById("form").appendChild(div);
        detail_div++;
    }

    function del_div() {
        var id = "details" + (detail_div - 1).toString();
        var e = document.getElementById(id);
        document.getElementById("form").removeChild(e);
        detail_div--;
    }
</script>
```

### 效果
如图
![实现效果](https://img-blog.csdnimg.cn/2018102916193475.gif)
## 参考
感谢！
[CraftsmanChen - JS实现动态添加和删除DIV](https://blog.csdn.net/cfl20121314/article/details/17092615)
和他的写法还是有差异的，大家可以对比着看。

**如果觉得有用，请点赞支持。**