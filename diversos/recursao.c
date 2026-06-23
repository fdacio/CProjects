#include <stdio.h>

void print_numbers(int n) {
  if (n <= 0) {
    return; // Base case: stop recursion when n is less than or equal to 0
  }
  
  print_numbers(n - 1); // Recursive call with n decremented by 1
  printf("%d\n", n); // Print the current number
}

int main(void) {
  int n = 5; // Example number to start printing from
  printf("Printing numbers from %d down to 1:\n", n);
  print_numbers(n); // Call the recursive function
  return 0;
}
