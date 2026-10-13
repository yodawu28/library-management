#include "library.h"

bool isPositiveId(int id) {
    return id > 0;
}

bool isNonNegativeNumber(int number) {
    return number >= 0;
}

bool isEmptyText(const string& text) {
    return text.empty();
}
