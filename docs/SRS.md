# Software Requirement Specification

## 1. Giới Thiệu

### 1.1 Bối Cảnh
Thư viện cần quản lý thông tin sách, độc giả và hoạt động mượn/trả. Với quy mô đồ án môn học, chương trình chạy trên console, dữ liệu được lưu trong file cục bộ.

### 1.2 Thực Trạng
Nếu quản lý thủ công bằng giấy hoặc bảng tính rời rạc, việc tìm kiếm sách, kiểm tra số lượng còn lại và theo dõi trạng thái mượn/trả dễ bị sai sót.

### 1.3 Mục Tiêu
- Xây dựng chương trình quản lý thư viện đơn giản, dễ sử dụng.
- Tách chức năng thành các module rõ ràng.
- Áp dụng kiến thức C++: `struct`, `vector`, `string`, function, reference, `const`, file I/O, search và sort.
- Có tài liệu yêu cầu, thiết kế và test case để hỗ trợ báo cáo cuối kỳ.

### 1.4 Phạm Vi
Chương trình hỗ trợ:
- Quản lý sách.
- Quản lý độc giả.
- Mượn sách.
- Trả sách.
- Hiển thị dữ liệu.
- Lưu và đọc dữ liệu từ file.

Chương trình không bao gồm:
- Đăng nhập phân quyền.
- Cơ sở dữ liệu server.
- Giao diện đồ họa.
- Tính phí phạt hoặc ngày hạn trả.

### 1.5 Công Nghệ Sử Dụng
- C++17.
- Console UI.
- `std::vector` để quản lý danh sách động.
- `std::string` để quản lý dữ liệu dạng chữ.
- File cục bộ trong thư mục `data/`.

## 2. Functional Requirements

### FR-01: Book Management
Hệ thống cho phép quản lý danh sách sách.

Chức năng:
- Add Book.
- Update Book.
- Delete Book.
- Search Book.
- Display Books.
- Sort Books.

Validation chính:
- Book ID phải dương và duy nhất.
- Title không được rỗng.
- Author không được rỗng.
- Quantity không được âm.
- Không xóa sách đang có bản ghi mượn chưa trả.

### FR-02: Reader Management
Hệ thống cho phép quản lý danh sách độc giả.

Chức năng:
- Add Reader.
- Update Reader.
- Delete Reader.
- Search Reader.
- Display Readers.

Validation chính:
- Reader ID phải dương và duy nhất.
- Name không được rỗng.
- Phone không được rỗng.
- Không xóa độc giả đang có bản ghi mượn chưa trả.

### FR-03: Borrow Book
Hệ thống cho phép độc giả mượn sách.

Validation chính:
- Reader tồn tại.
- Book tồn tại.
- Book quantity lớn hơn 0.
- Độc giả chưa mượn cùng sách đó ở trạng thái `BORROWED`.

Processing:
- Tạo `BorrowRecord`.
- Gán `status = BORROWED`.
- Giảm `Book.quantity`.
- Thông báo mượn sách thành công.

### FR-04: Return Book
Hệ thống cho phép độc giả trả sách.

Validation chính:
- Book tồn tại.
- Có borrow record phù hợp.
- Record đang ở trạng thái `BORROWED`.

Processing:
- Cập nhật `status = RETURNED`.
- Tăng `Book.quantity`.
- Thông báo trả sách thành công.

### FR-05: Save / Load Data
Hệ thống lưu và đọc dữ liệu từ các file:
- `data/books.dat`.
- `data/readers.dat`.
- `data/borrow_records.dat`.

Load chạy khi chương trình bắt đầu. Save chạy khi người dùng chọn Save Data hoặc khi thoát chương trình nếu nhóm triển khai auto-save.

## 3. Non-Functional Requirements

### Performance
Chương trình phản hồi gần như tức thì với dữ liệu ở quy mô đồ án môn học.

### Usability
- Menu rõ ràng.
- Thông báo lỗi dễ hiểu.
- Người dùng có thể quay lại menu trước bằng lựa chọn `0`.

### Reliability
- Không cho mượn sách khi quantity bằng 0.
- Không tạo ID trùng.
- Không làm mất dữ liệu khi lưu file thành công.

### Maintainability
- Code chia theo module.
- Function nhỏ, tên rõ nghĩa.
- `library.h` là contract chung.
- Kiểm tra bằng `./scripts/verify.sh` trước khi kết luận hoàn thành.
