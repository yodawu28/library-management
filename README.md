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
├── library.h
├── book.cpp
├── reader.cpp
├── borrow.cpp
├── file.cpp
├── data/
│   ├── books.dat
│   ├── readers.dat
│   └── borrow_records.dat
├── docs/
│   ├── SRS.md
│   ├── SYSTEM_DESIGN.md
│   └── TEST_DESIGN.md
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
| Member 4 | File I/O + Integration | `file.cpp`, `main.cpp` |

`library.h` là contract chung của cả nhóm, chỉ nên thay đổi khi nhóm đã thống nhất.

## Build Và Verification
Chạy verification chính:

```bash
./scripts/verify.sh
```

Script này kiểm tra compiler, file bắt buộc, dữ liệu mẫu, cú pháp C++, header
compile check, architecture documentation freshness và các automated regression
checks hiện có. Bảng test case trong `docs/TEST_DESIGN.md` vẫn là tài liệu
kiểm thử chính cho báo cáo; nếu nhóm thêm test tự động mới, mở rộng script này
thay vì tạo entrypoint khác.

## Tài Liệu
- `docs/SRS.md`: yêu cầu phần mềm.
- `docs/SYSTEM_DESIGN.md`: kiến trúc, data model, module, menu và flow logic.
- `docs/TEST_DESIGN.md`: test case theo module.
