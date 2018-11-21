/* Fyld et array med hold fra en fil */

# include "../main.h"
# include <stdio.h>
# include <string.h>
# include <ctype.h>

int fillArray(team *, const char *, int);

int main(void) {

  team all_teams[40];
  char file_name[30] = "holdnavne.txt";
  int num_of_teams = 9;

  fillArray(all_teams, file_name, num_of_teams);

  return 0;
}

int fillArray (team *all_teams, const char *file_name, int num_of_teams) {

  FILE * fP;
  char dump = ' ', level = ' ';

  /* Fylder alle teams med nul-tegn, og sætter alle niveauer til EMPTY */
  for (int i = 0; i < num_of_teams; i++) {
    all_teams[i].level = EMPTY;
    for (int j = 0; j < MAX_NAME_LEN; j++) {
      all_teams[i].team[j] = '\0';
    }
  }

  /* Åbner tekstfilen med holdnavne */
  fP = fopen(file_name, "r");

  /* Checker om filen blev åbnet */
  if (fP == NULL) {
     perror("Error opening file");
     return -1;
  }

  /* Gennemgår filen med holdnavne, og kopierer holdnavn og niveau over på de rigtige pladser i et array af structs */
  for (int i = 0; i < num_of_teams; i++) {
    /* Checker om filpointeren er kommet til slutningen af filen,
       og stopper hvis det er sandt */
    if (feof(fP)) {
      printf("EOF\nMulig fejl\n");
      break;
    }

    /* Test af output */
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n");

    fscanf(fP, " %[abcdefghijklmnopqrstuvwxyzæøåABCDEFGHIJKLMNOPQRSTUVWXYZÆØÅ0123456789 ]" " %c" " %c", all_teams[i].team, &dump, &level);

    all_teams[i].level = (level == 'N') ? N :
                         (level == 'A') ? A :
                         (level == 'B') ? B :
                         (level == 'C') ? C : EMPTY;

    /* Test af output */
    printf("Team : %s\n", all_teams[i].team);
    printf("Level: %d\n", all_teams[i].level);
  }

  fclose(fP);
  return 0;
}
