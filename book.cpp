#include "library.h"

#include <iostream>
#include <limits>

static bool bookIdExists(const vector<Book>& books, int id) {
    for (const Book& book : books) {
        if (book.id == id) {
            return true;
        }
    }

    return false;
}

void addBook(vector<Book>& books) {
    Book book;

    cout << "Enter book ID: ";
    if (!(cin >> book.id)) {
        cout << "Invalid book ID." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (book.id <= 0) {
        cout << "Book ID must be positive." << endl;
        return;
    }

    if (bookIdExists(books, book.id)) {
        cout << "Book ID already exists." << endl;
        return;
    }

    cout << "Enter title: ";
    getline(cin, book.title);
    if (book.title.empty()) {
        cout << "Title cannot be empty." << endl;
        return;
    }

    cout << "Enter author: ";
    getline(cin, book.author);
    if (book.author.empty()) {
        cout << "Author cannot be empty." << endl;
        return;
    }

    cout << "Enter quantity: ";
    if (!(cin >> book.quantity)) {
        cout << "Invalid quantity." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (book.quantity < 0) {
        cout << "Quantity cannot be negative." << endl;
        return;
    }

    books.push_back(book);
    cout << "Book added successfully." << endl;
}

void updateBook(vector<Book>& books) {
    int id;

    cout << "Enter book ID to update: ";
    if (!(cin >> id)) {
        cout << "Invalid book ID." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (Book& book : books) {
        if (book.id == id) {
            Book updatedBook = book;

            cout << "Enter new title: ";
            getline(cin, updatedBook.title);
            if (updatedBook.title.empty()) {
                cout << "Title cannot be empty." << endl;
                return;
            }

            cout << "Enter new author: ";
            getline(cin, updatedBook.author);
            if (updatedBook.author.empty()) {
                cout << "Author cannot be empty." << endl;
                return;
            }

            cout << "Enter new quantity: ";
            if (!(cin >> updatedBook.quantity)) {
                cout << "Invalid quantity." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return;
            }

            if (updatedBook.quantity < 0) {
                cout << "Quantity cannot be negative." << endl;
                return;
            }

            book = updatedBook;
            cout << "Book updated successfully." << endl;
            return;
        }
    }

    cout << "Book not found." << endl;
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
