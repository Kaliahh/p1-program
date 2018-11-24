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
int findMatch(match *tourn_match, match *all_matches, match *, const int);
int compareMatches (const match match_a, const match match_b);

int main(void) {
  int i = 0, number_of_teams = 17;
  int number_of_fields = 4;
  int number_of_matches = (6 * number_of_teams) / 2;
  team all_teams[17];
  match *all_matches;
  match *tournament;

  all_teams[0].level = 0;
  all_teams[1].level = 0;
  all_teams[2].level = 0;
  all_teams[3].level = 0;
  all_teams[4].level = 0;
  all_teams[5].level = 0;
  all_teams[6].level = 0;
  all_teams[7].level = 0;
  all_teams[8].level = 0;
  all_teams[9].level = 0;
  all_teams[10].level = 0;
  all_teams[11].level = 0;
  all_teams[12].level = 0;
  all_teams[13].level = 0;
  all_teams[14].level = 0;
  all_teams[15].level = 0;
  all_teams[16].level = 0;

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

  all_matches = malloc(number_of_matches * sizeof(match));

  createMatches(all_teams, all_matches, number_of_teams);

  for (i = 0; i < (3 * number_of_teams); i++) {
    printf("%s vs %s\n", all_matches[i].team_a, all_matches[i].team_b);
  }

  printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n");

  for (i = 0; i < number_of_teams; i++){
    printf("Hold %2d: %d kampe\n", i+1, all_teams[i].games);
  }

  tournament = malloc(number_of_matches * sizeof(match));

  createTournament(tournament, all_matches, number_of_matches, number_of_fields);

  printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n");

  for (i = 0; i < number_of_matches; i++) {
    if (i % number_of_fields == 0 && i != 0) {
      printf("- - - - - - - - - - - - - - - - - - - - - - - - -\n");
      printf("%2d | %8s vs %-10s\n", i + 1, tournament[i].team_a, tournament[i].team_b);
    }

    else {
      printf("%2d | %8s vs %-10s\n", i + 1, tournament[i].team_a, tournament[i].team_b);
    }
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

  int tournament_i = 1;
  int check_num = 0;
  int check_i = 0;
  int field_i = 0;
  int fill_i = 0;
  int match_i = 0;
  int fail_i = 0;
  int result = 0;

  /* Sætter alle kampenes bane til -1, for at indikere at de ikke har spillet */
  for (fill_i = 0; fill_i < number_of_matches; fill_i++) {
    all_matches[fill_i].field = -1;
  }

  /* Kopierer den første kamp over i turneringen */
  all_matches[0].field = 0;
  tournament[0] = all_matches[0];

  /* Gennemgår alle kampe, indtil turneringsindekset er lig med antallet af kampe der skal spilles */
  for (match_i = 0; tournament_i < number_of_matches && fail_i <= (number_of_matches * 2) + 1; match_i = (match_i + 1) % number_of_matches) {

    /* Indekser for når der skal tjekkes om et hold har spillet i den nuværende runde, og runden før */
    check_num = tournament_i - ((tournament_i % number_of_fields) + number_of_fields);
    field_i = tournament_i % number_of_fields;

    if (fail_i > number_of_matches * 2) {
      check_i = check_num;
      while (check_i < tournament_i) {
        if (tournament[check_i].field == field_i) {
          result = findMatch(&tournament[check_i], all_matches, tournament, number_of_matches);
          if (result == 1) {
            tournament_i++;
          }
          else {
            printf("Kunne ikke lave turneringen\n");
            fail_i += 10;
            break;
          }
        }
        else {
          check_i++;
        }
      }
    }

    /* Checker for det specialtilfælde, at vi er i den første runde */
    else if (tournament_i < number_of_fields) {
      check_i = 0;
      while(compareMatches(tournament[check_i], all_matches[match_i]) != 0 && check_i < tournament_i) {
        check_i++;
      }
      /* Hvis holdene i kampen ikke har spillet i sidste runde eller den nuværende,
         og kampen endnu ikke er blevet spillet, kopieres kampen over i turneringen */
      if (check_i == tournament_i && all_matches[match_i].field == -1) {
        all_matches[match_i].field = field_i;
        tournament[tournament_i] = all_matches[match_i];
        tournament_i++;
        fail_i = 0;
      }

      else {
        fail_i++;
      }
    }

    else {
       /* Gennemgår turneringen for at se om holdene i kampen der bliver sammenlignet med,
       allerede har spillet i den foregående runde eller den nuværende runde */
      check_i = check_num;
      while(compareMatches(tournament[check_i], all_matches[match_i]) != 0 && check_i < tournament_i) {
        check_i++;
      }
      if (check_i == tournament_i && all_matches[match_i].field == -1) {
        all_matches[match_i].field = field_i;
        tournament[tournament_i] = all_matches[match_i];
        tournament_i++;
        fail_i = 0;
      }

      else {
        fail_i++;
      }
    }
  }
}

int findMatch(match *tourn_match, match *all_matches, match *tournament, const int number_of_matches) {

  for (int i = 0; i < number_of_matches; i++) {
    if (strcmp(tourn_match->team_a, all_matches[i].team_b) == 0 && all_matches[i].field == -1) {
      *tourn_match = all_matches[i];
      return 1;
    }
    else {
      return 0;
    }
  }
  return 0;
}

/* Sammenligner to kampe, for at se om nogen af holdene går igen */
int compareMatches (const match match_a, const match match_b) {

  if (strcmp(match_a.team_a, match_b.team_a) == 0 || strcmp(match_a.team_a, match_b.team_b) == 0 ||
      strcmp(match_a.team_b, match_b.team_a) == 0 || strcmp(match_a.team_b, match_b.team_b) == 0) {
    return 0;
  }
  else {
    return 1;
  }
}
