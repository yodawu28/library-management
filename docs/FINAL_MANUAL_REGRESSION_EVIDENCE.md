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

Final status: Pending S7.3 manual run.

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

Final status: Pending S7.3 manual run.

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

- [ ] Book Management final evidence recorded.
- [ ] Reader Management final evidence recorded.
- [ ] Borrow / Return final evidence recorded.
- [ ] File I/O final evidence recorded.
- [ ] Menu Integration final evidence recorded.
- [ ] `./scripts/verify.sh` passed after final evidence updates.
