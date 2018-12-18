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
   Tager input fra brugen og derefter kalder passende funktioner i forhold til brugerens valg. */
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
    /* Laver en ny stævneplan fra bunden */
    if (choice == 1) {
      printf("\n");
      createNewTournament();
    }
    /* Opdaterer stævneplanen */
    else if (choice == 2) {
      printf("\n");
      fp = fopen("staevneplan.txt", "r");
      isFileOpen(fp);
      updateTournament(fp);
      fclose(fp);
    }

    else if (choice == 3) {
      printf("\n");
      createTemplate();
    }

    else if (choice == 0) {
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

int createMenu(void) {
  int choice = -1;

  while (choice != 0) {
    printf("\n");
    showCreateMenu();
    scanf(" %d", &choice);

    if (choice == 1) { /* Hurtigt plan */
      return 1;
    }
    else if (choice == 2) { /* Fejlfri plan */
      return 2;
    }
    else if (choice == 0) { /* Tilbage til hovedmenuen */
      return 0;
    }
    else {
      printf("\nUgyldigt input, proev igen\n");
    }
  }

  return 0;
}

void showCreateMenu(void) {
  printf("################  LAV NY STAEVNEPLAN  #################\n\n");
  printf("[1] Hurtig staevneplan\n"
         "[2] Bedste staevneplan\n"
         "[0] Afslut\n>> ");
}

/* Redigerings menu over hvilke muligheder der kan vælges, til at redigere en eksisterende stævneplan.
   Tager input fra brugen og derefter kalder passende funktioner i forhold til brugerens valg. */
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

/* Spørger brugeren om hvad der ønskes at gøre med stævneplanen, og kalder relevante funktioner.
   Parameterne er turneringen i form af en pointer til array af matches, en int med starttidspunkt for turneringen
   en int med antallet af runder, og en int med antallet af baner */
int printingMenu(const match *tournament, const int starting_time, const int number_of_rounds, const int number_of_fields) {
  int choice = -1;

  while (choice != 0) {
    showPrintingMenu();
    scanf(" %d", &choice);

    if (choice == 1) {  /* Se i terminalen */
      printProgram(stdout, tournament, starting_time, number_of_rounds, number_of_fields);
    }

    else if (choice == 2) { /* Gem stævneplan */
      FILE *fp;
      fp = fopen("staevneplan.txt", "w");
      isFileOpen(fp);
      printProgram(fp, tournament, starting_time, number_of_rounds, number_of_fields);
      fclose(fp);
    }

    else if (choice == 0) { /* Gå til hovedmenu */
      return 0;
    }

    else {
      printf("Fejl ved indtastning. Tast 1 eller 2\n>> ");
    }
  }
  return 0;
}

/* Viser valgmuligheder ved print i terminalen */
void showPrintingMenu(void) {
  printf("\n######################  PRINT  ######################\n\n");
  printf("[1] Se staevneplan i terminalen \n[2] Gem staevneplan\n[0] Gå til hovedmenuen\n>> ");
}
