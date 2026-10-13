#include "library.h"

#include <iostream>
#include <sstream>

int fail(const string& message) {
    cout << "FAIL: " << message << endl;
    return 1;
}

bool containsText(const string& text, const string& keyword) {
    return text.find(keyword) != string::npos;
}

string capturePrintReaderOutput(const Reader& reader) {
    ostringstream output;
    streambuf* originalOutput = cout.rdbuf(output.rdbuf());

    printReader(reader);

    cout.rdbuf(originalOutput);
    return output.str();
}

string captureDisplayReadersOutput(const vector<Reader>& readers) {
    ostringstream output;
    streambuf* originalOutput = cout.rdbuf(output.rdbuf());

    displayReaders(readers);

    cout.rdbuf(originalOutput);
    return output.str();
}

void verifyReaderManagementFunctionsAreLinked() {
    (void)static_cast<void (*)(const Reader&)>(&printReader);
    (void)static_cast<void (*)(const vector<Reader>&)>(&displayReaders);
}

int main() {
    verifyReaderManagementFunctionsAreLinked();

    Reader reader = {2001, "Nguyen Van An", "0901234567"};
    string printOutput = capturePrintReaderOutput(reader);
    if (!containsText(printOutput, "ID: 2001") ||
        !containsText(printOutput, "Name: Nguyen Van An") ||
        !containsText(printOutput, "Phone: 0901234567")) {
        return fail("printReader should print all reader fields");
    }

    vector<Reader> emptyReaders;
    string emptyOutput = captureDisplayReadersOutput(emptyReaders);
    if (!containsText(emptyOutput, "No readers available")) {
        return fail("Display Readers should print empty-list message");
    }

    vector<Reader> readers = {
        {2001, "Nguyen Van An", "0901234567"},
        {2002, "Tran Thi Binh", "0902222333"},
    };

    string listOutput = captureDisplayReadersOutput(readers);
    if (!containsText(listOutput, "Reader List") ||
        !containsText(listOutput, "ID: 2001") ||
        !containsText(listOutput, "Name: Nguyen Van An") ||
        !containsText(listOutput, "Phone: 0901234567") ||
        !containsText(listOutput, "ID: 2002") ||
        !containsText(listOutput, "Name: Tran Thi Binh") ||
        !containsText(listOutput, "Phone: 0902222333")) {
        return fail("Display Readers should print all reader fields");
    }

    cout << "PASS: reader management automated checks" << endl;
    return 0;
}
