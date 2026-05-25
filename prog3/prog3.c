#include <stdio.h>

// 1. Prints the binary representation of an integer (32-bit)
void printBits(int n) {
  // Start with the Most Significant Bit (MSB)
  for (int i = 31; i >= 0; i--) {
    int bit = (n >> i) & 1;
    printf("%d", bit);

    // Add a space every 4 bits for better readability
    if (i % 4 == 0)
      printf(" ");
  }
  printf("\n");
}

// 2. Counts the number of 1 bits using Brian Kernighan's Algorithm
int countOneBits(int n) {
  int count = 0;
  while (n) {
    n &= (n - 1); // Clears the lowest set (1) bit
    count++;
  }
  return count;
}

int main() {
  int num = 45; // Binary: 0000...00101101 (Five 1s)

  printf("Integer: %d\n", num);
  printf("Binary:  ");
  printBits(num);

  printf("Number of 1 bits: %d\n", countOneBits(num));

  return 0;
}