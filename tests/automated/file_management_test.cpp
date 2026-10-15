#include "library.h"

#include <fstream>
#include <iostream>
#include <sstream>

int fail(const string& message) {
    cout << "FAIL: " << message << endl;
    return 1;
}

string readTextFile(const string& filename) {
    ifstream file(filename);
    ostringstream content;
    content << file.rdbuf();
    return content.str();
}

void writeTextFile(const string& filename, const string& content) {
    ofstream file(filename);
    file << content;
}

struct FileBackup {
    string filename;
    string originalContent;

    FileBackup(const string& fileToBackup) {
        filename = fileToBackup;
        originalContent = readTextFile(filename);
    }

    ~FileBackup() {
        writeTextFile(filename, originalContent);
    }
};

void verifyFileManagementFunctionsAreLinked() {
    (void)static_cast<void (*)(const vector<Book>&)>(&saveBooks);
    (void)static_cast<void (*)(vector<Book>&)>(&loadBooks);
}

int main() {
    verifyFileManagementFunctionsAreLinked();

    const string booksFile = "data/books.dat";
    FileBackup booksFileBackup(booksFile);

    vector<Book> books;
    books.push_back({1001, "Clean Code", "Robert C. Martin", 3});
    books.push_back({1002, "Code Complete", "Steve McConnell", 2});

    saveBooks(books);

    string savedBooksFile = readTextFile(booksFile);
    if (savedBooksFile.find("1001|Clean Code|Robert C. Martin|3") == string::npos) {
        return fail("saveBooks should write the first book using the agreed text format");
    }
    if (savedBooksFile.find("1002|Code Complete|Steve McConnell|2") == string::npos) {
        return fail("saveBooks should write the second book using the agreed text format");
    }

    vector<Book> loadedBooks;
    loadBooks(loadedBooks);

    if (loadedBooks.size() != 2) {
        return fail("loadBooks should load two saved books");
    }
    if (loadedBooks[0].id != 1001 ||
        loadedBooks[0].title != "Clean Code" ||
        loadedBooks[0].author != "Robert C. Martin" ||
        loadedBooks[0].quantity != 3) {
        return fail("loadBooks should preserve all fields of the first book");
    }
    if (loadedBooks[1].id != 1002 ||
        loadedBooks[1].title != "Code Complete" ||
        loadedBooks[1].author != "Steve McConnell" ||
        loadedBooks[1].quantity != 2) {
        return fail("loadBooks should preserve all fields of the second book");
    }

    cout << "PASS: file management automated checks" << endl;
    return 0;
}
