#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getLargestPossibleJoltage(char *bank) {
  int bankLength = strlen(bank);
  char firstLargestJoltage = bank[0];
  int firstJoltagePosition = 0;

  for (int bankIndex = 0; bankIndex < bankLength - 1; bankIndex++) {
    if (bank[bankIndex] - firstLargestJoltage > 0) {
      firstLargestJoltage = bank[bankIndex];
      firstJoltagePosition = bankIndex;
    }
  }

  char secondLargestJoltage = bank[firstJoltagePosition + 1];
  for (int bankIndex = firstJoltagePosition + 1; bankIndex < bankLength;
       bankIndex++) {
    if (bank[bankIndex] - secondLargestJoltage > 0) {
      secondLargestJoltage = bank[bankIndex];
    }
  }

  char joltage[3];
  sprintf(joltage, "%c%c", firstLargestJoltage, secondLargestJoltage);

  return atoi(joltage);
}

int main(int argc, char *argv[]) {
  FILE *input;
  input = fopen(argv[1], "r");

  char bank[102];
  int totalOutputJoltage = 0;

  while (fgets(bank, sizeof(bank), input)) {
    bank[strcspn(bank, "\n")] = 0;
    totalOutputJoltage += getLargestPossibleJoltage(bank);
  }

  fclose(input);

  printf("Total Joltage: %d\n", totalOutputJoltage);
}
