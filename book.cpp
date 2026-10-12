#include "library.h"

#include <iostream>

void addBook(vector<Book>& books) {
    (void)books;
}

void updateBook(vector<Book>& books) {
    (void)books;
}

void deleteBook(vector<Book>& books) {
    (void)books;
}

void searchBook(const vector<Book>& books) {
    (void)books;
}

void displayBooks(const vector<Book>& books) {
    if (books.empty()) {
        cout << "No books available." << endl;
        return;
    }

    cout << "Book List" << endl;
    cout << "------------------------------" << endl;

    for (const Book& book : books) {
        cout << "ID: " << book.id << endl;
        cout << "Title: " << book.title << endl;
        cout << "Author: " << book.author << endl;
        cout << "Quantity: " << book.quantity << endl;
        cout << "------------------------------" << endl;
    }
}

void sortBooks(vector<Book>& books) {
    (void)books;
}
