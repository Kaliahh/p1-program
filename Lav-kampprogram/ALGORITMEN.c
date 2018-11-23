/* Funktioner til at sammensætte hold i kampe, og kampe i runder */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
# include "../main.h"

int createMatches (team *, match *, int);
int createMatchesByLevel (team *, match *, int, int);
void createTournament (match *tournament, match *all_matches, const int number_of_matches, const int number_of_fields);
int compareMatches (const match match_a, const match match_b);

int main(void) {
  int i = 0, number_of_teams = 11;
  //int number_of_rounds = 11;   /* Skal udregnes */
  int number_of_fields = 2;
  int number_of_matches = (6 * number_of_teams) / 2;
  team all_teams[11];
  match *all_matches;
  match *tournament;  /* antal runder = antal kampe / antal baner */

  all_teams[0].level = 0;
  all_teams[1].level = 0;
  all_teams[2].level = 0;
  all_teams[3].level = 0;
  all_teams[4].level = 0;
  all_teams[5].level = 1;
  all_teams[6].level = 1;
  all_teams[7].level = 1;
  all_teams[8].level = 1;
  all_teams[9].level = 1;
  all_teams[10].level = 1;

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

  all_matches = malloc(number_of_matches * sizeof(match));

  createMatches(all_teams, all_matches, number_of_teams);

  for (i = 0; i < (3 * number_of_teams); i++) {
    printf("%s vs %s\n", all_matches[i].team_a, all_matches[i].team_b);
  }

  printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n");

  for (i = 0; i < 11; i++){
    printf("Hold %d: %d kampe\n", i+1, all_teams[i].games);
  }

  tournament = malloc(number_of_matches * sizeof(match));

  createTournament(tournament, all_matches, number_of_matches, number_of_fields);

  printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n");

  for (i = 0; i < (3 * number_of_teams); i++) {
    printf("%s vs %s\n", tournament[i].team_a, tournament[i].team_b);
  }

  return 0;
}


int createMatches (team *all_teams, match *all_matches, int number_of_teams) {
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

  return match_count;
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

      all_teams[team_a].games++;
      all_teams[team_b].games++;
      match_count++;
    }
  }

  return match_count;
}

/* Hvis der ikke kan findes en kamp der passer ind med de nuværende regler:
  Gå til den sidste runde, på samme bane som vi er på nu, tag hold A, og find en kamp hvor det er hold B og kampen ikke er blevet spillet.
  Hvis det ikke virker, tag hold B og find en kamp hvor det er hold B og kampen ikke er blevet spillet.
  Hvis det ikke virker, tag hold A og find en kamp hvor det er hold A og kampen ikke er blevet spillet.
  Hvis det ikke virker, tag hold B og find en kamp hvor det er hold A og kampen ikke er blevet spillet.
  Sæt den ind her, gå videre. */

  /* Tjek lige hvor vi mange regler vi har med */

void createTournament (match *tournament, match *all_matches, const int number_of_matches, const int number_of_fields) {

  int j = 1;
  int n = 0;
  int k = 0;
  int h = 0;
  int f = 0;
  int i = 0;

  for (f = 0; f < number_of_matches; f++){
    all_matches[f].field = -1;
  }

  tournament[0] = all_matches[0];
  all_matches[0].field = 0;

  for (i = 0; j < number_of_matches; i = (i + 1) % number_of_matches) {
    n = j - ((j % number_of_fields) + number_of_fields);
    h = j % number_of_fields;

    printf("n = %d\n", n);

    /* Checker for det specialtilfælde, at vi er i den første runde */
    if (j < number_of_fields) {
      //printf("Hey!\n");

      for (k = 0; k < j; k++) {
        if (compareMatches(tournament[k], all_matches[i]) == 0) {
          break;
        }
      }

      if (k == j && all_matches[i].field == -1) {
        tournament[j] = all_matches[i];
        tournament[j].field = h;
        all_matches[i].field = h;
        j++;
      }
    }

    else {
      /* Går fra første kamp i runden før, til den nuværende kamp */
      for (k = n; k < j; k++) {

        if (compareMatches(tournament[k], all_matches[i]) == 0) {
          break;
        }
      }

      if (k == j && all_matches[i].field == -1) {
        tournament[j] = all_matches[i];
        tournament[j].field = h;
        all_matches[i].field = h;
        j++;
      }
    }
  }
}


int compareMatches (const match match_a, const match match_b) {

  if (strcmp(match_a.team_a, match_b.team_a) == 0 || strcmp(match_a.team_a, match_b.team_b) == 0 ||
      strcmp(match_a.team_b, match_b.team_a) == 0 || strcmp(match_a.team_b, match_b.team_b) == 0) {
    return 0;
  }
  else {
    return 1;
  }
}
