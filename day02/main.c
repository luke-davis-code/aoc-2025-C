# include <stdlib.h>
# include <stdio.h>
# include <string.h>

int isValid(char *id) {
  int len = strlen(id);
  if (len % 2) {
    return 0;
  }

  int halflen = len / 2;
  char half1[halflen+1];
  char half2[halflen+1];

  strncpy(half1, id, halflen);
  half1[halflen] = '\0';
  strncpy(half2, id+halflen, halflen);
  half2[halflen] = '\0';
  
  if (strcmp(half1, half2) == 0) {
    return 1;
  }

  return 0;
}

long long checkRange(char *lower, char *upper) {
  long long total = 0ll;
  for (long long i = atoll(lower); i <= atoll(upper); i++) {
    char strnum[16];
    sprintf(strnum, "%lld", i);
    if (isValid(strnum)) {
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
  for(int i=0; input[i]; i++){
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
