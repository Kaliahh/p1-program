/* Allokerer plads til et array af structs med hold */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../main.h"

/* Prototyper */
team* allocateSpaceForTeam(int);
match* allocateSpaceForMatch (int);

int main (void) {
  int number_of_teams = 20;
  team *all_teams = allocateSpaceForTeam(number_of_teams);
  match *all_matches = allocateSpaceForMatch(number_of_teams);

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

/* Allokerer plads til et array af structs med kampe.
   Returnerer pointer til arrayet */
match* allocateSpaceForMatch (int n) {
  match * all_matches = malloc(n * sizeof(match)); /* Allokerer plads */
  if(all_matches != NULL) { /* Returner pointer, hvis der kunne allokeres plads */
    return all_matches;
  }
  else { /* Fejlhåndtering, hvis der ikke kunne allokeres plads */
    printf("Der skete en fejl under pladsallokeringen \n");
    return all_matches;
  }
}
