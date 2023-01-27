---
title: 解决ajax请求成功但不进入success代码块
date: 2019-03-08 11:54:03
tags: ['ajax','error','success']
categories:
 - 开发语言 
 - HTML/JS/CSS
---



------------------
该方法不一定能解决您的问题，具体问题具体分析。如果有任何疑问，欢迎交流。

------------------


# 版本

- OS: `windows 7`
- IDE: `IDEA 2018.3.3`
- springboot: `2.1.0.RELEASE`
- thymeleaf: `同spring一致`

!-- more -->
#  问题代码

## JS 部分
前端页面点击按钮，触发一次POST请求，然后ajax得到请求的返回结果后，将当前页面某一小块div渲染出来。

```js
 $.ajax({
     type: 'POST',
     url: "/queryCMSSetting",
     dataType: 'json',
     data: array,
     beforeSend: function () {
         process.show();
     },
     complete: function () {
         process.close().remove();
     },
     success: function (response) {
         console.log("here-1");
         $("#settingContent").html(response);
         console.log("here-2");
     },
     error: function (response) {
         alert("error");
     }
```
## 后端部分

```java
@RequestMapping(value = "/queryCMSSetting")
public String queryCMSSetting(@RequestParam String environment, 
                            @RequestParam String configKey, Model model) {

    UpdateSettingDTO updateSettingDTO = new UpdateSettingDTO();
    updateSettingDTO.setConfigKey(configKey);
    updateSettingDTO.setEnvironment(environment);
    model.addAttribute("settingList", updateSettingService.updateSetting(updateSettingDTO));
    return "update_cms_setting::settingRow";
}
```
渲染的过程实际上是，取当前页面元素的某一待填充块`th:fragment="settingRow"`, 这个待填充块里面会包含一些变量。spring/thymeleaf将变量填充为具体数值后，返回给该请求的client。很明显！！！ 因为是网页元素，所以这个接口返回的content-type一定不是`JSON`，问题就在这里了，看到上述AJAX的`dataType` , 该处填写的是`json`.

# 解决问题

我这里也简单引入[w3school](http://www.w3school.com.cn/jquery/ajax_ajax.asp)关于ajax的dataType/success的解释
>`dataType`
类型：String
预期服务器返回的数据类型。如果不指定，jQuery 将自动根据 HTTP 包 MIME 信息来智能判断，比如 XML MIME 类型就被识别为 XML。在 1.4 中，JSON 就会生成一个 JavaScript 对象，而 script 则会执行这个脚本。随后服务器端返回的数据会根据这个值解析后，传递给回调函数。可用值:
`xml`: 返回 XML 文档，可用 jQuery 处理。
`html`: 返回纯文本 HTML 信息；包含的 script 标签会在插入 dom 时执行。
`script`: 返回纯文本 JavaScript 代码。不会自动缓存结果。除非设置了 "cache" 参数。注意：在远程请求时(不在同一个域下)，所有 POST 请求都将转为 GET 请求。（因为将使用 DOM 的 script标签来加载）
`json`: 返回 JSON 数据 。
`jsonp`: JSONP 格式。使用 JSONP 形式调用函数时，如 "myurl?callback=?" jQuery 将自动替换 ? 为正确的函数名，以执行回调函数。
`text`: 返回纯文本字符串

>`success`
类型：Function
请求成功后的回调函数。
参数：由服务器返回，并根据 dataType 参数进行处理后的数据；描述状态的字符串。
这是一个 Ajax 事件。

从上面的解释，可以看出，success跟dataType是有关系的。而此时接口返回的实际dataType和你填写的dataType有出入，ajax会判定为`error`. 所以 ：

ajax 处的参数dataType改为
```
dataType: 'html',
```
或者
（接口返回的是纯文本，浏览器会根据标签来解析你的纯文本）
```
dataType: text',
```
均可。