# Borrow / Return Manual E2E Test Guide

Manual E2E tests are run by starting the real console program, selecting menu
items, entering data, and recording the visible result. These are the tests to
use for classroom reporting and screenshots.

Before running these checks, prepare simple test data through the real program:
- Add reader ID `2001` with name `Nguyen Van An`.
- Add reader ID `2002` with name `Tran Thi Binh`.
- Add book ID `1001` with title `Clean Code` and quantity `2`.
- Add book ID `1002` with title `Code Complete` and quantity `0`.

## TC-BR01: Borrow Book Successfully

Steps:
1. Run the program.
2. Choose `Borrow Book`.
3. Enter reader ID `2001`.
4. Enter book ID `1001`.
5. Choose a display option that shows books or borrow records.

Expected result:
- Program prints a success message.
- Book ID `1001` quantity decreases by 1.
- A borrow record is created with reader ID `2001`, book ID `1001`, and status
  `BORROWED`.

## TC-BR02: Reject Missing Reader During Borrow

Steps:
1. Choose `Borrow Book`.
2. Enter reader ID `9999`.

Expected result:
- Program prints a reader-not-found message.
- No borrow record is created.
- Book quantities remain unchanged.

## TC-BR03: Reject Missing Book During Borrow

Steps:
1. Choose `Borrow Book`.
2. Enter reader ID `2001`.
3. Enter book ID `9999`.

Expected result:
- Program prints a book-not-found message.
- No borrow record is created.
- Existing book quantities remain unchanged.

## TC-BR04: Reject Unavailable Book During Borrow

Steps:
1. Confirm book ID `1002` has quantity `0`.
2. Choose `Borrow Book`.
3. Enter reader ID `2001`.
4. Enter book ID `1002`.

Expected result:
- Program prints an unavailable-book message.
- No borrow record is created.
- Book ID `1002` quantity remains `0`.

## TC-BR05: Reject Duplicate Active Borrow

Steps:
1. Borrow book ID `1001` with reader ID `2001`.
2. Choose `Borrow Book` again.
3. Enter reader ID `2001`.
4. Enter book ID `1001`.

Expected result:
- Program prints a duplicate-borrow message.
- No second active borrow record is created for the same reader and book.
- Book ID `1001` quantity is not decreased by the rejected request.

## TC-RT01: Return Book Successfully

Steps:
1. Borrow book ID `1001` with reader ID `2001`.
2. Choose `Return Book`.
3. Enter reader ID `2001`.
4. Enter book ID `1001`.
5. Choose a display option that shows books or borrow records.

Expected result:
- Program prints a success message.
- The matching borrow record status changes to `RETURNED`.
- Book ID `1001` quantity increases by 1.

## TC-RT02: Reject Return Without Matching Record

Steps:
1. Choose `Return Book`.
2. Enter reader ID `2002`.
3. Enter book ID `1001`.

Expected result:
- Program prints a borrow-record-not-found message.
- No borrow record is created or changed.
- Book quantities remain unchanged.

## TC-RT03: Reject Already Returned Record

Steps:
1. Borrow book ID `1001` with reader ID `2001`.
2. Return book ID `1001` with reader ID `2001`.
3. Choose `Return Book` again.
4. Enter reader ID `2001`.
5. Enter book ID `1001`.

Expected result:
- Program prints an already-returned message.
- The borrow record remains `RETURNED`.
- Book ID `1001` quantity is not increased by the rejected request.
