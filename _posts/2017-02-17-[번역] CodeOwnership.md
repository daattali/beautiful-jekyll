---
layout: post
title: '[번역] CodeOwnership'
subtitle: CodeOwnership에 대해
tags: [translate, codeownership, culture]
---

# 들어가며
필자가 이직할 회사를 알아보며 개발자로서 일하기에 좋은 회사는 어떤 곳일까에 대해 고민을 하던 중 **Code Ownership**([원문](https://martinfowler.com/bliki/CodeOwnership.html))에 대한 개념을 접하게 되었고 이를 공유하고자 나름의 번역을 글로 남깁니다. 피드백은 환영입니다.

# Code Ownership
**Code Ownership**의 형식은 다양한 모습으로 나타나는데 이를 크게 세 가지로 나누면 다음과 같다.

**Strong code ownership**은 code base를 모듈 (클래스, 함수, 파일)의 단위로 쪼개고, 각각의 모듈을 한명의 개발자에게 할당한다. 개발자들은 오로지 자신이 할당 받은 모듈만 수정할 수 있다. 만약 다른 사람의 모듈을 수정할 일이 생기면, 모듈의 소유자에게 요청해야 한다. 다른 모듈에 patch를 작성하는 것으로 이러한 과정을 효과적으로 진행할 수도 있다.

**Weak code ownership**은 모듈이 각 개발자에게 할당된다는 점에서 앞선 Strong code ownership과 유사하다. 하지만 다른 개발자가 할당받은 모듈을 수정하는게 허락된다는 큰 차이점을 보인다. 모듈의 소유자들은 모듈을 소유할 뿐 아니라, 다른 개발자들에 의해 변경되는 부분들도 주시하며 관리해야 할 책임을 갖는다. 만약 다른 사람의 모듈에 큰 변경이 필요한 경우에는 모듈의 소유자에게 이야기를 먼저 하는 것이 바람직하다.

**Collective code ownership**은 모듈에 대한 어떠한 소유의 개념도 적용되지 않는다. code base 자체가 전체 팀에 속하고, 팀의 어느 누구나 어떤 코드도 수정할 수 있다. 혹자는 코드가 어느 누구에게도 속하지 않는다고 여길 수 있으나, 여기서는 코드가 **개인이 아닌 팀에 속한다는** 개념을 더 중요시 해야 한다. (Collective code ownership이라는 용어는 **[Extreme Programming](https://en.wikipedia.org/wiki/Extreme_programming)** 에서 등장했다. 2nd edtion 에서는 Shared Code라는 용어로 사용되었다.)

위의 셋 중에 내(원자)가 싫어하는 것은 Strong code ownership이다. 다른 사람의 코드의 변경이 필요한 경우가 너무 많다. 코드를 변경하도록 요청하고, 그것을 기다리는 것은 너무 오랜 시간이 소요되며, 더 큰 문제를 야기한다. 변경이 사소한 것인 경우는 특히 짜증난다.

앞서 말한 사소한 변경의 좋은 예로는, public 메서드의 이름을 변경하는 것이다. 현대의 리팩토링 도구들은 이를 안전하게 수행할 수 있다. 그러나 모듈의 범위를 넘어선다면 code ownership을 어기는 경우가 된다. 기본적으로 개발자간의 모든 인터페이스들은 [PublishedInterfaces](https://martinfowler.com/bliki/PublishedInterface.html)로 전환되며 이를 변경하는 것에는 오버헤드가 발생한다.

더 심한 경우는 구현의 변경을 원하는 경우이다. 왜냐하면 다른 사람의 코드를 당신의 모듈로 복사를 하고, 복사된 코드를 호출하도록 코드를 변경하는 것은 불편하고 귀찮은 과정이다. 게다가 어지럽혀진 코드는 나중에 정리하려 했을 것이다.

Weak code ownership는 이러한 문제를 완화시키는 좋은 방법이다. 사람들은 자유롭게 코드를 수정하고, 코드의 소유자는 그것을 주시하기만 하면 된다.

Weak code ownership와 Collective Ownership 사이에서의 선택은 팀의 social dynamics과 관련이 깊다. 둘 다 좋을수도, 나쁠수도 있다. 개인적으로(원자) **[Extreme Programming](https://en.wikipedia.org/wiki/Extreme_programming)**에서의 관점에서 보자면, 후자를 더 선호한다.

# 마무으리
어떤 방식이 더 좋다 나쁘다를 따지는 것은 무의미한 것 같고, 어떤 환경에서 어떤 방식이 더 적합한지를 보는게 적절할 것 같다.

요즘의 대부분의 스타트업에서는 Collective Ownership을 선호하는데, 아무래도 요구사항이 시시각각 변하는 스타트업에서는 **[Extreme Programming](https://en.wikipedia.org/wiki/Extreme_programming)**의 개발 방식이 선호될 것이고, 자연스레 Collective Ownership을 따라가기 때문인 듯 하다.

스타트업에서 Collective Ownership을 사용할 때, 이를 잘 따르기 위해서는, 한사람이 쓴 것 같은 코드를 지향해야 한다. 그러기 위해서는 팀내에서 컨벤션, 코드 스타일이 명확하게 공유가 되야 한다. 또 개인으로서는 남들이 읽고 이해하기 쉬운, 간단하고 명료한 코드 (제일 어려움)를 작성할 수 있어야 한다.
