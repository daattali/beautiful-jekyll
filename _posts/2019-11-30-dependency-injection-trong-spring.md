---
layout: post
title: Dependency Injection trong Spring
author: [tony]
categories: [technology]
tags: [blockchain]
comments: true
---

Author: [@tonybui](https://github.com/tonybuivn)


# Giới thiệu
Bài đầu tiên trong series về Spring của mình sẽ là về khái niệm ***Dependency Injection***.

***Dependency Injection*** là một khái niệm không mới, nhưng lại vô cùng quan trọng, không chỉ trong Spring mà còn trong rất nhiều các Framework khác. 
Để có thể hiểu được về cách thức Spring làm việc, thì đây là một khái niệm bắt buộc phải nắm vững.

Thuật ngữ ***Dependency Injection*** thoạt nghe có vẻ rất hàn lâm, nó khiến người ta liên tưởng đến những kỹ thuật lập trình, hoặc những mẫu thiết kế Design Pattern phức tạp. Nhưng thực ra, ***Dependency Injection*** không hề phức tạp như mọi người vẫn nghĩ.
Bằng cách áp dụng ***Dependency Injection***  vào dự án của mình, bạn sẽ thấy code trở nên đơn giản một cách đáng kể, tăng tính đọc hiểu, đơn giản hóa quá trình test, không chỉ cho bạn mà cho cả team-mate.

# Dependency Injection là gì ?
Trước khi bắt đầu với **Dependency Injection**, các bạn có thể tham khảo các bài viết về nguyên lý S.O.L.I.D trên kipalog ở [đây](https://kipalog.com/posts/SOLID-la-gi---Ap-dung-cac-nguyen-ly-SOLID-de-tro-thanh-lap-trinh-vien-code--cung), hoặc tham khảo bài viết bằng tiếng Anh ở [đây](https://scotch.io/bar-talk/s-o-l-i-d-the-first-five-principles-of-object-oriented-design).
Nguyên lý cuối cùng trong S.O.L.I.**D** chính là **Dependency Inversion** (Đảo ngược sự phụ thuộc)
Nội dung của nguyên lý đó như sau :
1. Các module cấp cao không nên phụ thuộc vào các module cấp thấp. Cả 2 nên phụ thuộc vào abstraction.
2. Interface (abstraction) không nên phụ thuộc vào chi tiết, mà ngược lại, chi tiết nên phụ thuộc vào abstraction. ( Các class giao tiếp với nhau thông qua interface, không phải thông qua implementation)

> ***Dependency Inversion***  thì liên quan gì đến ***Dependency Injection*** nhỉ ?

Dependency Injection dịch ra tiếng Việt nghĩa là gì ?
Dependency = sự phụ thuộc
Injection = tiêm nhiễm, tiêm phòng hay ... tiêm chích ?
Vậy ***Dependency Injection*** có thể hiểu là *tiêm nhiễm sự phụ thuộc*, nhưng cái gì tiêm, và tiêm vào đâu nhỉ ?

![dependency injection](https://i0.wp.com/samueleresca.net/wp-content/uploads/2017/02/How-To-Use-Dependency-Injection-in-ASP.NET-MVC-6.jpg?fit=700%2C485&ssl=1)


Okay, tạm gác lý thuyết đó qua một bên, chúng ta cùng đi vào ví dụ cho dễ hình dung hơn nhé. Giả sử chúng ta có một anh chàng dũng sĩ đẹp trai được định nghĩa trong class `DungSiDepTrai` như sau :
```java
public class DungSiDepTrai implements DungSi {
	private NhiemVuDietRong nhiemvu;

	public DungSiDepTrai() {
    	this.nhiemvu = new NhiemVuDietRong();
    }

	public void thucHienNhiemVu() {
    	nhiemvu.thucHien();
    }
}
```
Anh chàng Dũng sĩ đẹp trai này đang được giao cho nhiệm vụ đó là phải tiêu diệt một con rồng hung dữ. Bạn có thể thấy, trong class `DungSiDepTrai` có một trường dữ liệu là `nhiemvu` với kiểu `NhiemVuDietRong` và được khởi tạo trong constructor của class này. Tuy nhiên, điều này sẽ khiến cho `DungSiDepTrai` bị *liên kết chặt chẽ* với `NhiemVuDietRong`. 

Ở đây, `NhiemVuDietRong` chính là một ***Dependency (phụ thuộc)*** của `DungSiDepTrai`, hay nói cách khác là `DungSiDepTrai` *bị phụ thuộc* vào `NhiemVuDietRong`.

> *Liên kết chặt chẽ* như vậy thì có vấn đề gì không nhỉ ???

*Liên kết chặt chẽ* thì sẽ có rất rất nhiều vấn đề.
Khi có một con rồng cần tiêu diệt, anh chàng dũng sĩ có thể hoàn thành tốt nhiệm vụ đó, nhưng khi công chúa muốn nhờ dũng sĩ tìm hộ con mèo bị mất tích, hay khi hoàng hậu muốn sai dũng sĩ đi chợ mua ít rau dền, v.v... thì sao ?

Để giải quyết những nhiệm vụ mới được giao này, anh chàng dũng sĩ sẽ phải khởi tạo các đối tượng có kiểu `NhiemVuTimMeo`, `NhiemVuMuaRauDen`,... trong constructor. Điều này sẽ khiến cho class `DungSiDepTrai` phình to ra, code trở nên phức tạp hơn rất nhiều.

Hơn nữa, chúng ta có thể thấy `new NhiemVuDietRong()` là một implementation của `NhiemVuDietRong`. Khi chúng ta muốn thay đổi implementation của `NhiemVuDietRong`, chẳng hạn anh chàng dũng sĩ này muốn thay đổi chiến thuật, thay vì dùng kiếm và khiên để chiến đấu mặt đối mặt trực tiếp với con rồng, anh ta sẽ chuốc thuốc mê nó rồi tiêu diệt trong nhẹ nhàng thì sao. Lúc này  chúng ta lại bắt buộc phải động đến `DungSiDepTrai`, hay tệ hơn nữa là phải duplicate ra một implementation mới.

Một ví dụ khác dễ thấy hơn là khi chúng ta muốn test `DungSiDepTrai`. Chẳng hạn, khi bạn muốn test để chắc chắn rằng phương thức `thucHien()` sẽ được gọi chính xác 1 lần khi gọi phương thức `thucHienNhiemVu()`, lúc này bạn sẽ phải *mock* thành object ảo, và phải viết test ở ngay trong `DungSiThongThai`. Vô cùng phức tạp phải không nào.

Đẹp trai thôi chưa đủ, các dũng sĩ còn phải cần thông thái và sáng suốt nữa.

> Vậy *liên kết* có cần thiết không ?

Câu trả lời tất nhiên là ... có rồi.

*Liên kết* (coupling) giống như một con dao 2 lưỡi. Một mặt, việc *liên kết chặt chẽ* khiến cho việc test trở nên khó khăn, code khó sử dụng lại, khó nắm bắt. Với những dự án có độ phức tạp đủ lớn, đôi khi việc fix bug sẽ giống như chơi trò chơi [whack-a-mole](https://en.wikipedia.org/wiki/Whac-A-Mole) vậy (việc fix một bug có thể dẫn đến việc tạo ra một hoặc nhiều bug mới).

Tuy nhiên, ở mặt khác, một lượng *liên kết* nhất định luôn cần thiết. Một dự án mà không có *liên kết* nào thì sẽ chẳng có ý nghĩa gì cả. Các class cần phải biết về nhau bằng một cách nào đó. *Liên kết* là cần thiết nhưng nên được quản lý một cách hợp lý.

Vậy chúng ta có thể hiểu, ***Dependency Injection*** nghĩa là các đối tượng (object) sẽ không cần quan tâm đến việc khởi tạo hay get các *phụ thuộc (dependency)* của mình, thay vào đó, sẽ có một bên thứ 3 đứng ra, *tiêm (inject)* các *dependency* này vào đối tượng.

Đến đây chúng ta có thể phân biệt 2 khái niệm
1. **Dependency Inversion** : là một nguyên lý thiết kế, có nghĩa là *đảo ngược sự phụ thuộc*.
2. **Dependency Injection** : là một cách thức để thực hiện dựa theo nguyên lý *Dependency Inversion*

Các bạn có thể hình dung ***Dependency Injection*** giống như, một bệnh nhân không cần quan tâm đến các loại thuốc cần thiết phải tiêm vào người mình để chữa khỏi bệnh, đã có một *bác sĩ* lo chuyện này. Vậy trong Spring, vị *bác sĩ* đó là ai, xin mời đọc tiếp phần sau.

# Dependency Injection trong Spring hoạt động như nào ?
Để hiểu rõ hơn về cách ***Dependency Injection*** hoạt động trong Spring, chúng ta hãy cùng xem `DungSiThongThai` dưới đây, anh ko những vừa đẹp trai, lại còn thông minh, dũng cảm. Không nhiệm vụ nào có thể làm khó được anh, từ tiêu diệt rồng cho đến tìm mèo cho công chúa, mua rau dền cho hoàng hậu,... anh đều có thể giải quyết trong một nốt nhạc.

```java
public class DungSiThongThai implements DungSi {
	private NhiemVu nhiemvu;

	public DungSiThongThai(NhiemVu nhiemvu) {
    	this.nhiemvu = nhiemvu;
    }

	public void thucHienNhiemVu() {
    	nhiemvu.thucHien();
    }
}
```

Các bạn có thể thấy, `DungSiThongThai`, không giống như `DungSiDepTrai`, anh không hề khởi tạo một đối tượng nhiệm vụ cụ thể nào trong constructor của mình. Thay vào đó, anh ấy truyền `nhiemvu` như là một tham số vào constructor tại thời điểm khởi tạo.
Đây là một kiểu của ***Dependency Injection*** được biết với tên **constructor injection**
(Ngoài  **Constructor injection** ra, trong Spring còn có một cách triển khai *Dependency Injection* là **Setter Injection**, mình xin phép giải thích ở một bài khác)

Trường dữ liệu `nhiemvu` của `DungSiThongThai` có kiểu là `NhiemVu`, một *interface* mà tất cả các class nhiệm vụ khác sẽ implement. Do đó, `DungSiThongThai` có thể thực hiện bất kỳ `NhiemVu` nào, từ `NhiemVuDietRong`,  `NhiemVuTimMeo` cho đến `NhiemVuMuaRauDen`,... miễn là nhiệm vụ đó có implement `NhiemVu`.

Điểm mấu chốt ở đây là `DungSiThongThai` không liên kết với bất kỳ một implementation cụ thể nào của `NhiemVu`. Người ta gọi đó là *liên kết lỏng*, đây cũng là lợi ích chính của ***Dependency Injection***. 
Nếu một đối tượng chỉ biết về các *dependency* (phụ thuộc) của nó thông qua interface của các *dependency* này (chứ không phải implementation của chúng), khi đó các *dependency* có thể dễ dàng thay đổi implementation của mình mà không làm ảnh hưởng đến đối tượng ban đầu.

Như đã nói ở trước, một trong những ví dụ phổ biến của việc một dependency bị thay đổi đó là khi chúng ta thực hiện test với một implementation *mock*. Bạn sẽ gặp nhiều khó khăn, quản lý code phức tạp khi test `DungSiDepTrai` có *liên kết chặt* với `NhiemVuDietRong`, nhưng bạn có thể dễ dàng test `DungSiThongThai` bằng cách sử dụng một implementation *mock* của `NhiemVu` như sau :

```java
import static org.mockito.Mockito.*;
import org.junit.Test;

public class DungSiThongThaiTest {
	@Test
    public void dungSiNenThucThiNhiemVu() {
  		NhiemVu nhiemVuMock = mock(NhiemVu.class);
 		DungSiThongThai dungsi = new DungSiThongThai(nhiemvuMock);
		dungsi.thucHienNhiemVu();
        verify(nhiemVuMock, time(1)).thucHien();
  	}
}
```
Trong đoạn code trên mình có sử dụng một framework đó là *Mockito* để tạo ra một implementation *mock* (giả lập) của interface `NhiemVu`. Đầu tiên là khởi tạo một instance của `DungSiThongThai` và truyền đối tượng giả lập `nhiemVuMock` vừa tạo qua constructor. Sau khi `dungsi` gọi phương thức `thucHienNhiemVu()`, *Mockito* sẽ test để xác nhận rằng phương thức `thucHien()` của `nhiemVuMock` chỉ được gọi chính xác 1 lần. 

Class `DungSiThongThai` đã được viết theo cách để bạn có thể giao cho anh ta bất kỳ nhiệm vụ nào bạn muốn. Ví dụ, khi bạn muốn anh chàng dũng sĩ này đi mua rau dền cho hoàng hậu, chúng ta sẽ có class `NhiemVuMuaRauDen` như dưới đây

```java
import java.io.PrintStream;

public class NhiemVuMuaRauDen implements NhiemVu {
	private PrintStream stream;

	public NhiemVuMuaRauDen(PrintStream stream) {
    	this.stream = stream;
    }
  
	public void thucHien() {
    	stream.println("Đang đi mua rau dền cho hoàng hậu...");
    }
}
```

> Sau khi đã có `NhiemVuMuaRauDen`, tiếp theo làm thế nào để có thể *giao* nó  cho `DungSiThongThai` nhỉ ?

Trong Spring, việc tạo ra một sự liên kết giữa các thành phần của ứng dụng thường được gọi là *wire (kết nối)*. Có rất nhiều cách để kết nối các thành phần lại với nhau, một phương pháp phổ biến thường được sử dụng là thông qua XML. 

Dưới đây là một đoạn mã XML đơn giản trong file cấu hình **dungsi.xml** của Spring. File cấu hình này sẽ liên kết `DungSiThongThai` và `NhiemVuMuaRauDen` lại với nhau, và chỉ có **dungsi.xml** mới biết nhiệm vụ nào sẽ được giao cho `DungSiThongThai`
```java
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
	xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation="http://www.springframework.org/schema/beans
	http://www.springframework.org/schema/beans/spring-beans.xsd">

<bean id="dungsi" class="com.kaopiz.dungsi.DungSiThongThai">
	<constructor-arg ref="nhiemvu" />
</bean>

<bean id="nhiemvu" class="com.kaopiz.nhiemvu.NhiemVuMuaRauDen">
	<constructor-arg value="#{T(System).out}" />
</bean>
```

Trong file cấu hình trên, `DungSiThongThai` và `NhiemVuMuaRauDen` đã được khai báo như là các *bean* trong Spring. Đối với *bean* `DungSiThongThai`, chúng ta truyền vào constructor của nó một tham chiếu đến *bean* `NhiemVuMuaRauDen`. 

Mặc dù `DungSiThongThai` phụ thuộc vào `NhiemVu`, anh ta không hề biết nhiệm vụ nào sẽ được giao cho mình. Tương tự  `NhiemVuMuaRauDen` cũng phụ thuộc vào `PrintStream`, nhưng nó sẽ không biết kiểu *Stream* nào sẽ được dùng. Chỉ có Spring, thông qua các file cấu hình của mình biết được bức tranh toàn cảnh. 

Đến đây, chắc các bạn cũng đã nhận ra vị *bác sĩ* mà mình đề cập đến ở phần trước chính là **dungsi.xml** rồi phải không.

# Lắp ghép các thành phần
Chúng ta đã hoàn thành việc khai báo mối quan hệ giữa `DungSiThongThai` và `NhiemVu`. Việc cuối cần phải làm là load file cấu hình XML, lắp ghép các thành phần lại với nhau và start ứng dụng.

Trong một ứng dụng Spring, một *application context* sẽ load các bean được định nghĩa trong file cấu hình và liên kết chúng lại với nhau. *Spring application context* chịu trách nhiệm hoàn toàn việc tạo và liên kết các đối tượng để xây dựng nên một ứng dụng Spring hoàn chỉnh.

Spring có nhiều implementation của *application context*. Trong VD của bài này, các bean được định nghĩa bằng XML, nên lựa chọn thích hợp cho *application context* sẽ là **ClassPathXmlApplicationContext**. Dưới đây là class **main** của ứng dụng

```java
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class DungSiMain {
	public static void main(String[] args) throws Exception {
    	ClassPathXmlApplicationContext context =
   			new ClassPathXmlApplicationContext("META-INF/spring/dungsi.xml");
  		DungSi dungsi = context.getBean(DungSi.class);
 		dungsi.thucHienNhiemVu();
		context.close();
    }
}
```

Trong class `DungSiMain` ở trên, *application context* được sử dụng để lấy bean có ID là *dungsi*. Đối tượng `dungsi` sau khi lấy được sẽ gọi hàm `thucHienNhiemVu()`, để thực hiện nhiệm vụ mà anh ta đã được giao (được cấu hình trong file dungsi.xml).
Lưu ý rằng class **main** này không hề biết về loại `NhiemVu` mà anh chàng dũng sĩ cần phải thực hiện, chỉ có duy nhất **dungsi.xml** biết điều này.

# Kết bài
Trong bài này mình đã giới thiệu về ***Dependency Injection*** cũng như cách thức sử dụng nó trong Spring.
Đây là một khái niệm cơ bản nhưng vô cùng quan trọng nếu muốn tìm hiểu hoặc làm việc sâu hơn với Spring.
Hẹn gặp lại các bạn trong các bài viết tiếp theo về Spring ^^

Bài viết có tham khảo các tài liệu
* [Spring In Action 4th](https://www.manning.com/books/spring-in-action-fourth-edition)
* [S.O.L.I.D: The First 5 Principles of Object Oriented Design](https://scotch.io/bar-talk/s-o-l-i-d-the-first-five-principles-of-object-oriented-design)
* [Trở lại với cơ bản: OOP, Dependency Injection và Cake Pattern](https://kipalog.com/posts/Tro-lai-voi-co-ban--OOP--Dependency-Injection-va-Cake-Pattern)