# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "../main.h"

match *scanFileForTeams (match *all_teams, int *number_of_teams, int number_of_new_teams);
void get_number_of_matches (FILE *fp, int *number_of_teams);
int doesTeamExist (char *temp_team, team * all_teams, int i);


int main(void) {
  int number_of_teams = 0, number_of_new_teams = 20;
  match *all_teams = NULL;

  scanFileForTeams(all_matches, &number_of_teams);

  for (int i = 0; i < number_of_teams; i++) {
    printf("%s | %c\n", all_teams[i].team, all_matches[i].level);
  }

  return 0;
}

match *scanFileForTeams (match *all_teams, int *number_of_teams, int number_of_new_teams) {
  int scanres = 0, dump = 0, i = 0;
  match temp[200], temp_team_a[MAX_NAME_LEN], temp_team_b[MAX_NAME_LEN];
  char temp_level;
  FILE *fp = fopen ("turneringsplan.txt", "r");

  /* Checker om filen blev åbnet */
  if (fP == NULL) {
     perror("Error opening file");
     return -1;
  }

  get_number_of_teams(fp, *number_of_matches);
  *number_of_teams += number_of_new_teams;

  all_teams = (team*) malloc (*number_of_teams * sizeof (team));

  while (!feof(pf)) {
    scanres = fsnanf (fp, " %[-A-Za-z0-9| ]", temp);
    if (scanres != 1) {
      printf("Fejl i scanning af fil\n");
    }
    if (strlen > 15) {
      sscanf (temp, " Bane %d | %c | %[A-Za-z0-9 ] vs %[A-Za-z0-9 ] ", dump, temp_level, temp_team_a, temp_team_b);
      if (doesTeamExist(temp_team_a, all_matches, i) == 0) {
        strcpy(all_teams[i].team, temp_team_a);
        i++;
      }
      if (doesTeamExist(temp_team_b, all_matches, i) == 0) {
        strcpy(all_teams[i].team, temp_team_b);
        i++;
      }
    }
  }
  close (fp);

  return all_teams;
}


void get_number_of_matches (FILE *fp, int *number_of_teams) {
  char *dump_string[200];
  int dump_int = 0;
  char dump_char;
  int scanres = 0, number_of_matches = 0;

  while (!feof(fp)) {
    scanres = fscanf (fp, " Bane %d | %c | %[A-Za-z0-9 ] vs %[A-Za-z0-9 ] ", dump_int, dump_char, dump_string, dump_string);
    if (scanres == 4) {
      *number_of_matches++;
    }
  }
  *number_of_teams = (number_of_matches - 1) / 3;
}

int doesTeamExist (char *temp_team, team * all_teams, int i) {
  int j = 0, exists = 0;

  for (j = 0; j < i && exists == 0; j++) {
    if (strcmp(temp_team, all_teams[j].team) == 0) {
      exists++;
    }
  }
  return exists;
}
