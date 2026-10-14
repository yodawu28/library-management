#include "library.h"

#include <iostream>
#include <sstream>

int fail(const string& message) {
    cout << "FAIL: " << message << endl;
    return 1;
}

bool containsText(const string& text, const string& keyword) {
    return text.find(keyword) != string::npos;
}

string runBorrowBookWithInput(
    vector<Book>& books,
    vector<Reader>& readers,
    vector<BorrowRecord>& records,
    const string& input
) {
    istringstream inputStream(input);
    ostringstream output;
    streambuf* originalInput = cin.rdbuf(inputStream.rdbuf());
    streambuf* originalOutput = cout.rdbuf(output.rdbuf());

    borrowBook(books, readers, records);

    cin.rdbuf(originalInput);
    cout.rdbuf(originalOutput);
    return output.str();
}

string runBorrowBookTwiceWithInput(
    vector<Book>& books,
    vector<Reader>& readers,
    vector<BorrowRecord>& records,
    const string& input
) {
    istringstream inputStream(input);
    ostringstream output;
    streambuf* originalInput = cin.rdbuf(inputStream.rdbuf());
    streambuf* originalOutput = cout.rdbuf(output.rdbuf());

    borrowBook(books, readers, records);
    borrowBook(books, readers, records);

    cin.rdbuf(originalInput);
    cout.rdbuf(originalOutput);
    return output.str();
}

void verifyBorrowManagementFunctionsAreLinked() {
    (void)static_cast<BorrowRecord* (*)(
        vector<BorrowRecord>&,
        int,
        int
    )>(&getActiveBorrowRecord);
    (void)static_cast<void (*)(
        vector<Book>&,
        vector<Reader>&,
        vector<BorrowRecord>&
    )>(&borrowBook);
}

int main() {
    verifyBorrowManagementFunctionsAreLinked();

    vector<BorrowRecord> helperRecords = {
        {1001, 2001, RETURNED},
        {1001, 2001, BORROWED},
        {1002, 2001, BORROWED},
    };
    BorrowRecord* activeRecord = getActiveBorrowRecord(helperRecords, 2001, 1001);
    if (activeRecord == nullptr || activeRecord->status != BORROWED) {
        return fail("getActiveBorrowRecord should return matching BORROWED record");
    }
    activeRecord->status = RETURNED;
    if (helperRecords[1].status != RETURNED) {
        return fail("getActiveBorrowRecord pointer should update the vector item");
    }
    if (getActiveBorrowRecord(helperRecords, 2001, 1001) != nullptr) {
        return fail("getActiveBorrowRecord should ignore returned records");
    }

    vector<Book> books = {
        {1001, "Clean Code", "Robert C. Martin", 2},
    };
    vector<Reader> readers = {
        {2001, "Nguyen Van An", "0901234567"},
    };
    vector<BorrowRecord> records;

    string borrowOutput = runBorrowBookWithInput(
        books,
        readers,
        records,
        "2001\n"
        "1001\n"
    );

    if (records.size() != 1) {
        return fail("valid Borrow Book should create one borrow record");
    }
    if (records[0].readerId != 2001 ||
        records[0].bookId != 1001 ||
        records[0].status != BORROWED) {
        return fail("valid Borrow Book should store reader ID, book ID, and BORROWED status");
    }
    if (books[0].quantity != 1) {
        return fail("valid Borrow Book should decrease book quantity");
    }
    if (!containsText(borrowOutput, "Book borrowed successfully")) {
        return fail("valid Borrow Book should print success message");
    }

    vector<Book> invalidReaderBooks = {
        {1002, "Code Complete", "Steve McConnell", 2},
    };
    vector<Reader> invalidReaderReaders = {
        {2002, "Tran Thi Binh", "0902222333"},
    };
    vector<BorrowRecord> invalidReaderRecords;
    string invalidReaderOutput = runBorrowBookTwiceWithInput(
        invalidReaderBooks,
        invalidReaderReaders,
        invalidReaderRecords,
        "abc\n"
        "2002\n"
        "1002\n"
    );
    if (invalidReaderRecords.size() != 1) {
        return fail("invalid reader ID should clear input so the next borrow can succeed");
    }
    if (invalidReaderBooks[0].quantity != 1) {
        return fail("valid borrow after invalid reader ID should decrease quantity once");
    }
    if (!containsText(invalidReaderOutput, "Invalid reader ID") ||
        !containsText(invalidReaderOutput, "Book borrowed successfully")) {
        return fail("invalid reader ID recovery should print error then success");
    }

    vector<Book> invalidBookBooks = {
        {1003, "The Pragmatic Programmer", "Andrew Hunt", 2},
    };
    vector<Reader> invalidBookReaders = {
        {2003, "Le Van Cuong", "0903333444"},
    };
    vector<BorrowRecord> invalidBookRecords;
    string invalidBookOutput = runBorrowBookTwiceWithInput(
        invalidBookBooks,
        invalidBookReaders,
        invalidBookRecords,
        "2003\n"
        "xyz\n"
        "2003\n"
        "1003\n"
    );
    if (invalidBookRecords.size() != 1) {
        return fail("invalid book ID should clear input so the next borrow can succeed");
    }
    if (invalidBookBooks[0].quantity != 1) {
        return fail("valid borrow after invalid book ID should decrease quantity once");
    }
    if (!containsText(invalidBookOutput, "Invalid book ID") ||
        !containsText(invalidBookOutput, "Book borrowed successfully")) {
        return fail("invalid book ID recovery should print error then success");
    }

    vector<Book> missingReaderBooks = {
        {1004, "Design Patterns", "Erich Gamma", 2},
    };
    vector<Reader> missingReaderReaders = {
        {2004, "Pham Thi Dung", "0904444555"},
    };
    vector<BorrowRecord> missingReaderRecords;
    string missingReaderOutput = runBorrowBookWithInput(
        missingReaderBooks,
        missingReaderReaders,
        missingReaderRecords,
        "9999\n"
    );
    if (!missingReaderRecords.empty()) {
        return fail("missing Reader should not create borrow record");
    }
    if (missingReaderBooks[0].quantity != 2) {
        return fail("missing Reader should not change book quantity");
    }
    if (!containsText(missingReaderOutput, "Reader not found")) {
        return fail("missing Reader should print not found message");
    }

    vector<Book> missingBookBooks = {
        {1005, "Refactoring", "Martin Fowler", 2},
    };
    vector<Reader> missingBookReaders = {
        {2005, "Hoang Van Em", "0905555666"},
    };
    vector<BorrowRecord> missingBookRecords;
    string missingBookOutput = runBorrowBookWithInput(
        missingBookBooks,
        missingBookReaders,
        missingBookRecords,
        "2005\n"
        "9999\n"
    );
    if (!missingBookRecords.empty()) {
        return fail("missing Book should not create borrow record");
    }
    if (missingBookBooks[0].quantity != 2) {
        return fail("missing Book should not change book quantity");
    }
    if (!containsText(missingBookOutput, "Book not found")) {
        return fail("missing Book should print not found message");
    }

    vector<Book> unavailableBooks = {
        {1006, "Domain-Driven Design", "Eric Evans", 0},
    };
    vector<Reader> unavailableReaders = {
        {2006, "Do Thi Giang", "0906666777"},
    };
    vector<BorrowRecord> unavailableRecords;
    string unavailableOutput = runBorrowBookWithInput(
        unavailableBooks,
        unavailableReaders,
        unavailableRecords,
        "2006\n"
        "1006\n"
    );
    if (!unavailableRecords.empty()) {
        return fail("unavailable Book should not create borrow record");
    }
    if (unavailableBooks[0].quantity != 0) {
        return fail("unavailable Book should keep quantity unchanged");
    }
    if (!containsText(unavailableOutput, "Book is unavailable")) {
        return fail("unavailable Book should print unavailable message");
    }

    vector<Book> duplicateBooks = {
        {1007, "Effective C++", "Scott Meyers", 2},
    };
    vector<Reader> duplicateReaders = {
        {2007, "Bui Van Hung", "0907777888"},
    };
    vector<BorrowRecord> duplicateRecords = {
        {1007, 2007, BORROWED},
    };
    string duplicateOutput = runBorrowBookWithInput(
        duplicateBooks,
        duplicateReaders,
        duplicateRecords,
        "2007\n"
        "1007\n"
    );
    if (duplicateRecords.size() != 1) {
        return fail("duplicate active borrow should not create another record");
    }
    if (duplicateBooks[0].quantity != 2) {
        return fail("duplicate active borrow should keep quantity unchanged");
    }
    if (!containsText(duplicateOutput, "Reader already borrowed this book")) {
        return fail("duplicate active borrow should print duplicate message");
    }

    cout << "PASS: borrow management automated checks" << endl;
    return 0;
}
