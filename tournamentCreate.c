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
  
  /* Check at filen er NULL */
  isFileOpen(fp);

  /* Finder antallet af hold */
  number_of_teams = getNumberOfTeams(fp);

  /* Udregner antallet af kampe og antallet af runder */
  number_of_matches = (number_of_teams * GAMES_PR_TEAM) / 2;

  /* Finder antallet af runder */
  number_of_rounds = getNumberOfRounds(number_of_matches, number_of_fields);

  /* Allokerer plads til teams arrayet og matches arrayet */
  all_teams = allocateMemoryTeams(number_of_teams);

  /* Fylder teams arrayet med hold */
  fillArray(fp, file_name, number_of_teams, all_teams);
  /* Sorterer teams arrayet efter niveau */
  /*sortArrayByLevel(all_teams, number_of_teams);*/

  /* Laver et turneringsarray ud fra kampene i all_matches */
  tournament = malloc(number_of_matches * sizeof(match));

  while (no_go_count != 0){

    for (i = 0; i < number_of_teams; i++) {
      all_teams[i].games = 0;
    }

    no_go_count = createTournament(number_of_teams, number_of_matches, number_of_fields, number_of_rounds, all_teams, tournament);
  }

  /* Printer det færdige kampprogram, enten til en fil eller til terminalen */
  printingMenu(tournament, starting_time, number_of_rounds, number_of_fields);

  /* Frigør den hukommelse der er allokeret til de forskellige arrays */
  free(all_teams);
  free(tournament);

  fclose(fp);

  return 0;
}

/* Laver en turneringsplan, som returnerer antallet af gange planen bryder med reglerne. */
int createTournament(const int number_of_teams, const int number_of_matches, const int number_of_fields, const int number_of_rounds, team *all_teams, match *tournament) {
  int i = 0;
  int round_count = 0;
  int end_of_round = 0;
  int start_of_round = 0;
  int start_of_next_round = 0;
  int sentinel_count = 0;
  int no_go_count = 0;
  int *team_a;
  int *team_b;

  team_a = (int *) malloc (number_of_fields * sizeof(int));
  team_b = (int *) malloc (number_of_fields * sizeof(int));

  /* Kører igennem hver runde. */
  for (round_count = 0; round_count < number_of_rounds; round_count++) {
    start_of_round = round_count * number_of_fields;
    start_of_next_round = (round_count + 1) * number_of_fields;

    end_of_round = createRound(start_of_next_round, start_of_round, number_of_teams, number_of_fields, team_a, team_b, all_teams, tournament);

    /* Tjekker om programmet overholder reglerne. */
    no_go_count = evaluateRound(tournament, end_of_round, number_of_fields);

    /* Hvis reglerne ikke overholder reglerne sammensættes runden på ny. */
    if (no_go_count > 0 && sentinel_count < CHECK_NUM) {
      /* Sætter antallet af kampe tilbage til det den var før runden blev sammensat. */
      for (i = 0; i < number_of_fields; i++) {
        all_teams[team_a[i]].games--;
        all_teams[team_b[i]].games--;
      }

      round_count--;
      sentinel_count++;
    }
    else if (sentinel_count >= CHECK_NUM) {
      return 1;
    }
    else {
      sentinel_count = 0;
    }
  }

  free(team_a);
  free(team_b);
  return no_go_count;
}

/* Finder hold, som kan sammensættes i en kamp.  */
int createRound(const int start_of_next_round, const int start_of_round, const int number_of_teams, const int number_of_fields, int *team_a, int *team_b, team *all_teams, match *tournament) {

  int tournament_index = 0;
  int i = 0;

  for (tournament_index = start_of_round; tournament_index < start_of_next_round; tournament_index++) {
    team_a[i] = findFirstTeam(tournament_index, number_of_fields, number_of_teams, all_teams, tournament);
    team_b[i] = findSecondTeam(tournament_index, number_of_teams, all_teams, tournament);

    i++;
  }

  return tournament_index;
}

int findFirstTeam(const int tournament_index, const int number_of_fields, const int number_of_teams, team *all_teams, match *tournament) {
  int sentinel_count = 0;
  int team_index = 0;

  while (sentinel_count < CHECK_NUM) {
    team_index = rand() % number_of_teams;

    if (all_teams[team_index].games < GAMES_PR_TEAM && all_teams[team_index].level < EMPTY) {
      tournament[tournament_index].team_a = all_teams[team_index];
      tournament[tournament_index].level = all_teams[team_index].level;
      tournament[tournament_index].field = tournament_index % number_of_fields;

      sentinel_count = CHECK_NUM;

      all_teams[team_index].games++;
    }

    sentinel_count++;
  }

  return team_index;
}

/* Finder det andet hold til en kamp, baseret på det første hold */
int findSecondTeam(const int tournament_index, const int number_of_teams, team *all_teams, match *tournament) {
  int sentinel_count = 0;
  int team_index = 0;

  while (sentinel_count < CHECK_NUM) {
    team_index = rand() % number_of_teams;

    if (strcmp(tournament[tournament_index].team_a.team, all_teams[team_index].team) != 0 &&
        all_teams[team_index].level == tournament[tournament_index].team_a.level &&
        all_teams[team_index].games < 6) {

      all_teams[team_index].games++;
      tournament[tournament_index].team_b = all_teams[team_index];

      sentinel_count = CHECK_NUM;
    }

    sentinel_count++;
  }

  return team_index;
}

/* Tjekker reglerne igennem og returnerer antallet af fejl. */
int evaluateRound(const match *tournament, const int tournament_index, const int number_of_fields) {
  int i = 0;
  int no_go_count = 0;
  int round_count = 0;

  round_count = tournament_index / number_of_fields;

  /* Kører igennem alle kampene i runden. */
  for (i = tournament_index - number_of_fields; i < tournament_index; i++) {
    /* Kører hvis kampen allerede er i samme runde. */
    if (isAlreadyInRound(tournament, i, number_of_fields) == 1) {
      no_go_count++;
    }
    /* Kører hvis det ikke er den første runde. */
    if (round_count != 0){
      no_go_count += isInPreviousRound(tournament, i, number_of_fields);
    }

  }

  return no_go_count;
}

/* Tjekker om et af holdene i en kamp allerede skal spille i runden. */
int isAlreadyInRound(const match *tournament, const int tournament_index, const int number_of_fields) {
  int i = 0;
  int start_of_round = 0;

  start_of_round = tournament_index - (tournament_index % number_of_fields);

  /* Kører igennem alle de forrige kampe i runden. */
  for (i = start_of_round; i < tournament_index; i++) {
    if (compareTeams(tournament + i, tournament + tournament_index) == 1) {
      return 1;
    }
  }

  return 0;
}

/* Tjekker om et af holdene i en kamp har spillet i forrige runde. */
int isInPreviousRound(const match *tournament, const int match_index, const int number_of_fields) {
  int i = 0;
  int no_go_count = 0;
  int start_of_previous_round = 0;
  int start_of_current_round = 0;

  start_of_previous_round = match_index - ((match_index % number_of_fields) + number_of_fields);
  start_of_current_round = match_index - (match_index % number_of_fields);

  /* Kører igennem for hver kamp i runden før. */
  for (i = start_of_previous_round; i < start_of_current_round; i++) {
    /* Køres hvis der er et hold som også har spillet i runden før. */
    if (compareTeams(tournament + i, tournament + match_index) == 1) {
      /* Køres hvis holdet ikke spiller på samme bane. */
      if (tournament[i].field != tournament[match_index].field){
        no_go_count++;
      }
    }
  }

  return no_go_count;
}

/* Sammenligner holdnavne */
int compareTeams(const match *a, const match *b) {
  if(strcmp(a->team_a.team, b->team_a.team) == 0 ||
     strcmp(a->team_a.team, b->team_b.team) == 0 ||
     strcmp(a->team_b.team, b->team_a.team) == 0 ||
     strcmp(a->team_b.team, b->team_b.team) == 0) {
    return 1;
  }

  return 0;
}

/* Finder antallet af runder
   Tjekker om der skal bruges en ekstra runde,
   i det tilfælde hvor den sidste runde ikke er fyldt helt ud */
int getNumberOfRounds(const int number_of_matches, const int number_of_fields) {
  if (number_of_matches % number_of_fields == 0) {
    return (number_of_matches / number_of_fields);
  }
  else {
    return (number_of_matches / number_of_fields) + 1;
  }
}

/* Får en char, der er et niveau for et hold. Funktionen konverterer niveauet til heltal, og returner resultatet. */
int getLevel(const char level) {
  return (level == 'N') ? N :
         (level == 'A') ? A :
         (level == 'B') ? B :
         (level == 'C') ? C : EMPTY;
}
