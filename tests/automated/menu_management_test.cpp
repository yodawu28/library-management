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
