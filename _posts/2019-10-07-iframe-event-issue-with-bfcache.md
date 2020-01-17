---
layout: post
title:  "BFCache 동작에서 발견된 iframe 내 비정상적 이벤트 발생 현상"
date:   2019-10-07 02:00:00 +0900
author: Changbae Bang
tags: [ 방창배, bfcache, 모바일, 브라우져,  ]
---
회사 블로그에 작성한 내용을 올려봅니다.
https://teamdable.github.io/techblog/iframe-event-issue-with-bfcache

안녕하세요. 방창배입니다.

최근 iOS에서만 발생하는 문제를 처리한 이슈를 소개하려고 합니다. 많은 프론트엔드 개발자들이 BFCache로 인해 페이지 이동 시에 발생하는 이벤트가 달라지는 고충을 겪는 것을 알고 있습니다. 하지만 이번에 소개하려는 내용은 페이지 이동 시 BFCache로 인해서 기대하는 이벤트가 발생하는 문제는 아닙니다. BFCache로 페이지가 이동한 후 `iframe`에서 정상적이지 않은 이벤트 흐름이 있는 것에 대해서 다루고자 합니다. 어떠한 조건으로 발생하는지, 그리고 해결책에는 어떤 것이 있을지 정리해보겠습니다.

## iPhone에서 클릭이 안 된다.
이슈는 특정 버전의 iPhone 상의 모든 브라우저(사파리, 크롬, 네이버 앱)에서 간헐적으로 발생하는 문제였습니다. 더욱이 안드로이드의 어떠한 브라우저에서도 재현되지 않는 현상이었습니다. 아주 먼 예전에 브라우저를 개발할 때, 각 브라우저의 동작을 확인해보기 위해서 최소 단위의 샘플을 제작하면서 작업을 시작하였습니다. 이번 이슈도 최소 단위의 재현 샘플을 만들며 그 원인을 찾아보았습니다.

### 발생 원인 요약
이 이슈는 평상시에는 재현되지 않습니다. 또한 iOS가 아니면 재현되지 않습니다. iOS에서도 항상 발생하는 것은 아니며 **BFCache**(Back-Forward Cache)를 사용할 때 문제가 발생합니다.

문제를 만드는 조건을 정리하면 다음과 같습니다.

1. 브라우저의 뒤로 가기를 이용하여 페이지를 전환한다.
2. `iframe` 에 `src` 등 어떠한 내부 페이지를 변경하는 동작을 하지 않는다.
3. `iframe` 로 로딩하는 html 내에 `link` *element* 가 반드시 존재한다.

재현 조건을 만족하는 부모 페이지는 아래와 같습니다.

```html
<html lang="ko">
  <head>
    <title>iOS iframe click bug with history back</title>
    <meta charset="utf-8">
  </head>
  <body>
    <iframe src="./widget.html" style="border: 0px;"></iframe>
  </body>
</html>
```

재현 조건을 만족하는 자식 페이지는 다음과 같습니다.

```html
<html>
  <head>
    <meta charset="utf-8">
    <title>Child Page</title>
    <link rel="stylesheet" href="./nothing.but.something.css">
  </head>
  <body >
    <a href="http://dable.io" target="_top">아이 프레임 버그 발생</a>
  </body>
</html>
```

자식 페이지에서 `link` *element* 를 제거하면 이슈가 재현되지 않습니다. 위 샘플에서 보는 것과 같이 `link` *element* 에서 style sheet를 로드하지 못해도 `iframe` 내에 클릭 이벤트가 발생하지 않습니다.

[페이지 예제](/techblog/example/bfcach-bug/sample/index.html)

쉽게 확인을 하기 위해 위 경로에 샘플을 올려놓았습니다.


## 문제 처리 방안
원인을 확인했으니 이제 처리 방안에 관해서 이야기하려고 합니다.

### 클릭 이벤트 발생
첫 번째 방법으로 클릭 이벤트를 발생시키는 것을 구현해보려고 합니다.

이 상황에서 `iframe` 내에 아무런 사용자 이벤트가 발생하지 않는 것은 아닙니다.

사용자가 링크를 클릭할 때 정상적이면 `mousedown`, `mouseup`, `touchstart`, `touchend`, `click` 순으로 이벤트가 발생합니다.
하지만 이슈가 재현되는 상황에서는 발생한 상황에서는 `touchstart`, `touchend` 두 이벤트만 발생합니다. 그로 인해서 사용자가 링크를 클릭하여도 아무런 반응이 없는 문제가 발생합니다.

이러한 문제가 발생한 경우 `touchstart`, `touchend` 두 이벤트를 이용하여 `click` 이벤트를 발생 시켜 버그를 해결할 수 있습니다.
구현에 대한 사항은 [NAVER D2: 터치 이벤트를 이용한 사용자 제스처 분석](https://d2.naver.com/helloworld/80243)를 참조하였습니다.

간단하게 생각해 보면 `touchmove`를 감지하여 같은 자리에서 `touchstart`와 `touchend`가 발생하였는지 확인할 수 있습니다. 이를 기반으로 `click`을 발생시킬 수 있습니다. 더욱 안전한 동작을 위해서 바로 `click`을 보내지 않고, 중간 이벤트를 만들어서 최대한 `click` 이 올라오는지 확인한 후 `click` 이 중간에 오면 `click` 이벤트 발생을 취소하고 이벤트가 발생하지 않는다면 구현을 통해서 이벤트를 발생시키도록 하였습니다.

```javascript
let addLazyClick = (ele) => {
  const target = ele;
  let isMoved = false;
  const timerInterval = 200;              // Allow to be Customized
  let preventInifite = 10;                // Allow to be Customized
  const triggeringEventName = "click";      // Allow to be Customized
  let  mediateEventName = "lazy-click";   // Allow to be Customized

  let isMediateEventNameVailable = () => {
    // warn to infinite loop
    while(ele["on"+mediateEventName] === "function") {
      mediateEventName = "-" + mediateEventName;
      preventInifite--;
      if(preventInifite === 0){
        throw new Error("custom event name could be not set.");
      }
    }
  };
  try{
    isMediateEventNameVailable()
  }catch(e) {
    console.error("mediateEvent could not be used in this page");
    return;
  }

  let eventDispatcher = (targetElement, eventName) => {
    console.info("triggering " + eventName);
    let evObj = document.createEvent('Events');
    evObj.initEvent(eventName, true, false);
    targetElement.dispatchEvent(evObj);
  };

  ele.addEventListener("touchmove", () => {
    isMoved = true;
  });

  ele.addEventListener("touchend", (_event_) => {
    if(isMoved === false) {
      let _lazyClickTimer_;
      let _remove_timer_ = () => {
        if(_lazyClickTimer_){
          console.info("remove timer " + _lazyClickTimer_);
          clearTimeout(_lazyClickTimer_);
          _lazyClickTimer_ = undefined;
        }
      };
      _lazyClickTimer_ = setTimeout(() => {
        console.info("remove " + triggeringEventName + " handler for cleartimer");
        target.removeEventListener(triggeringEventName, _remove_timer_);

        console.info("start " + mediateEventName + " event triggering.");
        eventDispatcher(target, mediateEventName);
      }, timerInterval);

      target.addEventListener(triggeringEventName, _remove_timer_);
    }
    isMoved = false;
  });

  ele.addEventListener(mediateEventName, () => eventDispatcher(target, triggeringEventName) );
}


// iOS for iframe does not trigger click event with history back
let aElements = document.querySelectorAll("a");
aElements.forEach((ele) => addLazyClick(ele));
```

[전체 페이지](/techblog/example/bfcach-bug/triggering-event-solution/index.html)

쉽게 확인을 하기 위해 위 경로에 샘플을 올려놓았습니다.

아름답지는 않지만, 해결은 됩니다.

자연스럽게 `click` 이벤트를 발생하여 페이지 이동을 하기 위해서 부자연스럽게 이벤트를 발생하는 코드가 추가 되었습니다.
이 경우 개발자가 `click` 이벤트 조건을 판단해야 합니다. 플랫폼 환경에 따라 `click` 판정이 달라진다고 가정을 해보면 머리가 지끈지끈해질 수 있습니다. 이번 경우에야 `touchmove`가 없는 것을 `click`으로 판단하였지만 만약 어느 정도 이동을 허용하는 플랫폼이 있다고 가정하면 개발자는 다양한 플랫폼을 하나의 코드에서 처리하고 관리해야 합니다. 또한 진짜 `click` 이벤트가 올라오는 지 감지하는 동작들에 많은 방어코드가 들어가 있습니다. 하지만 예외 상황을 벗어나는 동작이 발생할 경우에 대한 처리에 한계는 항상 있습니다. 위 예제 코드의 경우 `while` 을 사용하여 사용자 이벤트 등록 가능성을 확인하고 있습니다.

이처럼 브라우저에서 자연스럽게 해줘야 할 것들을 브라우저 위에서 구현하려고 하는 것에는 한계가 있을 수 밖에 없습니다.

그래서 다른 고민을 더 해보려고 합니다.

## iframe을 다시 로드하는 방법

상황에 따라서 이벤트를 임의 방생하는 방법도 있지만 `iframe` 을 새로 로딩하여 `click` 이벤트가 자연스럽게 발생하도록 처리하는 방법도 있을 것입니다.
이 방법은 스크립트도 줄일 수 있고 타이머를 사용하여 이벤트 발생 상태를 확인하지 않아도 됩니다. 단지 페이지를 다시 로드하여  `iframe` 내 `click` 이 발생하지 않는 조건을 제거할 수 있습니다.

잠시 기존에 겪고 있는 BFCache 문제로 돌아가 보도록 하겠습니다.
상세한 내용은 아래 블로그들을 참고 할 수 있을 것 같습니다.
* [[JavaScript] 브라우저에서 뒤로 가기 수행 시, 자바스크립트가 실행되지 않는 이유](https://programmingsummaries.tistory.com/380)
* [IOS Safari history.back() 문제 : pageshow Event](http://kdsr2z0.github.io/safari_javascript_cache/)

그리고 모질라에서는 아래와 같은 가이드를 제공하고 있습니다.

[Using Firefox 1.5 caching](https://developer.mozilla.org/en-US/docs/Mozilla/Firefox/Releases/1.5/Using_Firefox_1.5_caching)

정리해 보면, BFCache 상황은 `pageshow` 가 발생하였을 때 이벤트에 `persisted`를 여부를 가지고 판단할 수 있습니다.
그렇다면 이 상황에 필요한 `iframe`을 새로 갱신하여 이 문제를 처리할 수 있습니다.

데이블에서는 `iframe` 을 사용하여 위젯을 만들고 있습니다. 데이블에서 사용하는 위젯 스크립트를 사용하여 이어 설명하려고 합니다.
아래 코드를 이용하면 `iframe` 을 그리는 시점이 조금 밀리지만, 이제 `iframe` 에서 `click` 안되는 문제에서 간단하게 해결할 수 있습니다.

```javascript
window.addEventListener("pageshow", () => {
  dable('setService', 'standard_widget');
  dable('renderWidget', 'dablewidget_GlGeZnox');
});
```

[전체 페이지](/techblog/example/bfcach-bug/defered-rendering-solution/index.html)

쉽게 확인을 하기 위해 위 경로에 샘플을 올려놓았습니다.

하지만 이번 경우에도 위젯 사용에 대한 방법을 변경해야 하는 상황이 있습니다. 이미 사용하고 있는 서비스들이 모두 수정을 해야 하는 번거로움이 발생하고 맙니다.


## 위젯 스크립트에서 알아서 잘되도록 수정

위에서 언급한 것 처럼 위 방법으로 처리하기 위해서는 기존 데이블 위젯을 사용하는 개발자들에게 새로운 가이드를 보내 다시 개발을 진행하게 하는 큰 불편함이 있습니다. 가이드를 바꾸는 것은 내부 개발자들에게 매우 편한 일이지만 이 가이드를 따르고 있는 사용자에게는 매우 번거로운 일입니다. 좋은 기술이 되기 위해서 사용자의 코드를 바꾸지 않는 선에서 처리하는 방법을 다시 찾아보려고 합니다.

우선 많은 사용자가 사용하고 있는 위젯을 표현하는 스크립트는 변경하지 않으려고 합니다. 보통의 경우 인라인 스크립트를 사용하여 HTML 문서가 파싱될 때 인라인 스크립트로 사용하는 경우가 있었습니다.

```javascript
dable('setService', 'standard_widget');
dable('renderWidget', 'dablewidget_GlGeZnox');
```

그래서 내부적으로 위와 같은 위젯 명령이 전달될 때, 명령을 저장하는 동작을 새로 구현하였습니다.

```javascript
CommandQueue.prototype.push = function(params) {
  var i, item, len;
  if (util.isArray(params[0])) {
    for (i = 0, len = params.length; i < len; i++) {
      item = params[i];
      this.push(item);
    }
    return;
  }
  if (util.isIOSDevice() === true) {
    this.saveCommand(params);
  }
  return this.execute(params);
};
```

그리고 불필요한 이벤트 핸들러 등록을 막기 위해서 저장할 사항이 있으면 이벤트 핸들러를 등록할 수 있도록 저장 동작에서  `pageshow` 에 대한 이벤트 핸들러를 등록하도록 구현하였습니다.

```javascript
CommandQueue.prototype.saveCommand = function(params) {
  this.commands.push(params);
  if (this.isPageShowEventHandlerReady() !== true) {
    return this.attachPageShowEventHandler();
  }
};
```

그리고 `pageshow` 이벤트가 발행하면 BFCache 상황인지를 판단하여 저장한 명령을 실행할 수 있도록 하였습니다.
바로 명령을 실행하는 것이 아니라 이벤트를 발생하여 비동기로 수행할 수 있도록 구현하였습니다.

```javascript
CommandQueue.prototype.pageshowHandler = function(e) {
  if (e.persisted !== true) {
    return;
  }
  this.dettachPageShowEventHandler();
  this.attachRebuildEventHandler();
  return event.postEvent(document, "rebuild");
};
```

발생시킨 사용자 이벤트를 감지하여 이전에 받은 명령을 다시 실행하였고 이 동작으로 `iframe`을 다시 갱신할 수 있습니다.

```javascript
CommandQueue.prototype.rebuildHandler = function() {
  var command, i, len, results, tempCommands;
  this.dettachRebuildEventHandler();
  tempCommands = this.commands;
  this.commands = [];
  results = [];
  for (i = 0, len = tempCommands.length; i < len; i++) {
    command = tempCommands[i];
    results.push(this.push(command));
  }
  return results;
};
```

이러한 해결책을 통해서 사용자들의 개발 수정 없이 문제 사항을 제거해 보았습니다.

[전체 페이지](/techblog/example/bfcach-bug/plugin-updae-solution/index.html)


# 마치며
이 문제는 사실상 iOS에서 BFCache의 동작의 버그라고 생각합니다. 그래서 더더욱 어떤 식으로 플랫폼을 구현한 것인지 많이 궁금합니다.
하지만 궁금함을 뒤로하고 사용자의 불편함 없이 문제를 해결하는 방안을 고민해 보았습니다. 물론 버그로 볼 수 있지만, 현재의 동작하지 않는 문제를 그냥 두고만 볼 수 없는 까닭일듯합니다. 비록 버그성 동작이지만 BFCache 상에서 `click` 에 대한 문제가 있는 다른 개발자들에게 도움이 되길 바라며 내용을 정리해보았습니다.

그리고 다행스럽게도 `iframe`에 대한 처리 동작을 명령으로 잘 구현해 놓았기에 큰 어려움 없이 `iframe`을 조정할 수 있었습니다.
버그나 기능을 확장할 때 논리적인 명령을 잘 정리하는 것이 얼마나 중요한지 계속 깨닫습니다. 최근 합류한 Dable의 잘 정리된 코드들을 보면서 잘 합류하였다는 생각을 한 번 더 할 수 있었습니다.