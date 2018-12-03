#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../main.h"

void editMenu(team *, team *);

int main(void) {
  team *new_teams = NULL;
  team *removed_teams = NULL;

  editMenu(new_teams, removed_teams);

  return 0;
}

void editMenu(team *new_teams, team *removed_teams) {
  int i = 0;
  int n = 0;
  int time = 0;
  int hour = 0;
  int minute = 0;
  int number_of_added_teams = 0;
  int number_of_removed_teams = 0;
  char level = ' ';
  char team[MAX_NAME_LEN];

  printf("Hvad vil du gerne aendre?\n");
  printf("[1] Tilføj nyt hold\n"
         "[2] Slet eksisterende hold\n"
         "[3] Aendre startstidspunkt for et eksisterende hold\n"
         "[4] Aendre sluttidspunkt for et eksisterende hold\n"
         "[0] Afslut program\n");
  scanf(" %d", &n);

  /* Tilføjer et nyt hold */
  if (n == 1) {
    printf("Antal hold der oenskes at tilfoeje:\n");
    scanf(" %d", &number_of_added_teams);

    new_teams = malloc(number_of_added_teams * sizeof(team));

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
  /* Fjerner et eksisterende hold */
  else if (n == 2) {
    printf("Antal hold der oenskes at fjernes:\n");
    scanf(" %d", &number_of_removed_teams);

    removed_teams = malloc(number_of_removed_teams * sizeof(team));

    for (i = 0; i < number_of_removed_teams; i++) {
      printf("Indtast det %d. holdnavn:\n", i + 1);
      scanf(" %[-':.,?!a-zA-Z0-9 ]", removed_teams[i].team);

      /* KALD FUNKTION DER SAMMENLIGNER DET INDTASTEDE HOLDNAVN OG DET HOLDNAVN FRA FILEN. NIVEAU SKAL ERSTATTES MED 4. */
    }
  }
  /* Hvis et hold kommer senere bedømmes turneringsplanen efter dette. Tager ikke højde for, hvis to hold vil komme senere. Der bliver først genereret et kampprogram, som passer til det første hold. Når der så skal genereres et kampprogram som passer til det andet hold, vil det overskrive det første kampprogram, og ikke tage højde for deres behov. (SKAL LIGE OVEREVEJES. evt. tilføje start- og sluttidspunkt i structet team.) */
  else if (n == 3) {
    printf("Indtast holdnavnet på det hold der skal aendres:\n");
    scanf(" %[-':.,?!a-zA-Z0-9 ]", team);

    printf("Indtast startstidspunkt (med : mellem tallene):\n");
    scanf(" %d:%d", &hour, &minute);

    if (hour > 60 || minute > 60) {
      printf("Ikke et gyldigt tidspunkt. Prøv igen.\n");
      scanf(" %d:%d", &hour, &minute);
    }
  
    /* Kører ikke igen hvis der bliver tastet et bogstav. Bogstavet bliver læst som 0. */

    time = hour * 60 + minute;

    /* KØRER FUNKTION, HVOR DER SAMMENLIGNES MED ET HOLD. HOLDETS KAMPE BLIVER RYKKET SÅ DEN STARTER FRA ET SENERE TIDSPUNKT. */
  }
  /* Hvis et hold kommer senere bedømmes turneringsplanen efter dette. Tager ikke højde for, hvis to hold vil afsted tidligere. Se kommentar fra l. 82. Det samme gælder for denne funktion. */
  else if (n == 4) {
    printf("Indtast holdnavnet på det hold der skal aendres:\n");
    scanf(" %[-':.,?!a-zA-Z0-9 ]", team);

    printf("Indtast sluttidspunkt (med : mellem tallene):\n");
    scanf(" %d:%d", &hour, &minute);

    if (hour > 60 || minute > 60) {
      printf("Ikke et gyldigt tidspunkt. Prøv igen.\n");
      scanf(" %d:%d", &hour, &minute);
    }

    /* Kører ikke igen hvis der bliver tastet et bogstav. Bogstavet bliver læst som 0. */

    time = hour * 60 + minute;
    
    /* KØRER FUNKTION, HVOR DER SAMMENLIGNES MED ET HOLD. HOLDETS KAMPE BLIVER RYKKET SÅ DE SLUTTER PÅ ET TIDLIGERE TIDSPUNKT. */
  }
  else if (n == 0) {
    exit(0);
  }
  else {
    printf("Ugyldigt svar. Proev igen.\n");
    editMenu(new_teams, removed_teams);
  }
}
