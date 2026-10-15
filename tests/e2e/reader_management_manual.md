# Reader Management Manual E2E Test Guide

Manual E2E tests are run by starting the real console program, selecting menu
items, entering data, and recording the visible result. These are the tests to
use for classroom reporting and screenshots.

## TC-R01: Add Reader Successfully

Steps:
1. Run the program.
2. Open `Reader Management`.
3. Choose `Add Reader`.
4. Enter ID `2001`.
5. Enter name `Nguyen Van An`.
6. Enter phone `0901234567`.
7. Choose `Display Readers`.

Expected result:
- Program prints a success message.
- Display Readers shows ID `2001`, name `Nguyen Van An`, and phone
  `0901234567`.

## TC-R02: Reject Duplicate Reader ID

Steps:
1. Add reader ID `2001` once.
2. Choose `Add Reader` again.
3. Enter ID `2001`.

Expected result:
- Program prints a duplicate ID error.
- The reader list does not contain a second reader with ID `2001`.

## TC-R03: Reject Empty Reader Name

Steps:
1. Choose `Add Reader`.
2. Enter a new positive ID.
3. Leave name empty.

Expected result:
- Program prints an invalid name message.
- No new reader is added.

Additional manual check:
- Enter a valid name but leave phone empty and confirm no new reader is added.

## TC-R04: Update Reader Successfully

Steps:
1. Add a valid reader.
2. Choose `Update Reader`.
3. Enter the existing reader ID.
4. Enter a new name.
5. Enter a new phone.
6. Choose `Display Readers`.

Expected result:
- Program prints a success message.
- Display Readers shows the updated name and phone for the selected reader.
- Other readers remain unchanged.

## TC-R05: Reject Missing Reader ID During Update

Steps:
1. Choose `Update Reader`.
2. Enter an ID that does not exist.

Expected result:
- Program prints a not-found message.
- Existing readers remain unchanged.

Additional manual checks:
- Try updating with an empty new name and confirm the original reader data is
  unchanged.
- Try updating with an empty new phone and confirm the original reader data is
  unchanged.

## TC-R06: Delete Reader Successfully

Steps:
1. Add at least two valid readers.
2. Choose `Delete Reader`.
3. Enter the ID of one existing reader.
4. Choose `Display Readers`.

Expected result:
- Program prints a success message.
- The deleted reader no longer appears in Display Readers.
- Other readers remain visible in their original order.

Additional manual check:
- Enter an ID that does not exist and confirm the reader list is unchanged.

## TC-R07: Delete Reader With Active Borrow Record

Status:
- Covered by the Sprint 4 focused module check.

Reason:
- `deleteReader` now receives `LibraryData&` so it can inspect active
  `BorrowRecord` data before deleting a reader.

Expected result:
- Program rejects deleting a reader who still has an active borrowed book.
- Reader data remains unchanged.

## TC-R08: Search Reader By Name Keyword

Steps:
1. Add at least three valid readers with different names and phone numbers.
2. Choose `Search Reader`.
3. Choose search by name.
4. Enter a keyword that appears in one or more reader names.

Expected result:
- Program displays every reader whose name contains the keyword.
- Readers that do not match the keyword are not displayed.

Additional manual checks:
- Search by an existing ID and confirm the correct reader appears.
- Search by a phone keyword and confirm matching readers appear.
- Search using a keyword that does not exist and confirm a not-found message
  appears.
- Enter an invalid search choice and confirm a validation message appears.
- Leave the search keyword empty and confirm a validation message appears.
