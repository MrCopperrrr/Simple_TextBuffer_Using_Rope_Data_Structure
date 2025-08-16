# Simple_TextBuffer_Using_Rope_Data_Structure
Implement a simple textbuffer using rope data structure

## Ghi chú test private

Để test các thành phần private, cần thêm các dòng sau vào 4 vị trí trong các class như file RopeTextBuffer.h:

```cpp
// ===== FRIEND TEST HELPER (REMOVE BEFORE SUBMIT) =====
	friend class TestHelper; // <--- thêm dòng này để test private
// =====================================================
```

Các vị trí cần thêm:  
    - Trong class Node (private)  
    - Trong class Rope (public)  
    - Trong class RopeTextBuffer (public)  
    - Trong class History Manager (public)  

LƯU Ý: Nhớ xoá các dòng này trước khi nộp bài.

## Build & Run
### Build
```sh
g++ -o main main.cpp RopeTextBuffer.cpp -I . -std=c++17
```

### Run
```sh
./main
```
