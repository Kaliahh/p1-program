# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "../h-files/main.h"

team *scanFileForTeams (FILE *fp, int number_of_teams, const int number_of_new_teams);
int getNumberOfTeams (FILE *fp);
int doesTeamExist (team temp_team, team * all_teams, const int index);
int getNumberOfMatches (FILE *fp);
void sgetTeams(match* all_matches, char* teams);


int main(void) {
  int number_of_teams = 0, number_of_new_teams = 20;
  team *all_teams = NULL;

  FILE *fp = fopen ("turneringsplan.txt", "r");

  /* Checker om filen blev åbnet */
  if (fp == NULL) {
     perror("Error opening file");
     return -1;
  }

  number_of_teams = getNumberOfTeams(fp);
  printf("%d teams\n", number_of_teams);
  all_teams = scanFileForTeams(fp, number_of_teams, number_of_new_teams);

  for (int i = 0; i < number_of_teams; i++) {
    printf("%s | %c\n", all_teams[i].team, all_teams[i].level);
  }

  fclose(fp);
  free(all_teams);
  return 0;
}

team *scanFileForTeams (FILE *fp, int number_of_teams, const int number_of_new_teams) {
  int scanres = 0, i = 0;
  char temp[200];
  char temp_teams[200];
  match temp_match;
  team temp_team_a, temp_team_b;
  char level;

  rewind(fp);

  number_of_teams += number_of_new_teams;

  team *all_teams = (team*) malloc (number_of_teams * sizeof(team));

  while (fgets(temp, 200, fp) != NULL) {
  /*  scanres = fscanf (fp, " %[-A-Za-z0-9| ]", temp);
    if (scanres != 1) {
      printf("Fejl i scanning af fil\n");
    } */
    if (strlen(temp) > MIN_LINE_LEN) {     /* Hvis har en bestemt størrelse, må den indeholde en kamp */
      scanres = sscanf(temp, " Bane %*d | %c | %[a-zA-Z0-9æøåÆØÅ ] ", &level, temp_teams);
      if(scanres != 2) {
        perror("Error scanning matches");
      }
      temp_match.level = (enum levels) level; /* typecast til levels (int), og put den i struct */
      sgetTeams(&temp_match, temp_teams);
      /* Kopier data */
      strcpy(temp_team_a.team, temp_match.team_a.team);
      temp_team_a.level = temp_match.level;
      strcpy(temp_team_b.team, temp_match.team_b.team);
      temp_team_b.level = temp_match.level;

      /* Indsæt hold, hvis de ikke er der allerede */
      if (doesTeamExist(temp_team_a, all_teams, i) == 0) {
        strcpy(all_teams[i].team, temp_team_a.team);
        all_teams[i].level = temp_team_a.level;
        i++;
      }
      if (doesTeamExist(temp_team_b, all_teams, i) == 0) {
        strcpy(all_teams[i].team, temp_team_b.team);
        all_teams[i].level = temp_team_b.level;
        i++;
      }
    }
  }

  return all_teams;
}
/* Læser og returnerer antallet af hold i en given fil */
int getNumberOfTeams (FILE *fp) {
  int number_of_matches;
  number_of_matches = getNumberOfMatches(fp);
  /* Tidligere: (number_of_matches - 1) / 3
     Nu: */
  return number_of_matches / 3; /* Forklar udregningen */
}

/* Chekker om et givent team allerede er indsat i et givent array */
int doesTeamExist (team temp_team, team *all_teams, const int index) {
  int j = 0, exists = 0;
  for (j = 0; j < index && exists == 0; j++) {
    if (strcmp(temp_team.team, all_teams[j].team) == 0) {
      exists++;
    }
  }
  return exists;
}

/* Kopi af funktion -- skal muligvis slettes */
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

/* */
void sgetTeams(match* match, char* teams) {
  int SENTINEL = 0;
  int length = strlen(teams), i = 0;
  while(SENTINEL == 0) {
    if(teams[i] == 'v') {   /* Hvis der er et 'v' */
      if(teams[i-1] == ' ' && teams[i+1] == 's' && teams[i+2] == ' ') {  /* Check om det er en del af " vs " */
        strncpy((*match).team_a.team, teams, i - 1); /* Kopier første team navn, uden sidste mellemrum */
        (*match).team_a.team[i - 1] = '\0';  /* Definer enden af strengen */
        strncpy((*match).team_b.team, teams + (i + 3), length - (i+2)); /* Kopier det andet team navn */
        (*match).team_b.team[length - (i+1)] = '\0';  /* Definer enden af strengen */
        SENTINEL = 1;
      }
    }
    i++;
  }
}
