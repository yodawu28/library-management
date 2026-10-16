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
    (void)static_cast<void (*)(const vector<Reader>&)>(&saveReaders);
    (void)static_cast<void (*)(vector<Reader>&)>(&loadReaders);
    (void)static_cast<void (*)(const vector<BorrowRecord>&)>(&saveBorrowRecords);
    (void)static_cast<void (*)(vector<BorrowRecord>&)>(&loadBorrowRecords);
}

int main() {
    verifyFileManagementFunctionsAreLinked();

    const string booksFile = "data/books.dat";
    FileBackup booksFileBackup(booksFile);
    const string readersFile = "data/readers.dat";
    FileBackup readersFileBackup(readersFile);
    const string borrowRecordsFile = "data/borrow_records.dat";
    FileBackup borrowRecordsFileBackup(borrowRecordsFile);

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

    vector<Reader> readers;
    readers.push_back({2001, "Nguyen Van An", "090 123 4567"});
    readers.push_back({2002, "Tran Thi B, QA", "+84 98 765 4321"});

    saveReaders(readers);

    string savedReadersFile = readTextFile(readersFile);
    if (savedReadersFile.find("2001|Nguyen Van An|090 123 4567") == string::npos) {
        return fail("saveReaders should write the first reader using the agreed text format");
    }
    if (savedReadersFile.find("2002|Tran Thi B, QA|+84 98 765 4321") == string::npos) {
        return fail("saveReaders should write the second reader using the agreed text format");
    }

    vector<Reader> loadedReaders;
    loadReaders(loadedReaders);

    if (loadedReaders.size() != 2) {
        return fail("loadReaders should load two saved readers");
    }
    if (loadedReaders[0].id != 2001 ||
        loadedReaders[0].name != "Nguyen Van An" ||
        loadedReaders[0].phone != "090 123 4567") {
        return fail("loadReaders should preserve all fields of the first reader");
    }
    if (loadedReaders[1].id != 2002 ||
        loadedReaders[1].name != "Tran Thi B, QA" ||
        loadedReaders[1].phone != "+84 98 765 4321") {
        return fail("loadReaders should preserve all fields of the second reader");
    }

    vector<BorrowRecord> records;
    records.push_back({1001, 2001, BORROWED});
    records.push_back({1002, 2002, RETURNED});

    saveBorrowRecords(records);

    string savedBorrowRecordsFile = readTextFile(borrowRecordsFile);
    if (savedBorrowRecordsFile.find("1001|2001|1") == string::npos) {
        return fail("saveBorrowRecords should write the borrowed record using the agreed text format");
    }
    if (savedBorrowRecordsFile.find("1002|2002|0") == string::npos) {
        return fail("saveBorrowRecords should write the returned record using the agreed text format");
    }

    vector<BorrowRecord> loadedRecords;
    loadBorrowRecords(loadedRecords);

    if (loadedRecords.size() != 2) {
        return fail("loadBorrowRecords should load two saved borrow records");
    }
    if (loadedRecords[0].bookId != 1001 ||
        loadedRecords[0].readerId != 2001 ||
        loadedRecords[0].status != BORROWED) {
        return fail("loadBorrowRecords should preserve all fields of the borrowed record");
    }
    if (loadedRecords[1].bookId != 1002 ||
        loadedRecords[1].readerId != 2002 ||
        loadedRecords[1].status != RETURNED) {
        return fail("loadBorrowRecords should preserve all fields of the returned record");
    }

    cout << "PASS: file management automated checks" << endl;
    return 0;
}
