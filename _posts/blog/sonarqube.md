---
layout: post
title: Swift)SonarQube Integration with iOS(번역)
tags: [Production]
comments: true
---

![](/img/posts/post-18/001.png){: .center-block :}

SonarQube를 이해하는데 좋은 글이 있어서 번역하여 공유하고자합니다. 원본 링크는 [여기](https://medium.com/@pranay.urkude/sonarqube-integration-with-ios-b76df8405014)로 가시면 됩니다.


## SonarQube란?
SonarQube는 SonarSource가 개발한 오픈소스 플랫폼으로 20개 이상의 프로그래밍 언어에서 정적 코드 분석을 통해 버그 및 보안 취약점을 탐지하고 자동 검토를 수행하여 코드 품질을 지속적으로 검사합니다.

## Sonar Swift
Backelite에서 개발한 Swift 플러그인은 사람들이 SonarSwift를 프로젝트에 통합하는 데 도움이되었습니다. 다음 사항을 다룹니다.

### Code coverage
SonarQube에서 사용할 수있는 측정 중 하나이며, 자동화된 테스트가 실행되는 동안 실행되는 코드 줄 수를 설명합니다. SonarSwift는 실행되는 코드 덩어리를 제공 할뿐만 아니라 데이터를 드릴하고 특정 테스트 중에 실행된 코드와 실행되지 않은 코드를 정확하게 확인할 수 있습니다.
프로젝트에 코드 적용 범위를 설정하면 코드를 유지 관리하고 쉽게 변경할 수 있으며 대부분 또는 모든 응용 프로그램을 포괄하는 테스트를 사용하면 프로덕션 환경에서 문제가 발생하지 않을 가능성이 더 높아집니다.

![](/img/posts/post-18/002.png){: .center-block :}

### Maintainability
소나 유지 보수성은 미리 정의 된 규칙 세트 (사용중인 Lint 기준)에 따라 코드 수와 코드에 기술 부채가 있습니다. Sonar는 각 섹션에 대해 간단한 등급을 제공하므로 분석중인 앱의 성능을 빠르게 확인할 수 있습니다.

![](/img/posts/post-18/003.png){: .center-block :}

### Reliability
안정성은 정확성, 발견 및 수정된 버그 수, 응용 프로그램의 일관성 및 알려진 코드 루틴 결과에 대한 일관성과 동일합니다.

![](/img/posts/post-18/004.png){: .center-block :}

### Security
보안과 관련하여 Sonar는 프로젝트에서 발견 될 수있는 취약점의 수를 다룹니다. 모든 취약점 문제를 해결하기위한 노력이 몇 분 안에 나타납니다.

![](/img/posts/post-18/005.png){: .center-block :}


## Setting up Sonar for Swift
### Step 1. SonarQube 다운로드 및 설정
1. [SonarQube 다운로드](https://www.sonarqube.org/downloads/)
2. 압축을 푼 후 SonarQube로 이름을 변경합니다.
3. 변경한 폴더를 /Applications/으로 이동합니다.

### Step 2. SonarScanner 다운로드 및 설정
1. [SonarScanner 다운로드](https://docs.sonarqube.org/display/SCAN/Analyzing+with+SonarQube+Scanner)
2. 압축을 푼 후 SonarScanner로 이름을 변경합니다.
3. 변경한 폴더를 /Applications/으로 이동합니다.

### Step 3. .bash_profile 업데이트
1. 터미널을 시작하고 다음 명령을 실행합니다.
```
cd ~/
vi .bash_profile
```
2. 가장 마지막 줄로 이동하여 i를 눌러 아래의 명령어를 추가합니다.
```
# Sonar Setting
export PATH=$PATH:/Applications/SonarScanner/bin
export PATH=$PATH:/Applications/SonarQube/bin
```
3. esc를 누르고 wq 입력하고 종료합니다.

### Step 4. Backlite에서 SonarSwift 설정
1. [SonarSwift jar다운로드](https://github.com/Backelite/sonar-swift/releases)
2. 다운받은 jar 파일을 /Applications/SonarQube/extensions/plugins/ 으로 이동시킵니다.

### Step 5. SonarQube 시작
1. SonarQube 서버를 시작하려면 다음 명령어를 실행합니다.
```
sh /Applications/SonarQube/bin/macosx-universal-64/sonar.sh console
```
2. 만약 자바가 설치되어 있지 않다면 [여기서](https://www.oracle.com/technetwork/java/javase/downloads/index-jsp-138363.html#javasejdk) 다운받으면됩니다.
3. 모든게 잘 작동한다면 아래의 로그를 볼 수 있습니다.
```
Running SonarQube…
wrapper | → Wrapper Started as Console
wrapper | Launching a JVM…
jvm 1 | Wrapper (Version 3.2.3) http://wrapper.tanukisoftware.org
jvm 1 | Copyright 1999–2006 Tanuki Software, Inc. All Rights Reserved.
jvm 1 |
jvm 1 | 2019.03.12 11:49:46 INFO app[][o.s.a.AppFileSystem] Cleaning or creating temp directory /Applications/SonarQube/temp
jvm 1 | 2019.03.12 11:49:46 INFO app[][o.s.a.es.EsSettings] Elasticsearch listening on /127.0.0.1:9001
jvm 1 | 2019.03.12 11:49:47 INFO app[][o.s.a.p.ProcessLauncherImpl] Launch process[[key=’es’, ipcIndex=1, logFilenamePrefix=es]] from [/Applications/SonarQube/elasticsearch]: /Applications/SonarQube/elasticsearch/bin/elasticsearch -Epath.conf=/Applications/SonarQube/temp/conf/es
jvm 1 | 2019.03.12 11:49:47 INFO app[][o.s.a.SchedulerImpl] Waiting for Elasticsearch to be up and running
jvm 1 | 2019.03.12 11:49:47 INFO app[][o.e.p.PluginsService] no modules loaded
jvm 1 | 2019.03.12 11:49:47 INFO app[][o.e.p.PluginsService] loaded plugin [org.elasticsearch.transport.Netty4Plugin]
jvm 1 | 2019.03.12 11:49:54 INFO app[][o.s.a.SchedulerImpl] Process[es] is up
```
