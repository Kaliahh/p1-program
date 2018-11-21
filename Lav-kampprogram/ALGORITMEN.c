/* Funktioner til at sammensætte hold i kampe, og kampe i runder */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
# include "../main.h"
# define MAX 30


typedef struct{
  char team_a[MAX];
  char team_b[MAX];
  int level;
} match;

match *createMatches (team *all_teams, match *all_matches, int number_of_teams);


int main(void) {
  int i = 0, number_of_teams = 11;
  team all_teams[11];
  match *all_matches;

  all_teams[0].level = 1;
  all_teams[1].level = 1;
  all_teams[2].level = 1;
  all_teams[3].level = 0;
  all_teams[4].level = 0;
  all_teams[5].level = 0;
  all_teams[6].level = 0;
  all_teams[7].level = 0;
  all_teams[8].level = 0;
  all_teams[9].level = 0;
  all_teams[10].level = 0;

  all_teams[0].games = 0;
  all_teams[1].games = 0;
  all_teams[2].games = 0;
  all_teams[3].games = 0;
  all_teams[4].games = 0;
  all_teams[5].games = 0;
  all_teams[6].games = 0;
  all_teams[7].games = 0;
  all_teams[8].games = 0;
  all_teams[9].games = 0;
  all_teams[10].games = 0;

  strcpy(all_teams[0].team, "Hold 1");
  strcpy(all_teams[1].team, "Hold 2");
  strcpy(all_teams[2].team, "Hold 3");
  strcpy(all_teams[3].team, "Hold 4");
  strcpy(all_teams[4].team, "Hold 5");
  strcpy(all_teams[5].team, "Hold 6");
  strcpy(all_teams[6].team, "Hold 7");
  strcpy(all_teams[7].team, "Hold 8");
  strcpy(all_teams[8].team, "Hold 9");
  strcpy(all_teams[9].team, "Hold 10");
  strcpy(all_teams[10].team, "Hold 11");

  all_matches = (match*) calloc(100, sizeof(match));

  all_matches = createMatches(all_teams, all_matches, number_of_teams);

  for (i = 0; i <= 65; i++){
    printf("%s vs %s\n", all_matches[i].team_a, all_matches[i].team_b);
  }
  for (i = 0; i < 11; i++){
    printf("Hold %d: %d kampe\n", i+1, all_teams[i].games);
  }

  return 0;
}


match *createMatches (team *all_teams, match *all_matches, int number_of_teams){
  int i = 0, j = 0, match_count = 0;
  int number_of_matches = (6 * number_of_teams) / 2 - 1;

  for (i = 0; i < number_of_teams; i++){
    //number_of_matches = (6 * (number_of_teams - i)) / 2;
    for (j = 0; all_teams[i].games < 6 && match_count < number_of_matches; j = ((j + 1) % number_of_teams)){
      printf("i = %d   j = %d\n", i, j);

      if (all_teams[i].level == all_teams[j].level && all_teams[i].team != all_teams[j].team && all_teams[j].games < 6){

        strcpy(all_matches[match_count].team_a, all_teams[i].team);
        strcpy(all_matches[match_count].team_b, all_teams[j].team);
        all_matches[match_count].level = all_teams[i].level;

        all_teams[i].games++;
        all_teams[j].games++;
        match_count++;
      }
    }
  }

  return all_matches;

}


/*  (antal kampe pr hold) * (antal hold) / 2   */




/* Udregn number_of_teams (linie 78) med sizeof(all_teams). Virker ikke */
/* Hvis der er et ulige antal hold kan ikke alle spille 6 kampe. Loopet (linie 81) bliver uendelig fordi der ikke er nogen hold at spille med til det sidste hold. Tror jeg*/
