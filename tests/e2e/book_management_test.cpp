#include "library.h"

#include <cassert>
#include <iostream>
#include <sstream>

string captureDisplayBooksOutput(const vector<Book>& books) {
    ostringstream output;
    streambuf* originalBuffer = cout.rdbuf(output.rdbuf());

    displayBooks(books);

    cout.rdbuf(originalBuffer);
    return output.str();
}

void verifyBookManagementFunctionsAreLinked() {
    (void)static_cast<void (*)(vector<Book>&)>(&addBook);
    (void)static_cast<void (*)(vector<Book>&)>(&updateBook);
    (void)static_cast<void (*)(vector<Book>&)>(&deleteBook);
    (void)static_cast<void (*)(const vector<Book>&)>(&searchBook);
    (void)static_cast<void (*)(const vector<Book>&)>(&displayBooks);
    (void)static_cast<void (*)(vector<Book>&)>(&sortBooks);
}

int main() {
    verifyBookManagementFunctionsAreLinked();

    vector<Book> emptyBooks;
    string emptyOutput = captureDisplayBooksOutput(emptyBooks);
    assert(emptyOutput.find("No books available") != string::npos);

    vector<Book> books = {
        {1001, "Clean Code", "Robert C. Martin", 3},
        {1002, "Code Complete", "Steve McConnell", 2},
    };

    string listOutput = captureDisplayBooksOutput(books);
    assert(listOutput.find("ID: 1001") != string::npos);
    assert(listOutput.find("Title: Clean Code") != string::npos);
    assert(listOutput.find("Author: Robert C. Martin") != string::npos);
    assert(listOutput.find("Quantity: 3") != string::npos);
    assert(listOutput.find("ID: 1002") != string::npos);
    assert(listOutput.find("Title: Code Complete") != string::npos);
    assert(listOutput.find("Author: Steve McConnell") != string::npos);
    assert(listOutput.find("Quantity: 2") != string::npos);

    return 0;
}
