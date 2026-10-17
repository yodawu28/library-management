#include "library.h"

#ifndef LIBRARY_MANAGEMENT_TEST
int main() {
    LibraryData data;

    loadBooks(data.books);
    loadReaders(data.readers);
    loadBorrowRecords(data.borrowRecords);

    mainMenu(data);
    return 0;
}
#endif
