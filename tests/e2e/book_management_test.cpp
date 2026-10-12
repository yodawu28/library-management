#include "library.h"

#include <cassert>
#include <iostream>
#include <sstream>

string runAddBookWithInput(vector<Book>& books, const string& input) {
    istringstream inputStream(input);
    ostringstream output;
    streambuf* originalInput = cin.rdbuf(inputStream.rdbuf());
    streambuf* originalOutput = cout.rdbuf(output.rdbuf());

    addBook(books);

    cin.rdbuf(originalInput);
    cout.rdbuf(originalOutput);
    return output.str();
}

string runUpdateBookWithInput(vector<Book>& books, const string& input) {
    istringstream inputStream(input);
    ostringstream output;
    streambuf* originalInput = cin.rdbuf(inputStream.rdbuf());
    streambuf* originalOutput = cout.rdbuf(output.rdbuf());

    updateBook(books);

    cin.rdbuf(originalInput);
    cout.rdbuf(originalOutput);
    return output.str();
}

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

    vector<Book> addedBooks;
    string addOutput = runAddBookWithInput(
        addedBooks,
        "1001\n"
        "Clean Code\n"
        "Robert C. Martin\n"
        "3\n"
    );
    assert(addedBooks.size() == 1);
    assert(addedBooks[0].id == 1001);
    assert(addedBooks[0].title == "Clean Code");
    assert(addedBooks[0].author == "Robert C. Martin");
    assert(addedBooks[0].quantity == 3);
    assert(addOutput.find("Book added successfully") != string::npos);

    string duplicateOutput = runAddBookWithInput(
        addedBooks,
        "1001\n"
    );
    assert(addedBooks.size() == 1);
    assert(duplicateOutput.find("Book ID already exists") != string::npos);

    vector<Book> invalidBooks;
    string nonPositiveIdOutput = runAddBookWithInput(
        invalidBooks,
        "0\n"
        "Invalid ID Book\n"
        "Some Author\n"
        "2\n"
    );
    assert(invalidBooks.empty());
    assert(nonPositiveIdOutput.find("Book ID must be positive") != string::npos);

    string emptyTitleOutput = runAddBookWithInput(
        invalidBooks,
        "1002\n"
        "\n"
        "Some Author\n"
        "2\n"
    );
    assert(invalidBooks.empty());
    assert(emptyTitleOutput.find("Title cannot be empty") != string::npos);

    string emptyAuthorOutput = runAddBookWithInput(
        invalidBooks,
        "1003\n"
        "Some Title\n"
        "\n"
        "2\n"
    );
    assert(invalidBooks.empty());
    assert(emptyAuthorOutput.find("Author cannot be empty") != string::npos);

    string negativeQuantityOutput = runAddBookWithInput(
        invalidBooks,
        "1004\n"
        "Some Title\n"
        "Some Author\n"
        "-1\n"
    );
    assert(invalidBooks.empty());
    assert(negativeQuantityOutput.find("Quantity cannot be negative") != string::npos);

    vector<Book> updateBooks = {
        {1001, "Clean Code", "Robert C. Martin", 3},
        {1002, "Code Complete", "Steve McConnell", 2},
    };

    string updateOutput = runUpdateBookWithInput(
        updateBooks,
        "1001\n"
        "Clean Code Updated\n"
        "Robert Martin\n"
        "5\n"
    );
    assert(updateBooks.size() == 2);
    assert(updateBooks[0].id == 1001);
    assert(updateBooks[0].title == "Clean Code Updated");
    assert(updateBooks[0].author == "Robert Martin");
    assert(updateBooks[0].quantity == 5);
    assert(updateBooks[1].title == "Code Complete");
    assert(updateOutput.find("Book updated successfully") != string::npos);

    string missingUpdateOutput = runUpdateBookWithInput(
        updateBooks,
        "9999\n"
    );
    assert(updateBooks.size() == 2);
    assert(missingUpdateOutput.find("Book not found") != string::npos);

    string emptyUpdateTitleOutput = runUpdateBookWithInput(
        updateBooks,
        "1001\n"
        "\n"
        "Some Author\n"
        "4\n"
    );
    assert(updateBooks[0].title == "Clean Code Updated");
    assert(updateBooks[0].author == "Robert Martin");
    assert(updateBooks[0].quantity == 5);
    assert(emptyUpdateTitleOutput.find("Title cannot be empty") != string::npos);

    string emptyUpdateAuthorOutput = runUpdateBookWithInput(
        updateBooks,
        "1001\n"
        "Some Title\n"
        "\n"
        "4\n"
    );
    assert(updateBooks[0].title == "Clean Code Updated");
    assert(updateBooks[0].author == "Robert Martin");
    assert(updateBooks[0].quantity == 5);
    assert(emptyUpdateAuthorOutput.find("Author cannot be empty") != string::npos);

    string negativeUpdateQuantityOutput = runUpdateBookWithInput(
        updateBooks,
        "1001\n"
        "Some Title\n"
        "Some Author\n"
        "-1\n"
    );
    assert(updateBooks[0].title == "Clean Code Updated");
    assert(updateBooks[0].author == "Robert Martin");
    assert(updateBooks[0].quantity == 5);
    assert(negativeUpdateQuantityOutput.find("Quantity cannot be negative") != string::npos);

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
