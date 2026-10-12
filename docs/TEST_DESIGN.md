# Test Design

## 1. Test Scope

Test tập trung vào các chức năng chính:
- Book Management.
- Reader Management.
- Borrow Book.
- Return Book.
- File I/O.
- Menu integration.

Các test case dưới đây là cơ sở kiểm thử chính cho đồ án. Nhóm có thể chạy thủ công sau khi implement từng module, ghi lại actual result và chụp màn hình để đưa vào báo cáo.

E2E theo yêu cầu môn học là kiểm thử thủ công trên chương trình thật qua menu console. Các hướng dẫn chạy E2E thủ công được đặt trong `tests/e2e/`. Các file trong `tests/automated/` chỉ là kiểm tra tự động nội bộ của nhóm để phát hiện lỗi nhanh khi sửa code.

Không bắt buộc làm TDD. Quy trình phù hợp với môn học là:

```text
Thiết kế chức năng
↓
Implement module
↓
Chạy test case thủ công
↓
Ghi actual result và pass/fail
↓
Chạy ./scripts/verify.sh
```

## 2. Book Management Test Cases

| Test ID | Chức năng | Input | Expected Result | Actual Result | Status |
| --- | --- | --- | --- | --- | --- |
| TC-B01 | Add Book | ID mới, title hợp lệ, author hợp lệ, quantity >= 0 | Thêm sách thành công | Chưa chạy | Pending |
| TC-B02 | Add Book | ID đã tồn tại | Báo lỗi trùng ID | Chưa chạy | Pending |
| TC-B03 | Add Book | Title rỗng | Báo lỗi dữ liệu không hợp lệ | Chưa chạy | Pending |
| TC-B04 | Add Book | Quantity < 0 | Báo lỗi dữ liệu không hợp lệ | Chưa chạy | Pending |
| TC-B05 | Update Book | ID tồn tại, dữ liệu mới hợp lệ | Cập nhật sách thành công | Chưa chạy | Pending |
| TC-B06 | Update Book | ID không tồn tại | Báo lỗi không tìm thấy sách | Chưa chạy | Pending |
| TC-B07 | Delete Book | ID tồn tại và không đang được mượn | Xóa sách thành công | Chưa chạy | Pending |
| TC-B08 | Delete Book | ID tồn tại nhưng đang được mượn | Từ chối xóa | Chưa chạy | Pending |
| TC-B09 | Search Book | Search by title keyword | Hiển thị các sách khớp keyword | Chưa chạy | Pending |
| TC-B10 | Sort Books | Sort by title | Danh sách được sắp xếp theo title | Chưa chạy | Pending |

## 3. Reader Management Test Cases

| Test ID | Chức năng | Input | Expected Result | Actual Result | Status |
| --- | --- | --- | --- | --- | --- |
| TC-R01 | Add Reader | ID mới, name hợp lệ, phone hợp lệ | Thêm độc giả thành công | Chưa chạy | Pending |
| TC-R02 | Add Reader | ID đã tồn tại | Báo lỗi trùng ID | Chưa chạy | Pending |
| TC-R03 | Add Reader | Name rỗng | Báo lỗi dữ liệu không hợp lệ | Chưa chạy | Pending |
| TC-R04 | Update Reader | ID tồn tại, dữ liệu mới hợp lệ | Cập nhật độc giả thành công | Chưa chạy | Pending |
| TC-R05 | Update Reader | ID không tồn tại | Báo lỗi không tìm thấy độc giả | Chưa chạy | Pending |
| TC-R06 | Delete Reader | ID tồn tại và không đang mượn sách | Xóa độc giả thành công | Chưa chạy | Pending |
| TC-R07 | Delete Reader | ID tồn tại nhưng đang mượn sách | Từ chối xóa | Chưa chạy | Pending |
| TC-R08 | Search Reader | Search by name keyword | Hiển thị độc giả khớp keyword | Chưa chạy | Pending |

## 4. Borrow / Return Test Cases

| Test ID | Chức năng | Input | Expected Result | Actual Result | Status |
| --- | --- | --- | --- | --- | --- |
| TC-BR01 | Borrow Book | Reader tồn tại, book tồn tại, quantity > 0 | Mượn sách thành công, quantity giảm 1 | Chưa chạy | Pending |
| TC-BR02 | Borrow Book | Reader không tồn tại | Báo lỗi reader không tồn tại | Chưa chạy | Pending |
| TC-BR03 | Borrow Book | Book không tồn tại | Báo lỗi book không tồn tại | Chưa chạy | Pending |
| TC-BR04 | Borrow Book | Book quantity = 0 | Từ chối mượn | Chưa chạy | Pending |
| TC-BR05 | Borrow Book | Reader đã mượn book đó và chưa trả | Từ chối mượn trùng | Chưa chạy | Pending |
| TC-RT01 | Return Book | Record tồn tại và đang `BORROWED` | Trả sách thành công, quantity tăng 1 | Chưa chạy | Pending |
| TC-RT02 | Return Book | Không có record phù hợp | Báo lỗi không tìm thấy record | Chưa chạy | Pending |
| TC-RT03 | Return Book | Record đã `RETURNED` | Từ chối trả lại lần nữa | Chưa chạy | Pending |

## 5. File I/O Test Cases

| Test ID | Chức năng | Input | Expected Result | Actual Result | Status |
| --- | --- | --- | --- | --- | --- |
| TC-F01 | Save Books | Danh sách books có dữ liệu | `data/books.dat` được cập nhật | Chưa chạy | Pending |
| TC-F02 | Load Books | `data/books.dat` có dữ liệu hợp lệ | Load đúng danh sách books | Chưa chạy | Pending |
| TC-F03 | Save Readers | Danh sách readers có dữ liệu | `data/readers.dat` được cập nhật | Chưa chạy | Pending |
| TC-F04 | Load Readers | `data/readers.dat` có dữ liệu hợp lệ | Load đúng danh sách readers | Chưa chạy | Pending |
| TC-F05 | Save Borrow Records | Danh sách records có dữ liệu | `data/borrow_records.dat` được cập nhật | Chưa chạy | Pending |
| TC-F06 | Load Borrow Records | File records có dữ liệu hợp lệ | Load đúng danh sách records | Chưa chạy | Pending |

## 6. Integration Test Cases

| Test ID | Scenario | Steps | Expected Result | Actual Result | Status |
| --- | --- | --- | --- | --- | --- |
| TC-I01 | Add then display book | Add Book → Display Books | Book vừa thêm xuất hiện | Chưa chạy | Pending |
| TC-I02 | Add reader then borrow book | Add Reader → Add Book → Borrow Book | Record được tạo, quantity giảm | Chưa chạy | Pending |
| TC-I03 | Borrow then return book | Borrow Book → Return Book | Record chuyển `RETURNED`, quantity tăng | Chưa chạy | Pending |
| TC-I04 | Save then reload | Save Data → restart program → Load Data | Dữ liệu vẫn còn | Chưa chạy | Pending |
| TC-I05 | Invalid menu choice | Nhập lựa chọn ngoài menu | Báo lỗi và hiển thị lại menu | Chưa chạy | Pending |

## 7. Verification Command

Trước khi chốt một thay đổi, chạy:

```bash
./scripts/verify.sh
```

`./scripts/verify.sh` không thay thế bảng test case thủ công. Script này dùng để bắt lỗi deterministic như thiếu file, lỗi compiler, sai contract header, hoặc lỗi trong automated regression checks. Kết quả báo cáo chính vẫn dựa trên các test case thủ công và bằng chứng chạy chương trình thật.
