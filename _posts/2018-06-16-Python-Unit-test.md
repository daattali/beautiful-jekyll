---
layout: post
title: Python Unit-test
# subtile: Hãy viết code như một Pythonista
image: /img/2018-06-16-test/test.png
tags: [Python, Unit-Test]
categories: [Unit-Test]
date: 2018-06-16
---

Giới thiệu về các quy trình kiểm thử phần mềm trong phát triển phần mềm và cách viết unit-test trong Python.

## Kiểm thử phần mềm
Là một tiến trình hay một tập hợp các tiến trình được thiết kế để:

-  Đảm bảo phần mềm thực hiện đúng theo những thứ mà chúng đã được thiết kế. 
-  Trong quá trình sử dụng phần mềm không phát sinh bất cứ thứ gì không mong muốn. 


Đây là một pha quan trọng trong quá trình phát triển hệ thống phần mềm:
- Giúp cho khách hàng thấy được sản phẩm đặt ra đã đáp ứng được yêu cầu hay chưa.
- Đảm bảo chất lượng phần mềm khi đưa ra sử dụng. Tránh các rủi ro khi cho khách hàng khi đưa phần mềm vào sử dụng.
- Giảm thời gian bảo trì, bảo hành cho người viết phần mềm.

Có 2 kiểu kiểm thử phần mềm:

- Kiểm thử tĩnh (Static testing)

- Kiểm thử động (Dynamic testing)

### Kiểm thử tĩnh (Static testing)
- Là phương pháp kiểm thử phần mềm thủ công.
- Phương pháp này thường được những người phân tích thiết kế (BA) phần mềm thực hiện. 

**Cách thực hiện:**
Dùng giấy, bút để kiểm tra logic, kiểm tra từng chi tiết luồng nghiệp vụ theo yêu cầu đề bài mà không cần chạy chương trình.

**Mục đích:**
Cách làm này có thể sẽ giúp BA phát hiện ra những thiếu xót trong luồng nghiệp vụ để bổ sung tài liệu trước khi chuyển sang cho DEV. 

Đôi khi static testing sẽ bị nhầm lẫn với việc BA đưa tài liệu cho PO để review trước khi chuyển sang DEV.

### Kiểm thử động (Dynamic testing)
Phương pháp thử phần mềm thông qua việc chạy chương trình để theo dõi trạng thái, kết quả của từng bước / toàn bộ các bước trong quá trình thực thi phần mềm.

Cách thực hiện dựa trên các ca kiểm thử (test case) xác định bằng sự hoạt động của đối tượng kiểm thử hay toàn bộ chương trình.

Kiểm tra cách thức hoạt động động của mã lệnh, bao gồm luôn cả kiểm tra sự phản ứng vật lý từ hệ thống tới các biến luôn thay đổi theo thời gian.

**Mục đích:**
Trong kiểm thử động, tester quan tâm đến dữ liệu đầu vào và output đầu ra.

Với mỗi tập dữ liệu đầu vào sẽ phát sinh ra một tập dữ liệu output

Nếu chương trình nhận đầu vào để “chạy” sau đó đưa ra dữ liệu output giống như yêu cầu. Có thể nói đó là phần mềm đã hoạt động thành công.

**Các cách phân loại kiểm thử**
Có hai trường phái phân loại kiểm thử:
1. Phân loại theo mức độ kiểm thử
2. Phân loại theo chiến lược kiểm thử
- Kiểm thử hộp đen – Black box testing

- Kiểm thử hộp trắng– White box testing

- Kiểm thử hộp xám – Gray box testing

## Phân loại theo chiến lược kiểm thử
### Black box testing

- Xem chương trình như 1 “hộp đen”. 
- Kiểm thử dựa trên đặc tả của phần mềm.
- Không quan tâm cấu trúc bên trong của chương trình, tập trung tìm các trường hợp mà chương trình không thực hiện theo đặc tả của nó. 

**Các phương pháp:**

![black_box_testing](/img/2018-06-16-test/BBT_method.png)

**Đặc điểm:**
- Không cần biết tới code và cấu trúc chương trình.
- Đánh giá chương trình khách quan.
- Hạn chế: nhiều trường hợp áp dụng nhiều ca kiểm thử để kiểm tra trong khi chỉ cần 1 pha kiểm thử duy nhất  “Thăm dò mù”.

### White box testing

- Còn được gọi là clear box testing, glass box testing, transparent box testing. 
- Thường thiết kế các trường hợp kiểm thử dựa vào cấu trúc bên trong của phần mềm 

**Đặc điểm:**
- WBT đòi hỏi kỹ thuật lập trình am hiểu cấu trúc bên trong của phần mềm ( các đường, luồng dữ liệu, chức năng, kết quả ).
- Phương thức: Chọn các đầu vào và xem các đầu ra.
- Phụ thuộc vào các cài đặt hiện tại của hệ thống và của phần mềm, nếu có sự thay đổi thì bài test cũng phải thay đổi theo.
- Được ứng dụng trong các kiểm tra ở cấp độ module ( điển hình), tích hợp ( có khả năng ) và hệ thống của quá trình test phần mềm.

**Các phương pháp:**

![white_box_testing](/img/2018-06-16-test/WBT_method.png)

### Gray (grey) box testing
Kết hợp của Black box và White box testing.		

## Phân loại theo mức độ
![method](/img/2018-06-16-test/method.png)

**Các cấp độ kiểm thử**

![level](/img/2018-06-16-test/level.png)

### Unit Testing:
Kiểm thử trên các thành phần độc lập nhỏ nhất của phần mềm.

Phần mềm được chia nhỏ ra các thành phần độc lập nhau: 

Function -> Class -> Module -> Package 

Lập trình viên sau khi lập trình ra các thành phần, tự viết chương trình unit testing để đảm bảo dữ liệu do mình tạo ra hoạt động bình thường.

### Intergration Test: Kiểm thử tích hợp

Thực hiện test việc kết nối, ghép nối giữa các unit

Mục tiêu: 
- Phát hiện ra lỗi giao tiếp giữa các unit
- Phát hiện lỗi giao tiếp giữa hệ thống và các hệ thống khác (DB, Stack, …)
- Chuẩn bị cho System test

### System Test – Kiểm thử hệ thống: 
Kiểm thử thiết kế và toàn bộ hệ thống (sau khi tích hợp) có thỏa mãn yêu cầu đặt ra hay không. 

**System test:**
Kiểm thử chức năng (Functional Test) 
Kiểm thử hiệu năng (Performance Test) 
Kiểm thử khả năng chịu tải (Stress Test hay Load Test) 
Kiểm thử cấu hình (Configuration Test) 
Kiểm thử bảo mật (Security Test) 
Kiểm thử khả năng phục hồi (Recovery Test) 

--> Chuẩn bị cho Acceptance test 

### Acceptance Test – Kiểm thử chấp nhận sản phẩm: 
Chứng minh phần mềm thỏa mãn tất cả yêu cầu của khách hàng và khách hàng chấp nhận sản phẩm. 

Khách hàng có thể tự test hoặc thuê bên thứ 3 thực hiện test.

### Kiểm thử Alpha – Alpha Test và kiểm thử Beta – Beta Test. 
Kiểm thử Alpha được thực hiện trong nội bộ của ban phát triển phần mềm với các cộng tác viên là các tester, người dùng nội bộ hoặc các khách hàng được mời.

Kiểm thử Beta được thực hiện với số lượng các "tester" lớn hơn nhằm phát hiện các thay đổi hoặc lỗi trong quá trình đưa ra với người dùng.

Ghi chú: Nếu bạn có chơi game, hãy nhìn cách nhà xuất bản game đưa sản phẩm ra mắt.



### Release Testing: 
Acceptance testing được thực hiện sau khi triển khai phần mềm lên hệ thống thật


## Unit-test in Python
Cách thức kiểm thử các thành phần từ  những phần nhỏ nhất. 

Được xây dựng và sử dụng bởi các Dev. 

Thường được dựng prototype từ lúc các lập trình viên đọc yêu cầu bài toán


**Một ví dụ về Unit-test trong Python**

```Python
# test_module.py

import unittest
class TestStringMethods(unittest.TestCase):
    def test_upper(self):
        self.assertEqual('python'.upper(), 'PYTHON')

    def test_isupper(self):
        self.assertTrue('PYTHON'.isupper())
        self.assertFalse('Python'.isupper())

    def test_split(self):
        test_string = 'python is a best language'
        self.assertEqual(test_string.split(),
                        ['python', 'is', 'a', 'best', 'language'])
        # check that test_string.split fails when the separator is not a string
        with self.assertRaises(TypeError):
            test_string.split(2)

if __name__ == '__main__':
	unittest.main(verbosity=2)

```

### Một số function trong unit-test thường dùng.

#### Các function trong unit-test trả về True/False

`assertEqual(value1, value2)`
--> Trả về True: Nếu giá trị value1 == value2
--> Trả về False: nếu value1 != value2

`assertTrue(value)`
--> Trả về True: Nếu giá trị value == True
--> Trả về False: nếu value1 == False

`assertFalse(value)`
--> Trả về True: Nếu giá trị value == False
--> Trả về False: nếu value1 == True

```Python
with self.assertRaises(TypeException):
    --expressions--
```
Trả về True: Nếu trong các expressions phát sinh ra lỗi TypeException 
Trả về False: Nếu trong expressions không phát sinh ra lỗi


#### Các function khác


<div class="table-responsive">
    <table  class="table table-striped table-bordered table-hover table-condensed">
        <tbody>
            <tr><td><b>Method</b></td><td><b>Checks that</b></td></tr>
            <tr><td>assertEqual(a, b)</td><td>a == b</td></tr>
            <tr><td>assertNotEqual(a, b)</td><td>a != b</td></tr>
            <tr><td>assertTrue(x)</td><td>bool(x) is True</td></tr>
            <tr><td>assertFalse(x)</td><td>bool(x) is False</td></tr>
            <tr><td>assertIs(a, b)</td><td>a is b</td></tr>
            <tr><td>assertIsNot(a, b)</td><td>a is not b</td></tr>
            <tr><td>assertIsNone(x)</td><td>x is None</td></tr>
            <tr><td>assertIsNotNone(x)</td><td>x is not None</td></tr>
            <tr><td>assertIn(a, b)</td><td>a in b</td></tr>
            <tr><td>assertNotIn(a, b)</td><td>a not in b</td></tr>
            <tr><td>assertIsInstance(a, b)</td><td>isinstance(a, b)</td></tr>
            <tr><td>assertNotIsInstance(a, b)</td><td></td></tr>
            <tr><td>assertAlmostEqual(a, b)</td><td>round(a-b, 7) == 0</td></tr>
            <tr><td>assertNotAlmostEqual(a, b)</td><td>round(a-b, 7) != 0</td></tr>
            <tr><td>assertGreater(a, b)</td><td>a > b</td></tr>
            <tr><td>assertGreaterEqual(a, b)</td><td>a >= b</td></tr>
            <tr><td>assertLess(a, b)</td><td>a < b</td></tr>
            <tr><td>assertLessEqual(a, b)</td><td>a <= b</td></tr>
            <tr><td>assertRegex(s, r)</td><td>r.search(s)</td></tr>
            <tr><td>assertNotRegex(s, r)</td><td>not r.search(s)</td></tr>
            <tr><td>assertCountEqual(a, b)</td><td>a and b have the same elements in the same number, regardless of their order</td></tr>
        </tbody>
    </table>
</div>

### Các function so sánh các kiểu dữ liệu khác nhau.

<div class="table-responsive">
    <table  class="table table-striped table-bordered table-hover table-condensed">
        <tbody>
            <tr><td>Method</td><td>Used to compare</td></tr>
            <tr><td>assertMultiLineEqual(a, b)</td><td>strings</td></tr>
            <tr><td>assertSequenceEqual(a, b)</td><td>sequences</td></tr>
            <tr><td>assertListEqual(a, b)</td><td>lists</td></tr>
            <tr><td>assertTupleEqual(a, b)</td><td>tuples</td></tr>
            <tr><td>assertSetEqual(a, b)</td><td>sets or frozensets</td></tr>
            <tr><td>assertDictEqual(a, b)</td><td>dicts</td></tr>
        </tbody>
    </table>
</div>


### Cách chạy unit-test:

Quay lại ví dụ tại file test_module.py phía trên.


```
python3 -m unittest test_module.TestStringMethods 

```


![python1](/img/2018-06-16-test/python1.png)


```
python3 -m unittest test_module.TestStringMethods.test_split
```

![python2](/img/2018-06-16-test/python2.png)


### Ví dụ 

**Ví dụ 1:**
 Viết chương trình tìm nghiệm của phương trình bậc 1: aX + b = 0
 Viết unit test cho chương trình trên

Giải thuật:
Nếu a == 0 và b == 0  phương trình vô số nghiệm, trả về ALL

Nếu a == 0 và b != 0  Phương trình vô nghiệm, trả về NONE

X = -b / a 

```Python
# first_equation.py

def find_x(a,b):
    if a:
        return -b/a
    elif b:
        return "NONE"
    else:
        return "ALL"

def find_x_2(a,b):
    return -b/a


if __name__ == "__main__":
    print(find_x(10,10))
```

Unit-test:
```Python
# test_first_equation.py

import unittest
import first_equation

class TestFirst(unittest.TestCase):

    def test_find_x(self):
        args = (10, 10)
        self.assertEqual(first_equation.find_x(*args), -1)
        args = (0, 0)
        self.assertEqual(first_equation.find_x(*args), "ALL")
        args = (0, 10)
        self.assertEqual(first_equation.find_x(*args), "NONE")

if __name__ == '__main__':
    unittest.main(verbosity=2)


```

**Ví dụ 2**:
Cho 1 chuỗi cho trước, thực hiện tách chuỗi theo các khoảng trắng và trả về một list của các tuple dạng [(số thứ tự, giá trị),…]

Input: 
test_str = "Python is a best language”

Output:

[(1, 'Python'), (2, 'is'), (3, 'a'), (4, 'best'), (5, 'language')]

```Python

data = "Python is a best language"

def create_value(data_str):
    input_data = data_str.split()
    result = []
    for index, element in enumerate(input_data):
        result.append((index + 1, element))
    return result

if __name__ == "__main__":
    print(create_value(data))

```

Unit-test cho bài toán trên:

```Python
import unittest
import list_value

class TestStringMethods(unittest.TestCase):

    def test_create_tuple(self):
        test_str = list_value.data
        data_list = test_str.split()
        len_expected = len(data_list)
        result_list = list_value.create_value(test_str)
        self.assertIsInstance(result_list, list, "Dữ liệu trả về không đúng dạng list")
        for item in result_list:
            self.assertIsInstance(item, tuple, "Dữ liệu trả về không đúng dạng tuple")
        self.assertEqual(len(result_list), len_expected, "Số lượng phần tử không đúng")
        self.assertEqual(result_list[0][0], 1, 'Index phần tử đầu tiên không đúng')
        self.assertEqual(
            result_list[-1][0],
            len_expected,
            'Index phần tử cuối cùng không đúng'
        )


if __name__ == '__main__':
    unittest.main(verbosity=2)
```

**Ví dụ 3:** Xử lý chuỗi palindrome

Chuỗi palindrome có dạng: Chuỗi lớn hơn 1

Không phân biệt chữ hoa, thường

Viết xuôi hay ngược đều thu được kết quả như nhau

```Python
Input: 

test_str = ”Civic”
Output:

True
```

```Python
Input: 

test_str = ”Noon”
Output:

True

```

```Python
Input: 

test_str = ” Python”
Output:

False
```

Code:

```Python
def check_palindrome(text):
    if len(text) <= 1:
        return False
    text = text.strip().lower().replace(' ', '')
    return text == text[::-1]


if __name__ == "__main__":
    text = "Noon"
    print(check_palindrome(text))

```

Unit-test
```Python
import unittest
import palindrome


class TestExercise(unittest.TestCase):
    MESSAGE_FMT = 'Kết quả mong muốn là `{0}`, nhận được `{1}`: `{2}`'

    def _test_all(self, func, cases):
        for input_, expect in cases:
            output = func(input_)
            msg = self.MESSAGE_FMT.format(expect, output, input_)
            self.assertEqual(output, expect, msg)


class TestPalindrome(TestExercise):

    def test_check_palindrome(self):
        cases = [('ana', True),
                 ('Civic', True),
                 ('Python', False),
                 ('', False),
                 ('P', False),
                 ('Able was I ere I saw Elba', True)]
        self._test_all(palindrome.check_palindrome, cases)


if __name__ == '__main__':
    unittest.main(verbosity=2)

```





