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
    (void)static_cast<void (*)(
        vector<Book>&,
        vector<Reader>&,
        vector<BorrowRecord>&
    )>(&borrowBook);
}

int main() {
    verifyBorrowManagementFunctionsAreLinked();

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

    cout << "PASS: borrow management automated checks" << endl;
    return 0;
}
