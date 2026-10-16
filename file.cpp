#include "library.h"

#include <fstream>
#include <sstream>

bool readInteger(const string& text, int& number) {
    istringstream stream(text);
    char extra;

    if (!(stream >> number)) {
        return false;
    }

    if (stream >> extra) {
        return false;
    }

    return true;
}

void saveBooks(const vector<Book>& books) {
    ofstream file("data/books.dat");
    if (!file) {
        return;
    }

    for (const Book& book : books) {
        file << book.id << "|"
             << book.title << "|"
             << book.author << "|"
             << book.quantity << endl;
    }
}

void loadBooks(vector<Book>& books) {
    ifstream file("data/books.dat");
    if (!file) {
        return;
    }

    books.clear();

    string line;
    while (getline(file, line)) {
        Book book;
        string idText;
        string quantityText;

        size_t firstSeparator = line.find('|');
        size_t secondSeparator = line.find('|', firstSeparator + 1);
        size_t thirdSeparator = line.find('|', secondSeparator + 1);

        if (firstSeparator == string::npos ||
            secondSeparator == string::npos ||
            thirdSeparator == string::npos) {
            continue;
        }

        idText = line.substr(0, firstSeparator);
        book.title = line.substr(firstSeparator + 1, secondSeparator - firstSeparator - 1);
        book.author = line.substr(secondSeparator + 1, thirdSeparator - secondSeparator - 1);
        quantityText = line.substr(thirdSeparator + 1);

        if (!readInteger(idText, book.id) ||
            !readInteger(quantityText, book.quantity)) {
            continue;
        }

        if (!isPositiveId(book.id) ||
            isEmptyText(book.title) ||
            isEmptyText(book.author) ||
            !isNonNegativeNumber(book.quantity)) {
            continue;
        }

        books.push_back(book);
    }
}

void saveReaders(const vector<Reader>& readers) {
    ofstream file("data/readers.dat");
    if (!file) {
        return;
    }

    for (const Reader& reader : readers) {
        file << reader.id << "|"
             << reader.name << "|"
             << reader.phone << endl;
    }
}

void loadReaders(vector<Reader>& readers) {
    ifstream file("data/readers.dat");
    if (!file) {
        return;
    }

    readers.clear();

    string line;
    while (getline(file, line)) {
        Reader reader;
        string idText;

        size_t firstSeparator = line.find('|');
        size_t secondSeparator = line.find('|', firstSeparator + 1);

        if (firstSeparator == string::npos ||
            secondSeparator == string::npos) {
            continue;
        }

        idText = line.substr(0, firstSeparator);
        reader.name = line.substr(firstSeparator + 1, secondSeparator - firstSeparator - 1);
        reader.phone = line.substr(secondSeparator + 1);

        if (!readInteger(idText, reader.id)) {
            continue;
        }

        if (!isPositiveId(reader.id) ||
            isEmptyText(reader.name) ||
            isEmptyText(reader.phone)) {
            continue;
        }

        readers.push_back(reader);
    }
}

void saveBorrowRecords(const vector<BorrowRecord>& records) {
    ofstream file("data/borrow_records.dat");
    if (!file) {
        return;
    }

    for (const BorrowRecord& record : records) {
        file << record.bookId << "|"
             << record.readerId << "|"
             << record.status << endl;
    }
}

void loadBorrowRecords(vector<BorrowRecord>& records) {
    ifstream file("data/borrow_records.dat");
    if (!file) {
        return;
    }

    records.clear();

    string line;
    while (getline(file, line)) {
        BorrowRecord record;
        string bookIdText;
        string readerIdText;
        string statusText;

        size_t firstSeparator = line.find('|');
        size_t secondSeparator = line.find('|', firstSeparator + 1);

        if (firstSeparator == string::npos ||
            secondSeparator == string::npos) {
            continue;
        }

        bookIdText = line.substr(0, firstSeparator);
        readerIdText = line.substr(firstSeparator + 1, secondSeparator - firstSeparator - 1);
        statusText = line.substr(secondSeparator + 1);

        if (!readInteger(bookIdText, record.bookId) ||
            !readInteger(readerIdText, record.readerId) ||
            !readInteger(statusText, record.status)) {
            continue;
        }

        if (record.status != BORROWED && record.status != RETURNED) {
            continue;
        }

        if (!isPositiveId(record.bookId) ||
            !isPositiveId(record.readerId)) {
            continue;
        }

        records.push_back(record);
    }
}
