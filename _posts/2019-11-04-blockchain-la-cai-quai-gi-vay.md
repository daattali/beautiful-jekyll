---
layout: post
title: Block chain là cái quái gì vậy ???
author: [tony]
categories: [technology]
tags: [blockchain]
comments: true
---

Author: [@tonybui](https://github.com/tonybuivn)



Trừ khi bạn là người Sao Hỏa, còn không mình chắc chắn bạn đã từng nghe nói đến Bitcoin và Blockchain. 

Đây là 2 từ khóa nổi bật, là xu hướng, là chủ đề ưa thích trong thời gian gần đây - buzzword of the years. Ngay cả với những người chưa từng quan tâm đến [cryptocurrency](http://bitcoinvietnamnews.com/2017/02/cryptocurrency-la-gi.html) hay hiểu cách nó hoạt động cũng bàn luận về nó. Tôi có nhiều người bạn không làm trong ngành kỹ thuật, và vài tuần trở lại đây họ luôn buzzing tôi để nhờ giải thích về những từ khóa mới này. Tôi đoán có hàng ngàn người ngoài kia cũng có cảm giác tương tự như vậy.

# 1. Blockchain - Tại sao chúng ta phải cần một thứ gì đó phức tạp

> “***For every complex problem there is an answer that is clear, simple, and wrong***.” — H. L. Mencken

Không giống như những bài viết khác trên internet, thay vì định nghĩa khái niệm blockchain ngay từ đầu, chúng ta sẽ cũng thử tìm hiểu vấn đề mà blockchain giải quyết ở đây là gì.

Hãy thử tưởng tượng thế này, Joe là thằng bạn thân của bạn. Nó đi du lịch khắp mọi nơi trên thế giới, và đến ngày thứ 50 của chuyến đi, nó gọi cho bạn và nói "Hey dude, tao đang kẹt tiền quá. Đi du lịch tiêu quá tay hết cmnr".

Bạn đáp lại "Okay dude, chờ tí gửi ngay đây"

![Joe](https://cdn-images-1.medium.com/max/1000/1*BV9t2KZxRV6_ADIsV9OybQ.png)

Bạn liền gọi cho người quản lý tài khoản ở ngân hàng nơi bạn gửi tiền và bảo anh ấy "Hãy chuyển 1000$ từ tài khoản của tôi tới tài khoản của Joe nhé"

> Yes. sir

Người quản lý mở sổ cái, kiểm tra số dư trong tài khoản xem bạn có đủ 1000$ để chuyển cho Joe hay ko. 

Bởi vì bạn là người có tiền, do đó 1000$ không thành vấn đề, người quản lý sẽ tạo một mục trong cuốn sổ cái của bạn có dạng như sau

![transaction register](https://cdn-images-1.medium.com/max/1600/1*PJ8pYM3jjJAEEkxwOxoRdg.png)

*__Lưu ý__ : chúng ta sẽ bỏ qua các vấn đề phức tạp của máy tính để giữ cho mọi thứ đơn giản*

Bạn gọi cho Joe và bảo nó " Hey dude, tao chuyển tiền rồi đấy. Mày chỉ cần đến ngân hàng là rút được thôi"

![](https://cdn-images-1.medium.com/max/1600/1*nS_5WE-WmhuNioLX8ki4lA.png)

Hãy cùng suy nghĩ xem chuyện gì vừa xảy ra ? Cả bạn và Joe đều tin tưởng vào ***Ngân hàng*** để quản lý tiền của mình. Việc chuyển tiền thực chất chỉ là một chỉ mục trong cuốn sổ cái của bạn. Hay chính xác hơn, là một chỉ mục trong cuốn sổ mà cả bạn và joe đều không quản lý hay sở hữu.

Và đó chính là vấn đề của các hệ thống đang tồn tại.

> Để tạo dựng niềm tin giữa các cá nhân, chúng ta phải phụ thuộc vào một bên thứ ba

Trong nhiều năm qua, chúng ta đều phải phụ thuộc vào những bên trung gian để có thể tin tưởng lẫn nhau. ***Vậy, phụ thuộc vào họ thì có vấn đề gì ?***

* Điều gì sẽ xảy ra nếu cuốn sổ cái lưu trữ những giao dịch của bạn bị hack, bị xóa ?
* Sẽ thế nào nếu giả sử giao dịch của bạn bị nhập lỗi, bạn bị chuyển khoản 1500$ thay vì 1000 ?
* Hay sẽ thế nào nếu bạn biết người quản lý thực hiện những việc trên với ý đồ riêng ?

> Trong suốt nhiều năm qua, chúng ta đều đã đặt tất cả số trứng mình có vào một cái giỏ, và thậm chí nó cũng chẳng phải là giỏ của mình.

**Vậy liệu có thể có một hệ thống chúng ta có thể dùng để chuyển tiền mà không cần nhờ đến ngân hàng ko ?**

Để trả lời câu hỏi này, chúng ta cần phải đào sâu hơn nữa, và đặt ra một câu hỏi tốt hơn (sau tất cả, chỉ có những câu hỏi tốt mới dẫn đến những câu trả lời tốt @@)

Hãy thử suy nghĩ một chút, khái niệm "**chuyển tiền**" thực ra nghĩa là gì ? Đối với ngân hàng, đó chỉ là một chỉ mục trong cuốn sổ cái phải không ? Vậy thì câu hỏi cần đặt ra là 

> Liệu có cách nào để duy trì nội dung của cuốn sổ cái giữa chúng ta thay vì phải nhờ đến *__ai khác__* làm hộ chúng ta việc đó ?

Đó là một câu hỏi đáng giá. Hiển nhiên bạn hoàn toàn có thể đoán ra được câu trả lời. Đó chính là *__blockchain__*.

*__Blockchain__* là một phương thức để duy trì cuốn sổ cái giữa tất cả các người dùng, thay vì phải phụ thuộc vào ai khác.

Bạn vẫn tiếp tục đọc đến đây chứ. Thật tuyệt, bởi vì ngay từ lúc này, sẽ có rất nhiều câu hỏi nảy ra trong đầu bạn, và chúng ta sẽ cùng nhau tìm hiểu hệ thống *__sổ cái phân tán__* (distributed register) này hoạt động như thế nào nhé.

# 2. Okay. Giờ thì hãy nói cho tôi biết cái Blockchain này hoạt động như thế nào đi

Yêu cầu chính của phương thức này, đó là phải có đủ số lượng người cần thiết, những người không muốn tiền của họ bị phụ thuộc vào một bên thứ ba. Chỉ có như vậy nhóm người này mới có thể tự duy trì được sổ cái của họ.

Một câu hỏi đặt ra là, bao nhiêu người thì được coi là *đủ* ? 

> Ít nhất là ba ?

Trong ví dụ sau đây, giả sử có 10 người muốn không phải phụ thuộc vào ngân hàng hoặc bất kỳ tổ chức thứ ba nào. Theo như thỏa thuận ban đầu, họ sẽ có thông tin chi tiết về tài khoản của những người khác trong suốt thời gian thỏa thuận có hiệu lực, NGOẠI TRỪ MỘT THÔNG TIN QUAN TRỌNG - *__danh tính (identity)__* của người đó.

![](https://cdn-images-1.medium.com/max/800/1*0uFEch5XGG_Gqex1wXTFWg.png)

### 2.1 An empty folder
Tất cả mọi người đều được cung câp một thư mục rỗng (empty folder) để bắt đầu. Khi quá trình bắt đầu diễn ra, tất cả 10 cá nhân độc lập này sẽ cùng thêm các trang giấy vào thư mục rỗng hiện tại của họ. Và tập hợp các trang giấy này sẽ tạo thành một cuốn sổ cái để theo dõi các giao dịch.

### 2.2 Khi có một giao dịch xảy ra
Bây giờ, hãy tưởng tượng tất cả 10 người trong mạng lưới đều có một tờ giấy trắng và một chiếc bút chì trong tay. Mọi người đều đã sẵn sàng để ghi ra bất cứ giao dịch nào xảy ra trong hệ thống.

Giả sử có một giao dịch xảy ra, #2 muốn chuyển `10$` cho #9.

Để thực hiện giao dịch, #2 thông báo với tất cả mọi người 

> ***"Tôi muốn chuyển 10$ cho #9. Mọi người xin hãy note lại vào trang giấy của mình".***

Tiếp đó, tất cả mọi người sẽ cùng kiểm tra xem #2 có đủ số dư trong tài khoản để chuyển `10$` cho #9 hay không. Nếu ok, tất cả mọi người sẽ cùng note lại thông tin giao dịch trên trang giấy của mình.

![first transaction](https://cdn-images-1.medium.com/max/800/1*m0lFIWh2bmurf_6rPXoozw.png)

Giao dịch sau đó được coi là hoàn thành.

### 2.3 Các giao dịch tiếp tục được diễn ra
Theo thời gian, ngày càng có nhiều người trong mạng lưới có nhu cầu chuyển tiền cho nhau. Cứ mỗi khi họ muốn thực hiện một giao dịch, họ sẽ thông báo với tất cả những người khác. Và ngay khi nghe thấy thông báo, những người còn lại sẽ ngay lập tức viết thông tin của giao dịch đó lên trang giấy của mình.

Công việc này sẽ được tiếp tục, cho đến khi trang giấy của mọi người đều đã kín chỗ trống. Giả sử rằng mỗi trang giấy chỉ có đủ chỗ trống cho 10 giao dịch. 

![page_filled](https://cdn-images-1.medium.com/max/1600/1*mauQPdASOcD_xIZCN_cXDA.png)

Khi trang giấy của mọi người đều đã đầy, đã đến lúc cất trang giấy đó vào tập tài liệu cá nhân và lấy ra một trang giấy trắng mới, tiếp tục lặp lại các trình tự từ bước 2.2 ở trên.

### 2.4 Cất trang giấy ghi thông tin các giao dịch vào tập tài liệu
Trước khi cất trang giấy ghi lại các giao dịch vào tập tài liệu, chúng ta cần *niêm phong*  nó bằng một *__khoá unique__*  mà tất cả mọi người trong mạng (network) đều đồng ý. Bằng cách *niêm phong*  trang giấy này, chúng ta sẽ đảm bảo rằng không ai có thể thực hiện bất kỳ thay đổi về nội dung nào khi mà bản sao của nó được lưu giữ trong tập tài liệu của từng người - không phải hôm nay, ngày mai hay thậm chí là rất nhiều năm về sau. 

Một khi đã ở trong tập tài liệu, nó sẽ mãi ở trong đó, và luôn được *niêm phong*. Hơn nữa, nếu mọi người tin tưởng vào dấu *niêm phong*, mọi người cũng sẽ tin tưởng vào nội dung của trang giấy ghi lại giao dịch. *__Dấu niêm phong__* chính là điểm mấu chốt của phương pháp này.

Trước kia, các bên thứ 3, bên trung gian (ngân hàng, các tổ chức tài chính) tạo cho chúng ta niềm tin rằng bất cứ điều gì họ viết trong cuốn sổ cái (register) sẽ không bao giờ thay đổi. Trong một *__hệ thống phân tán__* (distributed) và *__không tập trung__* (decentralized) như hệ thống tôi đang mô tả, *__dấu niêm phong__* sẽ cung cấp niềm tin tương tự như thế.

# 3. Thật thú vị phải không! Vậy chúng ta sẽ niêm phong trang giấy ghi lại các giao dịch như thế nào ?
Trước khi tìm hiểu xem làm thế nào để có thể niêm phong lại trang giấy ghi giao dịch, chúng ta cần phải hiểu cách thức hoạt động của dấu niêm phong một cách tổng quát. 

Đã đến lúc chúng ta cùng làm quen với một thứ được gọi là ...

## Cỗ máy thần kỳ (The Magic Machine)
Hãy tưởng tượng có một cỗ máy được bao quanh bởi các bức tường dày. Nếu bạn đưa vào cỗ máy này một chiếc hộp chứa bên trong một thứ gì đó từ phía bên trái, nó sẽ trả ra một chiếc hộp chứa một thứ gì đó khác.

> [IT Fact] Thực ra chiếc hộp này có tên thật là *__Hash Function__* (Hàm băm), nhưng để hiểu được mớ lý thuyết sâu xa đằng sau khái niệm này cần nhiều thời gian và kiến thức chuyên ngành, nên hôm nay, để cho đơn giản tui sẽ chỉ gọi nó là *__Cỗ máy thần kỳ__*.

![The Magic Machine](https://cdn-images-1.medium.com/max/1600/1*ox9O7DmN1I1AiyNygulCrw.png)

Giả sử thế này, bạn gửi vào cỗ máy số `4` từ bên trái, sau quá trình xử lý nó sẽ đưa trả lại bạn một chuỗi ký tự `dcbea` ở bên phải.

Làm thế nào cỗ máy này có thể chuyển đổi từ số `4` sang xâu ký tự kia ? Không ai có thể biết. Hơn nữa, đây là một quá trình *__không thể đảo ngược__*, nghĩa là bạn KHÔNG thể gửi vào máy xâu ký tự `dcbea` và nhận lại giá trị ban đầu là số `4`. Nhưng bất cứ khi nào bạn đưa số `4` vào cỗ máy này, nó đều sẽ trả về cho bạn cùng một xâu ký tự là `dcbea`.

![The Magic Machine 2](https://cdn-images-1.medium.com/max/1600/1*G9UsASIX8eX_3xU1_3pg-w.png)
*hash(4) == dcbea*

Bây giờ hãy thử gửi một con số khác vào máy nhé. `26` thì sao ?

![The Magic Machine 3](https://cdn-images-1.medium.com/max/1600/1*HR3OyX1P-eeiwaOalY-W5A.png)
*hash(26) == 94c8e*

Lần này chúng ta nhận được chuỗi `94c8e`, và hãy để ý, chuỗi kết quả trả về có thể chứa ký tự là chữ số.

Bây giờ tui muốn hỏi bạn câu hỏi này :

> Bạn có thể nói cho tui biết tui cần gửi vào máy con số nào từ bên trái để có thể nhận được một chuỗi ký tự mà bắt đầu bằng 3 chữ số 0 không ? VD : `000ab`, `00069` hoặc `000fa`,...

![The Magic Machine 4](https://cdn-images-1.medium.com/max/1600/1*1p-LJxci-vdJ7JObPDcaUg.png)

Hãy thử suy nghĩ về câu hỏi này.

Như tui đã nói với các bạn, rằng với chuỗi ký tự được trả về ở bên phải, cỗ máy thần kỳ này không thể cho chúng ta biết giá trị đầu vào ở bên trái là gì. Vậy làm thế nào có thể trả lời được câu hỏi trên ?

Tui có nghĩ đến một phương pháp. Đó là sao chúng ta không thử từng số một cho đến khi thu được kết quả thoả mãn.

![The Magic Machine 5](https://cdn-images-1.medium.com/max/1600/1*NanhTPqi85WkwQoEpGQGHw.png)
........

Hãy lạc quan lên, sau vài nghìn lần thử, có thể chúng ta sẽ tìm được chuỗi ký tự đáp ứng yêu cầu ban đầu (chuỗi ký tự bắt đầu với 3 chữ số 0)

![The Magic Machine 6](https://cdn-images-1.medium.com/max/1600/1*_BOLJbfmKu8U1LNTtS_UMw.png)

Bạn thấy đấy, việc tính toán đầu vào ban đầu dựa vào kết quả đầu ra là cực kỳ khó khăn. Nhưng đồng thời, nó lại cựu kỳ dễ dàng để kiểm tra xem một đầu vào cho trước có thoả mãn đầu ra theo yêu cầu hay. Hãy nhớ rằng cỗ máy này trả về kết quả giống nhau với cùng một giá trị đầu vào.

Bạn nghĩ câu trả lời sẽ là gì, nếu tôi đưa bạn một số, VD `72533`, và hỏi bạn "Số này nếu đưa vào máy thì có thể cho ra một chuỗi ký tự bắt đầu bằng 3 chữ số 0 hay không ?"

Tất cả những gì bạn cần làm, là ném con số này vào cỗ máy thần kỳ và kiểm tra kết quả đầu ra. Done.

Đó cũng chính là chức năng quan trọng nhất của cỗ máy này.
> Với một kết quả output cho trước, sẽ rất khó để tính toán giá trị input, nhưng nếu có một giá trị input và kết quả output , bạn sẽ có thể dễ dàng kiểm tra giá trị input sau khi đưa qua cỗ máy có trả về giá trị output cho trước hay không

## Sử dụng cỗ máy thần kỳ này để niêm phong trang giấy như thế nào ?
Chúng ta sẽ cùng sử dụng cỗ máy thần kỳ này để sinh ra một dấu niêm phong cho những trang giấy ghi thông tin giao dịch của chúng ta. Như mọi khi, chúng ta sẽ cùng bắt đầu với một tình huống giả định.

Hãy tưởng tượng tôi đưa cho bạn 2 chiếc hộp. Chiếc hộp đầu tiên chứa con số `20893`. Sau đó, tôi sẽ hỏi bạn "Hey boy, cậu có thể tìm cho tôi một số mà khi cộng với con số trong chiếc hộp đầu tiên và đưa vào cỗ máy thần kỳ thì sẽ trả về cho chúng ta một chuỗi ký tự bắt đầu bằng 3 chữ số 0 không ?"

![The Magic Machine 7](https://cdn-images-1.medium.com/max/1600/1*0ChKQgKuRoOoFtj_jTMx2g.png)

Đây là một tình huống tương tự như những ví dụ mà chúng ta đã xem ở phần trước. Cách duy nhất để tính toán ra con số cần tìm là thử tất cả các số hợp lệ trong toàn vũ trụ này =))

Sau vài nghìn lần thử, có thể chúng ta sẽ ngẫu nhiên bắt được con số đó, VD `21191`, mà khi cộng với `20893` (i.e. 21191 + 20893 = 42084) và đưa qua cỗ máy, sẽ trả về chuỗi ký tự thoả mãn yêu cầu của tôi.

![The Magic Machine 8](https://cdn-images-1.medium.com/max/1600/1*ewcdx7L6_D1RIvbPFrMYiw.png)

Trong trường hợp này, con số `21191` sẽ trở thành dấu niêm phong cho số `20893`.

Giả sử mỗi một trang giấy ghi thông tin giao dịch của chúng ta được viết 1 con số lên đó. Và có 1 trang giấy ghi số `20893`. Để niêm phong trang thông tin giao dịch này (để không ai có thể thay đổi nội dung của nó), chúng ta sẽ đóng 1 con dấu đỏ có nhãn là con số `21191` lên trên trang giấy. Ngay khi con dấu chứa số niêm phong `21191` được đóng lên trang giấy, trang giấy sẽ ngay lập tức bị niêm phong.

![The Sealed Number 1](https://cdn-images-1.medium.com/max/1600/1*W5XSeKP6xoAQbxmmW4-dog.png)

> [IT Fact] Con số niêm phong được gọi là *__ProofOfWork__*, điều đó có nghĩa con số này là bằng chứng cho những nỗ lực để tính toán ra nó. Vì mục đích của bài viết, chúng ta vẫn sẽ thống nhất gọi nó là *__số niêm phong__* nhé.

Nếu ai đó muốn xác nhận xem nội dung của trang ghi thông tin giao dịch có bị thay đổi, hoặc đánh tráo hay không, tất cả những gì anh ta cần làm là cộng nội dung của trang giấy với số niêm phong và đưa qua `cỗ máy thần kỳ`. 
Nếu cỗ máy trả về một chuỗi ký tự bắt đầu bằng 3 chữ số 0, điều đó có nghĩa nội dung của trang ghi thông tin giao dịch không hề bị thay đổi. Nếu chuỗi kết quả trả về không đáp ứng yêu cầu, chúng ta có thể vứt bỏ trang giấy đó đi vì nội dung của nó đã bị xâm nhập và không còn hiệu lực.

Chúng ta sử dụng một cơ chế niêm phong tương tự như vậy để niêm phong tất cả các trang ghi thông tin giao dịch và sắp xếp chúng trong các thư mục tương ứng.

## Cuối cùng, niêm phong các trang giấy của chúng ta lại ...
Để niêm phong trang giấy ghi các thông tin giao dịch của toàn bộ network, chúng ta cần tìm ra một con số mà khi nối vào danh sách giao dịch và đưa qua cỗ máy thần kỳ, chúng ta sẽ thu được một chuỗi ký tự bắt đầu bằng 3 chữ số 0.

![The Sealed Number 2](https://cdn-images-1.medium.com/max/1600/1*ijsTUoELxn6zFkBa7r23VA.png)

> Lưu ý : tôi hay sử dụng cụm từ "Chuỗi ký tự bắt đầu bằng 3 chữ số 0" chỉ như là một ví dụ đơn giản. Mục đích là để minh hoạ các Hash Function hoạt động như thế nào. Những thử thách trong thực tế phức tạp hơn rất nhiều.

Khi chuỗi ký tự được tính toán sau khi đã tiêu tốn một khoảng thời gian (và cả điện năng), nó sẽ được dùng để niêm phong trang thông tin giao dịch. Nếu có một ai đó thử thay đổi nội dung của trang giấy này, số niêm phong sẽ cho phép bất kỳ ai cũng có thể kiểm tra tính toàn vẹn của trang giấy.

Sau khi đã hiểu về cơ chế niêm phong, chúng ta sẽ cùng quay lại thời điểm khi trang ghi thông tin ghi giao dịch đã ghi đầy 10 giao dịch và hết chỗ để viết thêm.

Lúc này, tất cả mọi người trong mạng sẽ cùng thực hiện việc tính toán để tìm ra con số niêm phong. *__Người đầu tiên tìm ra được số niêm phong sẽ thông báo cho tất cả những người còn lại__*.

![The Sealed Number 3](https://cdn-images-1.medium.com/max/1600/1*oMwunuVKyqWectTecENigQ.png)

Ngay khi nhận được số niêm phong, tất cả mọi người trong mạng sẽ xác nhận xem nếu dùng Hash Function (cỗ máy thần kỳ) với đầu vào là số niêm phong và trang ghi thông tin giao dịch, chuỗi ký tự trả về có thoả mãn yêu cầu đưa ra hay không. Nếu có, tất cả mọi người sẽ đóng dấu trang thông tin giao dịch của mình với số niêm phong này và đặt nó vào tập tài liệu.

**Nhưng nếu có ai đó, giả sử là #7**, nói rằng số niêm phong này không thoả mãn yêu cầu đầu ra. Những trường hợp như vậy không phải là điều bất thường. 

Những lý do có thể gây ra điều này bao gồm : 
1. Có lỗi trong quá trình tiếp nhận thông tin (nhiễu,...) do đó số niêm phong #7 nhận được không phải là số niêm phong đã được thông báo ra.
2. Anh ta có thể đã viết sai các giao dịch được thông báo trong mạng
3. Anh ta có thể đã cố gắng lừa dối mọi người hoặc không trung thực khi viết các giao dịch

Không quan trọng lý do là gì, #7 chỉ có duy nhất một lựa chọn, đó là loại bỏ trang ghi thông tin giao dịch của mình và copy lại từ một người khác, để sau đó có thể đặt nó vào tập thư mục của mình. 
Nếu #7 không đưa trang ghi thông tin giao dịch của mình vào tập thư mục, anh ta không thể tiếp tục viết thêm các giao dịch khác nữa, và như vậy anh ta sẽ bị cấm tham gia vào mạng lưới.

> Bất kể số niêm phong nào được đa số thành viên trong mạng đồng ý, sẽ trở thành số niêm phong chính được sử dụng.

**Một câu hỏi được đặt ra là, vậy tại sao tất cả mọi người lại phải bỏ công sức, nguồn lực của mình để thực hiện việc tính toán, khi mà họ biết ai đó trong mạng sẽ tìm thấy con số niêm phong và thông báo cho họ. Tại sao không đơn giản chỉ cần ngồi nhàn rỗi và chờ đợi thông báo ?**

Đây là một câu hỏi tuyệt vời. Và đây là nơi `sự khích lệ/ phần thưởng` bước vào trong bức tranh toàn cảnh. Tất cả mọi người là thành viên của mạng Blockchain đều có đủ điều kiện nhận phần thưởng. Người đầu tiên tìm ra được số niêm phong sẽ nhận được phần thưởng để khích lệ cho những nỗ lực anh ta đã bỏ ra (tiêu tốn điện sức mạnh của CPU và điện năng,...)

Hãy tưởng tượng đơn giản thế này, nếu #5 tìm ra số niêm phong của một trang, anh ta sẽ nhận được phần thưởng là một khoản tiền, VD 1$ . Nói cách khác, tài khoản của #5 được cộng thêm 1$ mà không làm giảm số dư tài khoản của những người khác trong mạng.

Đó chính là cách Bitcoin ra đời. Đó là đơn vị tiền tệ đầu tiên được giao dịch trên một Blockchain (hay có thể gọi là các *__sổ cái phân tán__*). 
Và đổi lại, để giữ cho những nỗ lực tính toán ra các con số niêm phong trong mạng được duy trì, mọi người sẽ được trả công bằng Bitcoin.

> Bây giờ thì bạn đã hình dung ra được, việc tính toán ra các con số niêm phong hay gọi theo ngôn ngữ thực tế chính là việc đào Bitcoin rồi phải không.

Và khi mọi người cất trang giấy đã ghi kín thông tin giao dịch của mình vào tập tài liệu, họ lại tiếp tục lấy ra một trang giấy mới và lặp lại toàn bộ quá trình này - do it forever =)).

> [IT Fact] Một trang giấy chính là một Khối (Block) giao dịch, và tập tài liệu chính là một *__Chuỗi các Khối__* (Chain of Block) ghi thông tin giao dịch. Tadaa, thuật ngữ Blockchain ra đời.

....

Ah còn một điều nữa tôi quên chưa kể với bạn.

Hãy tưởng tượng giả sử trong tập tài liệu đã có 5 trang ghi kín các thông tin giao dịch - và tất cả đều đã được đóng dấu với số niêm phong. Điều gì sẽ xảy ra nếu tôi quay lại trang thứ 2 và sửa thông tin một vài giao dịch để làm lợi cho bản thân mình. 

Như chúng ta đã cùng thảo luận trước đó, số niêm phong sẽ cho phép bất cứ ai phát hiện ra sự thay đổi trong các giao dịch đúng ko ? Vậy nếu tôi đi trước 1 bước và tính toán ra một số niêm phong mới cho các giao dịch đã được sửa đổi và đóng dấu trang giấy đó với số niêm phong mới thì sao ?

Để ngăn chặn vấn đề này, người ta đưa ra một số quy định cho việc cho tính toán số niêm phong

## Cùng bảo vệ số niêm phong
Bạn có nhớ trước đó tôi đã bảo là đưa cho bạn 2 chiếc hộp không ? Một chiếc hộp chứa con số `20893`, chiếc hộp còn lại để trống để chứa con số bạn sẽ tính toán. Trong thực tế, để tính toán một số niêm phong trong một Blockchain, thay vì 2, hệ thống sẽ cung cấp cho bạn 3 hộp - 2 hộp đã được điền sẵn và một hộp trống để dành cho bạn.

Khi nội dung của 3 hộp đã được điền và đưa vào Hash Function (cỗ máy thần kỳ), giá trị trả về phải thoả mãn các điều kiện yêu cầu.

Chúng ta đã biết rằng một hộp chứa danh sách các giao dịch, một hộp thì chứa số niêm phong. Vậy hộp thứ 3 chứa gì ? 

> Hộp thứ 3 sẽ chứa giá trị output của cỗ máy thần kỳ của trang giao dịch trước.

![The Sealed Number 4](https://cdn-images-1.medium.com/max/1600/1*Vz0UOPPuWYz8YNRhy0NCNQ.png)

Với thủ thuật nhỏ này, chúng ta có thể đảm bảo rằng tất cả mọi trang giao dịch *__đều phụ thuộc vào trang trước đó__*. Do đó, nếu ai đó có ý định thay đổi một trang, anh ta sẽ phải thay đổi nội dung và số niêm phong của tất cả các trang trước đó, để giữ cho nội dung của chuỗi được nhất quán.

Nếu một người trong 10 người trong VD ban đầu của chúng ta cố gắng cheat và thay đổi nội dung của Blockchain (thư mục chứa các trang giấy ghi danh sách tất cả các giao dịch trong mạng), anh ta sẽ phải điều chỉnh một vài trang và đồng thời phải tính toán số niêm phong cho tất cả các trang đó. Chúng ta đã biết việc tính toán một số niêm phong khó khăn đến mức nào rồi phải không.
Và do đó, một gã không trung thực sẽ không thể đánh bại 9 người trung thực còn lại.

Điều sẽ xảy ra là, từ trang giao dịch mà gã không trung thực đang cố gắng cheat, anh ta có thể tạo ra một chuỗi hoàn toàn khác trong mạng, nhưng chuỗi đó sẽ không thể nào có thể bắt kịp tốc độ của chuỗi chính, đơn giản bởi vì nỗ lực và tốc độ của anh ta không thể đánh bại nỗ lực và tốc độ của 9 người còn lại gộp lại. 

> Do đó, chuỗi dài nhất trong mạng sẽ được coi là chuỗi trung thực nhất.

![The Sealed Number 5](https://cdn-images-1.medium.com/max/2000/1*CRmIEzvK0k1fM--onASiHQ.png)

Khi tôi nói với bạn rằng một gã không trung thực không thể đánh bại 9 người trung thực, có điều gì đó nảy ra trong đầu bạn không ?

## Điều gì xảy ra nếu, thay vì một, mà là 6 người trong mạng cùng trở nên không trung thực ?
Trong trường hợp này, giao thức sẽ bị thất bại. Và nó được gọi là "51% Attack". Nếu phần lớn các thành viên trong mạng quyết định gian lận để lừa dối những người còn lại, giao thức sẽ không thành công.

Và đó là lý do duy nhất để Blockchain có thể sụp đổ nếu họ muốn. Có thể chúng ta tin tưởng rằng điều này khó có thể xảy ra, nhưng tất cả chúng ta cần phải biết điểm yếu của hệ thống.

> Blockchain được xây dựng trên giả định rằng đa số đám đông luôn luôn là trung thực.

## Lời kết
Trên đây là toàn bộ những gì liên quan đến Blockchain (ở mức dễ hình dung). Đây thực sự là một bài viết dài, nhưng nếu đọc được đến đây, thì xin chúc mừng cho những nỗ lực của bạn :))

Bài viết này mình dịch lại từ bài viết *__WTF is the Blockchain__* khá nổi tiếng, hy vọng sau khi đọc xong những người không chuyên về kỹ thuật cũng có thể hiểu được khái niệm cơ bản về Blockchain và Bitcoin.

Và nếu bạn thấy có ai đó bị bỏ rơi lại phía sau và tự hỏi "Blockchain là cái nồi gì vậy", hãy đưa cho họ bài viết này nhé.


----------------------------
*Tham khảo : https://hackernoon.com/wtf-is-the-blockchain-1da89ba19348*
