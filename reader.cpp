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

bool hasActiveBorrowForReader(const vector<BorrowRecord>& records, int readerId) {
    for (const BorrowRecord& record : records) {
        if (record.readerId == readerId && record.status == BORROWED) {
            return true;
        }
    }

    return false;
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

void deleteReader(LibraryData& data) {
    int id;

    cout << "Enter reader ID to delete: ";
    if (!(cin >> id)) {
        cout << "Invalid reader ID." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (hasActiveBorrowForReader(data.borrowRecords, id)) {
        cout << "Reader is currently borrowing books." << endl;
        return;
    }

    for (vector<Reader>::size_type i = 0; i < data.readers.size(); i++) {
        if (data.readers[i].id == id) {
            data.readers.erase(data.readers.begin() + i);
            cout << "Reader deleted successfully." << endl;
            return;
        }
    }

    cout << "Reader not found." << endl;
}

void searchReader(const vector<Reader>& readers) {
    int choice;

    cout << "Search Reader" << endl;
    cout << "1. Search by ID" << endl;
    cout << "2. Search by Name" << endl;
    cout << "3. Search by Phone" << endl;
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

        cout << "Enter reader ID: ";
        if (!(cin >> id)) {
            cout << "Invalid reader ID." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        for (const Reader& reader : readers) {
            if (reader.id == id) {
                printReader(reader);
                return;
            }
        }

        cout << "Reader not found." << endl;
        return;
    }

    if (choice == 2 || choice == 3) {
        string keyword;
        bool found = false;

        if (choice == 2) {
            cout << "Enter name keyword: ";
        } else {
            cout << "Enter phone: ";
        }

        getline(cin, keyword);
        if (isEmptyText(keyword)) {
            cout << "Keyword cannot be empty." << endl;
            return;
        }

        for (const Reader& reader : readers) {
            bool matchesName = choice == 2 && reader.name.find(keyword) != string::npos;
            bool matchesPhone = choice == 3 && reader.phone.find(keyword) != string::npos;

            if (matchesName || matchesPhone) {
                printReader(reader);
                found = true;
            }
        }

        if (!found) {
            cout << "No matching readers found." << endl;
        }

        return;
    }

    cout << "Invalid search choice." << endl;
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
