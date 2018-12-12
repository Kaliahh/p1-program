# include "../p1-program/h-files/main.h"
# include "../p1-program/h-files/memoryAllocationScanningSorting.h"
# include "../p1-program/h-files/printPrompt.h"
# include "../p1-program/h-files/tournament.h"
# include "../p1-program/h-files/menus.h"

/* Opdaterer en eksisterende turneringsplan. Modtager en filpointer som er placeret i starten af filen. Filpointer bliver rewinded i bunden. */
int updateTournament(FILE *fp) {
  int number_of_teams = 0;
  int number_of_matches = 0;
  int number_of_rounds = 0;
  int number_of_fields = 0;
  int starting_time = 0;
  team *all_teams = NULL;
  match *tournament = NULL;

  /* Finder antallet af hold. */
  number_of_teams = getNumberOfTeamsTournament(fp);
  printf("%d\n", number_of_teams);

  /* Prompter brugeren for ændringer der skal laves */
  all_teams = editMenu(fp, all_teams, &number_of_teams);

  /* Checker om der blev lavet ændringer. Hvis ikke, returnerer funktionen */
  if (all_teams == NULL) {
    return 1;
  }

  /* Udregner antallet af kampe. */
  number_of_matches = (number_of_teams * GAMES_PR_TEAM) / 2;

  /* Opdaterer kampprogrammet. */
  tournament = allocateMemoryTournament(number_of_matches);
  number_of_fields = getNumberOfFields(fp);
  number_of_rounds = getNumberOfRounds(number_of_matches, number_of_fields);
  createTournament(number_of_teams, number_of_matches, number_of_fields, number_of_rounds, all_teams, tournament);

  /* Printer det færdige kampprogram, enten til en fil eller til terminalen */
  starting_time = getStartingTime(fp);
  printingMenu(tournament, starting_time, number_of_rounds, number_of_fields);

  /* Frigører dynamisk lagerallokering. */
  free(all_teams);
  free(tournament);

  /* Sætter filpointeren tilbage til starten af filen */
  rewind(fp);
  return 0;
}

/* Tilføjer nye hold til all_teams arrayet. */
team *addTeams (FILE *fp, const int sentinel, team *all_teams, int *number_of_teams) {
  team *new_teams = NULL;
  int number_of_new_teams = 0;

  /* Prompter og scanner for antal nye hold. */
  printf("Antal hold der ønskes at tilføje\n>> ");
  scanf(" %d", &number_of_new_teams);

  /* Allokere plads til array med nye hold. */
  new_teams = allocateMemoryTeams(number_of_new_teams);

  *number_of_teams += number_of_new_teams;

  /* Checker om det er første gang programmet kommer her til. Hvis det er anden gang eller mere, reallokeres hukommelsen */
  if (sentinel != 1) {
    /* Scanner eksisterende kampprograms-fil og generere et array med de nuværende hold og plads til de nye. */
    all_teams = scanFileForTeams(fp, *number_of_teams);
  }
  else if (sentinel == 1) {
    all_teams = updateTeams(all_teams, *number_of_teams);
  }

  /* Printer de nuværende hold ud til terminalen. */
  printTeams(all_teams, *number_of_teams - number_of_new_teams);

  /* Prompter og scanner nye hold ind. */
  getNewTeams(number_of_new_teams, *number_of_teams, all_teams, new_teams);

  /* Sætter nye hold ind i all_teams arrayet. */
  copyTeams(new_teams, all_teams, number_of_new_teams, *number_of_teams);

  free(new_teams);
  return all_teams;
}

/* Fjerner hold fra all_teams arrayet. */
team *removeTeams(FILE *fp, const int sentinel, team *all_teams, int *number_of_teams) {
  int team_index = 0;
  int number_of_removed_teams = 0;
  team *removed_teams = NULL;

  /* Prompter og scanner for antal af hold der skal fjernes. */
  printf("Antal hold der ønskes at fjernes\n>> ");
  scanf(" %d", &number_of_removed_teams);

  /* Allokere plads til array med hold der skal fjernes. */
  removed_teams = allocateMemoryTeams(number_of_removed_teams);
  if (sentinel != 1) {
    /* Scanner eksisterende kampprograms-fil og generere et array med de nuværende hold. */
    all_teams = scanFileForTeams(fp, *number_of_teams);
  }


  /* Printer all nuværende hold ud. */
  printTeams(all_teams, *number_of_teams);

  /* Prompt og scan nye holdnavne. */
  for (team_index = 0; team_index < number_of_removed_teams; team_index++) {
    getTeamNames(team_index, removed_teams[team_index].team);
  }

  deleteTeams(removed_teams, number_of_removed_teams, *number_of_teams, all_teams);
  free(removed_teams);
  return all_teams;
}

/* Returnerer et array med alt data fra all_teams i et større array */
team *updateTeams(const team *all_teams, const int number_of_teams) {
  team *temp_teams;
  int i = 0;

  temp_teams = (team*) malloc(number_of_teams * sizeof(team));

  for (i = 0; i < number_of_teams; i++) {
    temp_teams[i] = all_teams[i];
  }

  return temp_teams;
}

/* Prompter og scanner for nye hold som input for brugeren. */
void getNewTeams(const int number_of_new_teams, const int number_of_teams, const team *all_teams, team *new_teams) {
  int team_index = 0;
  char level = '\0';

  /* Går igennem antallet af nye hold. */
  for (team_index = 0; team_index < number_of_new_teams; team_index++) {
    /* Prompter for holdnavn. */
    getTeamNames(team_index, new_teams[team_index].team);

    /* Chekker om holdet allerede er i listen */
    while (checkTeam(new_teams[team_index].team, all_teams, number_of_teams) == 1) {
      printf("Holdet \"%s\" er allerede paa listen\n", new_teams[team_index].team);
      getTeamNames(team_index, new_teams[team_index].team);
    }

    /* Prompter for level. */
    printf("Indtast det %d. holds niveau (N, A, B eller C)\n>> ", team_index + 1);
    scanf(" %c", &level);

    /* Oversætter char til enum værdi. */
    new_teams[team_index].level = getLevel(level);

    /* Køre så længe at der ikke er tastet et gyldigt niveau ind. */
    while (new_teams[team_index].level == EMPTY) {
      printf("%d. holds niveau er ikke gyldigt. Prøv igen.\n>> ", team_index + 1);
      scanf(" %c", &level);

      new_teams[team_index].level = getLevel(level);
    }
  }
}

/* Checker om et givent hold allerede er i listen af alle hold */
int checkTeam(const char *temp_team, const team *all_teams, const int number_of_teams) {
  int team_index = 0;

  for (team_index = 0; team_index < number_of_teams; team_index++) {
    if (strcmp(all_teams[team_index].team, temp_team) == 0 && all_teams[team_index].level != EMPTY) {
      return 1;
    }
  }

  return 0;
}

/* Prompt og scan nye holdnavne. */
void getTeamNames(const int team_index, char *team) {
  printf("Indtast det %d. holdnavn\n>> ", team_index + 1);
  scanf(" %[-':.,?!a-zA-Z0-9 ]", team);
}

/* Tilføjer nye hold til arrayet af eksisterende hold. */
void copyTeams(const team *new_teams, team *all_teams, const int number_of_new_teams, const int number_of_teams) {
  int i = 0;
  int j = 0;

  /* Går igennem all_teams arrayet, starter ved en tom plads, hvor der er plads til de nye hold. */
  for (i = number_of_teams - number_of_new_teams, j = 0; i < number_of_teams; i++, j++) {
    all_teams[i] = new_teams[j];
  }
}

/* Fjerner hold fra all_teams arrayet, som er i removed_teams arrayet. */
void deleteTeams(const team *removed_teams, const int number_of_removed_teams, const int number_of_teams, team *all_teams) {
  int i = 0;
  int j = 0;

  /* Går igennem removed_teams arrayet */
  for (i = 0; i < number_of_removed_teams; i++) {
    /* Går igennem all_teams arrayet */
    for (j = 0; j < number_of_teams; j++) {
      if (strcmp(removed_teams[i].team, all_teams[j].team) == 0) {
        all_teams[j].level = EMPTY;
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
