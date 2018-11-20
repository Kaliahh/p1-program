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

/* Find and return the number of lines with content from a given file.
   Returns -1 if an error is encounterd */
int getNumberOfTeams(FILE *fp) {
  char tmp[MAX_NAME_LEN];
  int number_of_teams = 0, sentinel = 0;

  /* Check that file is not NULL */
  if(fp == NULL) {
    printf("An error occured when opening the file\n");
    return(-1);
  }

  /* Go through every character and find the number of newlines. */
  while(sentinel == 0) {
    if(fgets(tmp, MAX_NAME_LEN, fp) != NULL) {
      for(int i = 0; i < strlen(tmp); i++) { /* Check if the string is empty. (Only whitespace) */
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
