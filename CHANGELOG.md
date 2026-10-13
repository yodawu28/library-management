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
- Ghi kết quả TC-R01 đến TC-R08 trong `docs/TEST_DESIGN.md`, với TC-R07
  deferred đến Sprint 4.0 vì cần Borrow/Return state.

## Planned
- Implement Borrow / Return.
- Implement File I/O.
- Integrate menus in `main.cpp`.
- Record manual test-case results and screenshots for the final report.
