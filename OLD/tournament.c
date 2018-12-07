# include "../p1-program/h-files/main.h"
# include "../p1-program/h-files/memoryAllocationScanningSorting.h"
# include "../p1-program/h-files/printPrompt.h"
# include "../p1-program/h-files/tournament.h"
# include "../p1-program/h-files/menus.h"
# include <time.h>

/* Laver og printer en ny turneringsplan */
int createNewTournament(void) {
  FILE *fp = NULL;
  int number_of_fields = 0;
  int number_of_rounds = 0;
  int number_of_teams = 0;
  int number_of_matches = 0;
  int starting_time = 0;
  match *tournament = NULL;
  team *all_teams = NULL;
  char file_name[MAX_NAME_LEN];
  time_t t;

  /* Initialiserer rand */
  srand(time(&t));

  /* Prompter brugeren for antallet af baner, startidspunkt og filnavn */
  number_of_fields = promptForFields();
  starting_time = promptForTime();
  promptForFileName(file_name);

  fp = fopen(file_name, "r");

  if (fp == NULL) { /* Check at filen er NULL */
    perror("Error opening file");
    return -1;
  }

  /* Finder antallet af hold */
  number_of_teams = getNumberOfTeams(fp);

  /* Udregner antallet af kampe og antallet af runder */
  number_of_matches = (number_of_teams * GAMES_PR_TEAM) / 2;
  number_of_rounds = (number_of_matches / number_of_fields) + 10;

  /* Allokerer plads til teams arrayet og matches arrayet */
  all_teams = allocateMemoryTeams(number_of_teams);

  /* Fylder teams arrayet med hold */
  fillArray(fp, all_teams, file_name, number_of_teams);
  /* Sorterer teams arrayet efter niveau */
  sortArrayByLevel(all_teams, number_of_teams);

  /* Laver et turneringsarray ud fra kampene i all_matches */
  tournament = malloc(number_of_matches * sizeof(match));
  createTournament(all_teams, number_of_teams, tournament, number_of_matches, number_of_fields);

  /* Printer det færdige kampprogram, enten til en fil eller til terminalen */
  printProgram(tournament, starting_time, number_of_rounds, number_of_fields);

  /* Frigør den hukommelse der er allokeret til de forskellige arrays */
  free(all_teams);
  free(tournament);

  fclose(fp);

  return 0;
}

/* Opdaterer en eksisterende turneringsplan */
int updateTournament(FILE *fp) {
  int number_of_teams = 0;
  int number_of_matches = 0;
  int number_of_rounds = 0;
  int number_of_fields = 0;
  int starting_time = 0;
  team *new_teams = NULL;
  team *removed_teams = NULL;
  team *all_teams = NULL;
  match *tournament = NULL;

  /* Prompter brugeren for ændringer der skal laves */
  all_teams = editMenu(fp, all_teams, new_teams, removed_teams, &number_of_teams);

  if (all_teams == NULL) {
    return 0;
  }

  number_of_matches = (number_of_teams * GAMES_PR_TEAM) / 2;

  /* Opdaterer kampprogrammet */
  tournament = malloc(number_of_matches * sizeof(match));
  number_of_fields = getNumberOfFields(fp);
  createTournament(all_teams, number_of_teams, tournament, number_of_matches, number_of_fields);

  /* Printer det færdige kampprogram, enten til en fil eller til terminalen */
  number_of_rounds = (number_of_matches / number_of_fields) + 10;
  starting_time = getStartingTime(fp);
  printProgram(tournament, starting_time, number_of_rounds, number_of_fields);

  free(new_teams);
  free(removed_teams);
  free(all_teams);
  free(tournament);

  rewind(fp);
  return 0;
}


/* Laver en turneringsplan, som returnerer antallet af gange planen bryder med reglerne. */
int createTournament(team *all_teams, const int number_of_teams, match *tournament, const int number_of_matches, const int number_of_fields) {
  int i = 0;
  int round_count = 0;
  int tournament_index = 0;
  int team_index = 0;
  int sentinel_count = 0;
  int sentinel_count_2 = 0;
  int grade = 0;
  int no_go_count = 0;
  int team_a[number_of_fields];
  int team_b[number_of_fields];

  /* Kører igennem hver runde. */
  for (round_count = 0; round_count < number_of_matches / number_of_fields; round_count++){
    /* Kører igennem kampene i en runde */
    for (i = 0, tournament_index = round_count * number_of_fields; tournament_index < (round_count + 1) * number_of_fields; tournament_index++){

      sentinel_count = 0;

      /* Finder et hold a. */
      while (sentinel_count < CHECK_NUM){
        team_index = rand() % number_of_teams;

        if (all_teams[team_index].games <= 6 && all_teams[team_index].level != 4){
          all_teams[team_index].games++;
          tournament[tournament_index].team_a = all_teams[team_index];
          tournament[tournament_index].field = tournament_index % number_of_fields;

          sentinel_count = CHECK_NUM;
          team_a[i] = team_index;
        }

        sentinel_count++;
      }

      sentinel_count = 0;

      /* Finder et hold b. */
      while (sentinel_count < CHECK_NUM){
        team_index = (rand() + 1) % number_of_teams;

        if (all_teams[team_index].games <= 6 && all_teams[team_index].level == tournament[tournament_index].team_a.level && strcmp(tournament[tournament_index].team_a.team, all_teams[team_index].team) != 0){
          all_teams[team_index].games++;
          tournament[tournament_index].team_b = all_teams[team_index];

          sentinel_count = CHECK_NUM;
          team_b[i] = team_index;
          i++;
        }

        sentinel_count++;
      }
    }

    /* Tjekker om programmet overholder reglerne. */
    no_go_count = evaluateRound(tournament, tournament_index, number_of_fields, &grade);
    /* Hvis reglerne ikke overholder reglerne sammensættes runden på ny. */
    if (no_go_count > 0 && sentinel_count_2 != CHECK_NUM){
      round_count--;
      sentinel_count_2++;

      /* Sætter antallet af kampe tilbage til det den var før runden blev sammensat. */
      for (i = 0; i < number_of_fields; i++){
        all_teams[team_a[i]].games--;
        all_teams[team_b[i]].games--;
      }
    }
    else if (sentinel_count_2 == CHECK_NUM){
      return 100;
    }
  }


  return no_go_count;
}

int evaluateRound(const match *tournament, const int tournament_index, const int number_of_fields, int *grade) {
  int i = 0, no_go_count = 0;
  int round_count = 0;

  round_count = tournament_index / number_of_fields;

  /* Kører igennem alle kampene i runden. */
  for (i = tournament_index - number_of_fields; i < tournament_index; i++){
    /* Kører hvis kampen allerede er i samme runde. */
    if (is_already_in_round(tournament, i, number_of_fields) == 1){
      no_go_count++;
    }
    /* Kører hvis det ikke er den første runde. */
    if (round_count != 0){
      no_go_count += is_in_previous_round(tournament, i, number_of_fields);
    }
    /* Hvis holdene ikke er i den forrige runde gives der en bedre karakter. */
    else if (round_count != 0){
      *grade += 2;
    }
  }

  return no_go_count;
}

/* Tjekker om et af holdene i en kamp allerede skal spille i runden. */
int is_already_in_round(const match *tournament, const int tournament_index, const int number_of_fields) {
  int i = 0, start_of_round = 0;

  start_of_round = tournament_index - (tournament_index % number_of_fields);

  /* Kører igennem alle de forrige kampe i runden. */
  for (i = start_of_round; i < tournament_index; i++) {
    if (strcmp(tournament[i].team_a.team, tournament[tournament_index].team_a.team) == 0 ||
        strcmp(tournament[i].team_a.team, tournament[tournament_index].team_b.team) == 0 ||
        strcmp(tournament[i].team_b.team, tournament[tournament_index].team_a.team) == 0 ||
        strcmp(tournament[i].team_b.team, tournament[tournament_index].team_b.team) == 0) {
      return 1;
    }
  }

  return 0;
}

/* Tjekker om et af holdene i en kamp har spillet i forrige runde. */
int is_in_previous_round(const match *tournament, const int match_index, const int number_of_fields) {
  int i = 0;
  int no_go_count = 0;
  int start_of_previous_round = 0;

  start_of_previous_round = match_index - ((match_index % number_of_fields) + number_of_fields);

  /* Kører igennem for hver kamp i runden før. */
  for (i = start_of_previous_round; i < match_index - (match_index % number_of_fields); i++) {
    /* Køres hvis der er et hold som også har spillet i runden før. */
    if (strcmp(tournament[i].team_a.team, tournament[match_index].team_a.team) == 0 ||
        strcmp(tournament[i].team_a.team, tournament[match_index].team_b.team) == 0 ||
        strcmp(tournament[i].team_b.team, tournament[match_index].team_a.team) == 0 ||
        strcmp(tournament[i].team_b.team, tournament[match_index].team_b.team) == 0) {
      /* Køres hvis holdet ikke spiller på samme bane. */
      if (is_same_field(tournament, match_index, number_of_fields) == 0){
        no_go_count++;
      }
    }
  }

  return no_go_count;
}

/* Tjekker om et hold spiller på den samme bane i begge runder. */
int is_same_field(const match *tournament, const int match_index, const int number_of_fields){
  if (strcmp(tournament[match_index - number_of_fields].team_a.team, tournament[match_index].team_a.team) == 0 &&
      strcmp(tournament[match_index - number_of_fields].team_b.team, tournament[match_index].team_b.team) != 0) {
    return 1;
  }
  else if(strcmp(tournament[match_index - number_of_fields].team_a.team, tournament[match_index].team_b.team) == 0 &&
      strcmp(tournament[match_index - number_of_fields].team_b.team, tournament[match_index].team_a.team) != 0){
    return 1;
  }
  else if (strcmp(tournament[match_index - number_of_fields].team_b.team, tournament[match_index].team_a.team) == 0 &&
           strcmp(tournament[match_index - number_of_fields].team_a.team, tournament[match_index].team_b.team) != 0){
    return 1;
  }
  else if (strcmp(tournament[match_index - number_of_fields].team_b.team, tournament[match_index].team_b.team) == 0 &&
           strcmp(tournament[match_index - number_of_fields].team_a.team, tournament[match_index].team_a.team) != 0){
    return 1;
  }

  return 0;
}
