# try..catch 블록

자바와 달리 함수 시그니처에 예외를 지정하지 않는다.

```kotlin
fun sendFormData(user: User?,data:Data?){
	user?: throw NullPointerException("User cannot be null")
	data ?: throw NullPointerException("Data cannot be null")
```

데이터의 유효성을 검사하고 nullpointerException을 생성한다.

```kotlin
fun onSendDataClicked(){
	try{
		sendFormData(usermdata)
} catch(e:AssertionError){
// 오류 처리
} finally {
	//선택적인 finally 블록
}//finally는 항상 실행된다.
```

설치여부확인하기.

```kotlin
val result = try{
	context.packageManager.getPackageInfo("com.text.app",0)
	true
} catch (ex: PackageManger.NameNotFoundException){
	false
}
```

getPackageInfo가 PackageManer.NameNotFoundException을 생성하며 catch블록이 실행