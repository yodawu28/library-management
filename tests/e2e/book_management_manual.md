# Book Management Manual E2E Test Guide

Manual E2E tests are run by starting the real console program, selecting menu
items, entering data, and recording the visible result. These are the tests to
use for classroom reporting and screenshots.

## TC-B01: Add Book Successfully

Steps:
1. Run the program.
2. Open `Book Management`.
3. Choose `Add Book`.
4. Enter ID `1001`.
5. Enter title `Clean Code`.
6. Enter author `Robert C. Martin`.
7. Enter quantity `3`.
8. Choose `Display Books`.

Expected result:
- Program prints a success message.
- Display Books shows ID `1001`, title `Clean Code`, author
  `Robert C. Martin`, and quantity `3`.

## TC-B02: Reject Duplicate Book ID

Steps:
1. Add book ID `1001` once.
2. Choose `Add Book` again.
3. Enter ID `1001`.

Expected result:
- Program prints a duplicate ID error.
- The book list does not contain a second book with ID `1001`.

## TC-B03: Reject Empty Title

Steps:
1. Choose `Add Book`.
2. Enter a new positive ID.
3. Leave title empty.

Expected result:
- Program prints an invalid title message.
- No new book is added.

## TC-B04: Reject Negative Quantity

Steps:
1. Choose `Add Book`.
2. Enter a new positive ID, a valid title, and a valid author.
3. Enter quantity `-1`.

Expected result:
- Program prints an invalid quantity message.
- No new book is added.

## TC-B05: Update Book Successfully

Steps:
1. Add a valid book.
2. Choose `Update Book`.
3. Enter the existing book ID.
4. Enter a new title, author, and quantity.
5. Choose `Display Books`.

Expected result:
- Program prints a success message.
- Display Books shows the updated title, author, and quantity.

## TC-B06: Reject Missing Book ID During Update

Steps:
1. Choose `Update Book`.
2. Enter an ID that does not exist.

Expected result:
- Program prints a not-found message.
- Existing books remain unchanged.
