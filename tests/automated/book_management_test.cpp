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

string runDeleteBookWithInput(vector<Book>& books, const string& input) {
    istringstream inputStream(input);
    ostringstream output;
    streambuf* originalInput = cin.rdbuf(inputStream.rdbuf());
    streambuf* originalOutput = cout.rdbuf(output.rdbuf());

    deleteBook(books);

    cin.rdbuf(originalInput);
    cout.rdbuf(originalOutput);
    return output.str();
}

string runSearchBookWithInput(const vector<Book>& books, const string& input) {
    istringstream inputStream(input);
    ostringstream output;
    streambuf* originalInput = cin.rdbuf(inputStream.rdbuf());
    streambuf* originalOutput = cout.rdbuf(output.rdbuf());

    searchBook(books);

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
    (void)static_cast<Book* (*)(vector<Book>&, int)>(&getBookById);
    (void)static_cast<const Book* (*)(const vector<Book>&, int)>(&getBookById);
    (void)static_cast<void (*)(const Book&)>(&printBook);
    (void)static_cast<void (*)(vector<Book>&)>(&addBook);
    (void)static_cast<void (*)(vector<Book>&)>(&updateBook);
    (void)static_cast<void (*)(vector<Book>&)>(&deleteBook);
    (void)static_cast<void (*)(const vector<Book>&)>(&searchBook);
    (void)static_cast<void (*)(const vector<Book>&)>(&displayBooks);
    (void)static_cast<void (*)(vector<Book>&)>(&sortBooks);
}

int main() {
    verifyBookManagementFunctionsAreLinked();

    vector<Book> helperBooks = {
        {1001, "Clean Code", "Robert C. Martin", 3},
        {1002, "Code Complete", "Steve McConnell", 2},
    };
    Book* mutableBook = getBookById(helperBooks, 1002);
    if (mutableBook == nullptr || mutableBook->title != "Code Complete") {
        return fail("getBookById should return a matching mutable book pointer");
    }
    mutableBook->quantity = 7;
    if (helperBooks[1].quantity != 7) {
        return fail("getBookById mutable pointer should update the vector item");
    }

    const vector<Book>& constHelperBooks = helperBooks;
    const Book* readonlyBook = getBookById(constHelperBooks, 1001);
    if (readonlyBook == nullptr || readonlyBook->author != "Robert C. Martin") {
        return fail("getBookById should return a matching const book pointer");
    }
    if (getBookById(constHelperBooks, 9999) != nullptr) {
        return fail("getBookById should return nullptr when ID is missing");
    }

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

    vector<Book> deleteBooks = {
        {1001, "Clean Code", "Robert C. Martin", 3},
        {1002, "Code Complete", "Steve McConnell", 2},
        {1003, "The Pragmatic Programmer", "Andrew Hunt", 4},
    };

    string deleteOutput = runDeleteBookWithInput(deleteBooks, "1002\n");
    if (deleteBooks.size() != 2 ||
        deleteBooks[0].id != 1001 ||
        deleteBooks[1].id != 1003) {
        return fail("Delete Book should remove selected book and keep remaining order");
    }
    if (!containsText(deleteOutput, "Book deleted successfully")) {
        return fail("Delete Book should print success message");
    }

    string missingDeleteOutput = runDeleteBookWithInput(deleteBooks, "9999\n");
    if (deleteBooks.size() != 2 ||
        deleteBooks[0].id != 1001 ||
        deleteBooks[1].id != 1003) {
        return fail("missing Delete Book ID should keep book list unchanged");
    }
    if (!containsText(missingDeleteOutput, "Book not found")) {
        return fail("missing Delete Book ID should print not found message");
    }

    vector<Book> searchBooks = {
        {1001, "Clean Code", "Robert C. Martin", 3},
        {1002, "Code Complete", "Steve McConnell", 2},
        {1003, "The Pragmatic Programmer", "Andrew Hunt", 4},
    };

    string searchByTitleOutput = runSearchBookWithInput(searchBooks, "2\nCode\n");
    if (!containsText(searchByTitleOutput, "Title: Clean Code") ||
        !containsText(searchByTitleOutput, "Title: Code Complete") ||
        containsText(searchByTitleOutput, "Title: The Pragmatic Programmer")) {
        return fail("Search Book by title keyword should print only matching books");
    }

    string searchByIdOutput = runSearchBookWithInput(searchBooks, "1\n1003\n");
    if (!containsText(searchByIdOutput, "ID: 1003") ||
        !containsText(searchByIdOutput, "Title: The Pragmatic Programmer")) {
        return fail("Search Book by ID should print the matching book");
    }

    string searchByAuthorOutput = runSearchBookWithInput(searchBooks, "3\nRobert\n");
    if (!containsText(searchByAuthorOutput, "Author: Robert C. Martin") ||
        containsText(searchByAuthorOutput, "Author: Andrew Hunt")) {
        return fail("Search Book by author keyword should print only matching books");
    }

    string missingSearchOutput = runSearchBookWithInput(searchBooks, "2\nDatabase\n");
    if (!containsText(missingSearchOutput, "No matching books found")) {
        return fail("Search Book with no keyword matches should print not-found message");
    }

    string missingSearchIdOutput = runSearchBookWithInput(searchBooks, "1\n9999\n");
    if (!containsText(missingSearchIdOutput, "Book not found")) {
        return fail("Search Book by missing ID should print not-found message");
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
