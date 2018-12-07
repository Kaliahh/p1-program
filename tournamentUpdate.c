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


  number_of_teams = getNumberOfTeamsTournament(fp);

  /* Prompter brugeren for ændringer der skal laves */
  editMenu(fp, all_teams, &number_of_teams);

  /*if (all_teams == NULL) {
    return 0;
  }*/

  number_of_matches = (number_of_teams * GAMES_PR_TEAM) / 2;

  /* Opdaterer kampprogrammet */
  tournament = allocateMemoryMatches(number_of_matches);
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

void addTeams (FILE *fp, team *all_teams, int *number_of_teams) {
  team *new_teams = NULL;
  int number_of_new_teams = 0;

  printf("Antal hold der ønskes at tilføje\n>> ");
  scanf(" %d", &number_of_new_teams);

  new_teams = allocateMemoryTeams(number_of_new_teams);
  all_teams = scanFileForTeams(fp, *number_of_teams, number_of_new_teams);

  printTeams(all_teams, *number_of_teams);

  getNewTeams(all_teams, number_of_new_teams, new_teams);

  copyTeams(new_teams, all_teams, number_of_new_teams, *number_of_teams);
}

/* Flyt til print og prompt */
void getNewTeams(team *all_teams, int number_of_new_teams, team *new_teams) {
  int team_index = 0;
  char level = '\0';

  for (team_index = 0; team_index < number_of_new_teams; team_index++) {
    getTeamNames(new_teams[team_index].team, team_index);

    printf("Indtast det %d. holds niveau (N, A, B eller C)\n>> ", team_index + 1);
    scanf(" %c", &level);

    new_teams[team_index].level = getLevel(level);

    while (new_teams[team_index].level == EMPTY) {
      printf("%d. holds niveau er ikke gyldigt. Prøv igen.\n>> ", team_index + 1);
      scanf(" %c", &level);

      new_teams[team_index].level = getLevel(level);
    }
  }
}

void getTeamNames(char *team, int team_index) {
  printf("Indtast det %d. holdnavn\n>> ", team_index + 1);
  scanf(" %[-':.,?!a-zA-Z0-9 ]", team);
}


/* Tilføjer hold til listen af hold. */
void copyTeams(const team *new_teams, team *all_teams, const int number_of_new_teams, const int number_of_teams) {
  int i = 0;
  int j = 0;

  for (i = number_of_teams; i < number_of_teams + number_of_new_teams; i++) {
    all_teams[i] = new_teams[j];
    j++;
  }
}

void removeTeams(FILE *fp, team *all_teams, int *number_of_teams) {
  int team_index = 0;
  int number_of_removed_teams = 0;
  team *removed_teams = NULL;

  printf("Antal hold der ønskes at fjernes\n>> ");
  scanf(" %d", &number_of_removed_teams);

  removed_teams = allocateMemoryTeams(number_of_removed_teams);
  all_teams = scanFileForTeams(fp, *number_of_teams, 0);

  printTeams(all_teams, *number_of_teams);

/* Samme som i add teams */
  for (team_index = 0; team_index < number_of_removed_teams; team_index++) {
    getTeamNames(removed_teams[team_index].team, team_index);
  }

  deleteTeams(removed_teams, all_teams, number_of_removed_teams, *number_of_teams);
}


/* Fjerner hold fra listen af hold. */
void deleteTeams(const team *removed_teams, team *all_teams, const int number_of_removed_teams, const int number_of_teams) {
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

/* Ændre starttidspunktet for et hold. */
/*void changeStartingTime(team *all_teams, const char *team, const int number_of_teams, int time) {
  int i = 0;

  for (i = 0; i < number_of_teams; i++) {
    if (strcmp(team, all_teams[i].team) == 0) {
      all_teams[i].starting_time = time;
    }
  }
}*/

/* Ændre sluttidspunktet for et hold. */
/*void changeEndingTime(team *all_teams, const char *team, const int number_of_teams, int time) {
  int i = 0;

  for (i = 0; i < number_of_teams; i++) {
    if (strcmp(team, all_teams[i].team) == 0) {
      all_teams[i].ending_time = time;
    }
  }
}*/
