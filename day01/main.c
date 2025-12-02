# include <stdlib.h>
# include <stdio.h>
# include <string.h>

int modulo(int x,int N){
    return (x % N + N) %N;
}

int main() {
  FILE *fptr = fopen("input.txt", "r");
  
  int dial = 50;
  int count = 0;

  if (fptr != NULL) {
    char line[100];
    while (fgets(line, sizeof(line), fptr) != NULL) {
      char *number = line+1;
     
      if (line[0] == 'L') {
        dial = modulo(dial-atoi(number), 100);
      }
      else if (line[0] == 'R') {
        dial = modulo(dial+atoi(number), 100);
      }
 
      if (dial == 0) {
        count += 1; 
      }
    }
  }
  
  printf("%d", count);
  
  return 0;
}
