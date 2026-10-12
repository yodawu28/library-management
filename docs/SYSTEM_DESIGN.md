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

Các module không tự ý xử lý trách nhiệm của nhau. `main.cpp` điều phối menu, các file module xử lý nghiệp vụ riêng.

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
```

Danh sách dữ liệu:

```cpp
vector<Book> books;
vector<Reader> readers;
vector<BorrowRecord> borrowRecords;
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
- `addBook(vector<Book>& books)`.
- `updateBook(vector<Book>& books)`.
- `deleteBook(vector<Book>& books)`.
- `searchBook(const vector<Book>& books)`.
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

### 3.2 Reader Management
File: `reader.cpp`

Function:
- `addReader(vector<Reader>& readers)`.
- `updateReader(vector<Reader>& readers)`.
- `deleteReader(vector<Reader>& readers)`.
- `searchReader(const vector<Reader>& readers)`.
- `displayReaders(const vector<Reader>& readers)`.

Search hỗ trợ:
- Search by ID.
- Search by Name keyword.
- Search by Phone.

### 3.3 Borrow / Return
File: `borrow.cpp`

Function:
- `borrowBook(vector<Book>& books, const vector<Reader>& readers, vector<BorrowRecord>& records)`.
- `returnBook(vector<Book>& books, vector<BorrowRecord>& records)`.

Business rules:
- Borrow cần kiểm tra reader, book, quantity và record đang mượn.
- Return cần tìm record đang `BORROWED`, sau đó chuyển sang `RETURNED`.

### 3.4 File I/O
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

### 3.5 User Interface
File: `main.cpp`

Function:
- `main()`.
- `bookMenu(vector<Book>& books)`.
- `readerMenu(vector<Reader>& readers)`.
- `mainMenu(vector<Book>& books, vector<Reader>& readers, vector<BorrowRecord>& records)`.

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
