#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../h-files/main.h"

void removeTeams(const team *, team *, const int, const int);
void addTeams(const team *, team *, const int, const int);
void changeStartingTime (team *, const char *, const int, int);
void changeEndingTime (team *, const char *, const int, int);

int main(void) {
  int i = 0;
  int number_of_teams = 17;
  int number_of_new_teams = 4;
  int number_of_removed_teams = 4;
  team all_teams[25];
  team new_teams[4];
  team removed_teams[4];

  all_teams[0].level = 0;
  all_teams[1].level = 0;
  all_teams[2].level = 0;
  all_teams[3].level = 0;
  all_teams[4].level = 0;
  all_teams[5].level = 1;
  all_teams[6].level = 1;
  all_teams[7].level = 1;
  all_teams[8].level = 2;
  all_teams[9].level = 2;
  all_teams[10].level = 2;
  all_teams[11].level = 3;
  all_teams[12].level = 3;
  all_teams[13].level = 3;
  all_teams[14].level = 3;
  all_teams[15].level = 2;
  all_teams[16].level = 2;

  all_teams[0].games = 0;
  all_teams[1].games = 0;
  all_teams[2].games = 0;
  all_teams[3].games = 0;
  all_teams[4].games = 0;
  all_teams[5].games = 0;
  all_teams[6].games = 0;
  all_teams[7].games = 0;
  all_teams[8].games = 0;
  all_teams[9].games = 0;
  all_teams[10].games = 0;
  all_teams[11].games = 0;
  all_teams[12].games = 0;
  all_teams[13].games = 0;
  all_teams[14].games = 0;
  all_teams[15].games = 0;
  all_teams[16].games = 0;

  strcpy(all_teams[0].team, "Hold 1");
  strcpy(all_teams[1].team, "Hold 2");
  strcpy(all_teams[2].team, "Hold 3");
  strcpy(all_teams[3].team, "Hold 4");
  strcpy(all_teams[4].team, "Hold 5");
  strcpy(all_teams[5].team, "Hold 6");
  strcpy(all_teams[6].team, "Hold 7");
  strcpy(all_teams[7].team, "Hold 8");
  strcpy(all_teams[8].team, "Hold 9");
  strcpy(all_teams[9].team, "Hold 10");
  strcpy(all_teams[10].team, "Hold 11");
  strcpy(all_teams[11].team, "Hold 12");
  strcpy(all_teams[12].team, "Hold 13");
  strcpy(all_teams[13].team, "Hold 14");
  strcpy(all_teams[14].team, "Hold 15");
  strcpy(all_teams[15].team, "Hold 16");
  strcpy(all_teams[16].team, "Hold 17");

  strcpy(removed_teams[0].team, "Hold 17");
  strcpy(removed_teams[1].team, "Hold 1");
  strcpy(removed_teams[2].team, "Hold 5");
  strcpy(removed_teams[3].team, "Hold 10");

  strcpy(new_teams[0].team, "Hold 18");
  strcpy(new_teams[1].team, "Hold 19");
  strcpy(new_teams[2].team, "Hold 20");
  strcpy(new_teams[3].team, "Hold 21");
  
  new_teams[0].level = 0;
  new_teams[1].level = 0;
  new_teams[2].level = 0;
  new_teams[3].level = 0;

  removeTeams(removed_teams, all_teams, number_of_removed_teams, number_of_teams);

  for (i = 0; i < number_of_teams; i++) {
    printf("TEAM: %s\nLEVEL: %d\n\n", all_teams[i].team, all_teams[i].level);
  }

  printf("-------------------------\n\n");

  addTeams(new_teams, all_teams, number_of_new_teams, number_of_teams);

  for (i = 0; i < number_of_teams + number_of_new_teams; i++) {
    printf("TEAM: %s\nLEVEL: %d\n\n", all_teams[i].team, all_teams[i].level);
  }

  changeStartingTime(all_teams*, team*, number_of_teams, time);
  
  changeEndingTime(all_teams*, team*, number_of_teams, time);
 
  return 0;
}

/* Fjerner hold fra listen af hold. */
void removeTeams(const team *removed_teams, team *all_teams, const int number_of_removed_teams, const int number_of_teams) {
  int i = 0;
  int j = 0;

  for (i = 0; i < number_of_removed_teams; i++) {
    for (j = 0; j < number_of_teams; j++) {
      if (strcmp(removed_teams[i].team, all_teams[j].team) == 0) {
        all_teams[j].level = 4;
      } 
    }
  }
}

/* Tilføjer hold til listen af hold. */
void addTeams(const team *new_teams, team *all_teams, const int number_of_new_teams, const int number_of_teams) {
  int i = 0;
  int j = 0;

  for (i = 0; i < number_of_teams; i++) {
    if (all_teams[i].level == 4) {
      strcpy(all_teams[i].team, new_teams[j].team);
      all_teams[i].level = new_teams[j].level;
      all_teams[i].games = 0;

      j++;
    }
  }
}

void changeStartingTime (team all_teams*, const char team*, const int number_of_teams, int time) {
  int i = 0;

  for (i = 0; i < number_of_teams; i++) {
    if (strcmp(team, all_teams[i].team) == 0) {
      all_teams[i].starting_time = time;
    }
  }
}

void changeEndingTime (team all_teams*, const char team*, const int number_of_teams, int time) {
  int i = 0;

  for (i = 0; i < number_of_teams; i++) {
    if (strcmp(team, all_teams[i].team) == 0) {
      all_teams[i].ending_time = time;
    }
  }
}






