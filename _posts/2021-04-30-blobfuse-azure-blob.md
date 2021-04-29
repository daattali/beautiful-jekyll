---
layout: post
title:  "Azure Blob 에서 Blobfuse 사용하기"
date:   2021-04-23 11:15:00 +0900
author: Changbae Bang
tags: [azure, blob, blobfuse, 새기능, content-type, 오픈소스, 야너두, 커미터모집, ]
---

# 불타는 블로그
  
이제는 글을 하루 걸러 하루씩 올려 보고 있습니다.

오늘은 짧은 글을 소개 합니다.

Blobfuse 를 통해 파일을 업로드 하게 되면 각 파일의 `content-type` 이 `application/octet-stream` 로 설정되는 상황이 있었습니다.

이렇게 되면 Web 서버에서 좀 곤란해 집니다.

이 문제가 2일 전에 해결이 되어 릴리즈가 되었습니다.

[릴리즈 노트](https://github.com/Azure/azure-storage-fuse/releases/tag/blobfuse-1.3.7)

만세!!!

그런데 말입니다. 약간 아쉬원 상태입니다.

# 지금 구현의 상태
[코오드](https://github.com/Azure/azure-storage-fuse/blob/master/cpplite/src/blob/blob_client.cpp#L189)

지원하는 Mime-Type 이 조금 적습니다.
```
std::map<std::string, std::string> contentTypeMap {
	{".css", "text/css"},
	{".gif",  "image/gif"},
	{".htm",  "text/html"},
	{".html", "text/html"},
	{".jpeg", "image/jpeg"},
	{".jpg",  "image/jpeg"},
	{".js",   "application/javascript"},
	{".mjs",  "application/javascript"},
	{".pdf",  "application/pdf"},
	{".png",  "image/png"},
	{".svg",  "image/svg+xml"},
	{".wasm", "application/wasm"},
	{".webp", "image/webp"},
	{".xml",  "text/xml"},
    {".m3u8", "application/x-mpegURL"},
    {".ts", "video/MP2T"},
};
```

구현이 어렵게 되어 있지 않습니다.
게다가 길면 뱉네요. 차라리 없으면 뱉지...

```
std::string GetContentType(std::string blob) {
    std::string type = "application/octet-stream";
    std::string ext = "";

    size_t i = blob.rfind('.', blob.length());
    if (i != std::string::npos) {
        ext = blob.substr(i, blob.length() - i);
        if (ext.length() > 6)
            return type;

        transform(ext.begin(), ext.end(), ext.begin(), ::tolower); 

        auto iter = contentTypeMap.find(ext);
        if (iter != contentTypeMap.end()) 
            type = iter->second;
    }

   return type;
}
```

# 지금이 기회!!
이거 사실 run time 에 파일 참조해서 Mime-type 설정하게 하면 완전 나이스 해집니다.

나름 blobfuse Mime-type 의 아버지(?)가 될 수 있는 기회인거죠

물론 저는 시간이 없고, 이제 컴파일이 무섭습니다.

CMake 보니까 울렁울렁하네요

최근에 릴리즈가 되어 바로 개발 계획은 없어 보이고..

지난 릴리즈가 작년 12월이고 그 전 페턴은 2달에 한번이라

대략 느낌상 2달 에서 4달의 기회가 있습니다.

C++ 가 주력인데 오픈소스 커미터가 되기 원하시는 분들 위해서는

나름 최적의 상황이 아닌가 싶습니다.


# 결론은
Blobfuse 사용시 content-type 문제가 있었다면...

업데이트를 하셔서 사용하셔도 좋습니다.

더 상세하게 설정하기 위해서는

위 코드를 살짝 고쳐 로컬에서 빌드해서 사용하는 방법을 추천드립니다.