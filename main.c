# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
# include "main.h"

void SortArrayByLevel(team *all_teams, int number_of_teams);
int comp (const void *a, const void *b)
int getNumberOfTeams(FILE *fp);
char *PromptForFileName(void);

int main(void) {

  printf("%Hey!\n");
  return 0;
}

/* Bruger qsort til at sortere arrayet af hold efter niveau */
void SortArrayByLevel(team *all_teams, int number_of_teams) {

  qsort(all_teams, number_of_teams, sizeof(team), comp);
}

/* Sammenligningsfunktion til qsort. Sammenligner to holds niveauer */
int comp (const void *a, const void*b) {
  team *team_a = (team*) a;
  team *team_b = (team*) b;

  return team_a->level - team_b->level;
}

int getNumberOfTeams(FILE *fp) {
  char tmp[MAX_NAME_LEN];
  int number_of_teams = 0, sentinel = 0;

  /* Saetter fil position til starten af filen */
  rewind(fp);

  if (fp == NULL) { /* Check at filen ikke er NULL */
    perror("Error opening file");
    return(-1);
  }

  /* Gennemgå hver linje i en fil.
     Returner antallet af linjer der indeholder andet end whitespace.
     Det antages at disse indeholder et holdnavn */
  while (sentinel == 0) {
    if (fgets(tmp, MAX_NAME_LEN, fp) != NULL) {
      for (int i = 0; i < strlen(tmp); i++) { /* Check om linjen er tom. (Kun whitespace) */
        if (!isspace(tmp[i])) {
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

char *PromptForFileName(void) {
  char *file_name;

  file_name = (char *) calloc(30, sizeof(char));

  printf("Indtast filnavn (afslut med .txt): ");
  scanf(" %s", file_name);

  return file_name;
}
