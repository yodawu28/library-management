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
    LibraryData& data,
    const string& input
) {
    istringstream inputStream(input);
    ostringstream output;
    streambuf* originalInput = cin.rdbuf(inputStream.rdbuf());
    streambuf* originalOutput = cout.rdbuf(output.rdbuf());

    borrowBook(data);

    cin.rdbuf(originalInput);
    cout.rdbuf(originalOutput);
    return output.str();
}

string runBorrowBookTwiceWithInput(
    LibraryData& data,
    const string& input
) {
    istringstream inputStream(input);
    ostringstream output;
    streambuf* originalInput = cin.rdbuf(inputStream.rdbuf());
    streambuf* originalOutput = cout.rdbuf(output.rdbuf());

    borrowBook(data);
    borrowBook(data);

    cin.rdbuf(originalInput);
    cout.rdbuf(originalOutput);
    return output.str();
}

string runReturnBookWithInput(
    LibraryData& data,
    const string& input
) {
    istringstream inputStream(input);
    ostringstream output;
    streambuf* originalInput = cin.rdbuf(inputStream.rdbuf());
    streambuf* originalOutput = cout.rdbuf(output.rdbuf());

    returnBook(data);

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
        LibraryData&
    )>(&borrowBook);
    (void)static_cast<void (*)(LibraryData&)>(&returnBook);
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

    LibraryData data;
    data.books.push_back({1001, "Clean Code", "Robert C. Martin", 2});
    data.readers.push_back({2001, "Nguyen Van An", "0901234567"});

    string borrowOutput = runBorrowBookWithInput(
        data,
        "2001\n"
        "1001\n"
    );

    if (data.borrowRecords.size() != 1) {
        return fail("valid Borrow Book should create one borrow record");
    }
    if (data.borrowRecords[0].readerId != 2001 ||
        data.borrowRecords[0].bookId != 1001 ||
        data.borrowRecords[0].status != BORROWED) {
        return fail("valid Borrow Book should store reader ID, book ID, and BORROWED status");
    }
    if (data.books[0].quantity != 1) {
        return fail("valid Borrow Book should decrease book quantity");
    }
    if (!containsText(borrowOutput, "Book borrowed successfully")) {
        return fail("valid Borrow Book should print success message");
    }

    LibraryData invalidReaderData;
    invalidReaderData.books.push_back({1002, "Code Complete", "Steve McConnell", 2});
    invalidReaderData.readers.push_back({2002, "Tran Thi Binh", "0902222333"});
    string invalidReaderOutput = runBorrowBookTwiceWithInput(
        invalidReaderData,
        "abc\n"
        "2002\n"
        "1002\n"
    );
    if (invalidReaderData.borrowRecords.size() != 1) {
        return fail("invalid reader ID should clear input so the next borrow can succeed");
    }
    if (invalidReaderData.books[0].quantity != 1) {
        return fail("valid borrow after invalid reader ID should decrease quantity once");
    }
    if (!containsText(invalidReaderOutput, "Invalid reader ID") ||
        !containsText(invalidReaderOutput, "Book borrowed successfully")) {
        return fail("invalid reader ID recovery should print error then success");
    }

    LibraryData invalidBookData;
    invalidBookData.books.push_back({1003, "The Pragmatic Programmer", "Andrew Hunt", 2});
    invalidBookData.readers.push_back({2003, "Le Van Cuong", "0903333444"});
    string invalidBookOutput = runBorrowBookTwiceWithInput(
        invalidBookData,
        "2003\n"
        "xyz\n"
        "2003\n"
        "1003\n"
    );
    if (invalidBookData.borrowRecords.size() != 1) {
        return fail("invalid book ID should clear input so the next borrow can succeed");
    }
    if (invalidBookData.books[0].quantity != 1) {
        return fail("valid borrow after invalid book ID should decrease quantity once");
    }
    if (!containsText(invalidBookOutput, "Invalid book ID") ||
        !containsText(invalidBookOutput, "Book borrowed successfully")) {
        return fail("invalid book ID recovery should print error then success");
    }

    LibraryData missingReaderData;
    missingReaderData.books.push_back({1004, "Design Patterns", "Erich Gamma", 2});
    missingReaderData.readers.push_back({2004, "Pham Thi Dung", "0904444555"});
    string missingReaderOutput = runBorrowBookWithInput(
        missingReaderData,
        "9999\n"
    );
    if (!missingReaderData.borrowRecords.empty()) {
        return fail("missing Reader should not create borrow record");
    }
    if (missingReaderData.books[0].quantity != 2) {
        return fail("missing Reader should not change book quantity");
    }
    if (!containsText(missingReaderOutput, "Reader not found")) {
        return fail("missing Reader should print not found message");
    }

    LibraryData missingBookData;
    missingBookData.books.push_back({1005, "Refactoring", "Martin Fowler", 2});
    missingBookData.readers.push_back({2005, "Hoang Van Em", "0905555666"});
    string missingBookOutput = runBorrowBookWithInput(
        missingBookData,
        "2005\n"
        "9999\n"
    );
    if (!missingBookData.borrowRecords.empty()) {
        return fail("missing Book should not create borrow record");
    }
    if (missingBookData.books[0].quantity != 2) {
        return fail("missing Book should not change book quantity");
    }
    if (!containsText(missingBookOutput, "Book not found")) {
        return fail("missing Book should print not found message");
    }

    LibraryData unavailableData;
    unavailableData.books.push_back({1006, "Domain-Driven Design", "Eric Evans", 0});
    unavailableData.readers.push_back({2006, "Do Thi Giang", "0906666777"});
    string unavailableOutput = runBorrowBookWithInput(
        unavailableData,
        "2006\n"
        "1006\n"
    );
    if (!unavailableData.borrowRecords.empty()) {
        return fail("unavailable Book should not create borrow record");
    }
    if (unavailableData.books[0].quantity != 0) {
        return fail("unavailable Book should keep quantity unchanged");
    }
    if (!containsText(unavailableOutput, "Book is unavailable")) {
        return fail("unavailable Book should print unavailable message");
    }

    LibraryData duplicateData;
    duplicateData.books.push_back({1007, "Effective C++", "Scott Meyers", 2});
    duplicateData.readers.push_back({2007, "Bui Van Hung", "0907777888"});
    duplicateData.borrowRecords.push_back({1007, 2007, BORROWED});
    string duplicateOutput = runBorrowBookWithInput(
        duplicateData,
        "2007\n"
        "1007\n"
    );
    if (duplicateData.borrowRecords.size() != 1) {
        return fail("duplicate active borrow should not create another record");
    }
    if (duplicateData.books[0].quantity != 2) {
        return fail("duplicate active borrow should keep quantity unchanged");
    }
    if (!containsText(duplicateOutput, "Reader already borrowed this book")) {
        return fail("duplicate active borrow should print duplicate message");
    }

    LibraryData returnData;
    returnData.books.push_back({1008, "C++ Primer", "Stanley Lippman", 1});
    returnData.borrowRecords.push_back({1008, 2008, BORROWED});
    string returnOutput = runReturnBookWithInput(
        returnData,
        "2008\n"
        "1008\n"
    );
    if (returnData.borrowRecords[0].status != RETURNED) {
        return fail("valid Return Book should update status to RETURNED");
    }
    if (returnData.books[0].quantity != 2) {
        return fail("valid Return Book should increase book quantity");
    }
    if (!containsText(returnOutput, "Book returned successfully")) {
        return fail("valid Return Book should print success message");
    }

    cout << "PASS: borrow management automated checks" << endl;
    return 0;
}
