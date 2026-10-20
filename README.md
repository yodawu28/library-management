# Library Management System

Đây là project đồ án môn Kỹ thuật lập trình: xây dựng chương trình quản lý thư viện bằng C++ theo hướng module hóa bằng `struct`, `vector`, `string`, function, file I/O, search và sort.

## Mục Tiêu
- Quản lý danh sách sách.
- Quản lý danh sách độc giả.
- Hỗ trợ mượn và trả sách.
- Lưu và đọc dữ liệu từ file.
- Tổ chức source code rõ ràng để nhóm có thể chia module và tích hợp.

## Công Nghệ
- Ngôn ngữ: C++17.
- Data model: `struct`.
- Danh sách động: `std::vector`.
- Text field: `std::string`.
- Lưu trữ: file trong thư mục `data/`.

## Cấu Trúc Project
```text
LibraryManagement/
├── main.cpp
├── menu.cpp
├── library.h
├── book.cpp
├── reader.cpp
├── borrow.cpp
├── file.cpp
├── validation.cpp
├── data/
│   ├── books.dat
│   ├── readers.dat
│   └── borrow_records.dat
├── docs/
│   ├── SRS.md
│   ├── SYSTEM_DESIGN.md
│   ├── TEST_DESIGN.md
│   └── FINAL_MANUAL_REGRESSION_EVIDENCE.md
├── tests/
│   ├── automated/
│   └── e2e/
├── scripts/
│   └── verify.sh
└── CHANGELOG.md
```

## Phân Công Module
| Thành viên | Module | File |
| --- | --- | --- |
| Member 1 | Book Management | `book.cpp` |
| Member 2 | Reader Management | `reader.cpp` |
| Member 3 | Borrow / Return | `borrow.cpp` |
| Member 4 | File I/O + Integration | `file.cpp`, `main.cpp`, `menu.cpp` |

`library.h` là contract chung của cả nhóm, chỉ nên thay đổi khi nhóm đã thống nhất.

## Build Và Verification
Build chương trình console:

```bash
c++ -std=c++17 -Wall -Wextra -Werror -pedantic main.cpp menu.cpp book.cpp reader.cpp borrow.cpp file.cpp validation.cpp -o library_management
```

Chạy chương trình:

```bash
./library_management
```

Chạy verification chính:

```bash
./scripts/verify.sh
```

Script này kiểm tra compiler, file bắt buộc, dữ liệu mẫu, cú pháp C++, header
compile check, architecture documentation freshness và các automated regression
checks trong `tests/automated/`.

## Kiểm Thử Và Bằng Chứng Báo Cáo
- `docs/TEST_DESIGN.md`: bảng test case theo module.
- `tests/e2e/`: hướng dẫn chạy E2E thủ công trên chương trình console thật.
- `tests/automated/`: kiểm tra tự động nội bộ để bắt lỗi deterministic khi sửa code.
- `docs/FINAL_MANUAL_REGRESSION_EVIDENCE.md`: bằng chứng chạy manual regression
  cuối cùng để dùng cho báo cáo và demo.

Khi cần lấy bằng chứng cho báo cáo, chạy chương trình bằng `./library_management`,
thực hiện các bước trong `tests/e2e/`, rồi ghi actual result vào
`docs/FINAL_MANUAL_REGRESSION_EVIDENCE.md`.

## Tài Liệu
- `docs/SRS.md`: yêu cầu phần mềm.
- `docs/SYSTEM_DESIGN.md`: kiến trúc, data model, module, menu và flow logic.
- `docs/TEST_DESIGN.md`: test case theo module.
- `docs/FINAL_MANUAL_REGRESSION_EVIDENCE.md`: kết quả manual regression cuối kỳ.
