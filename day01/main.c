# include <stdlib.h>
# include <stdio.h>
# include <string.h>

int modulo(int x,int N){
    return (x % N + N) %N;
}

int main() {
  FILE *fptr = fopen("input.txt", "r");
  
  int dial = 50;
  int password = 0;
  int i;

  if (fptr != NULL) {
    char line[100];
    while (fgets(line, sizeof(line), fptr) != NULL) {
      char direction = line[0];
      int distance = atoi(line+1);

      for (i = 0; i < distance; i++) {
        dial = direction == 'L' ? modulo(dial-1, 100) : modulo(dial+1, 100);
        if (dial == 0) {
          password += 1;
        }
      }
    }
  }
  
  printf("%d", password);
  
  return 0;
}
