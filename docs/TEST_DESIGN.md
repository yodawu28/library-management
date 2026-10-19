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

Kết quả Book Management hiện được ghi từ focused module checks trong
`tests/automated/book_management_test.cpp`. E2E qua menu console sẽ được chạy
lại sau Sprint 6.0 khi menu integration hoàn tất.

| Test ID | Chức năng | Input | Expected Result | Actual Result | Status |
| --- | --- | --- | --- | --- | --- |
| TC-B01 | Add Book | ID mới, title hợp lệ, author hợp lệ, quantity >= 0 | Thêm sách thành công | Focused module check thêm sách ID `1001`, lưu đúng title, author, quantity và in thông báo thành công | Pass |
| TC-B02 | Add Book | ID đã tồn tại | Báo lỗi trùng ID | Focused module check nhập lại ID `1001`, không thêm sách mới và in lỗi trùng ID | Pass |
| TC-B03 | Add Book | Title rỗng | Báo lỗi dữ liệu không hợp lệ | Focused module check title rỗng, không thêm sách và in lỗi title rỗng | Pass |
| TC-B04 | Add Book | Quantity < 0 | Báo lỗi dữ liệu không hợp lệ | Focused module check quantity `-1`, không thêm sách và in lỗi quantity âm | Pass |
| TC-B05 | Update Book | ID tồn tại, dữ liệu mới hợp lệ | Cập nhật sách thành công | Focused module check cập nhật ID `1001`, đổi đúng title, author, quantity và giữ sách khác không đổi | Pass |
| TC-B06 | Update Book | ID không tồn tại | Báo lỗi không tìm thấy sách | Focused module check nhập ID `9999`, danh sách không đổi và in lỗi không tìm thấy | Pass |
| TC-B07 | Delete Book | ID tồn tại và không đang được mượn | Xóa sách thành công | Focused module check xóa ID `1002`, danh sách giảm một phần tử và giữ đúng thứ tự sách còn lại | Pass |
| TC-B08 | Delete Book | ID tồn tại nhưng đang được mượn | Từ chối xóa | Focused module check dùng `LibraryData`, có record `BORROWED`, không xóa sách và in lỗi sách đang được mượn | Pass |
| TC-B09 | Search Book | Search by title keyword | Hiển thị các sách khớp keyword | Focused module check keyword `Code`, hiển thị đúng các sách có title khớp và không hiển thị sách không khớp | Pass |
| TC-B10 | Sort Books | Sort by title | Danh sách được sắp xếp theo title | Focused module check sort by title cho kết quả `Clean Code`, `Code Complete`, `The Pragmatic Programmer`; sort ID và quantity cũng đã được kiểm tra thêm | Pass |

## 3. Reader Management Test Cases

| Test ID | Chức năng | Input | Expected Result | Actual Result | Status |
| --- | --- | --- | --- | --- | --- |
| TC-R01 | Add Reader | ID mới, name hợp lệ, phone hợp lệ | Thêm độc giả thành công | Focused module check thêm reader ID `2001`, lưu đúng name, phone và in thông báo thành công | Pass |
| TC-R02 | Add Reader | ID đã tồn tại | Báo lỗi trùng ID | Focused module check nhập lại ID `2001`, không thêm reader mới và in lỗi trùng ID | Pass |
| TC-R03 | Add Reader | Name rỗng | Báo lỗi dữ liệu không hợp lệ | Focused module check name rỗng, không thêm reader và in lỗi name rỗng; phone rỗng cũng đã được kiểm tra thêm | Pass |
| TC-R04 | Update Reader | ID tồn tại, dữ liệu mới hợp lệ | Cập nhật độc giả thành công | Focused module check cập nhật ID `2001`, đổi đúng name, phone và giữ reader khác không đổi | Pass |
| TC-R05 | Update Reader | ID không tồn tại | Báo lỗi không tìm thấy độc giả | Focused module check nhập ID `9999`, danh sách không đổi và in lỗi không tìm thấy | Pass |
| TC-R06 | Delete Reader | ID tồn tại và không đang mượn sách | Xóa độc giả thành công | Focused module check xóa ID `2002`, danh sách giảm một phần tử và giữ đúng thứ tự reader còn lại | Pass |
| TC-R07 | Delete Reader | ID tồn tại nhưng đang mượn sách | Từ chối xóa | Focused module check dùng `LibraryData`, có record `BORROWED`, không xóa độc giả và in lỗi độc giả đang mượn sách | Pass |
| TC-R08 | Search Reader | Search by name keyword | Hiển thị độc giả khớp keyword | Focused module check keyword `Van`, hiển thị đúng các reader có name khớp và không hiển thị reader không khớp; search ID và phone cũng đã được kiểm tra thêm | Pass |

## 4. Borrow / Return Test Cases

| Test ID | Chức năng | Input | Expected Result | Actual Result | Status |
| --- | --- | --- | --- | --- | --- |
| TC-BR01 | Borrow Book | Reader tồn tại, book tồn tại, quantity > 0 | Mượn sách thành công, quantity giảm 1 | Focused module check tạo record `BORROWED`, lưu đúng Reader ID/Book ID, giảm quantity và in thông báo thành công | Pass |
| TC-BR02 | Borrow Book | Reader không tồn tại | Báo lỗi reader không tồn tại | Focused module check nhập Reader ID `9999`, không tạo record, không đổi quantity và in lỗi reader không tồn tại | Pass |
| TC-BR03 | Borrow Book | Book không tồn tại | Báo lỗi book không tồn tại | Focused module check nhập Book ID `9999`, không tạo record, không đổi quantity và in lỗi book không tồn tại | Pass |
| TC-BR04 | Borrow Book | Book quantity = 0 | Từ chối mượn | Focused module check quantity `0`, không tạo record, giữ quantity `0` và in lỗi sách không khả dụng | Pass |
| TC-BR05 | Borrow Book | Reader đã mượn book đó và chưa trả | Từ chối mượn trùng | Focused module check có record `BORROWED`, không tạo record thứ hai, không giảm quantity và in lỗi mượn trùng | Pass |
| TC-RT01 | Return Book | Record tồn tại và đang `BORROWED` | Trả sách thành công, quantity tăng 1 | Focused module check chuyển status sang `RETURNED`, tăng quantity và in thông báo thành công | Pass |
| TC-RT02 | Return Book | Không có record phù hợp | Báo lỗi không tìm thấy record | Focused module check không tạo hoặc đổi record, giữ quantity và in lỗi không tìm thấy borrow record | Pass |
| TC-RT03 | Return Book | Record đã `RETURNED` | Từ chối trả lại lần nữa | Focused module check giữ status `RETURNED`, không tăng quantity và in lỗi sách đã được trả | Pass |

## 5. File I/O Test Cases

| Test ID | Chức năng | Input | Expected Result | Actual Result | Status |
| --- | --- | --- | --- | --- | --- |
| TC-F01 | Save Books | Danh sách books có dữ liệu | `data/books.dat` được cập nhật | Focused module check ghi đúng `1001\|Clean Code\|Robert C. Martin\|3` và `1002\|Code Complete\|Steve McConnell\|2` vào `data/books.dat` | Pass |
| TC-F02 | Load Books | `data/books.dat` có dữ liệu hợp lệ | Load đúng danh sách books | Focused module check load lại 2 books, giữ đúng ID, title, author và quantity của từng sách | Pass |
| TC-F03 | Save Readers | Danh sách readers có dữ liệu | `data/readers.dat` được cập nhật | Focused module check ghi đúng `2001\|Nguyen Van An\|090 123 4567` và reader có dấu comma trong tên vào `data/readers.dat` | Pass |
| TC-F04 | Load Readers | `data/readers.dat` có dữ liệu hợp lệ | Load đúng danh sách readers | Focused module check load lại 2 readers, giữ đúng ID, name và phone kể cả phone có khoảng trắng | Pass |
| TC-F05 | Save Borrow Records | Danh sách records có dữ liệu | `data/borrow_records.dat` được cập nhật | Focused module check ghi đúng record `BORROWED` dạng `1001\|2001\|1` và record `RETURNED` dạng `1002\|2002\|0` | Pass |
| TC-F06 | Load Borrow Records | File records có dữ liệu hợp lệ | Load đúng danh sách records | Focused module check load lại 2 borrow records, giữ đúng bookId, readerId và status `BORROWED` / `RETURNED` | Pass |

## 6. Integration Test Cases

| Test ID | Scenario | Steps | Expected Result | Actual Result | Status |
| --- | --- | --- | --- | --- | --- |
| TC-I01 | Add then display book | Add Book → Display Books | Book vừa thêm xuất hiện | Menu integration check đi qua Main Menu → Book Menu, thêm book qua `Add Book`, sau đó `Display Books` hiển thị đúng book vừa thêm | Pass |
| TC-I02 | Add reader then borrow book | Add Reader → Add Book → Borrow Book | Record được tạo, quantity giảm | Menu integration check đi qua Reader Menu và Book Menu để tạo dữ liệu, sau đó `Borrow Book` tạo record `BORROWED` và giảm quantity | Pass |
| TC-I03 | Borrow then return book | Borrow Book → Return Book | Record chuyển `RETURNED`, quantity tăng | Menu integration check gọi `Borrow Book` rồi `Return Book`, record chuyển sang `RETURNED` và quantity tăng lại | Pass |
| TC-I04 | Save then reload | Save Data → restart program → Load Data | Dữ liệu vẫn còn | Menu Save Data check ghi đủ books/readers/borrow records; File I/O checks xác nhận load lại đúng dữ liệu; startup check xác nhận chương trình load dữ liệu trước khi vào Main Menu | Pass |
| TC-I05 | Invalid menu choice | Nhập lựa chọn ngoài menu | Báo lỗi và hiển thị lại menu | Menu integration check nhập invalid numeric và non-numeric ở Main/Book/Reader menu, chương trình in `Invalid choice.` và tiếp tục nhận lựa chọn hợp lệ | Pass |

## 7. Verification Command

Trước khi chốt một thay đổi, chạy:

```bash
./scripts/verify.sh
```

`./scripts/verify.sh` không thay thế bảng test case thủ công. Script này dùng để bắt lỗi deterministic như thiếu file, lỗi compiler, sai contract header, hoặc lỗi trong automated regression checks. Kết quả báo cáo chính vẫn dựa trên các test case thủ công và bằng chứng chạy chương trình thật.
