# Final Manual Regression Evidence Checklist

Purpose: this document maps each manual E2E guide to the final demo evidence
needed for the course report. Automated checks remain internal verification;
the final report evidence should come from running the real console program.

## Evidence Rules

- Run the real program from the project root.
- Use the manual guides under `tests/e2e/`.
- Capture screenshots or terminal output for the visible result.
- Record final actual results in this document during S7.3, S7.4, and S7.5.
- Back up and restore `data/books.dat`, `data/readers.dat`, and
  `data/borrow_records.dat` when a manual test changes persisted data.

## Book Management

Guide: `tests/e2e/book_management_manual.md`

Required final evidence:
- TC-B01: Add Book successfully.
- TC-B02: Reject duplicate Book ID.
- TC-B03: Reject empty title.
- TC-B04: Reject negative quantity.
- TC-B05: Update Book successfully.
- TC-B06: Reject missing Book ID during update.
- TC-B07: Delete Book successfully.
- TC-B09: Search Book by title keyword.
- TC-B10: Sort Books by title.

S7.3 manual run path: real console program from the project root, Main Menu
`1. Book Management`, with no Save Data step.

Actual results:
- TC-B01: Add Book printed `Book added successfully.`; Display Books showed
  ID `1001`, title `Clean Code`, author `Robert C. Martin`, quantity `3`.
- TC-B02: Adding ID `1001` again printed `Book ID already exists.` and did
  not ask for duplicate title/author/quantity data.
- TC-B03: Adding a new ID with an empty title printed
  `Title cannot be empty.` and returned to Book Management.
- TC-B04: Adding a valid title/author with quantity `-1` printed
  `Quantity cannot be negative.` and returned to Book Management.
- TC-B05: Updating ID `1001` printed `Book updated successfully.`; later
  Display Books showed title `Clean Code Updated`, author
  `Robert C. Martin`, quantity `5`.
- TC-B06: Updating missing ID `9999` printed `Book not found.`.
- TC-B07: Deleting ID `1004` printed `Book deleted successfully.`; later
  Display Books no longer showed `Zebra Book` and still showed the remaining
  books.
- TC-B09: Search by title keyword `Code` displayed only ID `1001` with title
  `Clean Code Updated` from the current run.
- TC-B10: Sort by title printed `Books sorted successfully.` and displayed
  `Algorithms` before `Clean Code Updated`.

Final status: Completed in S7.3 manual run.

## Reader Management

Guide: `tests/e2e/reader_management_manual.md`

Required final evidence:
- TC-R01: Add Reader successfully.
- TC-R02: Reject duplicate Reader ID.
- TC-R03: Reject empty Reader name.
- TC-R04: Update Reader successfully.
- TC-R05: Reject missing Reader ID during update.
- TC-R06: Delete Reader successfully.
- TC-R07: Delete Reader with active borrow record.
- TC-R08: Search Reader by name keyword.

S7.3 manual run path: real console program from the project root, Main Menu
`2. Reader Management`; TC-R07 additionally used Main Menu `3. Borrow Book`
to create an active borrow record before attempting deletion.

Actual results:
- TC-R01: Add Reader printed `Reader added successfully.`; Display Readers
  showed ID `2001`, name `Nguyen Van An`, phone `0901234567`.
- TC-R02: Adding ID `2001` again printed `Reader ID already exists.` and did
  not create a duplicate reader.
- TC-R03: Adding a new ID with an empty name printed
  `Name cannot be empty.` and returned to Reader Management.
- TC-R04: Updating ID `2001` printed `Reader updated successfully.`; later
  Display Readers showed name `Nguyen Van An Updated`, phone `0909999999`.
- TC-R05: Updating missing ID `9999` printed `Reader not found.`.
- TC-R06: Deleting ID `2003` printed `Reader deleted successfully.`; later
  Display Readers no longer showed `Tran Thi Binh`.
- TC-R07: After borrowing book ID `1010` for reader ID `2010`, deleting
  reader ID `2010` printed `Reader is currently borrowing books.`.
- TC-R08: Search by name keyword `Nguyen` displayed only ID `2001` with name
  `Nguyen Van An Updated` from the current run.

Final status: Completed in S7.3 manual run.

## Borrow / Return

Guide: `tests/e2e/borrow_return_manual.md`

Required final evidence:
- TC-BR01: Borrow Book successfully.
- TC-BR02: Reject missing reader during borrow.
- TC-BR03: Reject missing book during borrow.
- TC-BR04: Reject unavailable book during borrow.
- TC-BR05: Reject duplicate active borrow.
- TC-RT01: Return Book successfully.
- TC-RT02: Reject return without matching record.
- TC-RT03: Reject already returned record.

Final status: Pending S7.4 manual run.

## File I/O

Guide: `tests/e2e/file_management_manual.md`

Required final evidence:
- TC-F01: Save Books.
- TC-F02: Load Books.
- TC-F03: Save Readers.
- TC-F04: Load Readers.
- TC-F05: Save Borrow Records.
- TC-F06: Load Borrow Records.
- Malformed Data Check: malformed lines are skipped and valid lines still load.

Final status: Pending S7.4 manual run.

## Menu Integration

Guide: `tests/e2e/menu_integration_manual.md`

Required final evidence:
- TC-I01: Add then display book.
- TC-I02: Add reader then borrow book.
- TC-I03: Borrow then return book.
- TC-I04: Save then reload.
- TC-I05: Invalid menu choice.

Final status: Pending S7.5 manual run.

## Final Handoff Checklist

- [x] Book Management final evidence recorded.
- [x] Reader Management final evidence recorded.
- [ ] Borrow / Return final evidence recorded.
- [ ] File I/O final evidence recorded.
- [ ] Menu Integration final evidence recorded.
- [ ] `./scripts/verify.sh` passed after final evidence updates.
