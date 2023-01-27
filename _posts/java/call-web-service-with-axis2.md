---
title: 使用axis2调用web service
date: 2018-09-29 12:12:35
updated: 2018-09-29 12:12:35
tags: ['java调用ws','web service','axis2生成客户端']
categories: 
 - 开发语言
 - Java
---

# 使用axis2生成客户端代码

1. 下载axis2 , 点击[这里](http://axis.apache.org/axis2/java/core/download.html), 选择 Binary distribution
2. 下载后解压，解压进入到bin目录
3. 执行命令生成客户端代码

>$ wsdl2java --help    // 查看帮助，命令选项可供参考

- 将所有的类都合并成了一个类（文件）
>$ wsdl2java -uri http://localhost:8080/services/XXXService.svc?wsdl -p com.xxx.yyy -o d:\myCode

- 将接口涉及到的不同的接口入参/出参/返回/枚举等等拆分成了不同的类，并且文件较多
>$ wsdl2java -uri http://your_soa_url -p com.xx.yy.zz -o d:\your_local_path -s -u

上面两种情况，具体怎么选择，由你决定。
建议： 如果通过方式1生成的文件少于3M, 可以选择1. 反之选择2.
因为当一个类文件超过一定大小后，IDEA会特别卡。

\-uri: 后可以接wsdl连接，或者wsdl文件
\-p : 指定生成的包名，可以和项目一致，比如你想将生成的代码放置于 com.example.test 里面，那么-p com.example.test 
\-o : 指定生成代码存放在本地的路径，看你个人喜好

1. 生成客户端代码后，将代码拷贝到你项目中
# 引入jar包

通过maven引入

```
        <!-- https://mvnrepository.com/artifact/org.apache.axis2/axis2-kernel -->
        <dependency>
            <groupId>org.apache.axis2</groupId>
            <artifactId>axis2-kernel</artifactId>
            <version>1.7.8</version>
        </dependency>
        <!-- https://mvnrepository.com/artifact/org.apache.axis2/axis2-adb -->
        <dependency>
            <groupId>org.apache.axis2</groupId>
            <artifactId>axis2-adb</artifactId>
            <version>1.7.8</version>
        </dependency>
        <!-- https://mvnrepository.com/artifact/org.apache.axis2/axis2-transport-local -->
        <dependency>
            <groupId>org.apache.axis2</groupId>
            <artifactId>axis2-transport-local</artifactId>
            <version>1.7.8</version>
        </dependency>
        <!-- https://mvnrepository.com/artifact/org.apache.axis2/axis2-transport-http -->
        <dependency>
            <groupId>org.apache.axis2</groupId>
            <artifactId>axis2-transport-http</artifactId>
            <version>1.7.8</version>
        </dependency>
```

# 调用客户端代码请求wsdl

部分代码经过了脱敏处理
```
String url = "http://localhost:8080/services/XXXService.svc";
// 下面的内容基本都是依葫芦画瓢即可
AxxServiceStub stub = new AxxServiceStub(url);
Options options = stub._getServiceClient().getOptions();
options.setTimeOutInMilliSeconds(100000);
stub._getServiceClient().setOptions(options);
// 初始化请求入参
AxxServiceStub.InvestReq investReq = new AxxServiceStub.InvestReq();
// set请求字段数据
investReq.setAccount(1);
// 这里需要留意一下
// Source是服务端自定义字段
investReq.setSource(AxxServiceStub.ClientToInvestType.PC);

AxxServiceStub.Invest invest = new AxxServiceStub.Invest();
invest.setReq(investReq);
AxxServiceStub.InvestResp response = stub.invest(invest).getInvestResult();

log.info("调用xx返回结果：" + response.getMessage());
```