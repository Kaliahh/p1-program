/* Allokerer plads til et array af structs med hold */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../main.h"

team* allocateSpaceForTeam(int n);

int main (void) {
  int number_of_teams = 20;
  team *all_teams = allocateSpaceForTeam(number_of_teams);

  printf("%d\n", sizeof(team));

  strcpy(all_teams[19].team, "hold 1");
  all_teams[19].games = 6;
  all_teams[19].level = 2;
  printf("%s, %d, %d\n", all_teams[19].team, all_teams[19].games, all_teams[19].level);
  printf("%s, %d, %d\n", all_teams[20].team, all_teams[20].games, all_teams[20].level);

  &all_teams + 30;
  free(all_teams);

  return 0;
}

/* Allokerer plads til et array af structs med hold.
   Returnerer pointer til arrayet */
team* allocateSpaceForTeam (int n) {
  team * all_teams = malloc(n * sizeof(team)); /* Allokerer plads */
  if(all_teams != NULL) { /* Returner pointer, hvis der kunne allokeres plads */
    return all_teams;
  }
  else { /* Fejlhåndtering, hvis der ikke kunne allokeres plads */
    printf("Der skete en fejl under pladsallokeringen \n");
    return all_teams;
  }
}
