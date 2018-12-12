/* Menu der spørger om brugeren vil redigere et eksisterende kampprogram, eller lave et nyt kampprogram */
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
  printf("           ______ ___   ___  ___   ___   ___ \n"      );
  printf("          /_  __// _ \\ |_  |/ _ \\ / _ \\ / _ \\\n"  );
  printf("           / /  / ___// __// // // // // // /\n"      );
  printf("          /_/  /_/   /____/\\___/ \\___/ \\___/\n"    );
  printf("                      Working title\n\n"              );

  while (choice != 0) {
    printMainMenu();
    scanf(" %d", &choice);
    /* Laver en ny turneringsplan fra bunden */
    if (choice == 1) {
      printf("\n");
      createNewTournament();
    }
    /* Opdaterer turneringsplanen */
    else if (choice == 2) {
      printf("\n");
      fp = fopen("turneringsplan.txt", "r");
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
void printMainMenu(void) {
  printf("#####################  HOVEDMENU  #####################\n\n");
  printf("[1] Lav et nyt kampprogram\n");
  printf("[2] Rediger et eksisterende kampprogram (!)\n");
  printf("[3] Lav skabelon til liste af holdnavne (!)\n");
  printf("[0] Afslut\n>> ");
}

/* Redigerings menu over hvilke muligheder der kan vælges, til at redigere et eksisterende kampprogram.
   Tager input fra brugen og derefter kalder passende funktioner i forhold til brugerens valg. */
team *editMenu(FILE *fp, team *all_teams, int *number_of_teams) {
  int choice = -1;
  int sentinel = 0;

    while (choice != 0) {
      /* printf("%d\n", *number_of_teams); */
      printEditMenu();
      scanf(" %d", &choice);

      if (choice == 1) {
        all_teams = addTeams(fp, sentinel, all_teams, number_of_teams);
        sentinel = 1;
      }
      else if (choice == 2) {
        all_teams = removeTeams(fp, sentinel, all_teams, number_of_teams);
        sentinel = 1;
      }
      else if (choice == 3) {
        return all_teams;
      }
      else if (choice == 0) {
        if (all_teams != NULL) {
          free(all_teams);
        }
        return NULL;
      }
      else {
        printf("Ugyldigt svar. Proev igen.\n");
      }
    }

  return NULL;
}

/* Printer valgmulighederne for redigerings menuen. */
void printEditMenu(void) {
  printf("######################  REDIGER  ######################\n\n");
  printf("Hvad vil du gerne aendre?\n");
  printf("[1] Tilføj nyt hold\n"
         "[2] Slet eksisterende hold\n"
         "[3] Lav nyt kampprogram\n"
         "[0] Gaa til hovedmenuen\n>> ");
}

/* Spørger brugeren om hvad der ønskes at gøre med turneringsplanen, og kalder relevante funktioner.
   Parameterne er turneringen i form af en pointer til array af matches, en int med starttidspunkt for turneringen
   en int med antallet af runder, og en int med antallet af baner */
int printingMenu(const match *tournament, const int starting_time, const int number_of_rounds, const int number_of_fields) {
  int choice = -1;

  while (choice != 0) {
    showPrintOptions();
    scanf(" %d", &choice);

    if (choice == 1) {  /* Se i terminalen */
      printProgram(stdout, tournament, starting_time, number_of_rounds, number_of_fields);
    }

    else if (choice == 2) { /* Gem kampprogram */
      FILE *fp;
      fp = fopen("turneringsplan.txt", "w");
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
void showPrintOptions(void) {
  printf("\n#####################    PRINT    #####################\n\n");
  printf("[1] Se kampprogram i terminalen \n[2] Gem kampprogram\n[0] Gå til hovedmenuen\n>> ");
}







  /*int team_index = 0;
  int time = 0;
  int hour = 0;
  int minute = 0;


  *number_of_teams = getNumberOfTeamsTournament(fp);*/

  /* Hvis et hold kommer senere bedømmes turneringsplanen efter dette.
     Tager ikke højde for, hvis to hold vil komme senere.
     Der bliver først genereret et kampprogram, som passer til det første hold.
     Når der så skal genereres et kampprogram som passer til det andet hold,
     vil det overskrive det første kampprogram, og ikke tage højde for deres behov.
     (SKAL LIGE OVEREVEJES. evt. tilføje start- og sluttidspunkt i structet team.) */
  /*else if (choice == 3) {
    printf("Indtast holdnavnet på det hold der skal ændres\n>> ");
    scanf(" %[-':.,?!a-zA-Z0-9 ]", team);

    printf("Indtast startstidspunkt (med : mellem tallene)\n>> ");
    scanf(" %d:%d", &hour, &minute);

    if (hour > 60 || minute > 60) {
      printf("Ikke et gyldigt tidspunkt. Prøv igen.\n>> ");
      scanf(" %d:%d", &hour, &minute);
    }*/

    /* Kører ikke igen hvis der bliver tastet et bogstav. Bogstavet bliver læst som 0. */

  /*  time = hour * 60 + minute;

    changeStartingTime(all_teams, team, *number_of_teams, time);
  }*/
  /* Hvis et hold kommer senere bedømmes turneringsplanen efter dette.
     Tager ikke højde for, hvis to hold vil afsted tidligere.
     Se kommentar fra l. 82. Det samme gælder for denne funktion. */
  /*else if (choice == 4) {
    printf("Indtast holdnavnet på det hold der skal ændres\n>> ");
    scanf(" %[-':.,?!a-zA-Z0-9 ]", team);

    printf("Indtast sluttidspunkt (med : mellem tallene)\n>> ");
    scanf(" %d:%d", &hour, &minute);

    if (hour > 60 || minute > 60) {
      printf("Ikke et gyldigt tidspunkt. Prøv igen.\n>> ");
      scanf(" %d:%d", &hour, &minute);
    }
*/
    /* Kører ikke igen hvis der bliver tastet et bogstav. Bogstavet bliver læst som 0. */
/*
    time = hour * 60 + minute;

    changeEndingTime(all_teams, team, *number_of_teams, time);
  }
  else if (choice == 0) {
    rewind(fp);
    *number_of_teams += (number_of_new_teams > 0) ? number_of_new_teams : 0;
    return all_teams;
  }
  else {

  }

  rewind(fp);

  *number_of_teams += (number_of_new_teams > 0) ? number_of_new_teams : 0;
  return all_teams;
}*/
