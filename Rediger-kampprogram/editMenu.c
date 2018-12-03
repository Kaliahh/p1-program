#include <stdio.h>
#include <stdlib.h>
#include "../main.h"

void editMenu (void);

int main(void) {

  editMenu();

  return 0;
}

void editMenu (void) {
  int i = 0;
  int n = 0;
  int number_of_added_teams = 0;
  int number_of_removed_teams = 0;
  char level = ' ';
  char team[MAX_NAME_LEN];
  team *new_teams;
  team *removed_teams;

  printf("Hvad vil du gerne aendre?\n");
  printf("[1] Tilføj nyt hold\n"
         "[2] Slet eksisterende hold\n"
         "[3] Aendre startstidspunkt for et eksisterende hold\n"
         "[4] Aendre sluttidspunkt for et eksisterende hold\n"
         "[0] Afslut program\n");
  scanf(" %d", &n);

  if (n == 1) {
    printf("Antal hold der oenskes at tilfoeje:\n");
    scanf(" %d", &number_of_added_teams);

    new_teams = (team *) calloc (number_of_added_teams, sizeof(team));

    for (i = 0; i < number_of_added_teams; i++) {
      printf("Indtast det %d. holdnavn:\n", i + 1);
      scanf(" %[-':.,?!a-zA-Z0-9 ]", new_teams[i].team);

      printf("Indtast det %d. holds niveau (med blokbogstaver):\n", i + 1);
      scanf(" %c", &level);

      new_teams[i].level = (level == 'N') ? N :
                           (level == 'A') ? A :
                           (level == 'B') ? B :
                           (level == 'C') ? C : EMPTY;

      while (new_teams[i].level == EMPTY) {
        printf("%d. holds niveau er ikke gyldigt. Prøv igen.\n", i + 1);
        scanf(" %c", &level);

        new_teams[i].level = (level == 'N') ? N :
                             (level == 'A') ? A :
                             (level == 'B') ? B :
                             (level == 'C') ? C : EMPTY;
      }
    }

    /* KALD FUNKTION, SOM KØRER algoritmen FRA STARTEN AF MED DE TILFØJEDE HOLD. */
  }
  else if (n == 2) {
    printf("Antal hold der oenskes at fjernes:\n");
    scanf(" %d", &number_of_removed_teams);

    removed_teams = (team *) calloc (number_of_removed_teams, sizeof(team));

    for (i = 0; i < number_of_removed_teams; i++) {
      printf("Indtast det %d. holdnavn:\n", i + 1);
      scanf(" %[-':.,?!a-zA-Z0-9 ]", removed_teams[i].team);

      /* KALD FUNKTION DER SAMMENLIGNER DET INDTASTEDE HOLDNAVN OG DET HOLDNAVN FRA FILEN. NIVEAU SKAL ERSTATTES MED 4. */
    }
  }
  else if (n == 3) {
    printf("Indtast holdnavnet på det hold der skal aendres:\n");
    scanf(" %[-':.,?!a-zA-Z0-9 ]", team);

    /* KØRER FUNKTION, HVOR DER SAMMENLIGNES MED ET HOLD. HOLDETS KAMPE BLIVER RYKKET SÅ DEN STARTER FRA ET SENERE TIDSPUNKT. */
  }
  else if (n == 4) {
    printf("Indtast holdnavnet på det hold der skal aendres:\n");
    scanf(" %[-':.,?!a-zA-Z0-9 ]", team);

    /* KØRER FUNKTION, HVOR DER SAMMENLIGNES MED ET HOLD. HOLDETS KAMPE BLIVER RYKKET SÅ DE SLUTTER PÅ ET TIDLIGERE TIDSPUNKT. */
  }
  else if (n == 0) {
    exit(0);
  }
  else {
    printf("Ugyldigt svar. Proev igen.\n");
    editMenu();
  }
}
