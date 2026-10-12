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

## Planned
- Implement Reader Management.
- Implement Borrow / Return.
- Implement File I/O.
- Integrate menus in `main.cpp`.
- Record manual test-case results and screenshots for the final report.
