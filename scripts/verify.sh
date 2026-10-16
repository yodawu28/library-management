#!/usr/bin/env bash
set -euo pipefail

fail() {
  printf 'REJECTED_FAIL_CLOSED: %s\n' "$*" >&2
  exit 1
}

note() {
  printf '[verify] %s\n' "$*"
}

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd -P)" || fail "cannot resolve repository root"
cd "$ROOT_DIR" || fail "cannot enter repository root"

CXX_BIN="${CXX:-c++}"
command -v "$CXX_BIN" >/dev/null 2>&1 || fail "C++ compiler not found: $CXX_BIN"

HEADER="library.h"
SOURCES=(main.cpp book.cpp reader.cpp borrow.cpp file.cpp validation.cpp)
DATA_FILES=(data/books.dat data/readers.dat data/borrow_records.dat)
TEST_SOURCES=(
  tests/automated/book_management_test.cpp
  tests/automated/reader_management_test.cpp
  tests/automated/borrow_management_test.cpp
  tests/automated/file_management_test.cpp
)
CXXFLAGS=(-std=c++17 -Wall -Wextra -Werror -pedantic)

[[ -f "$HEADER" && -r "$HEADER" ]] || fail "missing or unreadable $HEADER"

for src in "${SOURCES[@]}"; do
  [[ -f "$src" && -r "$src" ]] || fail "missing or unreadable $src"
done

for test_src in "${TEST_SOURCES[@]}"; do
  [[ -f "$test_src" && -r "$test_src" ]] || fail "missing or unreadable $test_src"
done

[[ -d data ]] || fail "missing data directory"
for fixture in "${DATA_FILES[@]}"; do
  [[ -f "$fixture" && -r "$fixture" ]] || fail "missing or unreadable $fixture"
done

note "checking architecture documentation freshness"
[[ -f ARCHITECTURE.md && -r ARCHITECTURE.md ]] || fail "missing or unreadable ARCHITECTURE.md"
[[ -f README.md && -r README.md ]] || fail "missing or unreadable README.md"
[[ -f CHANGELOG.md && -r CHANGELOG.md ]] || fail "missing or unreadable CHANGELOG.md"

if grep -q "Book module | \`book.cpp\` | Present, currently empty" ARCHITECTURE.md; then
  fail "ARCHITECTURE.md still says book.cpp is empty"
fi

if grep -q "application implementation has not started" ARCHITECTURE.md; then
  fail "ARCHITECTURE.md still says implementation has not started"
fi

if grep -q "implementation files are empty" ARCHITECTURE.md; then
  fail "ARCHITECTURE.md still says implementation files are empty"
fi

if grep -q "update, delete, and search pending" ARCHITECTURE.md; then
  fail "ARCHITECTURE.md still says Reader update/delete/search are pending"
fi

if grep -q "Sprint 3.0 has started" ARCHITECTURE.md; then
  fail "ARCHITECTURE.md still says Sprint 3.0 has only started"
fi

if grep -q "builds/runs the Book Management automated regression check" ARCHITECTURE.md; then
  fail "ARCHITECTURE.md omits Reader Management automated regression check"
fi

if grep -q "reader.cpp.*not implemented yet" ARCHITECTURE.md; then
  fail "ARCHITECTURE.md still says reader.cpp is not implemented"
fi

if grep -Eq "Borrow / Return module.*In progress|Sprint 4\.0 is implementing|remaining Borrow / Return validation|Borrow / Return currently in" ARCHITECTURE.md; then
  fail "ARCHITECTURE.md still describes Borrow/Return as unfinished"
fi

if grep -Eq "library\.h:[0-9]" ARCHITECTURE.md; then
  fail "ARCHITECTURE.md uses fragile library.h line references"
fi

if grep -Eq "bookMenu\(vector<Book>&|readerMenu\(vector<Reader>&|mainMenu\(vector<Book>&" library.h docs/SYSTEM_DESIGN.md; then
  fail "menu contract should use LibraryData for cross-list workflows"
fi

if awk '
  FNR == 1 { in_main_menu = 0 }
  /mainMenu[[:space:]]*\(/ { in_main_menu = 1 }
  in_main_menu && /vector<(Book|Reader|BorrowRecord)>&/ { found = 1 }
  in_main_menu && /\)/ { in_main_menu = 0 }
  END { exit found ? 0 : 1 }
' library.h docs/SYSTEM_DESIGN.md; then
  fail "mainMenu contract should use LibraryData instead of separate vectors"
fi

if grep -q "nếu sau này nhóm thêm test tự động" README.md; then
  fail "README.md still describes automated tests as future work"
fi

if grep -q -- "- Implement Book Management." CHANGELOG.md; then
  fail "CHANGELOG.md still lists Book Management as planned"
fi

if grep -Eq -- "- Implement Borrow / Return\.|deferred đến Sprint 4\.0" CHANGELOG.md; then
  fail "CHANGELOG.md still describes Borrow/Return or TC-R07 as pending"
fi

if ! grep -q "Book: id|title|author|quantity" docs/SYSTEM_DESIGN.md; then
  fail "docs/SYSTEM_DESIGN.md missing Book file format"
fi

if ! grep -q "Reader: id|name|phone" docs/SYSTEM_DESIGN.md; then
  fail "docs/SYSTEM_DESIGN.md missing Reader file format"
fi

if ! grep -q "BorrowRecord: bookId|readerId|status" docs/SYSTEM_DESIGN.md; then
  fail "docs/SYSTEM_DESIGN.md missing BorrowRecord file format"
fi

note "checking Borrow/Return manual E2E guide"
BORROW_RETURN_GUIDE="tests/e2e/borrow_return_manual.md"
[[ -f "$BORROW_RETURN_GUIDE" && -r "$BORROW_RETURN_GUIDE" ]] ||
  fail "missing or unreadable $BORROW_RETURN_GUIDE"

for test_id in TC-BR01 TC-BR02 TC-BR03 TC-BR04 TC-BR05 TC-RT01 TC-RT02 TC-RT03; do
  if ! grep -q "$test_id" "$BORROW_RETURN_GUIDE"; then
    fail "$BORROW_RETURN_GUIDE missing $test_id"
  fi
done

if grep -Eq "TC-(BR|RT)[0-9][0-9].*\| Chưa chạy \| Pending" docs/TEST_DESIGN.md; then
  fail "docs/TEST_DESIGN.md still has pending Borrow/Return test results"
fi

TMP_DIR="$(mktemp -d "${TMPDIR:-/tmp}/library-verify.XXXXXX")" || fail "cannot create temp directory"
trap 'rm -rf "$TMP_DIR"' EXIT

note "checking source syntax"
for src in "${SOURCES[@]}"; do
  "$CXX_BIN" "${CXXFLAGS[@]}" -fsyntax-only "$src" || fail "source syntax check failed: $src"
done

cat > "$TMP_DIR/header_check.cpp" <<'CPP'
#include "library.h"

int main() {
    std::vector<Book> books;
    std::vector<Reader> readers;
    std::vector<BorrowRecord> records;
    LibraryData data;

    books.push_back({1, "Title", "Author", 2});
    readers.push_back({1, "Reader", "000"});
    records.push_back({1, 1, BORROWED});
    data.books.push_back({2, "Data Title", "Data Author", 3});
    data.readers.push_back({2, "Data Reader", "111"});
    data.borrowRecords.push_back({2, 2, RETURNED});

    return (books[0].id == 1 &&
            readers[0].id == 1 &&
            records[0].status == BORROWED &&
            data.books[0].quantity == 3 &&
            data.readers[0].id == 2 &&
            data.borrowRecords[0].status == RETURNED &&
            RETURNED == 0) ? 0 : 1;
}
CPP

note "building header compile check"
"$CXX_BIN" "${CXXFLAGS[@]}" -I. "$TMP_DIR/header_check.cpp" -o "$TMP_DIR/header_check" ||
  fail "header compile check build failed"

note "running header compile check"
"$TMP_DIR/header_check" || fail "header compile check failed"

note "building book management automated test"
"$CXX_BIN" "${CXXFLAGS[@]}" -I. tests/automated/book_management_test.cpp book.cpp validation.cpp -o "$TMP_DIR/book_management_test" ||
  fail "book management automated test build failed"

note "running book management automated test"
"$TMP_DIR/book_management_test" || fail "book management automated test failed"

note "building reader management automated test"
"$CXX_BIN" "${CXXFLAGS[@]}" -I. tests/automated/reader_management_test.cpp reader.cpp validation.cpp -o "$TMP_DIR/reader_management_test" ||
  fail "reader management automated test build failed"

note "running reader management automated test"
"$TMP_DIR/reader_management_test" || fail "reader management automated test failed"

note "building borrow management automated test"
"$CXX_BIN" "${CXXFLAGS[@]}" -I. tests/automated/borrow_management_test.cpp borrow.cpp book.cpp reader.cpp validation.cpp -o "$TMP_DIR/borrow_management_test" ||
  fail "borrow management automated test build failed"

note "running borrow management automated test"
"$TMP_DIR/borrow_management_test" || fail "borrow management automated test failed"

note "building file management automated test"
"$CXX_BIN" "${CXXFLAGS[@]}" -I. tests/automated/file_management_test.cpp file.cpp -o "$TMP_DIR/file_management_test" ||
  fail "file management automated test build failed"

note "running file management automated test"
"$TMP_DIR/file_management_test" || fail "file management automated test failed"

note "ACCEPTED: deterministic verification passed"
