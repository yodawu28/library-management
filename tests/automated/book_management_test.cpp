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
    streambuf* originalOutput = cout.rdbuf(output.rdbuf());

    displayBooks(books);

    cout.rdbuf(originalOutput);
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

    if (addedBooks.size() != 1) {
        return fail("valid Add Book should insert one book");
    }
    if (addedBooks[0].id != 1001 ||
        addedBooks[0].title != "Clean Code" ||
        addedBooks[0].author != "Robert C. Martin" ||
        addedBooks[0].quantity != 3) {
        return fail("valid Add Book should store all book fields");
    }
    if (!containsText(addOutput, "Book added successfully")) {
        return fail("valid Add Book should print success message");
    }

    string duplicateOutput = runAddBookWithInput(addedBooks, "1001\n");
    if (addedBooks.size() != 1) {
        return fail("duplicate Add Book should not insert a book");
    }
    if (!containsText(duplicateOutput, "Book ID already exists")) {
        return fail("duplicate Add Book should print duplicate ID message");
    }

    vector<Book> invalidBooks;
    string nonPositiveIdOutput = runAddBookWithInput(
        invalidBooks,
        "0\n"
        "Invalid ID Book\n"
        "Some Author\n"
        "2\n"
    );
    if (!invalidBooks.empty()) {
        return fail("non-positive Book ID should not insert a book");
    }
    if (!containsText(nonPositiveIdOutput, "Book ID must be positive")) {
        return fail("non-positive Book ID should print validation message");
    }

    string emptyTitleOutput = runAddBookWithInput(
        invalidBooks,
        "1002\n"
        "\n"
        "Some Author\n"
        "2\n"
    );
    if (!invalidBooks.empty()) {
        return fail("empty title should not insert a book");
    }
    if (!containsText(emptyTitleOutput, "Title cannot be empty")) {
        return fail("empty title should print validation message");
    }

    string emptyAuthorOutput = runAddBookWithInput(
        invalidBooks,
        "1003\n"
        "Some Title\n"
        "\n"
        "2\n"
    );
    if (!invalidBooks.empty()) {
        return fail("empty author should not insert a book");
    }
    if (!containsText(emptyAuthorOutput, "Author cannot be empty")) {
        return fail("empty author should print validation message");
    }

    string negativeQuantityOutput = runAddBookWithInput(
        invalidBooks,
        "1004\n"
        "Some Title\n"
        "Some Author\n"
        "-1\n"
    );
    if (!invalidBooks.empty()) {
        return fail("negative quantity should not insert a book");
    }
    if (!containsText(negativeQuantityOutput, "Quantity cannot be negative")) {
        return fail("negative quantity should print validation message");
    }

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
    if (updateBooks.size() != 2 ||
        updateBooks[0].id != 1001 ||
        updateBooks[0].title != "Clean Code Updated" ||
        updateBooks[0].author != "Robert Martin" ||
        updateBooks[0].quantity != 5 ||
        updateBooks[1].title != "Code Complete") {
        return fail("valid Update Book should update only the selected book");
    }
    if (!containsText(updateOutput, "Book updated successfully")) {
        return fail("valid Update Book should print success message");
    }

    string missingUpdateOutput = runUpdateBookWithInput(updateBooks, "9999\n");
    if (updateBooks.size() != 2) {
        return fail("missing Update Book ID should not change list size");
    }
    if (!containsText(missingUpdateOutput, "Book not found")) {
        return fail("missing Update Book ID should print not found message");
    }

    string emptyUpdateTitleOutput = runUpdateBookWithInput(
        updateBooks,
        "1001\n"
        "\n"
        "Some Author\n"
        "4\n"
    );
    if (updateBooks[0].title != "Clean Code Updated" ||
        updateBooks[0].author != "Robert Martin" ||
        updateBooks[0].quantity != 5) {
        return fail("empty update title should keep original book data");
    }
    if (!containsText(emptyUpdateTitleOutput, "Title cannot be empty")) {
        return fail("empty update title should print validation message");
    }

    string emptyUpdateAuthorOutput = runUpdateBookWithInput(
        updateBooks,
        "1001\n"
        "Some Title\n"
        "\n"
        "4\n"
    );
    if (updateBooks[0].title != "Clean Code Updated" ||
        updateBooks[0].author != "Robert Martin" ||
        updateBooks[0].quantity != 5) {
        return fail("empty update author should keep original book data");
    }
    if (!containsText(emptyUpdateAuthorOutput, "Author cannot be empty")) {
        return fail("empty update author should print validation message");
    }

    string negativeUpdateQuantityOutput = runUpdateBookWithInput(
        updateBooks,
        "1001\n"
        "Some Title\n"
        "Some Author\n"
        "-1\n"
    );
    if (updateBooks[0].title != "Clean Code Updated" ||
        updateBooks[0].author != "Robert Martin" ||
        updateBooks[0].quantity != 5) {
        return fail("negative update quantity should keep original book data");
    }
    if (!containsText(negativeUpdateQuantityOutput, "Quantity cannot be negative")) {
        return fail("negative update quantity should print validation message");
    }

    vector<Book> emptyBooks;
    string emptyOutput = captureDisplayBooksOutput(emptyBooks);
    if (!containsText(emptyOutput, "No books available")) {
        return fail("Display Books should print empty-list message");
    }

    vector<Book> books = {
        {1001, "Clean Code", "Robert C. Martin", 3},
        {1002, "Code Complete", "Steve McConnell", 2},
    };

    string listOutput = captureDisplayBooksOutput(books);
    if (!containsText(listOutput, "ID: 1001") ||
        !containsText(listOutput, "Title: Clean Code") ||
        !containsText(listOutput, "Author: Robert C. Martin") ||
        !containsText(listOutput, "Quantity: 3") ||
        !containsText(listOutput, "ID: 1002") ||
        !containsText(listOutput, "Title: Code Complete") ||
        !containsText(listOutput, "Author: Steve McConnell") ||
        !containsText(listOutput, "Quantity: 2")) {
        return fail("Display Books should print all book fields");
    }

    cout << "PASS: book management automated checks" << endl;
    return 0;
}
