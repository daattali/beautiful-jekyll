---
title: centos7解决fatal error pcap.h No such file or directory
date: 2019-12-31 14:30:17
tags: ['centos','pcap.h','libpcap-devel']
categories: 
 - OS
 - Linux
---

>[root@tiger-pit-s1 gowork]# go get github.com/buger/gor
>\# github.com/buger/goreplay/vendor/github.com/google/gopacket/pcap
>src/github.com/buger/goreplay/vendor/github.com/google/gopacket/pcap/pcap_unix.go:34:18: fatal error: pcap.h: No such file or directory
>#include <pcap.h>
>       ^

折腾了好久，centos需要安装`libpcap-devel`

执行 `yum install libpcap-devel`
