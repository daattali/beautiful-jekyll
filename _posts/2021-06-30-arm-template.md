---
layout: post
title:  "Azure ARM Template 사용하여 배포하기"
date:   2021-06-30 13:40:00 +0900
author: Changbae Bang
tags: [azure, arm, batch, deploy,  ]
---

# ARM Template 을 사용하여 Batch 를 배포
JSON 파일을 사용하여 Batch(account, pool 그리고 storage 들)을 배포하는 샘플을 작성해 보았습니다.

[코드 링크](https://github.com/changbaebang/azure_arm_template/blob/main/batch/withFileShare/azuredeploy.json)

[배포 링크](https://github.com/changbaebang/azure_arm_template/blob/main/batch/withFileShare/READM.md)

원래는 linked template 을 사용하려고 했는데 dependency 설정이... 안습이 되어서...  
하나로 합쳐서 만들어 놓았습니다.


# ARM Template 이란?
ARM Template 은 반복적인 배포를 편하게 돕는 제품입니다.  
배포 동작 자체를 코드로서 만들어 관리할 수 있습니다.  

JSON 과 Bicep이라는 언어로 작성할 수 있습니다.  

[공식 문서](https://docs.microsoft.com/ko-kr/azure/azure-resource-manager/templates/overview)  


작성한 JSON 샘플 코드를 살펴 보면
parameters, variables, resources 로 구분이 됩니다.

## parameters
Portal 이나 Powershell 을 통해 deploy 할 때 뭔가 전달하여 설정할 수 있는 값들입니다.

```
"parameters": {
    "batchAccountName": {
      "type": "string",
      "defaultValue": "[concat(toLower(uniqueString(resourceGroup().id)), 'batch')]",
      "metadata": {
        "description": "Batch Account Name"
      }
    }, ...
```

[안내 문서](https://docs.microsoft.com/ko-kr/azure/azure-resource-manager/templates/template-tutorial-add-parameters?tabs=azure-powershell)  
[설명 문서](https://docs.microsoft.com/ko-kr/azure/azure-resource-manager/templates/parameters)

## variable
내부에서 사용하는 변수입니다. 내부적으로 반복 사용하는 값이 있으면 편하겠죠?
```
"variables": {
    "storageAccountName": "[concat(uniqueString(resourceGroup().id),'storage')]",
    "shareAccountName": "[concat(uniqueString(resourceGroup().id),'share')]",
    "accountKind" : "StorageV2",
    "skuName": "Standard_LRS",
    "skuTier": "Standard",
    "vmSize": "STANDARD_D2S_V3"
},
```

[안내 문서](https://docs.microsoft.com/ko-kr/azure/azure-resource-manager/templates/template-tutorial-add-variables?tabs=azure-powershell)  
[설명 문서](https://docs.microsoft.com/ko-kr/azure/azure-resource-manager/templates/variables)

## 함수
`concat` 이나 `toLower` 등 많은 함수를 지원합니다.

[안내 문서](https://docs.microsoft.com/ko-kr/azure/azure-resource-manager/templates/template-functions)

## resources
이건 배포할 것들이 됩니다.

[안내 문서](https://docs.microsoft.com/ko-kr/azure/azure-resource-manager/templates/template-tutorial-add-resource?tabs=azure-powershell)  

## 이미 있는 리소스가 있다면?
Template 으로 내보낼 수 있습니다.
![Foo](https://docs.microsoft.com/ko-kr/azure/azure-resource-manager/templates/media/export-template-portal/select-all-resources.png)

이 틀을 기반으로 parameter 나 variable 설정을 잘 만들어도 활용이 잘 되는 것을 만들수 있다고 생각합니다.

[안내 문서](https://docs.microsoft.com/ko-kr/azure/azure-resource-manager/templates/export-template-portal)


# Batch 는?
대규모 병렬 및 HPC(고성능 컴퓨팅) 일괄 작업을 할 때 사용할 수 있습니다.  
인스턴스 여럿을 만들어서 Task 를 실행시킬 수 있습니다.  
[안내 문서](https://docs.microsoft.com/ko-kr/azure/batch/batch-technical-overview)

# 만들면서 아쉬운 것
`relativeMountPath` 설정할 때 `/` 로 시작해서도 안되고 2 depth 를 두어서도 동작을 안합니다.  
금방 고칠 수 있을 것 같은데.. 이럴 때 다시 git 에 commit 하는 일을 하고 싶다는 생각이 들지만 현재는 실제고 실제는 실존이라...  
뭐 그냥 오늘은 여기까지만 할까 합니다.


# 결론은
계속 인프라를 반복 배포해야 한다면 만들어볼 필요가 있고
CLI, Rest API 등으로 사용할 수 있기 때문에 배포 자동화에 어느 정도 큰 기여를 할 수 있다고 생각합니다.

[안내 문서](https://docs.microsoft.com/ko-kr/azure/azure-resource-manager/templates/deploy-rest)

