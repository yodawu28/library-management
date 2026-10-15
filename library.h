#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>

using namespace std;

const int BORROWED = 1;
const int RETURNED = 0;

struct Book {
    int id;
    string title;
    string author;
    int quantity;
};


struct Reader {
    int id;
    string name;
    string phone;
};

struct BorrowRecord {
    int bookId;
    int readerId;
    int status;
};

struct LibraryData {
    vector<Book> books;
    vector<Reader> readers;
    vector<BorrowRecord> borrowRecords;
};

// ====================
// Validation Helpers
// ====================

bool isPositiveId(int id);

bool isNonNegativeNumber(int number);

bool isEmptyText(const string& text);


// ====================
// Book Management
// ====================

Book* getBookById(vector<Book>& books, int id);

bool hasActiveBorrowForBook(const vector<BorrowRecord>& records, int bookId);

void printBook(const Book& book);

void addBook(vector<Book>& books);

void updateBook(vector<Book>& books);

void deleteBook(LibraryData& data);

void searchBook(vector<Book>& books);

void displayBooks(const vector<Book>& books);

void sortBooks(vector<Book>& books);

// ====================
// Reader Management
// ====================

Reader* getReaderById(vector<Reader>& readers, int id);

bool hasActiveBorrowForReader(const vector<BorrowRecord>& records, int readerId);

void printReader(const Reader& reader);

void addReader(vector<Reader>& readers);

void updateReader(vector<Reader>& readers);

void deleteReader(LibraryData& data);

void searchReader(const vector<Reader>& readers);

void displayReaders(const vector<Reader>& readers);

// ====================
// Borrow / Return
// ====================

BorrowRecord* getActiveBorrowRecord(
    vector<BorrowRecord>& records,
    int readerId,
    int bookId
);

void borrowBook(
    LibraryData& data
);

void returnBook(
    LibraryData& data
);

// ====================
// File I/O
// ====================

void saveBooks(const vector<Book>& books);

void loadBooks(vector<Book>& books);

void saveReaders(const vector<Reader>& readers);

void loadReaders(vector<Reader>& readers);

void saveBorrowRecords(
    const vector<BorrowRecord>& records
);

void loadBorrowRecords(
    vector<BorrowRecord>& records
);

// ====================
// Menu
// ====================

void bookMenu(LibraryData& data);

void readerMenu(LibraryData& data);

void mainMenu(
    LibraryData& data
);


#endif
