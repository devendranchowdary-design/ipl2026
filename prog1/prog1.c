#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "records.dat"
#define TEMP_FILE "temp.dat"

typedef struct {
  int id;
  char name[30];
  float gpa;
} Record;

// Function Prototypes
void storeRecords(int n);
void displayMthRecord(int m);
void deleteRecord(int idToDelete);
void displayAllRecords(); // Helper to verify results

int main() {
  // 1. Store 3 initial records
  printf("--- Storing Records ---\n");
  storeRecords(3);
  displayAllRecords();

  // 2. Read the 2nd record (Index 1, if 0-indexed)
  printf("\n--- Fetching 2nd Record (Index 1) using fseek ---\n");
  displayMthRecord(1);

  // 3. Delete a record by ID
  printf("\n--- Deleting Record with ID 102 ---\n");
  deleteRecord(102);
  displayAllRecords();

  return 0;
}

// Store N records into a binary file
void storeRecords(int n) {
  FILE *file = fopen(FILE_NAME, "wb");
  if (!file) {
    perror("Error opening file for writing");
    return;
  }

  Record data[] = {
      {101, "Alice", 3.8}, {102, "Bob", 3.5}, {103, "Charlie", 3.9}};

  // Ensure we don't overflow the hardcoded array sample size
  int count = (n > 3) ? 3 : n;
  fwrite(data, sizeof(Record), count, file);
  fclose(file);
  printf("Stored %d records successfully.\n", count);
}

// Fetch and display the m-th record using fseek (0-indexed)
void displayMthRecord(int m) {
  FILE *file = fopen(FILE_NAME, "rb");
  if (!file) {
    perror("Error opening file for reading");
    return;
  }

  Record r;
  // Move the file pointer to the m-th record
  if (fseek(file, m * sizeof(Record), SEEK_SET) == 0) {
    if (fread(&r, sizeof(Record), 1, file) == 1) {
      printf("Record %d -> ID: %d, Name: %s, GPA: %.2f\n", m, r.id, r.name,
             r.gpa);
    } else {
      printf("Record at index %d does not exist.\n", m);
    }
  } else {
    printf("Error seeking to position.\n");
  }

  fclose(file);
}

// Delete a record by ID using the temporary file shift method
void deleteRecord(int idToDelete) {
  FILE *file = fopen(FILE_NAME, "rb");
  FILE *tempFile = fopen(TEMP_FILE, "wb");

  if (!file || !tempFile) {
    perror("Error opening files during deletion");
    if (file)
      fclose(file);
    if (tempFile)
      fclose(tempFile);
    return;
  }

  Record r;
  int found = 0;

  // Read all records; copy over only those that don't match the ID
  while (fread(&r, sizeof(Record), 1, file) == 1) {
    if (r.id == idToDelete) {
      found = 1; // Skip writing this record
    } else {
      fwrite(&r, sizeof(Record), 1, tempFile);
    }
  }

  fclose(file);
  fclose(tempFile);

  if (found) {
    remove(FILE_NAME);            // Delete old file
    rename(TEMP_FILE, FILE_NAME); // Rename temp to original
    printf("Record with ID %d deleted successfully.\n", idToDelete);
  } else {
    remove(TEMP_FILE); // Clean up temp file
    printf("Record with ID %d not found.\n", idToDelete);
  }
}

// Helper function to print the current state of the file
void displayAllRecords() {
  FILE *file = fopen(FILE_NAME, "rb");
  if (!file)
    return;

  Record r;
  printf("\nCurrent File Content:\n");
  while (fread(&r, sizeof(Record), 1, file) == 1) {
    printf("ID: %d | Name: %s | GPA: %.2f\n", r.id, r.name, r.gpa);
  }
  fclose(file);
}
