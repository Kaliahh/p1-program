/* Menu der spørger om brugeren vil redigere en eksisterende stævneplan, eller lave en ny stævneplan */
# include "../p1-program/h-files/main.h"
# include "../p1-program/h-files/tournament.h"
# include "../p1-program/h-files/menus.h"
# include "../p1-program/h-files/printPrompt.h"
# include "../p1-program/h-files/memoryAllocationScanningSorting.h"
# include <time.h>

int main(void) {
  time_t t;

  /* Initialiserer rand. */
  srand(time(&t));

  mainMenu();

  return 0;
}

/* Hovedmenuen til programmet.
   Tager input fra brugen og kalder derefter funktioner i forhold til brugerens valg. */
int mainMenu(void) {
  int choice = -1;
  FILE *fp = NULL;

  /* Printer navn på programmet. */
  /* (Teksten er genereret af http://patorjk.com/software/taag/ ) */
  printf("             _____ ____ ___  ____  ____  ____        \n");
  printf("            / ___// __ \\__ \\/ __ \\/ __ \\/ __ \\  \n");
  printf("            \\__ \\/ /_/ /_/ / / / / / / / / / /     \n");
  printf("           ___/ / ____/ __/ /_/ / /_/ / /_/ /        \n");
  printf("          /____/_/   /____|____/\\____/\\____/       \n");
  printf("                                                     \n");
  printf("        Stævneplanlægning til Kidzliga Floorball\n   \n");

  while (choice != 0) {
    showMainMenu();
    scanf(" %d", &choice);

    if (choice == 1) { /* Lav stævneplan fra bunden */
      printf("\n");
      createNewTournament();
    }
    else if (choice == 2) { /* Opdater eksisterende stævneplan */
      printf("\n");
      fp = fopen("staevneplan.txt", "r");
      isFileOpen(fp);
      updateTournament(fp);
      fclose(fp);
    }
    else if (choice == 0) { /* Gå tilbage til hovedmenuen */
      printf("\n");
      printf("Farvel!\n");
    }
    else {
      printf("\nUgyldigt input, proev igen\n");
    }
  }

  return 0;
}

/* Printer valgmulighederne for hovedmenuen. */
void showMainMenu(void) {
  printf("#####################  HOVEDMENU  #####################\n\n");
  printf("[1] Lav en ny staevneplan\n"
         "[2] Rediger en eksisterende staevneplan\n"
         "[3] Lav skabelon til liste af holdnavne (!)\n"
         "[0] Afslut\n>> ");
}

/* Menu til valg af metode til generering af stævneplan */
int createMenu(void) {
  int choice = -1;

  while (choice != 1 && choice != 2) {
    printf("\n");
    showCreateMenu();
    scanf(" %d", &choice);

    if (choice == 1) { /* Hurtigt plan */
      return 1;
    }
    else if (choice == 2) { /* Fejlfri plan */
      return 2;
    }
    else {
      printf("\nUgyldigt input, proev igen\n");
    }
  }

  return 0;
}

/* Printer valgmulighederne af metoder */
void showCreateMenu(void) {
  printf("################  LAV NY STAEVNEPLAN  #################\n\n");
  printf("[1] Hurtig staevneplan\n"
         "[2] Bedste staevneplan\n>> ");
}

/* Redigerings menu. Brugeren vælger om der skal tilføjes eller fjernes hold fra en eksisterende stævneplan.
   Tager input fra brugen og kalder funktioner i forhold til brugerens valg. */
team *editMenu(FILE *fp, team *all_teams, int *number_of_teams) {
  int choice = -1;

  /* Scanner holdnavne og niveau ind fra filen med stævneplanen */
  all_teams = scanFileForTeams(fp, *number_of_teams);

    while (choice != 0) {
      showEditMenu();
      scanf(" %d", &choice);

      if (choice == 1) { /* Tilføj hold */
        all_teams = modifyTeams(copyTeams, ADD, all_teams, number_of_teams);
      }
      else if (choice == 2) { /* Fjern hold */
        all_teams = modifyTeams(deleteTeams, REMOVE, all_teams, number_of_teams);
      }
      else if (choice == 3) { /* Generer ny stævneplan */
        return all_teams;
      }
      else if (choice == 999) { /* Debug */
        printTeams(all_teams, *number_of_teams);
      }
      else if (choice == 0) { /* Gå tilbage til hovedmenuen */
        if (all_teams != NULL) {
          free(all_teams);
        }
        return NULL;
      }
      else {
        printf("\nUgyldigt input, proev igen\n");
      }
    }

  return NULL;
}

/* Printer valgmulighederne for redigerings menuen. */
void showEditMenu(void) {
  printf("######################  REDIGER  ######################\n\n");
  printf("Hvad vil du gerne aendre?\n");
  printf("[1] Tilføj hold\n"
         "[2] Slet eksisterende hold\n"
         "[3] Lav ny staevneplan\n"
         "[0] Gaa til hovedmenuen\n>> ");
}

/* Print menu. Brugeren vælger om stævneplanen skal printes i terminalen,
   eller gemmes i "staevneplan.txt" */
int printingMenu(const match *tournament, const int starting_time, const int number_of_rounds, const int number_of_fields) {
  int choice = -1;
  FILE *fp = NULL;

  while (choice != 0) {
    showPrintingMenu();
    scanf(" %d", &choice);

    if (choice == 1) {  /* Se stævneplan i terminalen */
      printProgram(stdout, tournament, starting_time, number_of_rounds, number_of_fields);
    }

    else if (choice == 2) { /* Gem stævneplan */
      fp = fopen("staevneplan.txt", "w");
      isFileOpen(fp);
      printProgram(fp, tournament, starting_time, number_of_rounds, number_of_fields);
      fclose(fp);
    }

    else if (choice == 0) { /* Gå til hovedmenu */
      return 0;
    }

    else {
      printf("\nUgyldigt input, proev igen\n");
    }
  }
  return 0;
}

/* Viser valgmuligheder ved print i terminalen */
void showPrintingMenu(void) {
  printf("\n######################  PRINT  ######################\n\n");
  printf("[1] Se staevneplan i terminalen\n"
         "[2] Gem staevneplan\n"
         "[0] Gå til hovedmenuen\n>> ");
}
