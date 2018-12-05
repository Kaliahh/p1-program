/* Menu der spørger om brugeren vil redigere et eksisterende kampprogram, eller lave et nyt kampprogram */
# include "../p1-program/h-files/main.h"
# include "../p1-program/h-files/tournament.h"
# include "../p1-program/h-files/menus.h"
# include "../p1-program/h-files/printPrompt.h"
# include "../p1-program/h-files/matches.h"
# include "../p1-program/h-files/memoryAllocationScanningSorting.h"

# define NOGET 1;

int main(void) {

  mainMenu();

  return 0;
}

int mainMenu(void) {
  int choice = -1;
  FILE *fp = NULL;

  /* printf("\nTurnerings Planlægger 2000\n\n"); */

  printf("            ______ ___   ___  ___   ___   ___ \n");
  printf("           /_  __// _ \\ |_  |/ _ \\ / _ \\ / _ \\\n");
  printf("            / /  / ___// __// // // // // // /\n");
  printf("           /_/  /_/   /____/\\___/ \\___/ \\___/\n\n");

  printMainMenu();

  while (choice != 0) {
    scanf(" %d", &choice);

    if (choice == 1) {
      printf("\n");
      createNewTournament();
      printMainMenu();
    }

    else if (choice == 2) {
      printf("\n");

      fp = fopen("turneringsplan.txt", "r");
      updateTournament(fp);
      printMainMenu();
    }

    else if (choice == 3) {
      printf("\n");
      createTemplate();
      printMainMenu();
    }

    else if (choice == 0) {
      printf("\n");
      printf("Farvel!\n");
    }

    else {
      printf("\nUgyldigt input, prøv igen\n");
    }
  }


  if (fp != NULL) {
    fclose(fp);
  }

  return 0;
}

void printMainMenu(void) {
  printf("#####################  HOVEDMENU  #####################\n\n");
  printf("[1] Lav et nyt kampprogram\n");
  printf("[2] Rediger et eksisterende kampprogram\n");
  printf("[3] Lav skabelon til liste af holdnavne\n");
  printf("[0] Afslut\n>> ");
}

team *editMenu(FILE *fp, team *all_teams, team *new_teams, team *removed_teams, int *number_of_teams) {
  int team_index = 0;
  int choice = 0;
  int time = 0;
  int hour = 0;
  int minute = 0;
  int number_of_new_teams = 0;
  int number_of_removed_teams = 0;
  char level = ' ';
  char team[MAX_NAME_LEN];

  *number_of_teams = getNumberOfTeamsTournament(fp);


  printf("######################  REDIGER  ######################\n\n");
  printf("Hvad vil du gerne ændre?\n");
  printf("[1] Tilføj nyt hold\n"
         "[2] Slet eksisterende hold\n"
         "[3] Ændre startstidspunkt for et eksisterende hold\n"
         "[4] Ændre sluttidspunkt for et eksisterende hold\n"
         "[0] Gå til hovedmenuen\n>> ");
  scanf(" %d", &choice);

  /* Tilføjer et nyt hold */
  if (choice == 1) {
    printf("Antal hold der ønskes at tilføje\n>> ");
    scanf(" %d", &number_of_new_teams);

    new_teams = malloc(number_of_new_teams * sizeof(team));
    all_teams = scanFileForTeams(fp, *number_of_teams, number_of_new_teams);

    for (team_index = 0; team_index < number_of_new_teams; team_index++) {
      printf("Indtast det %d. holdnavn\n>> ", team_index + 1);
      scanf(" %[-':.,?!a-zA-Z0-9 ]", new_teams[team_index].team);

      printf("Indtast det %d. holds niveau (med blokbogstaver)\n>> ", team_index + 1);
      scanf(" %c", &level);

      new_teams[team_index].level = (level == 'N') ? N :
                           (level == 'A') ? A :
                           (level == 'B') ? B :
                           (level == 'C') ? C : EMPTY;

      while (new_teams[team_index].level == EMPTY) {
        printf("%d. holds niveau er ikke gyldigt. Prøv igen.\n>> ", team_index + 1);
        scanf(" %c", &level);

        new_teams[team_index].level = (level == 'N') ? N :
                             (level == 'A') ? A :
                             (level == 'B') ? B :
                             (level == 'C') ? C : EMPTY;
      }
    }


    addTeams(new_teams, all_teams, number_of_new_teams, *number_of_teams);
    sortArrayByLevel(all_teams, *number_of_teams);
  }
  /* Fjerner et eksisterende hold */
  else if (choice == 2) {
    printf("Antal hold der ønskes at fjernes\n>> ");
    scanf(" %d", &number_of_removed_teams);

    removed_teams = malloc(number_of_removed_teams * sizeof(team));
    all_teams = scanFileForTeams(fp, *number_of_teams, 0);

    for (team_index = 0; team_index < number_of_removed_teams; team_index++) {
      printf("Indtast det %d. holdnavn\n>> ", team_index + 1);
      scanf(" %[-':.,?!a-zA-Z0-9 ]", removed_teams[team_index].team);
    }

    removeTeams(removed_teams, all_teams, number_of_removed_teams, *number_of_teams);
    sortArrayByLevel(all_teams, *number_of_teams);
  }
  /* Hvis et hold kommer senere bedømmes turneringsplanen efter dette.
     Tager ikke højde for, hvis to hold vil komme senere.
     Der bliver først genereret et kampprogram, som passer til det første hold.
     Når der så skal genereres et kampprogram som passer til det andet hold,
     vil det overskrive det første kampprogram, og ikke tage højde for deres behov.
     (SKAL LIGE OVEREVEJES. evt. tilføje start- og sluttidspunkt i structet team.) */
  else if (choice == 3) {
    printf("Indtast holdnavnet på det hold der skal ændres\n>> ");
    scanf(" %[-':.,?!a-zA-Z0-9 ]", team);

    printf("Indtast startstidspunkt (med : mellem tallene)\n>> ");
    scanf(" %d:%d", &hour, &minute);

    if (hour > 60 || minute > 60) {
      printf("Ikke et gyldigt tidspunkt. Prøv igen.\n>> ");
      scanf(" %d:%d", &hour, &minute);
    }

    /* Kører ikke igen hvis der bliver tastet et bogstav. Bogstavet bliver læst som 0. */

    time = hour * 60 + minute;

    changeStartingTime(all_teams, team, *number_of_teams, time);
  }
  /* Hvis et hold kommer senere bedømmes turneringsplanen efter dette.
     Tager ikke højde for, hvis to hold vil afsted tidligere.
     Se kommentar fra l. 82. Det samme gælder for denne funktion. */
  else if (choice == 4) {
    printf("Indtast holdnavnet på det hold der skal ændres\n>> ");
    scanf(" %[-':.,?!a-zA-Z0-9 ]", team);

    printf("Indtast sluttidspunkt (med : mellem tallene)\n>> ");
    scanf(" %d:%d", &hour, &minute);

    if (hour > 60 || minute > 60) {
      printf("Ikke et gyldigt tidspunkt. Prøv igen.\n>> ");
      scanf(" %d:%d", &hour, &minute);
    }

    /* Kører ikke igen hvis der bliver tastet et bogstav. Bogstavet bliver læst som 0. */

    time = hour * 60 + minute;

    changeEndingTime(all_teams, team, *number_of_teams, time);
  }
  else if (choice == 0) {
    rewind(fp);
    *number_of_teams += (number_of_new_teams > 0) ? number_of_new_teams : -number_of_removed_teams;
    return all_teams;
  }
  else {
    printf("Ugyldigt svar. Prøv igen.\n>> ");
    editMenu(fp, all_teams, new_teams, removed_teams, number_of_teams);
  }

  rewind(fp);

  *number_of_teams += (number_of_new_teams > 0) ? number_of_new_teams : -number_of_removed_teams;
  return all_teams;
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
