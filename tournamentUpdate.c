# include "../p1-program/h-files/main.h"
# include "../p1-program/h-files/memoryAllocationScanningSorting.h"
# include "../p1-program/h-files/printPrompt.h"
# include "../p1-program/h-files/tournament.h"
# include "../p1-program/h-files/menus.h"

/* Opdaterer en eksisterende stævneplan. Modtager en filpointer som er placeret i starten af filen. Filpointer bliver rewinded i bunden. */
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

  /* Prompter brugeren for ændringer der skal laves */
  all_teams = editMenu(fp, all_teams, &number_of_teams);

  /* Checker om brugeren vil tilbage til hovedmenuen */
  if (all_teams == NULL) {
    return 1;
  }

  /* Udregner antallet af kampe. */
  number_of_matches = (number_of_teams * GAMES_PR_TEAM) / 2;

  /* Opdaterer stævnenen. */
  tournament = allocateMemoryMatch(number_of_matches);
  number_of_fields = getNumberOfFields(fp);
  number_of_rounds = getNumberOfRounds(number_of_matches, number_of_fields);

  /* Sammensætter og evaluerer stævneplaner, indtil der findes en der er acceptabel */
  generateTournament(number_of_teams, number_of_matches, number_of_fields, number_of_rounds, tournament, all_teams);

  /* Printer den færdige stævneplan, enten til en fil eller til terminalen */
  starting_time = getStartingTime(fp);
  printingMenu(tournament, starting_time, number_of_rounds, number_of_fields);

  /* Frigører dynamisk lagerallokering. */
  free(all_teams);
  free(tournament);

  /* Sætter filpointeren tilbage til starten af filen */
  rewind(fp);
  return 0;
}

/* Ændrer på all_teams, baseret på funktionen *f og konstanten modifier */
team *modifyTeams(void (*f)(const team *, const int, const int, team *), const int modifier, team *all_teams, int *number_of_teams) {
  team *temp_mod_array = NULL;
  int number_of_mod_teams = 0;

  /* Prompter brugeren for antallet af hold der skal fjernes eller tilføjes.
     modifier bestemmer om der bliver printet "tilføjes" eller "fjernes"
     til terminalen */
  number_of_mod_teams = promptForNumberOfTeams(modifier);

  /* Allokerer plads til et array med plads til de hold der skal fjernes eller tilføjes */
  temp_mod_array = allocateMemoryTeams(number_of_mod_teams);

  /* Checker om all_teams skal udvides */
  if (modifier == ADD) {
    *number_of_teams += number_of_mod_teams;
    all_teams = updateTeams(all_teams, *number_of_teams);
  }

  /* Printer de nuværende hold til terminalen */
  printTeams(all_teams, (modifier == ADD) ? *number_of_teams - number_of_mod_teams : *number_of_teams);

  /* Prompter og scanner nye hold ind. */
  getTeams(number_of_mod_teams, *number_of_teams, all_teams, modifier, temp_mod_array);

  /* Fjerner eller tilføjer hold, alt efter hvor modifyTeams blev kaldt */
  (*f)(temp_mod_array, number_of_mod_teams, *number_of_teams, all_teams);

  if (modifier == REMOVE) {
    /* Flytter de fjernede hold til sidst i all_teams */
    sortArrayByLevel(all_teams, *number_of_teams);
    *number_of_teams -= number_of_mod_teams;
  }

  return all_teams;
}

/* Returnerer et array med alt data fra all_teams i et større array */
team *updateTeams(const team *all_teams, const int number_of_teams) {
  team *temp_teams;
  int team_index = 0;

  temp_teams = allocateMemoryTeams(number_of_teams);

  for (team_index = 0; team_index < number_of_teams; team_index++) {
    temp_teams[team_index] = all_teams[team_index];
  }

  return temp_teams;
}

/* Prompter brugeren for de hold der skal modificeres, og foretager forskellige ændringer, alt efter hvilken modifier den får ind */
void getTeams(const int number_of_modified_teams, const int number_of_teams, const team *all_teams, const int modifier, team *temp_mod_array) {
  int team_index = 0;
  char level = '\0';

  for (team_index = 0; team_index < number_of_modified_teams; team_index++) {
    getTeamNames(team_index, temp_mod_array[team_index].team);

    /* Checker om holdet enten er i listen eller ikke er det, alt efter om der tilføjes eller fjernes hold */
    while (checkTeam(temp_mod_array[team_index].team, all_teams, number_of_teams) == modifier) {
      printf("Holdet \"%s\" er %s paa listen\n", temp_mod_array[team_index].team, (modifier == ADD) ? "allerede" : "ikke");
      getTeamNames(team_index, temp_mod_array[team_index].team);
    }

    /* Checker om der skal tilføjes niveau */
    if (modifier == ADD) {
      /* Prompter for level. */
      printf("Indtast det %d. holds niveau (N, A, B eller C)\n>> ", team_index + 1);
      scanf(" %c", &level);

      /* Oversætter char til enum værdi. */
      temp_mod_array[team_index].level = getLevel(level);

      /* Kører så længe at der ikke er tastet et gyldigt niveau ind. */
      while (temp_mod_array[team_index].level == EMPTY) {
        printf("\"%c\" er ikke et gyldigt niveau. Prøv igen.\n>> ", level);
        scanf(" %c", &level);

        temp_mod_array[team_index].level = getLevel(level);
      }
    }
  }
}

/* Prompt og scan nye holdnavne. */
void getTeamNames(const int team_index, char *team) {
  printf("Indtast det %d. holdnavn\n>> ", team_index + 1);
  scanf(" %[-':.,?!a-zA-Z0-9 ]", team);
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

/* Tilføjer nye hold til arrayet af eksisterende hold. */
void copyTeams(const team *new_teams, const int number_of_new_teams, const int number_of_teams, team *all_teams) {
  int i = 0;
  int j = 0;

  /* Går igennem all_teams arrayet, starter ved en tom plads, hvor der er plads til de nye hold. */
  /* i er et indeks der starter i all_teams hvor de nye hold skal sættes ind.
     j er et indeks der starter fra starten af new_teams */
  for (i = number_of_teams - number_of_new_teams, j = 0; i < number_of_teams; i++, j++) {
    all_teams[i] = new_teams[j];
  }
}

/* Fjerner hold fra all_teams arrayet, som er i removed_teams arrayet. */
void deleteTeams(const team *removed_teams, const int number_of_removed_teams, const int number_of_teams, team *all_teams) {
  int team_index = 0;
  int rem_team_index = 0;

  /* Går igennem removed_teams arrayet */
  for (rem_team_index = 0; rem_team_index < number_of_removed_teams; rem_team_index++) {
    /* Går igennem all_teams arrayet for at finde holdet der skal fjernes,
       ud fra removed_teams */
    for (team_index = 0; team_index < number_of_teams; team_index++) {
      if (strcmp(removed_teams[rem_team_index].team, all_teams[team_index].team) == 0) {
        all_teams[team_index].level = EMPTY;
      }
    }
  }
}
