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

    LibraryData mainData;
    string mainMenuOutput = runMainMenuWithInput(mainData, "0\n");
    if (!containsText(mainMenuOutput, "LIBRARY MANAGEMENT SYSTEM") ||
        !containsText(mainMenuOutput, "0. Exit")) {
        return fail("mainMenu should display the Main Menu and allow Exit");
    }

    cout << "PASS: menu management automated checks" << endl;
    return 0;
}

#endif
