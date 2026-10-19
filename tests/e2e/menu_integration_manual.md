# Console Menu Integration Manual E2E Test Guide

Manual E2E tests are run by starting the real console program, using the Main
Menu and submenus, entering data, and recording the visible result. These checks
cover the integrated flow across Book, Reader, Borrow / Return, File I/O, and
menu input handling.

Before running these checks:
- Back up `data/books.dat`, `data/readers.dat`, and `data/borrow_records.dat`.
- Run the real program from the project root.
- Restore the original data files after screenshots are captured.
- Use unique IDs in each run to avoid duplicate-ID messages from previous data.

## TC-I01: Add Then Display Book

Steps:
1. Run the program.
2. Choose `Book Management`.
3. Choose `Add Book`.
4. Enter book ID `3101`.
5. Enter title `Menu Integration Book`.
6. Enter author `Student Team`.
7. Enter quantity `5`.
8. Choose `Display Books`.
9. Choose `Back`.
10. Choose `Exit`.

Expected result:
- Program prints `Book added successfully`.
- Display Books shows book ID `3101`, title `Menu Integration Book`, author
  `Student Team`, and quantity `5`.
- Program returns from Book Management to the Main Menu.

## TC-I02: Add Reader Then Borrow Book

Steps:
1. Run the program.
2. Choose `Reader Management`.
3. Choose `Add Reader`.
4. Enter reader ID `4101`.
5. Enter name `Menu Reader One`.
6. Enter phone `0904101001`.
7. Choose `Back`.
8. Choose `Book Management`.
9. Choose `Add Book`.
10. Enter book ID `3102`.
11. Enter title `Borrow Flow Book`.
12. Enter author `Student Team`.
13. Enter quantity `2`.
14. Choose `Back`.
15. Choose `Borrow Book`.
16. Enter reader ID `4101`.
17. Enter book ID `3102`.
18. Choose `Display Data`.
19. Choose `Exit`.

Expected result:
- Program prints `Reader added successfully`.
- Program prints `Book added successfully`.
- Program prints `Book borrowed successfully`.
- Display Data shows reader ID `4101`, book ID `3102`, and a borrow record with
  status `Borrowed`.
- Book ID `3102` quantity decreases from `2` to `1`.

## TC-I03: Borrow Then Return Book

Steps:
1. Run the program.
2. Prepare one reader and one available book through the Main Menu if they do
   not already exist.
3. Choose `Borrow Book`.
4. Enter the prepared reader ID.
5. Enter the prepared book ID.
6. Choose `Return Book`.
7. Enter the same reader ID.
8. Enter the same book ID.
9. Choose `Display Data`.
10. Choose `Exit`.

Expected result:
- Borrow step prints `Book borrowed successfully`.
- Return step prints `Book returned successfully`.
- Display Data shows the matching borrow record with status `Returned`.
- The returned book quantity increases by 1 after the return step.

## TC-I04: Save Then Reload

Steps:
1. Run the program.
2. Add one new book and one new reader through the Main Menu.
3. Choose `Save Data`.
4. Choose `Exit`.
5. Run the program again.
6. Choose `Display Data`.
7. Choose `Exit`.

Expected result:
- Save Data prints `Data saved successfully`.
- After restarting the program, Display Data still shows the book and reader
  added before saving.
- The saved records are present in `data/books.dat`, `data/readers.dat`, and
  `data/borrow_records.dat` when applicable.

## TC-I05: Invalid Menu Choice

Steps:
1. Run the program.
2. At the Main Menu, enter `9`.
3. At the Main Menu, enter `abc`.
4. Choose `Book Management`.
5. Enter `abc`.
6. Choose `Back`.
7. Choose `Reader Management`.
8. Enter `abc`.
9. Choose `Back`.
10. Choose `Exit`.

Expected result:
- Each invalid choice prints `Invalid choice.`.
- The program does not crash or exit unexpectedly.
- After invalid input, the same menu is displayed again and accepts the next
  valid choice.
