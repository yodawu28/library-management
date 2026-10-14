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
    vector<Book>& books,
    vector<Reader>& readers,
    vector<BorrowRecord>& records
) {
    int readerId;
    cout << "Enter reader ID: ";
    if (!(cin >> readerId)) {
        cout << "Invalid reader ID." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    Reader* reader = getReaderById(readers, readerId);
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

    Book* book = getBookById(books, bookId);
    if (book == nullptr) {
        cout << "Book not found." << endl;
        return;
    }

    if (book->quantity <= 0) {
        cout << "Book is unavailable." << endl;
        return;
    }

    if (getActiveBorrowRecord(records, readerId, bookId) != nullptr) {
        cout << "Reader already borrowed this book." << endl;
        return;
    }

    BorrowRecord record;
    record.readerId = readerId;
    record.bookId = bookId;
    record.status = BORROWED;

    records.push_back(record);
    book->quantity--;

    cout << "Book borrowed successfully." << endl;
}
