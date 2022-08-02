---
layout: post
title:  ""
date:   2022-08-02 12:00:00 +0900
author: Changbae Bang
tags: [react-query,  query-keys, translation]
---

공식 repo 클론해서 한글 문서를 번역해서 올려 볼까 싶다.

[번역 문서](https://github.com/Changbae-Bang-BV/query/blob/main/docs-kr/guides/query-keys.md)

물론 어딘가 번역 잘 되어 있는 것이 있고 오픈소스 커뮤니티가 있겠지만, 나 나름으로 해보려고 한다.  

쿼리 키는 고유 값이고 이 키에 따라서 데이터를 가져오게 되니 신중히 하면 좋을 것 같다.  

아래와 같은 데이터를 긁어서 화면에서 보여주고 있다.
- /a/b/:id
- /a/b/:id/c 

```tsx
useQuery(['a', 'b', id, { type: 'basic'}], ...)
useQuery(['a', 'b', id, { type: 'detail'}], ...)
```

위 처럼 데이터를 땡겨 옵니다.


```tsx
queryClient.invalidateQueries(['a', 'b', id]);
```

위 처럼 쿼리 갱신을 하여 땡겨온 데이터를 한방에 갱신 할 수 있습니다.

키가 이렇게 중요합니다.

