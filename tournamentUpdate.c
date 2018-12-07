# include "../p1-program/h-files/main.h"
# include "../p1-program/h-files/memoryAllocationScanningSorting.h"
# include "../p1-program/h-files/printPrompt.h"
# include "../p1-program/h-files/tournament.h"
# include "../p1-program/h-files/menus.h"



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

  for (i = number_of_teams; i < number_of_teams + number_of_new_teams; i++) {
    strcpy(all_teams[i].team, new_teams[j].team);
    all_teams[i].level = new_teams[j].level;
    all_teams[i].games = 0;
    j++;
  }
}

/* Ændre starttidspunktet for et hold. */
void changeStartingTime(team *all_teams, const char *team, const int number_of_teams, int time) {
  int i = 0;

  for (i = 0; i < number_of_teams; i++) {
    if (strcmp(team, all_teams[i].team) == 0) {
      all_teams[i].starting_time = time;
    }
  }
}

/* Ændre sluttidspunktet for et hold. */
void changeEndingTime(team *all_teams, const char *team, const int number_of_teams, int time) {
  int i = 0;

  for (i = 0; i < number_of_teams; i++) {
    if (strcmp(team, all_teams[i].team) == 0) {
      all_teams[i].ending_time = time;
    }
  }
}
