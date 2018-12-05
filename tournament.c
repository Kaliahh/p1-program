# include "../p1-program/h-files/main.h"
# include "../p1-program/h-files/memoryAllocationScanningSorting.h"
# include "../p1-program/h-files/printPrompt.h"
# include "../p1-program/h-files/matches.h"
# include "../p1-program/h-files/tournament.h"
# include "../p1-program/h-files/menus.h"
# include <time.h>

/* Laver og printer en ny turneringsplan */
int createNewTournament(void) {
  FILE *fp = NULL;
  match *tournament = NULL;
  match *all_matches = NULL;
  team *all_teams = NULL;
  int number_of_fields = 0;
  int number_of_rounds = 0;
  int number_of_teams = 0;
  int number_of_matches = 0;
  int starting_time = 0;
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
  all_matches = allocateMemoryMatches(number_of_matches);

  /* Fylder teams arrayet med hold */
  fillArray(fp, all_teams, file_name, number_of_teams);
  /* Sorterer teams arrayet efter niveau */
  sortArrayByLevel(all_teams, number_of_teams);

  /* Laver alle kampe der skal spilles, og lægger dem over i matches arrayet */
  createMatches(all_teams, all_matches, number_of_teams);
  /* Sætter alle kampenes field member til -1, da ingen kampe er spillet endnu */
  resetFields(number_of_matches, all_matches);

  /* Laver et turneringsarray ud fra kampene i all_matches */
  tournament = malloc(number_of_matches * sizeof(match));
  createTournament(all_matches, number_of_matches, number_of_fields, tournament);

  /* Printer det færdige kampprogram, enten til en fil eller til terminalen */
  printProgram(tournament, starting_time, number_of_rounds, number_of_fields);

  /* Frigør den hukommelse der er allokeret til de forskellige arrays */
  free(all_teams);
  free(all_matches);
  free(tournament);

  fclose(fp);

  return 0;
}

/* Laver et turneringsarray ud fra kampene i all_matches */
void createTournament(const match *all_matches, const int number_of_matches, const int number_of_fields, match *tournament) {
  match *copy_of_matches;
  int tournament_index = 0;
  int match_index = 0;
  int SENTINEL = 0;

  copy_of_matches = malloc(number_of_matches * sizeof(match));

  copyMatches(all_matches, number_of_matches, copy_of_matches);

  while (SENTINEL == 0) {
    match_index = rand() % number_of_matches;
    /* printf("index: %d\n", match_index); */
    /* printf("%d\n", copy_of_matches[match_index].field); */

    if (copy_of_matches[match_index].field == -1) {
      copy_of_matches[match_index].field = tournament_index % number_of_fields;
      tournament[tournament_index] = copy_of_matches[match_index];
      tournament_index++;
    }

    else if (tournament_index >= number_of_matches) {
      SENTINEL = 1;
    }
  }
}

void resetFields(const int number_of_matches, match *copy_of_matches) {
  int match_index = 0;

  for (match_index = 0; match_index < number_of_matches; match_index++) {
    copy_of_matches[match_index].field = -1;
  }
}

void copyMatches(const match *all_matches, const int number_of_matches, match *copy_of_matches) {
  int match_index = 0;

  for (match_index = 0; match_index < number_of_matches; match_index++) {
    copy_of_matches[match_index] = all_matches[match_index];
  }
}
