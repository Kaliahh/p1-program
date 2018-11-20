/* Allokerer plads til et array af structs med hold */
#include <stdio.h>
#include <stdlib.h>
#include "../main.h"

team* allocateSpaceForTeam(int n);

int main (void) {
  int number_of_teams = 20, length = 0;
  team *all_teams = allocateSpaceForTeam(number_of_teams);

  length = sizeof(all_teams)/sizeof(team);

  printf("%d\n", length);

  free(all_teams);

  return 0;
}

team* allocateSpaceForTeam (int n) {
  team* all_teams = (team*) calloc(n, sizeof(team));

  return all_teams;
}
