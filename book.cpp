#include "library.h"

#include <iostream>
#include <limits>
#include <utility>

Book* getBookById(vector<Book>& books, int id) {
    for (Book& book : books) {
        if (book.id == id) {
            return &book;
        }
    }

    return nullptr;
}

const Book* getBookById(const vector<Book>& books, int id) {
    for (const Book& book : books) {
        if (book.id == id) {
            return &book;
        }
    }

    return nullptr;
}

void printBook(const Book& book) {
    cout << "ID: " << book.id << endl;
    cout << "Title: " << book.title << endl;
    cout << "Author: " << book.author << endl;
    cout << "Quantity: " << book.quantity << endl;
    cout << "------------------------------" << endl;
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

    if (getBookById(books, book.id) != nullptr) {
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

    Book* book = getBookById(books, id);
    if (book == nullptr) {
        cout << "Book not found." << endl;
        return;
    }

    Book updatedBook = *book;

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

    *book = updatedBook;
    cout << "Book updated successfully." << endl;
}

void deleteBook(vector<Book>& books) {
    int id;

    cout << "Enter book ID to delete: ";
    if (!(cin >> id)) {
        cout << "Invalid book ID." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (vector<Book>::size_type i = 0; i < books.size(); i++) {
        if (books[i].id == id) {
            books.erase(books.begin() + i);
            cout << "Book deleted successfully." << endl;
            return;
        }
    }

    cout << "Book not found." << endl;
}

void searchBook(const vector<Book>& books) {
    int choice;

    cout << "Search Book" << endl;
    cout << "1. Search by ID" << endl;
    cout << "2. Search by Title" << endl;
    cout << "3. Search by Author" << endl;
    cout << "Enter your choice: ";

    if (!(cin >> choice)) {
        cout << "Invalid search choice." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 1) {
        int id;

        cout << "Enter book ID: ";
        if (!(cin >> id)) {
            cout << "Invalid book ID." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        const Book* book = getBookById(books, id);
        if (book == nullptr) {
            cout << "Book not found." << endl;
            return;
        }

        printBook(*book);
        return;
    }

    if (choice == 2 || choice == 3) {
        string keyword;
        bool found = false;

        if (choice == 2) {
            cout << "Enter title keyword: ";
        } else {
            cout << "Enter author keyword: ";
        }

        getline(cin, keyword);
        if (keyword.empty()) {
            cout << "Keyword cannot be empty." << endl;
            return;
        }

        for (const Book& book : books) {
            bool matchesTitle = choice == 2 && book.title.find(keyword) != string::npos;
            bool matchesAuthor = choice == 3 && book.author.find(keyword) != string::npos;

            if (matchesTitle || matchesAuthor) {
                printBook(book);
                found = true;
            }
        }

        if (!found) {
            cout << "No matching books found." << endl;
        }

        return;
    }

    cout << "Invalid search choice." << endl;
}

void displayBooks(const vector<Book>& books) {
    if (books.empty()) {
        cout << "No books available." << endl;
        return;
    }

    cout << "Book List" << endl;
    cout << "------------------------------" << endl;

    for (const Book& book : books) {
        printBook(book);
    }
}

void sortBooks(vector<Book>& books) {
    int choice;

    cout << "Sort Books" << endl;
    cout << "1. Sort by ID" << endl;
    cout << "2. Sort by Title" << endl;
    cout << "3. Sort by Quantity" << endl;
    cout << "Enter your choice: ";

    if (!(cin >> choice)) {
        cout << "Invalid sort choice." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice < 1 || choice > 3) {
        cout << "Invalid sort choice." << endl;
        return;
    }

    for (vector<Book>::size_type i = 0; i < books.size(); i++) {
        for (vector<Book>::size_type j = i + 1; j < books.size(); j++) {
            bool shouldSwap = false;

            if (choice == 1 && books[i].id > books[j].id) {
                shouldSwap = true;
            } else if (choice == 2 && books[i].title > books[j].title) {
                shouldSwap = true;
            } else if (choice == 3 && books[i].quantity > books[j].quantity) {
                shouldSwap = true;
            }

            if (shouldSwap) {
                swap(books[i], books[j]);
            }
        }
    }

    cout << "Books sorted successfully." << endl;
    displayBooks(books);
}
