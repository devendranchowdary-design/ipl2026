#include <stdio.h>

// Define the structure with bit-fields
struct Bitfield {
  unsigned int firstbit : 1; // 1 bit (stores 0 or 1)
  unsigned int nextbits : 3; // 3 bits (stores 0 to 7)
  unsigned int padding : 4;  // 4 bits padding
};

int main() {
  // Initialize the structure
  struct Bitfield a;

  // Assign values
  a.firstbit = 1;
  a.nextbits = 5;

  // Test and print values
  printf("a.firstbit: %u\n", a.firstbit);
  printf("a.nextbits: %u\n", a.nextbits);
  printf("Size of structure: %lu byte(s)\n", sizeof(a));

  return 0;
}