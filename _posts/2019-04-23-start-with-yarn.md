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
회사에서는 React를 가지고 [Enact](https://enactjs.com/)를 만들어 쓰고 있다. 그래서 간단하게 Web App을 만들때도, Enact를 꼭 사용하고 있다. 최근에 Front-End에 대해서 기술적으로 이야기 할 때, 내가 고립되어 있는 것 같다는 생각을 했다. 최근 5년간 사용한 JavaScript Framework 는 [Enyo](https://enyojs.com/)와 [Enact](https://enactjs.com/)였다. 예전에 W3C HTML5 포럼에서 발표했던 [Enyo 세션](http://www.html5forum.or.kr/api/filedown.jsp?filename=%ED%8A%B8%EB%9E%993_31_LG%EC%A0%84%EC%9E%90_%EB%B0%A9%EC%B0%BD%EB%B0%B0_%EC%A3%BC%EC%9E%84_%EC%9B%B9OS_%EC%95%A0%ED%94%8C%EB%A6%AC%EC%BC%80%EC%9D%B4%EC%85%98_%ED%94%84%EB%A0%88%EC%9E%84%EC%9B%8C%ED%81%AC_Enyo_W3C_2015.pdf&folder=upload/board)도 벌써 4년전 일이 되어가고 있다. Enyo가 좋다고 떠들고 다니던 때도 벌써 5년이 지나버렸다. Enyo는 이제 너무 예전 일들이 되었고 최신 기술을 습득하지 못한다는 생각이 들었다. 게다가 Enact는 Enyo때보다 객체지향스러움이, 정확하게 말하면 확장성이 조금 아쉬웠다. UI Control을 가지고 무언가 변경을 할 때 불편함이 많았다. 내가 즐기는 프로그램 방식에서는 사용성이 줄다보니 Enact는 조금 아쉬움이 남았다. 그래서 Vue를 사용하게 되었다.
내 생각엔 Vue를 사용하면 Template과 데이터를 나누어 개발하여 UI 구성에 애를 먹지 않았다. 만약 컨트롤을 바꾸려고 하면 Template을 수정하거나 재구성하면 된다. JSX로 구현한 내부를 수정하다보면 점점 코드가 더러워지는 듯한 느낌이 들었는데, Vue를 사용할 때는 그런 느낌이 덜했다. 친한 Front-End 개발자는 Vue를 사용하면 Publisher와 일하기 편하다고 했는데, 그것이 무슨 뜻인지 조금 알 것 같았다.
회사의 녹을 먹기에 Enact를 배제할 수는 없겠지만 Vue 개발자라고 할 수 있는 수준이 될 수 있게 무언가 해야겠다는 생각이 들었다.

## 나도 이제 오픈 소스 개발자가 되고 싶다.
Vue.js의 일원이 되는 여러 방법이 있겠지만, 소소한 Commit 이라도 하여 기부자가 되는 것이 어떨까 싶었다. 누군가 불편해 하는 것을 살짝 바꿔주면 나도 보람되고 그 누군가도 좋겠지만... 나에게 쉬운 일은 아닐 것 같다는 생각이 들었다. 그래도 시작은 해보려고 한다.
[Vue 개발자 설정](https://github.com/vuejs/vue/blob/dev/.github/CONTRIBUTING.md#development-setup)을 보다보니 잘 안쓰던 이름이 나왔다. Yarn? Npm도 잘 쓰고 있는데 더 필요한 것이 있을까? 사실 아직은 잘 모르겠다. Yarn은 Npm에 대한 개선이 있었다고 한다.([Yarn: A new package manager for JavaScript](https://code.fb.com/web/yarn-a-new-package-manager-for-javascript/)과 여러 포스트를 보면서 Yarn에 대해서 알아보았다.)
- 매우 빠르다.
- 매우 안전하다.
- 신뢰가 된다.  
하지만 아직 이제 처음 써보는 것이라서 와닿지는 않는다. 현재로서는 명령어를 전환해야 해서 귀찮다는 생각이 조금 든다. 이제 Yarn으로 Vue 프로젝트를 함께 해봐야지... Core도 좋지만 CLI도 무언가 만들어 보고 싶다는 생각이 있다. Template을 몇 만들어 보고 싶다는 생각도 있고 Webpack구성을 조금 만져보던가 Parcel로 대체하는 것도 고민이 된다.

## 아재같을 순 있겠지만..
Npm에서 Yarn으로 넘어갈 생각을 하다보니 예전 Source Safe에서 SVN이나 CVS로 넘어갈 때 생각이 난다. SVN에서 git으로 옮길때도 매우 귀찮았었다. 하지만 지금 생각해보면 SVN 명령어가 기억이 흐릿흐릿 하다.
[Yarn vs npm: Everything You Need to Know](https://www.sitepoint.com/yarn-vs-npm/)을 참고해보면, 그 외에 다른 여러 포스트를 참고해보면 아래와 같은 결과를 얻을 수 있었다.  
- npm install => yarn 
- npm install myPackage => yarn add myPackage
- npm install myPackage --save-dev => yarn add myPackage --dev
- npm uninstall myPackage --save-dev => yarn remove myPackage --dev
- npm -g install myPackage => yarn global add myPackage
- npm init => yarn init
- npm run => yarn run
- npm test => yarn test
내가 자주쓰는 명령어 위주로 정리를 해보았다. 이제 시작을 해봐야지.

## 삼천포로 빠지고 말았다. Vue 설정은 어디로...
간단하게 명령어를 정리하면서 Yarn을 정리해보았다. Yarn이 무엇입니까에 대해서 매우 추상적으로 이야기 할 수도 있다. 그런 개념을들 파볼수도 있지만, 결국 Yarn이 무엇이냐 한다면 Package 관리자일게고 그 후엔 어떤 명령으로 Package를 관리하느냐가 될 것 같다는 생각이 들어 명령어를 정리해보았다.
더 사용하면서 Yarn이 무엇인지 더 정리해보자 한다.
