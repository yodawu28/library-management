# System Design

## 1. Architecture

Chương trình được tổ chức theo hướng module hóa bằng function:

```text
Library Management System
├── Data Structures
│   ├── Book
│   ├── Reader
│   └── BorrowRecord
├── Book Management
├── Reader Management
├── Borrow / Return
├── File Management
└── User Interface
```

Luồng phụ thuộc chính:

```text
UI
↓
Function
↓
Data
↓
File
```

Các module không tự ý xử lý trách nhiệm của nhau. `main.cpp` khởi động chương
trình, `menu.cpp` điều phối menu, các file module xử lý nghiệp vụ riêng.

## 2. Data Model

Contract hiện tại nằm trong `library.h`.

```cpp
struct Book {
    int id;
    string title;
    string author;
    int quantity;
};

struct Reader {
    int id;
    string name;
    string phone;
};

struct BorrowRecord {
    int bookId;
    int readerId;
    int status;
};

struct LibraryData {
    vector<Book> books;
    vector<Reader> readers;
    vector<BorrowRecord> borrowRecords;
};
```

Danh sách dữ liệu:

```cpp
LibraryData data;
```

Trạng thái mượn/trả:

```cpp
const int BORROWED = 1;
const int RETURNED = 0;
```

## 3. Module Design

### 3.1 Book Management
File: `book.cpp`

Function:
- `getBookById(vector<Book>& books, int id)`.
- `hasActiveBorrowForBook(const vector<BorrowRecord>& records, int bookId)`.
- `printBook(const Book& book)`.
- `addBook(vector<Book>& books)`.
- `updateBook(vector<Book>& books)`.
- `deleteBook(LibraryData& data)`.
- `searchBook(vector<Book>& books)`.
- `displayBooks(const vector<Book>& books)`.
- `sortBooks(vector<Book>& books)`.

Search hỗ trợ:
- Search by ID.
- Search by Title keyword.
- Search by Author keyword.

Sort hỗ trợ:
- Sort by ID.
- Sort by Title.
- Sort by Quantity.

`getBookById` là helper dùng chung cho các chức năng cần tìm sách theo ID.
Hàm trả về con trỏ đến `Book` nếu tìm thấy, hoặc `nullptr` nếu không tìm thấy.
`hasActiveBorrowForBook` kiểm tra sách có bản ghi mượn đang `BORROWED` trước
khi cho phép xóa.
`printBook` là helper dùng chung để hiển thị một quyển sách theo cùng format.

### 3.2 Validation Helpers
File: `validation.cpp`

Function:
- `isPositiveId(int id)`.
- `isNonNegativeNumber(int number)`.
- `isEmptyText(const string& text)`.

Các helper này dùng chung cho Book và Reader để tránh lặp validation ID dương,
số không âm, và chuỗi rỗng.

### 3.3 Reader Management
File: `reader.cpp`

Function:
- `getReaderById(vector<Reader>& readers, int id)`.
- `hasActiveBorrowForReader(const vector<BorrowRecord>& records, int readerId)`.
- `printReader(const Reader& reader)`.
- `addReader(vector<Reader>& readers)`.
- `updateReader(vector<Reader>& readers)`.
- `deleteReader(LibraryData& data)`.
- `searchReader(const vector<Reader>& readers)`.
- `displayReaders(const vector<Reader>& readers)`.

Search hỗ trợ:
- Search by ID.
- Search by Name keyword.
- Search by Phone.

`getReaderById` là helper dùng chung cho các chức năng cần tìm độc giả theo ID.
`hasActiveBorrowForReader` kiểm tra độc giả có bản ghi mượn đang `BORROWED`
trước khi cho phép xóa.
`printReader` là helper dùng chung để hiển thị một độc giả theo cùng format.
`displayReaders` dùng `printReader` để tránh lặp logic in thông tin độc giả.

### 3.4 Borrow / Return
File: `borrow.cpp`

Function:
- `getActiveBorrowRecord(vector<BorrowRecord>& records, int readerId, int bookId)`.
- `borrowBook(LibraryData& data)`.
- `returnBook(LibraryData& data)`.

Business rules:
- Borrow cần kiểm tra reader, book, quantity và record đang mượn.
- Borrow và Return nhận `LibraryData&` vì hai chức năng này cần phối hợp
  nhiều danh sách dữ liệu cùng lúc.
- Borrow dùng lại `getReaderById` và `getBookById` để tránh lặp logic tìm ID.
- Borrow và Return dùng lại `getActiveBorrowRecord` để tìm bản ghi mượn đang
  active theo Reader ID và Book ID.
- Return cần tìm record đang `BORROWED`, sau đó chuyển sang `RETURNED`.

### 3.5 File I/O
File: `file.cpp`

Function:
- `saveBooks(const vector<Book>& books)`.
- `loadBooks(vector<Book>& books)`.
- `saveReaders(const vector<Reader>& readers)`.
- `loadReaders(vector<Reader>& readers)`.
- `saveBorrowRecords(const vector<BorrowRecord>& records)`.
- `loadBorrowRecords(vector<BorrowRecord>& records)`.

File dữ liệu:
- `data/books.dat`.
- `data/readers.dat`.
- `data/borrow_records.dat`.

Định dạng lưu trữ dùng text file đơn giản, mỗi dòng là một record, các field
phân tách bằng ký tự `|`:

```text
Book: id|title|author|quantity
Reader: id|name|phone
BorrowRecord: bookId|readerId|status
```

Ví dụ:

```text
1001|Clean Code|Robert C. Martin|3
2001|Nguyen Van An|0901234567
1001|2001|1
```

Sprint 5.0 implement các hàm save/load trong `file.cpp`. Sprint 6.0 đã tích
hợp việc gọi load khi khởi động chương trình, gọi save từ menu, và điều hướng
menu trong `main.cpp` / `menu.cpp`.

### 3.6 User Interface
File:
- `main.cpp`: điểm bắt đầu chương trình.
- `menu.cpp`: giao diện menu console và điều hướng chức năng.

Function:
- `main()`.
- `bookMenu(LibraryData& data)`.
- `readerMenu(LibraryData& data)`.
- `mainMenu(LibraryData& data)`.

Menu nhận `LibraryData&` để các lựa chọn Delete Book, Delete Reader, Borrow
Book và Return Book đều dùng chung dữ liệu sách, độc giả và phiếu mượn sau khi
Sprint 6.0 hoàn tất phần UI integration.

## 4. Menu Design

### 4.1 Main Menu
```text
========================================
       LIBRARY MANAGEMENT SYSTEM
========================================

1. Book Management
2. Reader Management
3. Borrow Book
4. Return Book
5. Display Data
6. Save Data
0. Exit

Enter your choice:
```

### 4.2 Book Menu
```text
========================================
          BOOK MANAGEMENT
========================================

1. Add Book
2. Update Book
3. Delete Book
4. Search Book
5. Display Books
6. Sort Books
0. Back

Enter your choice:
```

### 4.3 Reader Menu
```text
========================================
         READER MANAGEMENT
========================================

1. Add Reader
2. Update Reader
3. Delete Reader
4. Search Reader
5. Display Readers
0. Back

Enter your choice:
```

## 5. Flow Logic

### 5.1 Main Program
```text
START
  ↓
Load data from files
  ↓
Display Main Menu
  ↓
User selects an option
  ↓
Run selected module
  ↓
Continue?
  ├── Yes → Main Menu
  └── No  → Save Data → END
```

### 5.2 Borrow Book
```text
START
  ↓
Input Reader ID
  ↓
Reader exists?
  ├── No  → Display error → END
  └── Yes
        ↓
Input Book ID
  ↓
Book exists?
  ├── No  → Display error → END
  └── Yes
        ↓
Book quantity > 0?
  ├── No  → Display unavailable → END
  └── Yes
        ↓
Reader already borrowed this book?
  ├── Yes → Display error → END
  └── No
        ↓
Create BorrowRecord
  ↓
Decrease Book Quantity
  ↓
Display success
  ↓
END
```

### 5.3 Return Book
```text
START
  ↓
Input Reader ID
  ↓
Input Book ID
  ↓
Find BorrowRecord
  ↓
Record exists and status = BORROWED?
  ├── No  → Display error → END
  └── Yes
        ↓
Update status = RETURNED
  ↓
Increase Book Quantity
  ↓
Display success
  ↓
END
```

## 6. Implementation Order
```text
Step 1: Struct + constants
Step 2: Book Management
Step 3: Reader Management
Step 4: Borrow / Return
Step 5: File I/O
Step 6: Menu integration
Step 7: Testing
```
