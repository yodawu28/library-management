#include "library.h"

#include <iostream>

void printReader(const Reader& reader) {
    cout << "ID: " << reader.id << endl;
    cout << "Name: " << reader.name << endl;
    cout << "Phone: " << reader.phone << endl;
    cout << "------------------------------" << endl;
}

void displayReaders(const vector<Reader>& readers) {
    if (readers.empty()) {
        cout << "No readers available." << endl;
        return;
    }

    cout << "Reader List" << endl;
    cout << "------------------------------" << endl;

    for (const Reader& reader : readers) {
        printReader(reader);
    }
}
