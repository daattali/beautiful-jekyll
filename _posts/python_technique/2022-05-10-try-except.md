---
layout: post
title: python technique : try-except
subtitle: try-except 예외처리
cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/thumb.png
share-img: /assets/img/path.jpg
tags: [try-except]
---
try-except 예외 처리
```python
try:
    raise TypeError("Hello, World!")  # line 2
except Exception as e:
    print(
        type(e).__name__,          # TypeError
        __file__,                  # /tmp/example.py
        e.__traceback__.tb_lineno  # 2
    )
```

## @ 참고
