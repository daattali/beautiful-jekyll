---
layout: post
title: Yarn을 처음 접하면서
subtitle: Vue 를 해보려고 하니 Yarn 을 하라고 하네
gh-repo: changbaebang/changbaebang.github.io
gh-badge: [star, fork, follow]
tags: [Yarn, 명령어비교]
comments: true
---

## 시작하면서
다니고 있는 회사의 공식 JavaScript UI Framework는 [Enact](https://enactjs.com/)이다.(React를 가지고 Enyo를 계승한 그 무언가이다.) 그래서 간단하게 Web App을 만들때도, Enact를 사용해 달라고 요구를 받는다. 최근 5년간 사용한 JavaScript Framework 는 [Enyo](https://enyojs.com/)와 [Enact](https://enactjs.com/)이고 이들은 모두 회사에서 개발한 것들이다. 물론 내가 개발한 것은 아니자만 나는 이들을 널리 퍼트리는 역할을 하고 있기에 달리 다른 것들을 선택할 여지는 없었다.  

회사의 공식 UI Framework만 사용하다보니 왠지 마음에 불안함이 들었다. 최근 주변 개발자들과 Front-End에 대해서 이야기 할 때, 내가 고립되어 있다는 생각을 지울수가 없었다. 사실 처음엔 그런 생각이 들지 않았다. 예전에 W3C HTML5 포럼에서 [Enyo 세션](http://www.html5forum.or.kr/api/filedown.jsp?filename=%ED%8A%B8%EB%9E%993_31_LG%EC%A0%84%EC%9E%90_%EB%B0%A9%EC%B0%BD%EB%B0%B0_%EC%A3%BC%EC%9E%84_%EC%9B%B9OS_%EC%95%A0%ED%94%8C%EB%A6%AC%EC%BC%80%EC%9D%B4%EC%85%98_%ED%94%84%EB%A0%88%EC%9E%84%EC%9B%8C%ED%81%AC_Enyo_W3C_2015.pdf&folder=upload/board)을 발표 할 때만 해도, 잘 버티면 작은 그룹은 만들 수 있지않을까 생각하기도 했었다. 그 일이 벌써 4년전 일이 되어가고 있다. Enyo는 결국 폭파되었고, Enact라는 다른 무언가로 전환되었다. 전환기에 나는 어쩌다보니 배제되기도 했었지만, Technical Evangelist의 업무가 왜곡되기도 했었어서 슬슬 이제 일을 마무리 해야 하나 하는 그런 시점이기도 했다. 어쨌든 그렇게 새로운 Enact가 나왔지만 과거의 망령때문인지 Enact는 Enyo때보다 객체지향스러움이, 정확하게 말하면 확장성이 조금 아쉬웠다. UI Control을 가지고 무언가 변경을 할 때 불편함이 많았다. 내가 즐기는 프로그램 방식에서는 사용성이 줄다보니 Enact는 조금 아쉬움이 남았다. 그래서 다른 UI Framework를 찾게 되었다. 그때 찾은 것은 Vue.js 였다.  

내 경험엔 Vue를 사용하면 Template과 데이터를 나누어 개발할 수 있어 좋았고, 그렇기에 UI를 마구 변경해달라는 요구사항에 그렇게 겁이 나지 않았다. 컨트롤을 바꿀때도 Template 쪽을 나름 간단히 수정하여 재구성하기 좋았다. Enact로 사실 React로 UI를 구현할 때 JSX로 구현한 내부를 수정하다보면 점점 코드가 더러워지는 듯한 느낌이 들었다. 특히 나는 또 대괄호({})를 이용하여, 삼항연산자나 map을 날리면서 안에서 무언가 뿌작뿌작 구현하는 경우가 많았는데, 그것을 들어내야할 때면 마음이 아프고 머리가 아팠다.(처음부터 요구사항 좀 잘 주지 싶었지만...) 결론적으로 Vue를 사용할 때는 그런 느낌이 덜했다. 친한 Front-End 개발자는 Vue를 사용하면 Publisher와 일하기 편하다고 했는데, 그것이 무슨 뜻인지 조금 알 것 같았다.
회사의 녹을 먹기에 Enact를 배제할 수는 없겠지만 Vue 개발자라고 할 수 있는 수준이 될 수 있게 무언가 해야겠다는 생각이 들었다.  

## 나도 이제 오픈 소스 개발자가 되고 싶다.
Vue.js의 일원이 되는 여러 방법이 있겠지만, 소소한 Commit 이라도 하여 기부자가 되는 것이 어떨까 싶었다. 누군가 불편해 하는 것을 살짝 바꿔주면 나도 보람되고 그 누군가도 좋겠지만... 나에게 쉬운 일은 아닐 것 같다는 생각이 들었다. 그래도 시작은 해보려고 한다.  

[Vue 개발자 설정](https://github.com/vuejs/vue/blob/dev/.github/CONTRIBUTING.md#development-setup)을 보다보니 잘 안쓰던 이름이 나왔다. Yarn? Npm도 잘 쓰고 있는데 더 필요한 것이 있을까? 사실 아직은 잘 모르겠다. Yarn은 Npm에 대한 개선이 있었다고 한다.([Yarn: A new package manager for JavaScript](https://code.fb.com/web/yarn-a-new-package-manager-for-javascript/)과 여러 포스트를 보면서 Yarn에 대해서 알아보았다.)  

- 매우 빠르다.
- 매우 안전하다.
- 신뢰가 된다.  

하지만 아직 이제 처음 써보는 것이라서 와닿지는 않는다. 현재로서는 명령어를 전환해야 해서 귀찮다는 생각이 조금 든다. 이제 Yarn으로 Vue 프로젝트를 함께 해봐야지... Core도 좋지만 CLI도 무언가 만들어 보고 싶다는 생각이 있다. Template을 몇 만들어 보고 싶다는 생각도 있고 Webpack구성을 조금 만져보던가 Parcel로 대체하는 것도 고민이 된다. (흠 하지만 NPM Package 하는 것들도 Post 하고 싶은데... Yarn으로 바꿔볼까 고민이 되지만 아직 하지도 않을 일을 고민해서는 뭐 될 것도 없겠지..)  

## 아재같을 순 있겠지만..
Npm에서 Yarn으로 넘어갈 생각을 하다보니 예전 Source Safe에서 SVN이나 CVS로 넘어갈 때 생각이 난다. SVN에서 git으로 옮길때도 매우 귀찮았었다. 하지만 지금 생각해보면 SVN 명령어가 기억이 흐릿흐릿 하다. 사실 넘어가는 과정은 큰 산 같았지만 넘어가고 보면 예전이 기억이 안난다. 그만큼 새로 선택한 툴이 편하다는 것이겠지.. SVN이나 git으로 넘어간 후로는 누가 checkout을 하고 가버리는 수정할 수 없어 관리자나 checkout을 한 분(이라고 쓰고 놈이라고 읽는다)를 찾을 필요도 없어졌다. 대신 내가 막 수정해서 올리려고 했는데 충돌이 난다는 메세지를 얻게 되었지만 예전의 고통을 생각해보면 병합은 일도 아니다 무튼 Yarn도 그럴 것이라고 생각해보지만 아직은 Yarn과 Npm이 Source Safe와 git 같지는 않기에 병행해서 사용할 것 같다는 생각은 한다. 다시 Yarn으로 돌아와서 [Yarn vs npm: Everything You Need to Know](https://www.sitepoint.com/yarn-vs-npm/)과 여러 포스트를 참고해서 정리를 해보았다. 정리를 해보니아래와 같은 결과를 얻을 수 있었다.  

| NPM | YARN |
| :------ |:--- |
| npm install | yarn |
| npm install myPackage | yarn add myPackage |
| npm install myPackage &#45;&#45;save-dev | yarn add myPackage &#45;&#45;dev |
| npm uninstall myPackage &#45;&#45;save-dev | yarn remove myPackage &#45;&#45;dev |
| npm -g install myPackage | yarn global add myPackage |
| npm init | yarn init |
| npm run | yarn run |
| npm test | yarn test |

내가 자주쓰는 명령어 위주로 정리를 해보았다. 이제 시작을 해봐야지.(pack도 종종 쓰는데 pack은 더 공부를 해보고 다룰가 한다.)  

## 삼천포로 빠지고 말았다. Vue 설정은 어디로...
간단하게 명령어를 정리하면서 Yarn을 정리를 마무리해본다. Yarn이 무엇입니까에 대해서 매우 추상적으로 이야기 할 수도 있다. 면접에서 떠들만한 그런 것들을 쓰기는 편하다. 하지만 그런 추상적인 것을 면접에서 떠들고 나면 내 안의 공허함만 더 커지고 나는 더 모르는 사람입니다를 광고하는 기분이 들었던 것 같다. 그래서 그런 광파는 이야기는 재베해보았다. 그럼에도 불구하고 Yarn이 무엇이냐 한다면 Package 관리자일게고 그 후엔 어떤 명령으로 Package를 관리하느냐가 될 것 같다는 생각이 들어 명령어를 정리해보았다.
더 사용하면서 Yarn이 무엇인지 더 정리해보자 한다. 첫 포스트를 마무리하니 왠지 10만 글을 쓴거 같이 뿌듯하지만 몇 년뒤에 이 글을 보고 또 수정할 것 같긴하다.