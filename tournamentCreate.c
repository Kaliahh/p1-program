# include "../p1-program/h-files/main.h"
# include "../p1-program/h-files/memoryAllocationScanningSorting.h"
# include "../p1-program/h-files/printPrompt.h"
# include "../p1-program/h-files/tournament.h"
# include "../p1-program/h-files/menus.h"

/* Laver og printer en ny turneringsplan */
int createNewTournament(void) {
  FILE *fp = NULL;
  int number_of_fields = 0;
  int number_of_rounds = 0;
  int number_of_teams = 0;
  int number_of_matches = 0;
  int starting_time = 0;
  int i = 0;
  int no_go_count = CHECK_NUM;
  match *tournament = NULL;
  team *all_teams = NULL;
  char file_name[MAX_NAME_LEN];


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

  while (no_go_count != 0){

    for (i = 0; i < number_of_teams; i++) {
      all_teams[i].games = 0;
    }

    no_go_count = createTournament(all_teams, number_of_teams, tournament, number_of_matches, number_of_fields);
  }

  /* Printer det færdige kampprogram, enten til en fil eller til terminalen */
  printProgram(tournament, starting_time, number_of_rounds, number_of_fields);

  /* Frigør den hukommelse der er allokeret til de forskellige arrays */
  free(all_teams);
  free(tournament);

  fclose(fp);

  return 0;
}


/* Laver en turneringsplan, som returnerer antallet af gange planen bryder med reglerne. */
int createTournament(team *all_teams, const int number_of_teams, match *tournament, const int number_of_matches, const int number_of_fields) {
  int i = 0;
  int round_count = 0;
  int tournament_index = 0;
  int grade = 0;
  int no_go_count = 0;

  /* Kører igennem hver runde. */
  for (round_count = 0; round_count < number_of_matches / number_of_fields; round_count++) {
    /* Kører igennem kampene i en runde */
    for (i = 0, tournament_index = round_count * number_of_fields; tournament_index < (round_count + 1) * number_of_fields; tournament_index++) {
      findFirstTeam(tournament_index, number_of_fields, number_of_teams, all_teams, tournament);
      findSecondTeam(tournament_index, number_of_teams, all_teams, tournament, &i);
    }
    no_go_count = checkRules(number_of_fields, tournament_index, number_of_teams, tournament, all_teams, &grade, &round_count);
  }

  return no_go_count;
}

/* Finder det første hold til en kamp */
void findFirstTeam(const int tournament_index, const int number_of_fields, const int number_of_teams, team *all_teams, match *tournament) {
  int sentinel_count = 0;
  int team_index = 0;

  while (sentinel_count < CHECK_NUM) {
    team_index = rand() % number_of_teams;

    if (all_teams[team_index].games < 6 && all_teams[team_index].level != 4) {
      all_teams[team_index].games++;
      tournament[tournament_index].team_a = all_teams[team_index];
      tournament[tournament_index].level = all_teams[team_index].level;
      tournament[tournament_index].field = tournament_index % number_of_fields;

      sentinel_count = CHECK_NUM;
    }

    sentinel_count++;
  }
}

/* Finder det andet hold til en kamp, baseret på det første hold */
void findSecondTeam(const int tournament_index, const int number_of_teams, team *all_teams, match *tournament, int *i) {
  int sentinel_count = 0;
  int team_index = 0;

  while (sentinel_count < CHECK_NUM) {
    team_index = (rand() + 1) % number_of_teams;

    if (all_teams[team_index].games < 6 &&
        all_teams[team_index].level == tournament[tournament_index].team_a.level &&
        strcmp(tournament[tournament_index].team_a.team, all_teams[team_index].team) != 0) {
      all_teams[team_index].games++;
      tournament[tournament_index].team_b = all_teams[team_index];

      sentinel_count = CHECK_NUM;
      *i += 1;
    }

    sentinel_count++;
  }
}

/* Checker om reglerne bliver overholdt for den nuværende runde og runden før */
int checkRules(const int number_of_fields, const int last_match_index, const int number_of_teams, match *tournament, team *all_teams, int *grade, int *round_count) {
  int no_go_count = 0;
  int count = 0;
  int sentinel_count = 0;

  /* Tjekker om programmet overholder reglerne. */
  no_go_count = evaluateRound(tournament, last_match_index, number_of_fields, grade);

  /* Hvis reglerne ikke overholder reglerne sammensættes runden på ny. */
  if (no_go_count > 0 && sentinel_count != CHECK_NUM){
    *round_count -= 1;
    sentinel_count++;

    /* Sætter antallet af kampe tilbage til det den var før runden blev sammensat. */
    resetGames(tournament, all_teams, (last_match_index - number_of_fields), last_match_index, number_of_teams);
  }

  return no_go_count;
}

/* NAVNET SKAL ÆNDERS */
void resetGames(match * tournament, team *all_teams, int i, const int end_of_round, const int number_of_teams) {
  int j = 0;

  for (; i < end_of_round; i++){
    for (j = 0; j < number_of_teams; j++) {
      if (strcmp(tournament[i].team_a.team, all_teams[j].team) == 0 ||
          strcmp(tournament[i].team_b.team, all_teams[j].team) == 0) {
        all_teams[j].games--;
      }
    }
  }
}

int evaluateRound(const match *tournament, const int last_match_index, const int number_of_fields, int *grade) {
  int i = 0, no_go_count = 0;
  int round_count = 0;

  round_count = last_match_index / number_of_fields;

  /* Kører igennem alle kampene i runden. */
  for (i = last_match_index - number_of_fields; i < last_match_index; i++) {
    /* Kører hvis kampen allerede er i samme runde. */
    if (is_already_in_round(tournament, i, number_of_fields) == 1) {
      no_go_count++;
    }
    /* Kører hvis det ikke er den første runde. */
    if (round_count != 0) {
      no_go_count += is_in_previous_round(tournament, i, number_of_fields, grade);
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
    if (compareTeams(&tournament[i], &tournament[tournament_index]) == 1) {
      return 1;
    }
  }

  return 0;
}

/* Tjekker om et af holdene i en kamp har spillet i forrige runde. */
int is_in_previous_round(const match *tournament, const int match_index, const int number_of_fields, int *grade) {
  int i = 0;
  int no_go_count = 0;
  int start_of_previous_round = 0;

  start_of_previous_round = match_index - ((match_index % number_of_fields) + number_of_fields);

  /* Kører igennem for hver kamp i runden før. */
  for (i = start_of_previous_round; i < match_index - (match_index % number_of_fields); i++) {
    /* Køres hvis der er et hold som også har spillet i runden før. */
    if (compareTeams(&tournament[i], &tournament[match_index]) == 1) {
      /* Køres hvis holdet ikke spiller på samme bane. */
      if (tournament[i].field != tournament[match_index].field){
        no_go_count++;
      }
    }
    /* Hvis holdene ikke er i den forrige runde gives der en bedre karakter. */
    else {
      *grade += 2;
    }
  }

  return no_go_count;
}

/* Sammenligner to kampes hold, og returner 1 hvis den finder et hold der går igen */
int compareTeams(const match *tp1, const match *tp2) {
  if (strcmp(tp1->team_a.team, tp2->team_a.team) == 0 || strcmp(tp1->team_a.team, tp2->team_b.team) == 0 ||
      strcmp(tp1->team_b.team, tp2->team_a.team) == 0 || strcmp(tp1->team_b.team, tp2->team_b.team) == 0) {
    return 1;
  }
  else {
    return 0;
  }
}
