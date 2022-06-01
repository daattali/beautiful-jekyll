---
layout: single
title: XML 파싱 및 수정을 위한 파이썬 내장 라이브러리 (xml)
tags: [python library, xml]
categories: python_lib
---

XML은 hierachical 데이터 형식이고 이를 나타내는 방법은 일반적으로 트리가 있다.  
elementTree는 이 목적을 달성하기 위해 두 가지 클래스를 가진다.   
- ElementTree는 전체 XML 문서를 트리로 나타낸다.      
- Element는 트리에 있는 단일 노드를 나타낸다.   
파일 읽기와 쓰기 등의 전체 문서 상호작용은 ElementTree에서 이뤄진다.   
단일 xml 엘리먼트와 서브 xml 엘리먼트의 상호작용은 Element에서 이뤄진다.   



## 1.모듈 임포트
```
from xml.etree.ElementTree import Element, SubElement, ElementTree
```

## 2.데이터 로드 방법
파싱 방법에는 파일형태와 문자열 형태가 있다.   
1. xml이 파일형태로 존재할 경우.    
경로와 함께 parser() 메소드를 사용.    
```
tree = ElementTree.parse('경로')
root = tree.getroot()
```
2. 문자열 형태로 불러오고 싶은 경우.
```
root = ElementTree.fromstring(string_data)   
```

## 3.파싱 방법  
root에는 tag와 attribute dict이 있다.   
```
>>> root.tag
또는
>>> root.attrib
```

아래는 파싱 튜토리얼을 위한 샘플 데이터   
```
<?xml version="1.0"?>
<data>
    <country name="Liechtenstein">
        <rank>1</rank>
        <year>2008</year>
        <gdppc>141100</gdppc>
        <neighbor name="Austria" direction="E"/>
        <neighbor name="Switzerland" direction="W"/>
    </country>
    <country name="Singapore">
        <rank>4</rank>
        <year>2011</year>
        <gdppc>59900</gdppc>
        <neighbor name="Malaysia" direction="N"/>
    </country>
    <country name="Panama">
        <rank>68</rank>
        <year>2011</year>
        <gdppc>13600</gdppc>
        <neighbor name="Costa Rica" direction="W"/>
        <neighbor name="Colombia" direction="E"/>
    </country>
</data>
```

root에 이터레이트를 할 수 있는 자식 노드를 아래와 같이 불러올 수 있다.    
```
>>> for child in root:
...     print(child.tag, child.attrib)
...
country {'name': 'Liechtenstein'}
country {'name': 'Singapore'}
country {'name': 'Panama'}
```
엘리먼트를 찾기 위해 여러 방법을 사용할 수 있다.   

- 아래있는 모든 서브 트리를 재귀적으로 이터레이트하여 특정 태그를 서치할 경우 : Element.iter()   
```
>>> for neighbor in root.iter('neighbor'):
...     print(neighbor.attrib)
...
{'name': 'Austria', 'direction': 'E'}
{'name': 'Switzerland', 'direction': 'W'}
{'name': 'Malaysia', 'direction': 'N'}
{'name': 'Costa Rica', 'direction': 'W'}
{'name': 'Colombia', 'direction': 'E'}
```
- 현재 엘리먼트의 direct child에서만 서치할 경우 : Element.findall('{name}')    
- 엘리먼트의 cotent를 얻으려는 경우 : Element.text   
- 엘리먼스의 attribute 값을 얻으려는 경우 : Element.get('{attribute}')
```
>>> for country in root.findall('country'):
...     rank = country.find('rank').text
...     name = country.get('name')
...     print(name, rank)
...
Liechtenstein 1
Singapore 4
Panama 68
```
### 4. 수정 방법
- tree의 변경을 반영하고자 하는 경우 : ElementTree.write()
- element의 content를 바꾸려는 경우 : Element.text로 값을 가져온 후 직접 변경
- element의 attribute를 수정하는 경우 : Element.set(key, value)
- element에 자식 노드를 추가할 경우 : Element.append()
```
>>> for rank in root.iter('rank'):
...     new_rank = int(rank.text) + 1
...     rank.text = str(new_rank)
...     rank.set('updated', 'yes')
...
>>> tree.write('output.xml')
``` 

- 또는  SubElement를 이용해 자식노드를 다음과 같이 편리하게 만들 수 있다.
xml.etree.ElementTree.SubElement(parent, tag, attrib={}, **extra)¶
```
>>> a = ET.Element('a')
>>> b = ET.SubElement(a, 'b')
>>> c = ET.SubElement(a, 'c')
>>> d = ET.SubElement(c, 'd')
>>> ET.dump(a)
<a><b /><c><d /></c></a>
```

## 3. 참고
https://dololak.tistory.com/253
https://docs.python.org/ko/3/library/xml.etree.elementtree.html
https://sjh836.tistory.com/118?category=687142

#### *XML 구성요소
(1) XML element   
element는 아래처럼 시작과 종료 태그로 한쌍이 되어야 함.  


<태그명>요소내용</태그명>    
요소내용은 PCDATA(Parsed Character DATA)라고 함.   
데이터가 비어있는 경우 <태그명/>으로 사용가능   


(2) XML Attribute   
태그 내에 인라인으로 정보나 데이터를 표현하는 것.  
<!-- 태그 표현 --> <product> <id>50</id> <name>samsung</name> <category>computer</category> <price>1500000</price> </product> <!-- 속성 표현 --> <product id="50" name="samsung" category="computer" price="1500000"> </product>

