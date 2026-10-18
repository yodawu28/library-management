#include "library.h"

#include <iostream>

void bookMenu(LibraryData& data) {
    (void)data;

    int choice;

    do {
        cout << "========================================" << endl;
        cout << "          BOOK MANAGEMENT" << endl;
        cout << "========================================" << endl;
        cout << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Update Book" << endl;
        cout << "3. Delete Book" << endl;
        cout << "4. Search Book" << endl;
        cout << "5. Display Books" << endl;
        cout << "6. Sort Books" << endl;
        cout << "0. Back" << endl;
        cout << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            return;
        }

        if (choice == 1) {
            addBook(data.books);
        } else if (choice == 2) {
            updateBook(data.books);
        } else if (choice == 3) {
            deleteBook(data);
        } else if (choice == 4) {
            searchBook(data.books);
        } else if (choice == 5) {
            displayBooks(data.books);
        } else if (choice == 6) {
            sortBooks(data.books);
        } else if (choice != 0) {
            cout << "Invalid choice." << endl;
        }
    } while (choice != 0);
}

void readerMenu(LibraryData& data) {
    (void)data;

    int choice;

    do {
        cout << "========================================" << endl;
        cout << "         READER MANAGEMENT" << endl;
        cout << "========================================" << endl;
        cout << endl;
        cout << "1. Add Reader" << endl;
        cout << "2. Update Reader" << endl;
        cout << "3. Delete Reader" << endl;
        cout << "4. Search Reader" << endl;
        cout << "5. Display Readers" << endl;
        cout << "0. Back" << endl;
        cout << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            return;
        }

        if (choice == 1) {
            addReader(data.readers);
        } else if (choice == 2) {
            updateReader(data.readers);
        } else if (choice == 3) {
            deleteReader(data);
        } else if (choice == 4) {
            searchReader(data.readers);
        } else if (choice == 5) {
            displayReaders(data.readers);
        } else if (choice != 0) {
            cout << "Invalid choice." << endl;
        }
    } while (choice != 0);
}

void mainMenu(LibraryData& data) {
    int choice;

    do {
        cout << "========================================" << endl;
        cout << "       LIBRARY MANAGEMENT SYSTEM" << endl;
        cout << "========================================" << endl;
        cout << endl;
        cout << "1. Book Management" << endl;
        cout << "2. Reader Management" << endl;
        cout << "3. Borrow Book" << endl;
        cout << "4. Return Book" << endl;
        cout << "5. Display Data" << endl;
        cout << "6. Save Data" << endl;
        cout << "0. Exit" << endl;
        cout << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            return;
        }

        if (choice == 1) {
            bookMenu(data);
        } else if (choice == 2) {
            readerMenu(data);
        } else if (choice == 3) {
            borrowBook(data);
        } else if (choice == 4) {
            returnBook(data);
        } else if (choice != 0) {
            cout << "This menu option will be implemented in Sprint 6." << endl;
        }
    } while (choice != 0);
}
