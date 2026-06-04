#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isInvalid(char *id) {
  int length = strlen(id);
  int halfLength = length / 2;

  for (int i = halfLength; i > 0; i--) {
    if (length % i == 0) {
      int comparisonCount = (length / i) - 1;
      int invalid = 0;
      while (comparisonCount > 0) {
        int comparison = strncmp(id + (i * (comparisonCount - 1)),
                                 id + (i * comparisonCount), i);
        invalid += abs(comparison);
        comparisonCount -= 1;
      }

      if (invalid == 0) {
        return 1;
      }
    }
  }

  return 0;
}

long long checkRange(char *lower, char *upper) {
  long long total = 0ll;
  for (long long i = atoll(lower); i <= atoll(upper); i++) {
    char strnum[16];
    sprintf(strnum, "%lld", i);
    if (isInvalid(strnum)) {
      total += i;
    }
  }
  return total;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
    return 1;
  }

  FILE *fptr;
  fptr = fopen(argv[1], "r");
  if (fptr == NULL) {
    fprintf(stderr, "Error: could not open %s\n", argv[1]);
    return 1;
  }

  char input[1000];
  fgets(input, 1000, fptr);

  long long total = 0;

  char id1[16] = "";
  char id2[16] = "";
  int hitDash = 0;
  for (int i = 0; input[i]; i++) {
    if (input[i] == '-') {
      hitDash = 1;
    } else if (input[i] == ',') {
      total += checkRange(id1, id2);
      hitDash = 0;
      id1[0] = '\0';
      id2[0] = '\0';
    } else if (hitDash) {
      strncat(id2, &input[i], 1);
    } else {
      strncat(id1, &input[i], 1);
    }
  }
  // Check last range which is missed as no trailing comma.
  total += checkRange(id1, id2);

  fclose(fptr);

  printf("Total: %lld\n", total);

  return 0;
}
