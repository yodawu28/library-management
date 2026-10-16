#include "library.h"

#include <fstream>

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

        book.id = stoi(idText);
        book.quantity = stoi(quantityText);

        books.push_back(book);
    }
}
