#include "library.h"

#include <iostream>
#include <limits>

Reader* getReaderById(vector<Reader>& readers, int id) {
    for (Reader& reader : readers) {
        if (reader.id == id) {
            return &reader;
        }
    }

    return nullptr;
}

void printReader(const Reader& reader) {
    cout << "ID: " << reader.id << endl;
    cout << "Name: " << reader.name << endl;
    cout << "Phone: " << reader.phone << endl;
    cout << "------------------------------" << endl;
}

void addReader(vector<Reader>& readers) {
    Reader reader;

    cout << "Enter reader ID: ";
    if (!(cin >> reader.id)) {
        cout << "Invalid reader ID." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!isPositiveId(reader.id)) {
        cout << "Reader ID must be positive." << endl;
        return;
    }

    if (getReaderById(readers, reader.id) != nullptr) {
        cout << "Reader ID already exists." << endl;
        return;
    }

    cout << "Enter name: ";
    getline(cin, reader.name);
    if (isEmptyText(reader.name)) {
        cout << "Name cannot be empty." << endl;
        return;
    }

    cout << "Enter phone: ";
    getline(cin, reader.phone);
    if (isEmptyText(reader.phone)) {
        cout << "Phone cannot be empty." << endl;
        return;
    }

    readers.push_back(reader);
    cout << "Reader added successfully." << endl;
}

void updateReader(vector<Reader>& readers) {
    int id;

    cout << "Enter reader ID to update: ";
    if (!(cin >> id)) {
        cout << "Invalid reader ID." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Reader* reader = getReaderById(readers, id);
    if (reader == nullptr) {
        cout << "Reader not found." << endl;
        return;
    }

    Reader updatedReader = *reader;

    cout << "Enter new name: ";
    getline(cin, updatedReader.name);
    if (isEmptyText(updatedReader.name)) {
        cout << "Name cannot be empty." << endl;
        return;
    }

    cout << "Enter new phone: ";
    getline(cin, updatedReader.phone);
    if (isEmptyText(updatedReader.phone)) {
        cout << "Phone cannot be empty." << endl;
        return;
    }

    *reader = updatedReader;
    cout << "Reader updated successfully." << endl;
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
