/* Menu der spørger om brugeren vil redigere et eksisterende kampprogram, eller lave et nyt kampprogram */
# include "../p1-program/h-files/main.h"
# include "../p1-program/h-files/tournament.h"
# include "../p1-program/h-files/menus.h"
# include "../p1-program/h-files/printPrompt.h"
# include "../p1-program/h-files/memoryAllocationScanningSorting.h"
# include <time.h>

int main(void) {
  time_t t;

  /* Initialiserer rand */
  srand(time(&t));

  mainMenu();

  return 0;
}

/* Hovedmenuen til programmet */
int mainMenu(void) {
  int choice = -1;
  FILE *fp = NULL;

  printf("           ______ ___   ___  ___   ___   ___ \n");
  printf("          /_  __// _ \\ |_  |/ _ \\ / _ \\ / _ \\\n");
  printf("           / /  / ___// __// // // // // // /\n");
  printf("          /_/  /_/   /____/\\___/ \\___/ \\___/\n");
  printf("                      Working title\n\n");



  while (choice != 0) {
    printMainMenu();
    scanf(" %d", &choice);

    if (choice == 1) {
      printf("\n");
      createNewTournament();
    }

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

/* Printer valgmulighederne for hovedmenuen */
void printMainMenu(void) {
  printf("#####################  HOVEDMENU  #####################\n\n");
  printf("[1] Lav et nyt kampprogram\n");
  printf("[2] Rediger et eksisterende kampprogram (!)\n");
  printf("[3] Lav skabelon til liste af holdnavne (!)\n");
  printf("[0] Afslut\n>> ");
}

/* Funktioner til ændringer af eksisterende kampprogram. Skal deles op i flere funktioner */
int editMenu(FILE *fp, team *all_teams, int *number_of_teams) {
  int choice = -1;

    printEditMenu();
    scanf(" %d", &choice);

    if (choice == 1){
      addTeams(fp, all_teams, number_of_teams);
    }
    else if (choice == 2){
      removeTeams(fp, all_teams, number_of_teams);
    }
    else if (choice == 0){
      return 0;
    }
    else {
      printf("Ugyldigt svar. Proev igen.\n");
      editMenu(fp, all_teams, number_of_teams);
    }
  printf("test\n");
  return 0;
}

void printEditMenu(void){

  printf("######################  REDIGER  ######################\n\n");
  printf("Hvad vil du gerne aendre?\n");
  printf("[1] Tilføj nyt hold\n"
         "[2] Slet eksisterende hold\n"
         "[0] Gaa til hovedmenuen\n>> ");
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
