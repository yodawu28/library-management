#include "library.h"

#include <iostream>
#include <limits>

BorrowRecord* getActiveBorrowRecord(
    vector<BorrowRecord>& records,
    int readerId,
    int bookId
) {
    for (BorrowRecord& record : records) {
        if (record.readerId == readerId &&
            record.bookId == bookId &&
            record.status == BORROWED) {
            return &record;
        }
    }

    return nullptr;
}

void borrowBook(
    LibraryData& data
) {
    int readerId;
    cout << "Enter reader ID: ";
    if (!(cin >> readerId)) {
        cout << "Invalid reader ID." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    Reader* reader = getReaderById(data.readers, readerId);
    if (reader == nullptr) {
        cout << "Reader not found." << endl;
        return;
    }

    int bookId;
    cout << "Enter book ID: ";
    if (!(cin >> bookId)) {
        cout << "Invalid book ID." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    Book* book = getBookById(data.books, bookId);
    if (book == nullptr) {
        cout << "Book not found." << endl;
        return;
    }

    if (book->quantity <= 0) {
        cout << "Book is unavailable." << endl;
        return;
    }

    if (getActiveBorrowRecord(data.borrowRecords, readerId, bookId) != nullptr) {
        cout << "Reader already borrowed this book." << endl;
        return;
    }

    BorrowRecord record;
    record.readerId = readerId;
    record.bookId = bookId;
    record.status = BORROWED;

    data.borrowRecords.push_back(record);
    book->quantity--;

    cout << "Book borrowed successfully." << endl;
}

void returnBook(
    LibraryData& data
) {
    int readerId;
    cout << "Enter reader ID: ";
    if (!(cin >> readerId)) {
        cout << "Invalid reader ID." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int bookId;
    cout << "Enter book ID: ";
    if (!(cin >> bookId)) {
        cout << "Invalid book ID." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    BorrowRecord* record = getActiveBorrowRecord(data.borrowRecords, readerId, bookId);
    if (record == nullptr) {
        for (const BorrowRecord& currentRecord : data.borrowRecords) {
            if (currentRecord.readerId == readerId &&
                currentRecord.bookId == bookId &&
                currentRecord.status == RETURNED) {
                cout << "Book already returned." << endl;
                return;
            }
        }

        cout << "Borrow record not found." << endl;
        return;
    }

    Book* book = getBookById(data.books, bookId);
    if (book == nullptr) {
        cout << "Book not found." << endl;
        return;
    }

    record->status = RETURNED;
    book->quantity++;

    cout << "Book returned successfully." << endl;
}
