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

string runAddReaderWithInput(vector<Reader>& readers, const string& input) {
    istringstream inputStream(input);
    ostringstream output;
    streambuf* originalInput = cin.rdbuf(inputStream.rdbuf());
    streambuf* originalOutput = cout.rdbuf(output.rdbuf());

    addReader(readers);

    cin.rdbuf(originalInput);
    cout.rdbuf(originalOutput);
    return output.str();
}

void verifyReaderManagementFunctionsAreLinked() {
    (void)static_cast<bool (*)(int)>(&isPositiveId);
    (void)static_cast<bool (*)(const string&)>(&isEmptyText);
    (void)static_cast<void (*)(const Reader&)>(&printReader);
    (void)static_cast<void (*)(vector<Reader>&)>(&addReader);
    (void)static_cast<void (*)(const vector<Reader>&)>(&displayReaders);
}

int main() {
    verifyReaderManagementFunctionsAreLinked();

    if (!isPositiveId(1) || isPositiveId(0) || isPositiveId(-1)) {
        return fail("isPositiveId should accept only positive IDs");
    }
    if (!isEmptyText("") || isEmptyText("Nguyen Van An")) {
        return fail("isEmptyText should detect only empty text");
    }

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

    vector<Reader> addedReaders;
    string addOutput = runAddReaderWithInput(
        addedReaders,
        "2001\n"
        "Nguyen Van An\n"
        "0901234567\n"
    );

    if (addedReaders.size() != 1) {
        return fail("valid Add Reader should insert one reader");
    }
    if (addedReaders[0].id != 2001 ||
        addedReaders[0].name != "Nguyen Van An" ||
        addedReaders[0].phone != "0901234567") {
        return fail("valid Add Reader should store all reader fields");
    }
    if (!containsText(addOutput, "Reader added successfully")) {
        return fail("valid Add Reader should print success message");
    }

    string duplicateOutput = runAddReaderWithInput(addedReaders, "2001\n");
    if (addedReaders.size() != 1) {
        return fail("duplicate Add Reader should not insert a reader");
    }
    if (!containsText(duplicateOutput, "Reader ID already exists")) {
        return fail("duplicate Add Reader should print duplicate ID message");
    }

    vector<Reader> invalidReaders;
    string nonPositiveIdOutput = runAddReaderWithInput(
        invalidReaders,
        "0\n"
        "Invalid Reader\n"
        "0900000000\n"
    );
    if (!invalidReaders.empty()) {
        return fail("non-positive Reader ID should not insert a reader");
    }
    if (!containsText(nonPositiveIdOutput, "Reader ID must be positive")) {
        return fail("non-positive Reader ID should print validation message");
    }

    string emptyNameOutput = runAddReaderWithInput(
        invalidReaders,
        "2002\n"
        "\n"
        "0900000000\n"
    );
    if (!invalidReaders.empty()) {
        return fail("empty reader name should not insert a reader");
    }
    if (!containsText(emptyNameOutput, "Name cannot be empty")) {
        return fail("empty reader name should print validation message");
    }

    string emptyPhoneOutput = runAddReaderWithInput(
        invalidReaders,
        "2003\n"
        "Tran Thi Binh\n"
        "\n"
    );
    if (!invalidReaders.empty()) {
        return fail("empty reader phone should not insert a reader");
    }
    if (!containsText(emptyPhoneOutput, "Phone cannot be empty")) {
        return fail("empty reader phone should print validation message");
    }

    cout << "PASS: reader management automated checks" << endl;
    return 0;
}
