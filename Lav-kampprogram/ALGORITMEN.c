/* Funktioner til at sammensætte hold i kampe, og kampe i runder */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
# include "../main.h"

void createMatches (team *, match *, int );
int createMatchesByLevel (team *, match *, int , int );

int main(void) {
  int i = 0, number_of_teams = 11;
  team all_teams[11];
  match *all_matches;

  all_teams[0].level = 0;
  all_teams[1].level = 0;
  all_teams[2].level = 0;
  all_teams[3].level = 1;
  all_teams[4].level = 1;
  all_teams[5].level = 1;
  all_teams[6].level = 1;
  all_teams[7].level = 2;
  all_teams[8].level = 2;
  all_teams[9].level = 3;
  all_teams[10].level = 3;

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

  all_matches = (match*) calloc(100, sizeof(match));

  createMatches(all_teams, all_matches, number_of_teams);

  for (i = 0; i < (3 * number_of_teams); i++){
    printf("%s vs %s\n", all_matches[i].team_a, all_matches[i].team_b);
  }
  printf("____________________________\n");
  for (i = 0; i < 11; i++){
    printf("Hold %d: %d kampe\n", i+1, all_teams[i].games);
  }

  return 0;
}


void createMatches (team *all_teams, match *all_matches, int number_of_teams) {
  int i = 0, match_count = 0;
  int N_counter = 0, A_counter = 0, B_counter = 0, C_counter = 0;
  int team_pointer = 0;

  /* Tæl antallet af hold i hver niveau */
  for (i = 0; i < number_of_teams; i++) {
    if (all_teams[i].level == 0) {
      N_counter++;
    }
    else if (all_teams[i].level == 1) {
      A_counter++;
    }
    else if (all_teams[i].level == 2) {
      B_counter++;
    }
    else {
      C_counter++;
    }
  }

  /* Laver kampe for niveauerne, og tæller antallet af kampe */
  if (number_of_teams > 0) {
    if (N_counter > 0) {
      match_count = createMatchesByLevel(all_teams + team_pointer, all_matches, N_counter, match_count);
      team_pointer += N_counter;
    }
    if (A_counter > 0) {
      match_count = createMatchesByLevel(all_teams + team_pointer, all_matches, A_counter, match_count);
      team_pointer += A_counter;
    }
    if (B_counter > 0) {
      match_count = createMatchesByLevel(all_teams + team_pointer, all_matches, B_counter, match_count);
      team_pointer += B_counter;
    }
    if (C_counter > 0) {
      match_count = createMatchesByLevel(all_teams + team_pointer, all_matches, C_counter, match_count);
    }
  }
  else {
    printf("Ingen hold fundet\n");
  }
}


int createMatchesByLevel (team *all_teams, match *all_matches, int level_counter, int match_count) {

  int skip = 1, team_a = 0, team_b = 0;
  int round_count = GAMES_PR_TEAM / 2;      /* Skal have sin egen kommentar */

  for (skip = 1; skip <= round_count; skip++) {
    for (team_a = 0; team_a < level_counter; team_a++) {
      if ((skip % level_counter) == 0) {
        team_b = (team_a + skip + 1) % level_counter;
      }
      else {
        team_b = (team_a + skip) % level_counter;
      }

      strcpy(all_matches[match_count].team_a, all_teams[team_a].team);
      strcpy(all_matches[match_count].team_b, all_teams[team_b].team);
      all_matches[match_count].level = all_teams[team_a].level;

      /*all_teams[team_a].games++;
      all_teams[team_b].games++;*/
      match_count++;
    }
  }

  return match_count;
}
