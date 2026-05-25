#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 3

typedef struct {
  int id;
  char name[20];
  float marks;
} Student;

// Function prototypes
void saveToFile(const char *filename, Student arr[], int n);
long *createSeekPositions(const char *filename, int n);
void displayRecord(const char *filename, long seekPos);

int main() {
  const char *filename = "students.txt";
  Student students[MAX_RECORDS] = {
      {101, "Alice", 85.5}, {102, "Bob", 90.2}, {103, "Charlie", 78.4}};

  // 1. Store array of structures in ASCII format
  saveToFile(filename, students, MAX_RECORDS);

  // 2. Create an array of seek positions
  long *positions = createSeekPositions(filename, MAX_RECORDS);

  if (positions != NULL) {
    // 3. Display a specific record given its seek position (e.g., index 1 ->
    // Bob)
    printf("Displaying record at index 1:\n");
    displayRecord(filename, positions[1]);

    printf("\nDisplaying record at index 0:\n");
    displayRecord(filename, positions[0]);

    free(positions);
  }

  return 0;
}

// Stores array of structures in ASCII format
void saveToFile(const char *filename, Student arr[], int n) {
  FILE *fp = fopen(filename, "w");
  if (!fp)
    return;

  for (int i = 0; i < n; i++) {
    // Formatted text output ensures ASCII storage
    fprintf(fp, "%d %s %.2f\n", arr[i].id, arr[i].name, arr[i].marks);
  }
  fclose(fp);
}

// Creates an array containing the start position of each record
long *createSeekPositions(const char *filename, int n) {
  FILE *fp = fopen(filename, "r");
  if (!fp)
    return NULL;

  long *positions = (long *)malloc(n * sizeof(long));
  char buffer[100];

  for (int i = 0; i < n; i++) {
    positions[i] =
        ftell(fp); // Record the start position before reading the line
    if (fgets(buffer, sizeof(buffer), fp) == NULL) {
      break;
    }
  }

  fclose(fp);
  return positions;
}

// Displays a single record from the given seek position
void displayRecord(const char *filename, long seekPos) {
  FILE *fp = fopen(filename, "r");
  if (!fp)
    return;

  // Move to the specific record position
  fseek(fp, seekPos, SEEK_SET);

  Student s;
  // Read the ASCII formatted data back into the structure
  if (fscanf(fp, "%d %s %f", &s.id, s.name, &s.marks) == 3) {
    printf("ID: %d, Name: %s, Marks: %.2f\n", s.id, s.name, s.marks);
  }

  fclose(fp);
}