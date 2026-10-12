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
SOURCES=(main.cpp book.cpp reader.cpp borrow.cpp file.cpp)
DATA_FILES=(data/books.dat data/readers.dat data/borrow_records.dat)
TEST_SOURCES=(tests/automated/book_management_test.cpp)
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

    books.push_back({1, "Title", "Author", 2});
    readers.push_back({1, "Reader", "000"});
    records.push_back({1, 1, BORROWED});

    return (books[0].id == 1 &&
            readers[0].id == 1 &&
            records[0].status == BORROWED &&
            RETURNED == 0) ? 0 : 1;
}
CPP

note "building header compile check"
"$CXX_BIN" "${CXXFLAGS[@]}" -I. "$TMP_DIR/header_check.cpp" -o "$TMP_DIR/header_check" ||
  fail "header compile check build failed"

note "running header compile check"
"$TMP_DIR/header_check" || fail "header compile check failed"

note "building book management automated test"
"$CXX_BIN" "${CXXFLAGS[@]}" -I. tests/automated/book_management_test.cpp book.cpp -o "$TMP_DIR/book_management_test" ||
  fail "book management automated test build failed"

note "running book management automated test"
"$TMP_DIR/book_management_test" || fail "book management automated test failed"

note "ACCEPTED: deterministic verification passed"
