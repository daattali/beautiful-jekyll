---
layout: post
title: Hackerrank - phần 2-Basic-Data-Types-Challenges
subtile: Python coding like a Pythonista
image: /img/2017-06-15-HackerRank/Hackerrank1.png
tags: [Python, lap-trinh, programming-language, hacker-rank]
categories: [Dev-Python]
date: 2017-06-16
---


Bài tập phần 2: Một vài thử thách sử dụng list của Python. [Basic-Data-Types-Challenges](https://www.hackerrank.com/domains/python/py-basic-data-types) 


> Phần 2 này trên hackerrank cứ yêu cầu nhập giá trị từ bàn phím. Cách này `stupid` nên tôi bỏ qua :)) Vẫn có lệnh input để bạn nào thích thì dùng

# [Ex2_1: List](https://www.hackerrank.com/challenges/python-lists/problem)

Với một list (list = []), bạn có thể thực hiện các "tác vụ" sau:
1. _Insert i e:  Thêm mới một phần tử e vào vị trí i
2. _Print_: In ra danh sách bên trong list
3. _remove e_: Xóa phần tử có giá trị e đầu tiên mà list gặp
4. _append e_: Thêm phần tử giá trị e vào cuối của list
5. _sort_: Sắp xếp lại các phần tử trong list
6. _pop_: lấy ra phần tử cuối của trong list
7. _reverse_: Đảo ngược lại list

Khởi tạo một list của bạn và đọc các giá trị của n dòng chứa các "tác vụ" (n là giá trị dòng đầu tiên được đọc vào) trong 7 loại tác vụ đã nêu ở trên. Lặp lại từng lệnh theo thứ tự và thực hiện thao tác tương ứng trong danh sách của bạn.

Ví dụ:
**Input:**

```
12
insert 0 5
insert 1 10
insert 0 6
print 
remove 6
append 9
append 1
sort 
print
pop
reverse
print
```
**Sample Output:**

```
[6, 5, 10]
[1, 5, 9, 10]
[9, 5, 1]

```



```python
INPUT_COMMANDS = '''12
insert 0 5
insert 1 10
insert 0 6
print 
remove 6
append 9
append 1
sort 
print
pop
reverse
print'''
```


```python

def do_command_list(input_commands):
    commands = input_commands.strip().split("\n")
    my_list = []
    for line_command in commands[1:]:
        actions = line_command.split(" ")
        if actions[0] == "insert":
            my_list.insert(int(actions[1]), int(actions[2]))
        elif actions[0] == "remove":
            my_list.remove(int(actions[1]))
        elif actions[0] == "append":
            my_list.append(int(actions[1]))
        elif actions[0] == "pop":
            my_list.pop()
        elif actions[0] == "sort":
            my_list.sort()
        elif actions[0] == "reverse":
            my_list.reverse()
        elif actions[0] == "print":
            print(my_list)
            
```


```python
def main():
    do_command_list(INPUT_COMMANDS)
```


```python
main()
```

    [6, 5, 10]
    [1, 5, 9, 10]
    [9, 5, 1]
    

## Đây là bài giải dùng để push lên Hackerrank
Quá hại não với hàm main với input của nó :(





```python
if __name__ == '__main__':
    n = int(input())
    input_list = []
    input_list.append(str(n))
    for _ in range(n):
        s = input().strip()
        input_list.append(s)
    input_string = "\n".join(input_list)
    do_command_list(input_string)
```

    2
    insert 2 5
    print
    [5]
    

# [Ex2_2: Tuple](https://www.hackerrank.com/challenges/python-tuples/problem)
Nhập vào số nguyên n từ bàn phím
Số n tương ứng với số lượng phần tử được nhập từ bàn phím ở dòng thứ 2. Mỗi phần tử cách nhau một dấu cách. 
Tạo một tuple t với n số nguyên này, sau đó tính toán và in ra màn hình giá trị của hash(t)

Ví dụ

**Input**
```
2
1 2

```
**Output**
```
3713081631934410656

```


```python
def create_tuple(integer_list):
    my_tuple = tuple(integer_list)
    print(hash(my_tuple))

```


```python
if __name__ == "__main__":
    # n = int(input())
    integer_list = map(int, input().split())
    create_tuple(integer_list)
```

    1 2
    3713081631934410656
    


# [Ex2_3: List Comprehensions](https://www.hackerrank.com/challenges/list-comprehensions/problem)

Ta có 3 số nguyên X, Y, Z là ba chiều của một khối cuboid (khối chữ nhật). Và một số nguyên N.
Yêu cầu in ra màn hình tất cả các tọa độ có thể tạo bởi (i,j,k) trong lưới 3D thỏa mãn: 
- i + j + k != N và 0 <= i <= X, 0 <= j <= Y, 0 <= k <= Z.
- Sắp xếp các tọa độ theo chiều tăng dần i, j , k
- Yêu cầu sử dụng List Comprehension
Ví dụ:

**Input:**
```
1
1
1
2
```
**Output:**

```
[[0, 0, 0], [0, 0, 1], [0, 1, 0], [1, 0, 0], [1, 1, 1]] 
```

Nếu sử dụng list bình thường, code có thể sử dụng như sau:

```Python
x = int ( raw_input())
y = int ( raw_input())
n = int ( raw_input())
ar = []
p = 0
for i in range ( x + 1 ) :
    for j in range( y + 1):
        if i+j != n:
            ar.append([])
            ar[p] = [ i , j ]
            p+=1
print ar    
```



```python
def create_list(x,y,z,n):
    print([[i, j, k] for i in range(0, x + 1)
           for j in range(0, y + 1)
           for k in range(0, z + 1)
           if i + j + k != n])

```


```python
if __name__ == '__main__':
    # x = int(input())
    # y = int(input())
    # z = int(input())
    # n = int(input())
    x = y = z = 1
    n = 2
    create_list(x, y, z, n)

```

    [[0, 0, 0], [0, 0, 1], [0, 1, 0], [1, 0, 0], [1, 1, 1]]
    


# [Ex2_4: Find the Second Largest Number](https://www.hackerrank.com/challenges/find-second-maximum-number-in-a-list/problem)

Ta có n số nguyên 2 <= n <= 10, giá trị các số nguyên nằm trong giải (-100, 100). Đưa các số nguyên vào một list.
Hãy tìm số nguyên có giá trị lớn thứ 2 trong list.

Ví dụ: 
**Input**

```
5
2 3 6 6 5
```

**Output**
```
5
```


```python
def find_second_largest(integer_list):
    return sorted(list(set(integer_list)))[-2]
```


```python
if __name__ == '__main__':
    # n = int(input())
    # arr = map(int, input().split())
    integer_list = map(int, "1 -4 0 -2 -4".split())
    print(find_second_largest(integer_list))
```

    0
    


# [Ex2_5: Nested Lists](https://www.hackerrank.com/challenges/nested-list/problem)

Một lớp có N sinh viên, mỗi sinh viên có tên và một điểm tổng kết. Dữ liệu được lưu trong một nested list.
Hãy in ra màn hình tên của những sinh viên có điểm thấp nhất thứ nhì của lớp (Xếp thứ 2 từ dưới lên).
Ghi chú: nếu có nhiều hơn một sinh viên thì sắp xếp theo thứ tự alphabe
Ví dụ: 

**Input**
```
5
Harry
37.21
Berry
37.21
Tina
37.2
Akriti
41
Harsh
39
```
**Output**
```
Berry
Harry
```


```python
def find_second_lowest(students_list):
    lowest_student = min(students_list, key=lambda x: x[1])
    second_lowest_student =  min([student for student in students_list if student[1] != lowest_student[1]], key=lambda x: x[1])
    sub_student = sorted([student[0] for student in students_list if student[1] == second_lowest_student[1]])
    print('\n'.join(sub_student))
```


```python
if __name__ == '__main__':
    # students_list = []
    # for _ in range(int(input())):
    #     name = input()
    #     score = float(input())
    #     students_list.append([name, score])
    students_list = [['Harry', 37.21], ['Berry', 37.21], ['Tina', 37.2], ['Akriti', 41], ['Harsh', 39]]
    find_second_lowest(students_list)

```

    Berry
    Harry
    


# [Ex2_6: Finding the percentage](https://www.hackerrank.com/challenges/finding-the-percentage/problem)

Bạn có N bản ghi thông tin sinh viên. Mỗi bản ghi chứa thông tin tên của sinh viên, điểm tổng kết các môn: Toán, Vật lý, Hóa Học. Điểm ở định dạng float.
Lưu các bản ghi trên vào một dictionary với dữ liệu {tên sinh viên, điểm trung bình 3 môn với 2 số thập phân}

Ví dụ:
**Input:**

```
3
Krishna 67 68 69
Arjun 70 98 63
Malika 52 56 60
Malika
```

**Output:**

```
56.00
```



```python
if __name__ == '__main__':
    # n = int(input())
    # student_marks = {}
    # for _ in range(n):
    #     name, *line = input().split()
    #     scores = list(map(float, line))
    #     student_marks[name] = scores
    # query_name = input()
    student_marks = {}
    query_name = "Malika"
    student_marks['Krishna'] = list(map(float, "67 68 69".split()))
    student_marks['Arjun'] = list(map(float, "70 98 63".split()))
    student_marks['Malika'] = list(map(float, "52 56 60".split()))
    student_mark = sum(student_marks[query_name])/3
    print("{0:.2f}".format(student_mark))

```

    56.00
    
