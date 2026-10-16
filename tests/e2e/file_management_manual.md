# File Management Manual E2E Test Guide

Manual E2E tests are run by preparing the project data files, running the real
program or the File Management verification check, and recording the visible
file contents or load result. These checks support classroom reporting and
screenshots for the File I/O module.

Before running these checks:
- Back up `data/books.dat`, `data/readers.dat`, and `data/borrow_records.dat`.
- Restore the original files after screenshots are captured.
- Use `|` as the field separator because titles, names, and phone text may
  contain spaces or commas.

## TC-F01: Save Books

Steps:
1. Prepare a book list with book ID `1001`, title `Clean Code`, author
   `Robert C. Martin`, and quantity `3`.
2. Run the save books function through the program flow or File Management
   check.
3. Open `data/books.dat`.

Expected result:
- `data/books.dat` contains a line like
  `1001|Clean Code|Robert C. Martin|3`.
- The title and author are kept as full text.

## TC-F02: Load Books

Steps:
1. Write this line into `data/books.dat`:
   `1002|Code Complete|Steve McConnell|2`.
2. Run the load books function through the program flow or File Management
   check.
3. Display or inspect the loaded book list.

Expected result:
- The program loads book ID `1002`.
- The title is `Code Complete`.
- The author is `Steve McConnell`.
- The quantity is `2`.

## TC-F03: Save Readers

Steps:
1. Prepare a reader list with reader ID `2001`, name `Nguyen Van An`, and phone
   `090 123 4567`.
2. Run the save readers function through the program flow or File Management
   check.
3. Open `data/readers.dat`.

Expected result:
- `data/readers.dat` contains a line like
  `2001|Nguyen Van An|090 123 4567`.
- The name and phone text are kept as full text.

## TC-F04: Load Readers

Steps:
1. Write this line into `data/readers.dat`:
   `2002|Tran Thi B, QA|+84 98 765 4321`.
2. Run the load readers function through the program flow or File Management
   check.
3. Display or inspect the loaded reader list.

Expected result:
- The program loads reader ID `2002`.
- The name is `Tran Thi B, QA`.
- The phone is `+84 98 765 4321`.
- The comma in the name does not break the file format.

## TC-F05: Save Borrow Records

Steps:
1. Prepare a borrow record list with book ID `1001`, reader ID `2001`, and
   status `BORROWED`.
2. Run the save borrow records function through the program flow or File
   Management check.
3. Open `data/borrow_records.dat`.

Expected result:
- `data/borrow_records.dat` contains a line like `1001|2001|1`.
- Status `1` represents `BORROWED`.

## TC-F06: Load Borrow Records

Steps:
1. Write these lines into `data/borrow_records.dat`:
   - `1001|2001|1`
   - `1002|2002|0`
2. Run the load borrow records function through the program flow or File
   Management check.
3. Display or inspect the loaded borrow record list.

Expected result:
- The program loads one `BORROWED` record with book ID `1001` and reader ID
  `2001`.
- The program loads one `RETURNED` record with book ID `1002` and reader ID
  `2002`.
- Status `1` is treated as `BORROWED`.
- Status `0` is treated as `RETURNED`.

## Malformed Data Check

Steps:
1. Add one malformed line and one valid line into each data file.
2. Run the related load function.
3. Inspect the loaded list.

Expected result:
- Malformed lines are skipped.
- Valid lines in the same file are still loaded.
- The program does not crash.
