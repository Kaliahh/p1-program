# include "main.h"
# include "matches.h"

void createMatches(team *all_teams, match *all_matches, int number_of_teams) {
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

int createMatchesByLevel(team *all_teams, match *all_matches, int level_counter, int match_count) {

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

      all_teams[team_a].games++;
      all_teams[team_b].games++;
      match_count++;
    }
  }

  return match_count;
}

/* Returner 0, hvis kampene har hold tilfælles, ellers returnerer den 1 */
int compareMatches(const match match_a, const match match_b) {

  if (strcmp(match_a.team_a, match_b.team_a) == 0 || strcmp(match_a.team_a, match_b.team_b) == 0 ||
      strcmp(match_a.team_b, match_b.team_a) == 0 || strcmp(match_a.team_b, match_b.team_b) == 0) {
    return 0;
  }
  else {
    return 1;
  }
}
