# Changelog

## v0.1.0 - 2026-10-12
- Khởi tạo cấu trúc project C++ cho đồ án quản lý thư viện.
- Thêm verification script: `scripts/verify.sh`.
- Ghi nhận kiến trúc dự án theo hướng C++ module hóa.
- Thêm tài liệu dự án: `README.md`, SRS, System Design và Test Design.
- Điều chỉnh workflow implementation theo hướng sinh viên: code theo module, kiểm thử thủ công bằng test case, rồi chạy verification.

## v0.2.0 - 2026-10-12
- Hoàn thành Sprint 2.0 Book Management.
- Implement `addBook`, `updateBook`, `deleteBook`, `searchBook`,
  `displayBooks`, `sortBooks`, `getBookById`, và `printBook`.
- Thêm automated regression checks nội bộ cho Book Management.
- Ghi kết quả TC-B01 đến TC-B10 trong `docs/TEST_DESIGN.md`.
- Thêm architecture documentation freshness checks vào `scripts/verify.sh`.

## v0.3.0 - 2026-10-13
- Hoàn thành Sprint 3.0 Reader Management.
- Implement `addReader`, `updateReader`, `deleteReader`, `searchReader`,
  `displayReaders`, `getReaderById`, và `printReader`.
- Thêm automated regression checks nội bộ cho Reader Management.
- Thêm hướng dẫn manual E2E cho Reader Management trong `tests/e2e/`.
- Ghi kết quả TC-R01 đến TC-R08 trong `docs/TEST_DESIGN.md`; TC-R07 cần
  Borrow/Return state và đã được hoàn tất trong v0.4.0.

## v0.4.0 - 2026-10-15
- Hoàn thành Sprint 4.0 Borrow / Return.
- Implement `borrowBook`, `returnBook`, `getActiveBorrowRecord`, và các kiểm
  tra mượn/trả quan trọng: reader không tồn tại, book không tồn tại, hết sách,
  mượn trùng, trả hợp lệ, không có record, và record đã trả.
- Cập nhật `deleteBook` và `deleteReader` để từ chối xóa khi còn record
  `BORROWED` đang active.
- Thêm automated regression checks nội bộ và hướng dẫn manual E2E cho
  Borrow / Return.
- Ghi kết quả TC-BR01 đến TC-BR05 và TC-RT01 đến TC-RT03 trong
  `docs/TEST_DESIGN.md`.

## v0.5.0 - 2026-10-16
- Hoàn thành Sprint 5.0 File I/O & Persistence.
- Implement `saveBooks`, `loadBooks`, `saveReaders`, `loadReaders`,
  `saveBorrowRecords`, và `loadBorrowRecords`.
- Dùng định dạng text đơn giản với dấu `|`: `id|title|author|quantity`,
  `id|name|phone`, và `bookId|readerId|status`.
- Thêm automated regression checks nội bộ cho File I/O, bao gồm dữ liệu rỗng,
  dòng sai format, dữ liệu không hợp lệ, và restore lại fixture `data/*.dat`.
- Thêm hướng dẫn manual E2E cho File I/O trong `tests/e2e/`.
- Ghi kết quả TC-F01 đến TC-F06 trong `docs/TEST_DESIGN.md`.

## v0.6.0 - 2026-10-19
- Hoàn thành Sprint 6.0 Console Menu Integration.
- Implement startup load trong `main.cpp` và tách menu routing sang `menu.cpp`.
- Hoàn thiện Main Menu, Book Menu, Reader Menu, Borrow Book, Return Book,
  Display Data, Save Data, Exit flow, và invalid input recovery.
- Thêm automated regression checks nội bộ cho Menu Management và Startup Load.
- Thêm hướng dẫn manual E2E cho Console Menu trong `tests/e2e/`.
- Ghi kết quả TC-I01 đến TC-I05 trong `docs/TEST_DESIGN.md`.

## v0.7.0 - 2026-10-20
- Hoàn thành Sprint 7.0 final hardening cho phạm vi evidence và tài liệu.
- Thêm `docs/FINAL_MANUAL_REGRESSION_EVIDENCE.md` để lưu Final manual
  regression evidence cho Book, Reader, Borrow / Return, File I/O, và Menu
  Integration.
- Ghi actual results cho S7.3, S7.4, và S7.5 từ các lần chạy console thật.
- Cập nhật `README.md` với source layout hiện tại, lệnh build, lệnh run, lệnh
  verify, và vị trí bằng chứng báo cáo.
- Thêm Final verification evidence gates trong `scripts/verify.sh` để phát
  hiện README/evidence/documentation drift trước khi commit.
- Refresh `ARCHITECTURE.md`, `CHANGELOG.md`, và `docs/SYSTEM_DESIGN.md` để
  phản ánh trạng thái cuối của Sprint 7.0.

## Planned
- Final release verification handoff and PR preparation.
