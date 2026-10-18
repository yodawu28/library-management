#include "library.h"

#include <iostream>
#include <sstream>

#ifdef STARTUP_LOAD_TEST

int loadStep = 0;
bool wrongLoadOrder = false;
bool mainMenuCalled = false;
int booksSeenByMenu = 0;
int readersSeenByMenu = 0;
int recordsSeenByMenu = 0;

int fail(const string& message) {
    cout << "FAIL: " << message << endl;
    return 1;
}

void loadBooks(vector<Book>& books) {
    if (loadStep != 0) {
        wrongLoadOrder = true;
    }
    books.push_back({1001, "Clean Code", "Robert C. Martin", 3});
    loadStep++;
}

void loadReaders(vector<Reader>& readers) {
    if (loadStep != 1) {
        wrongLoadOrder = true;
    }
    readers.push_back({2001, "Nguyen Van An", "0901234567"});
    loadStep++;
}

void loadBorrowRecords(vector<BorrowRecord>& records) {
    if (loadStep != 2) {
        wrongLoadOrder = true;
    }
    records.push_back({1001, 2001, BORROWED});
    loadStep++;
}

void mainMenu(LibraryData& data) {
    mainMenuCalled = true;
    if (loadStep != 3) {
        wrongLoadOrder = true;
    }
    booksSeenByMenu = data.books.size();
    readersSeenByMenu = data.readers.size();
    recordsSeenByMenu = data.borrowRecords.size();
}

int libraryProgramMain();

int main() {
    int result = libraryProgramMain();

    if (result != 0) {
        return fail("program main should return 0");
    }
    if (!mainMenuCalled) {
        return fail("main should enter mainMenu after startup load");
    }
    if (wrongLoadOrder) {
        return fail("main should load books, readers, and borrow records before mainMenu");
    }
    if (booksSeenByMenu != 1 || readersSeenByMenu != 1 || recordsSeenByMenu != 1) {
        return fail("mainMenu should receive data loaded from all files");
    }

    cout << "PASS: startup load automated checks" << endl;
    return 0;
}

#else

int fail(const string& message) {
    cout << "FAIL: " << message << endl;
    return 1;
}

bool containsText(const string& text, const string& keyword) {
    return text.find(keyword) != string::npos;
}

string runBookMenuWithInput(LibraryData& data, const string& input) {
    istringstream inputStream(input);
    ostringstream output;
    streambuf* originalInput = cin.rdbuf(inputStream.rdbuf());
    streambuf* originalOutput = cout.rdbuf(output.rdbuf());

    bookMenu(data);

    cin.rdbuf(originalInput);
    cout.rdbuf(originalOutput);
    return output.str();
}

string runReaderMenuWithInput(LibraryData& data, const string& input) {
    istringstream inputStream(input);
    ostringstream output;
    streambuf* originalInput = cin.rdbuf(inputStream.rdbuf());
    streambuf* originalOutput = cout.rdbuf(output.rdbuf());

    readerMenu(data);

    cin.rdbuf(originalInput);
    cout.rdbuf(originalOutput);
    return output.str();
}

string runMainMenuWithInput(LibraryData& data, const string& input) {
    istringstream inputStream(input);
    ostringstream output;
    streambuf* originalInput = cin.rdbuf(inputStream.rdbuf());
    streambuf* originalOutput = cout.rdbuf(output.rdbuf());

    mainMenu(data);

    cin.rdbuf(originalInput);
    cout.rdbuf(originalOutput);
    return output.str();
}

int main() {
    LibraryData bookData;
    bookData.books.push_back({1001, "Clean Code", "Robert C. Martin", 3});
    string bookMenuOutput = runBookMenuWithInput(bookData, "0\n");
    if (!containsText(bookMenuOutput, "BOOK MANAGEMENT") ||
        !containsText(bookMenuOutput, "0. Back")) {
        return fail("bookMenu should display the Book Management menu and allow Back");
    }
    if (bookData.books.size() != 1) {
        return fail("bookMenu Back option should not change book data");
    }

    LibraryData addBookData;
    string addBookOutput = runBookMenuWithInput(
        addBookData,
        "1\n"
        "1001\n"
        "Clean Code\n"
        "Robert C. Martin\n"
        "3\n"
        "0\n"
    );
    if (addBookData.books.size() != 1 ||
        addBookData.books[0].id != 1001 ||
        addBookData.books[0].title != "Clean Code" ||
        addBookData.books[0].author != "Robert C. Martin" ||
        addBookData.books[0].quantity != 3) {
        return fail("bookMenu Add Book option should call addBook with data.books");
    }
    if (!containsText(addBookOutput, "Book added successfully")) {
        return fail("bookMenu Add Book option should print add success message");
    }

    LibraryData updateBookData;
    updateBookData.books.push_back({1001, "Clean Code", "Robert C. Martin", 3});
    string updateBookOutput = runBookMenuWithInput(
        updateBookData,
        "2\n"
        "1001\n"
        "Clean Code Updated\n"
        "Robert Martin\n"
        "5\n"
        "0\n"
    );
    if (updateBookData.books[0].title != "Clean Code Updated" ||
        updateBookData.books[0].author != "Robert Martin" ||
        updateBookData.books[0].quantity != 5) {
        return fail("bookMenu Update Book option should call updateBook with data.books");
    }
    if (!containsText(updateBookOutput, "Book updated successfully")) {
        return fail("bookMenu Update Book option should print update success message");
    }

    LibraryData protectedDeleteData;
    protectedDeleteData.books.push_back({1001, "Clean Code", "Robert C. Martin", 3});
    protectedDeleteData.borrowRecords.push_back({1001, 2001, BORROWED});
    string protectedDeleteOutput = runBookMenuWithInput(
        protectedDeleteData,
        "3\n"
        "1001\n"
        "0\n"
    );
    if (protectedDeleteData.books.size() != 1) {
        return fail("bookMenu Delete Book option should use active-borrow-aware deleteBook");
    }
    if (!containsText(protectedDeleteOutput, "Book is currently borrowed")) {
        return fail("bookMenu Delete Book option should reject active borrowed books");
    }

    LibraryData deleteBookData;
    deleteBookData.books.push_back({1001, "Clean Code", "Robert C. Martin", 3});
    string deleteBookOutput = runBookMenuWithInput(
        deleteBookData,
        "3\n"
        "1001\n"
        "0\n"
    );
    if (!deleteBookData.books.empty()) {
        return fail("bookMenu Delete Book option should remove an unborrowed book");
    }
    if (!containsText(deleteBookOutput, "Book deleted successfully")) {
        return fail("bookMenu Delete Book option should print delete success message");
    }

    LibraryData searchBookData;
    searchBookData.books.push_back({1001, "Clean Code", "Robert C. Martin", 3});
    string searchBookOutput = runBookMenuWithInput(
        searchBookData,
        "4\n"
        "1\n"
        "1001\n"
        "0\n"
    );
    if (!containsText(searchBookOutput, "Clean Code")) {
        return fail("bookMenu Search Book option should call searchBook with data.books");
    }

    LibraryData displayBookData;
    displayBookData.books.push_back({1001, "Clean Code", "Robert C. Martin", 3});
    string displayBookOutput = runBookMenuWithInput(displayBookData, "5\n0\n");
    if (!containsText(displayBookOutput, "Book List") ||
        !containsText(displayBookOutput, "Clean Code")) {
        return fail("bookMenu Display Books option should call displayBooks with data.books");
    }

    LibraryData sortBookData;
    sortBookData.books.push_back({1002, "Code Complete", "Steve McConnell", 2});
    sortBookData.books.push_back({1001, "Clean Code", "Robert C. Martin", 3});
    string sortBookOutput = runBookMenuWithInput(sortBookData, "6\n1\n0\n");
    if (sortBookData.books.size() != 2 ||
        sortBookData.books[0].id != 1001 ||
        sortBookData.books[1].id != 1002) {
        return fail("bookMenu Sort Books option should call sortBooks with data.books");
    }
    if (!containsText(sortBookOutput, "Books sorted successfully")) {
        return fail("bookMenu Sort Books option should print sort success message");
    }

    LibraryData readerData;
    readerData.readers.push_back({2001, "Nguyen Van An", "0901234567"});
    string readerMenuOutput = runReaderMenuWithInput(readerData, "0\n");
    if (!containsText(readerMenuOutput, "READER MANAGEMENT") ||
        !containsText(readerMenuOutput, "0. Back")) {
        return fail("readerMenu should display the Reader Management menu and allow Back");
    }
    if (readerData.readers.size() != 1) {
        return fail("readerMenu Back option should not change reader data");
    }

    LibraryData addReaderData;
    string addReaderOutput = runReaderMenuWithInput(
        addReaderData,
        "1\n"
        "2001\n"
        "Nguyen Van An\n"
        "0901234567\n"
        "0\n"
    );
    if (addReaderData.readers.size() != 1 ||
        addReaderData.readers[0].id != 2001 ||
        addReaderData.readers[0].name != "Nguyen Van An" ||
        addReaderData.readers[0].phone != "0901234567") {
        return fail("readerMenu Add Reader option should call addReader with data.readers");
    }
    if (!containsText(addReaderOutput, "Reader added successfully")) {
        return fail("readerMenu Add Reader option should print add success message");
    }

    LibraryData updateReaderData;
    updateReaderData.readers.push_back({2001, "Nguyen Van An", "0901234567"});
    string updateReaderOutput = runReaderMenuWithInput(
        updateReaderData,
        "2\n"
        "2001\n"
        "Nguyen Van An Updated\n"
        "0912345678\n"
        "0\n"
    );
    if (updateReaderData.readers[0].name != "Nguyen Van An Updated" ||
        updateReaderData.readers[0].phone != "0912345678") {
        return fail("readerMenu Update Reader option should call updateReader with data.readers");
    }
    if (!containsText(updateReaderOutput, "Reader updated successfully")) {
        return fail("readerMenu Update Reader option should print update success message");
    }

    LibraryData protectedReaderDeleteData;
    protectedReaderDeleteData.readers.push_back({2001, "Nguyen Van An", "0901234567"});
    protectedReaderDeleteData.borrowRecords.push_back({1001, 2001, BORROWED});
    string protectedReaderDeleteOutput = runReaderMenuWithInput(
        protectedReaderDeleteData,
        "3\n"
        "2001\n"
        "0\n"
    );
    if (protectedReaderDeleteData.readers.size() != 1) {
        return fail("readerMenu Delete Reader option should use active-borrow-aware deleteReader");
    }
    if (!containsText(protectedReaderDeleteOutput, "Reader is currently borrowing books")) {
        return fail("readerMenu Delete Reader option should reject readers with active borrows");
    }

    LibraryData deleteReaderData;
    deleteReaderData.readers.push_back({2001, "Nguyen Van An", "0901234567"});
    string deleteReaderOutput = runReaderMenuWithInput(
        deleteReaderData,
        "3\n"
        "2001\n"
        "0\n"
    );
    if (!deleteReaderData.readers.empty()) {
        return fail("readerMenu Delete Reader option should remove a reader without active borrows");
    }
    if (!containsText(deleteReaderOutput, "Reader deleted successfully")) {
        return fail("readerMenu Delete Reader option should print delete success message");
    }

    LibraryData searchReaderData;
    searchReaderData.readers.push_back({2001, "Nguyen Van An", "0901234567"});
    string searchReaderOutput = runReaderMenuWithInput(
        searchReaderData,
        "4\n"
        "1\n"
        "2001\n"
        "0\n"
    );
    if (!containsText(searchReaderOutput, "Nguyen Van An")) {
        return fail("readerMenu Search Reader option should call searchReader with data.readers");
    }

    LibraryData displayReaderData;
    displayReaderData.readers.push_back({2001, "Nguyen Van An", "0901234567"});
    string displayReaderOutput = runReaderMenuWithInput(displayReaderData, "5\n0\n");
    if (!containsText(displayReaderOutput, "Reader List") ||
        !containsText(displayReaderOutput, "Nguyen Van An")) {
        return fail("readerMenu Display Readers option should call displayReaders with data.readers");
    }

    LibraryData mainData;
    string mainMenuOutput = runMainMenuWithInput(mainData, "0\n");
    if (!containsText(mainMenuOutput, "LIBRARY MANAGEMENT SYSTEM") ||
        !containsText(mainMenuOutput, "0. Exit")) {
        return fail("mainMenu should display the Main Menu and allow Exit");
    }

    LibraryData mainBookData;
    string mainBookOutput = runMainMenuWithInput(mainBookData, "1\n0\n0\n");
    if (!containsText(mainBookOutput, "BOOK MANAGEMENT")) {
        return fail("mainMenu Book Management option should open bookMenu");
    }

    LibraryData mainReaderData;
    string mainReaderOutput = runMainMenuWithInput(mainReaderData, "2\n0\n0\n");
    if (!containsText(mainReaderOutput, "READER MANAGEMENT")) {
        return fail("mainMenu Reader Management option should open readerMenu");
    }

    LibraryData mainBorrowData;
    mainBorrowData.books.push_back({1001, "Clean Code", "Robert C. Martin", 2});
    mainBorrowData.readers.push_back({2001, "Nguyen Van An", "0901234567"});
    string mainBorrowOutput = runMainMenuWithInput(
        mainBorrowData,
        "3\n"
        "2001\n"
        "1001\n"
        "0\n"
    );
    if (mainBorrowData.borrowRecords.size() != 1 ||
        mainBorrowData.borrowRecords[0].readerId != 2001 ||
        mainBorrowData.borrowRecords[0].bookId != 1001 ||
        mainBorrowData.borrowRecords[0].status != BORROWED ||
        mainBorrowData.books[0].quantity != 1) {
        return fail("mainMenu Borrow Book option should call borrowBook with LibraryData");
    }
    if (!containsText(mainBorrowOutput, "Book borrowed successfully")) {
        return fail("mainMenu Borrow Book option should print borrow success message");
    }

    LibraryData mainReturnData;
    mainReturnData.books.push_back({1001, "Clean Code", "Robert C. Martin", 1});
    mainReturnData.readers.push_back({2001, "Nguyen Van An", "0901234567"});
    mainReturnData.borrowRecords.push_back({1001, 2001, BORROWED});
    string mainReturnOutput = runMainMenuWithInput(
        mainReturnData,
        "4\n"
        "2001\n"
        "1001\n"
        "0\n"
    );
    if (mainReturnData.borrowRecords[0].status != RETURNED ||
        mainReturnData.books[0].quantity != 2) {
        return fail("mainMenu Return Book option should call returnBook with LibraryData");
    }
    if (!containsText(mainReturnOutput, "Book returned successfully")) {
        return fail("mainMenu Return Book option should print return success message");
    }

    cout << "PASS: menu management automated checks" << endl;
    return 0;
}

#endif
