#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../main.h"

/* Prototypes */
int getNumberOfTeams(FILE *team_names);
/*
int main(void) {
  FILE *fp;

  fp = fopen("holdnavne.txt", "r");
  printf("Number of teams is %d \n", getNumberOfTeams(fp));

  return 0;
}
*/

/* Find og returner antallet af linjer med indhold i en fil.
   Returner -1 Hvis der sker en fejl. */
int getNumberOfTeams(FILE *fp) {
  char tmp[MAX_NAME_LEN];
  int number_of_teams = 0, sentinel = 0;

  /* Saetter fil position til starten af filen */
  rewind(fp);

  if(fp == NULL) { /* Check at filen ikke er NULL */
    perror("Error opening file");
    return(-1);
  }

  /* Gennemgå hver linje i en fil.
     Returner antallet af linjer der indeholder andet end whitespace.
     Det antages at disse indeholder et holdnavn */
  while(sentinel == 0) {
    if(fgets(tmp, MAX_NAME_LEN, fp) != NULL) {
      for(int i = 0; i < strlen(tmp); i++) { /* Check om linjen er tom. (Kun whitespace) */
        if(!isspace(tmp[i])) {
          ++number_of_teams;
          break;
        }
      }
    }
    else {
      sentinel = 1;
    }
  }
  return number_of_teams;
}
