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


// ====================
// Book Management
// ====================

Book* getBookById(vector<Book>& books, int id);

const Book* getBookById(const vector<Book>& books, int id);

void printBook(const Book& book);

void addBook(vector<Book>& books);

void updateBook(vector<Book>& books);

void deleteBook(vector<Book>& books);

void searchBook(const vector<Book>& books);

void displayBooks(const vector<Book>& books);

void sortBooks(vector<Book>& books);

// ====================
// Reader Management
// ====================

void printReader(const Reader& reader);

void addReader(vector<Reader>& readers);

void updateReader(vector<Reader>& readers);

void deleteReader(vector<Reader>& readers);

void searchReader(const vector<Reader>& readers);

void displayReaders(const vector<Reader>& readers);

// ====================
// Borrow / Return
// ====================

void borrowBook(
    vector<Book>& books,
    const vector<Reader>& readers,
    vector<BorrowRecord>& records
);

void returnBook(
    vector<Book>& books,
    vector<BorrowRecord>& records
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

void bookMenu(vector<Book>& books);

void readerMenu(vector<Reader>& readers);

void mainMenu(
    vector<Book>& books,
    vector<Reader>& readers,
    vector<BorrowRecord>& records
);


#endif
