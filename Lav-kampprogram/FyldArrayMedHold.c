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

  /* Fylder alle teams med nul-tegn,
     sætter alle niveauer til EMPTY
     og antallet af spillede kampe til 0 */
  for (int k = 0; k < num_of_teams; k++) {
    all_teams[k].level = EMPTY;
    all_teams[k].games = 0;
    for (int j = 0; j < MAX_NAME_LEN; j++) {
      all_teams[k].team[j] = '\0';
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

    fscanf(fP, " %[abcdefghijklmnopqrstuvwxyzæøåABCDEFGHIJKLMNOPQRSTUVWXYZÆØÅ0123456789 ]" " %c" " %c", all_teams[i].team, &dump, &level);

    /* Sætter niveauet til stort */
    level = toupper(level);

    all_teams[i].level = (level == 'N') ? N :
                         (level == 'A') ? A :
                         (level == 'B') ? B :
                         (level == 'C') ? C : EMPTY;
  }

  fclose(fP);
  return 0;
}
