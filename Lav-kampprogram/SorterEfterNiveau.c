/* Sorter et array af hold efter niveau */

/*# include <stdio.h>
# include <stdlib.h>
#include <string.h>
# include "../main.h"

void SortArrayByLevel(team *all_teams, int number_of_teams);
int comp (const void *a, const void*b);

int main(void) {
  int number_of_teams = 5;
  team all_teams[5];

  all_teams[0].level = 0;
  all_teams[1].level = 4;
  all_teams[2].level = 3;
  all_teams[3].level = 2;
  all_teams[4].level = 3;

  strcpy(all_teams[0].team, "Hold 1");
  strcpy(all_teams[1].team, "Hold 2");
  strcpy(all_teams[2].team, "Hold 3");
  strcpy(all_teams[3].team, "Hold 4");
  strcpy(all_teams[4].team, "Hold 5");

  SortArrayByLevel(all_teams, number_of_teams);

  for (int i = 0; i <=4; i++){
    printf("team %s: level %d\n", all_teams[i].team, all_teams[i].level);
  }
  return 0;
}*/


void SortArrayByLevel(team *all_teams, int number_of_teams){

  qsort(all_teams, number_of_teams, sizeof(team), comp);

}

int comp (const void *a, const void*b){
  team *team_a = (team*) a;
  team *team_b = (team*) b;

  return team_a->level - team_b->level;
}
