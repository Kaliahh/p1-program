/*# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <math.h>

char *PromptForFileName(void);

int main(void) {

  char *file_name;

  file_name = (char *) calloc(30, sizeof(char));

  strcpy(file_name, PromptForFileName());

  printf("fil navn: %s\n", file_name);

  return 0;
}*/

char *PromptForFileName(void){
  char *file_name;

  file_name = (char *) calloc(30, sizeof(char));

  printf("Indtast filnavn (afslut med .txt): ");
  scanf(" %s", file_name);

  return file_name;
}
