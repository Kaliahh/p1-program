# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "../h-files/main.h"

match *scanFileForMatches (FILE *fp, const int number_of_matches);
int getNumberOfMatches (FILE *fp);
void sgetTeams(match* all_matches, char* teams, const int index);

int main(void) {
  int number_of_matches = 0, i = 0;
  match *all_matches = NULL;

  FILE *fp = fopen ("turneringsplan.txt", "r");

  /* Checker om filen blev åbnet */
  if (fp == NULL) {
     perror("Error opening file");
     return -1;
  }

  number_of_matches = getNumberOfMatches(fp);
  all_matches = scanFileForMatches(fp, number_of_matches);

  for (i = 0; i < number_of_matches; i++) {
    printf("%20s vs %-22s | %c\n", all_matches[i].team_a, all_matches[i].team_b, all_matches[i].level);
  }

  fclose (fp);
  free(all_matches);

  return 0;
}

/* Laver et array med et givent antal matches, indsætter kampe fra en given fil. */
match *scanFileForMatches (FILE *fp, const int number_of_matches) {
  int scanres = 0, i = 0;
  char temp[200];
  char temp_teams[200];
  char level;

  match *all_matches = (match*) malloc(number_of_matches * sizeof (match));

  rewind(fp); /* Gå til starten af filen */

  while (fgets(temp, 200, fp) != NULL) {   /* Gennemgår hele filen */
    if (strlen(temp) > MIN_LINE_LEN) {     /* Hvis har en bestemt størrelse, må den indeholde en kamp */
      scanres = sscanf(temp, " Bane %*d | %c | %[a-zA-Z0-9æøåÆØÅ ] ", &level, temp_teams);
      if(scanres != 2) {
        perror("Error scanning matches");
      }
      all_matches[i].level = (enum levels) level; /* typecast til levels (int), og put den i struct */
      sgetTeams(all_matches, temp_teams, i);
      i++;
    }
  }

  return all_matches;
}

/* Tæller og returnerer antallet af kampe i en given fil */
int getNumberOfMatches (FILE *fp) {
  char dump[5];
  int number_of_matches = 0;

  rewind(fp); /* Gå til starten af filen */

  while (fgets (dump, 5, fp) != NULL) { /* Læser indtil der ikke er mere at læse (EOF) */
    if (strcmp(dump, "Bane") == 0) {    /* Hvis der står "bane" betyder det at der er en kamp på linjen */
      number_of_matches += 1;
    }
  }
  /* For testing purposes
  printf("%d matches\n", number_of_matches);
  */
  return number_of_matches;
}

void sgetTeams(match* all_matches, char* teams, const int index) {
  int SENTINEL = 0;
  int length = strlen(teams), i = 0;
  while(SENTINEL == 0) {
    if(teams[i] == 'v') {   /* Hvis der er et 'v' */
      if(teams[i-1] == ' ' && teams[i+1] == 's' && teams[i+2] == ' ') {  /* Check om det er en del af " vs " */
        strncpy(all_matches[index].team_a, teams, i - 1); /* Kopier første team navn, uden sidste mellemrum */
        strncpy(all_matches[index].team_b, teams + (i + 3), length - (i+2)); /* Kopier det andet team navn */
        SENTINEL = 1;
      }
    }
    i++;
  }
}
