/* Scanner en fil for antallet af linjer, og derfor antallet af hold */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../main.h"

/* Prototyper */
int getNumberOfTeams(FILE *team_names);

int main(void) {
  FILE *fp;

  fp = fopen("holdnavne.txt", "r");
  printf("Number of teams is %d \n", getNumberOfTeams(fp));

  return 0;
}


/* Find og returner antallet af linjer med indhold i en fil.
   Returner -1 Hvis der sker en fejl. */
int getNumberOfTeams(FILE *fp) {
  char tmp[MAX_NAME_LEN];
  int number_of_teams = 0, has_content = 0, SENTINEL = 0;

  /* Saetter fil position til starten af filen */
  rewind(fp);

  if(fp == NULL) { /* Check at filen ikke er NULL */
    perror("Error opening file");
    return(-1);
  }

  /* Gennemgå hver linje i en fil.
     Returner antallet af linjer der indeholder andet end whitespace.
     Det antages at disse indeholder et holdnavn */
  while(SENTINEL == 0) {
    if(fgets(tmp, MAX_NAME_LEN, fp) != NULL) {
      has_content = 0;
      for(int i = 0; i < strlen(tmp); i++) { /* Check om linjen er tom. (Kun whitespace) */
        if(!isspace(tmp[i]) && !has_content) {
          has_content = 1;
        }
      }
      if(has_content) { /* Forstør antallet hvis der er indhold på linjen */
        number_of_teams++;
      }
    }
    else {
      SENTINEL = 1;
    }
  }
  return number_of_teams - 1;
}
