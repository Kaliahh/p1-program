/* Funktioner til at sammensætte hold i kampe, og kampe i runder */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
# include <time.h>
# include "../h-files/main.h"
# define NUMBER_OF_MATCHES 63

/* Struct for en kamp */
typedef struct{
  team team_a;
  team team_b;
  int level;
  int field;
} match_2;

void createNewTournament(team *, int, match_2 *, int, int);
int evaluateRound(match_2 *, int, int, int *);
int is_already_in_round(match_2 *, int, int);
int is_in_previous_round(match_2 *, int, int);
int is_same_field(match_2 *, int, int);


int main(void){
  int number_of_teams = 21;
  int number_of_fields = 2;
  match_2 tournament[NUMBER_OF_MATCHES];
  team all_teams[21];

  time_t t;
  /* initialiserer rand */
  srand(time(&t));

  all_teams[0].level = 0;
  all_teams[1].level = 0;
  all_teams[2].level = 0;
  all_teams[3].level = 0;
  all_teams[4].level = 0;
  all_teams[5].level = 0;
  all_teams[6].level = 0;
  all_teams[7].level = 0;
  all_teams[8].level = 0;
  all_teams[9].level = 0;
  all_teams[10].level = 1;
  all_teams[11].level = 1;
  all_teams[12].level = 1;
  all_teams[13].level = 1;
  all_teams[14].level = 1;
  all_teams[15].level = 1;
  all_teams[16].level = 1;
  all_teams[17].level = 1;
  all_teams[18].level = 1;
  all_teams[19].level = 1;
  all_teams[20].level = 1;

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
  all_teams[11].games = 0;
  all_teams[12].games = 0;
  all_teams[13].games = 0;
  all_teams[14].games = 0;
  all_teams[15].games = 0;
  all_teams[16].games = 0;
  all_teams[17].games = 0;
  all_teams[18].games = 0;
  all_teams[19].games = 0;
  all_teams[20].games = 0;

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
  strcpy(all_teams[11].team, "Hold 12");
  strcpy(all_teams[12].team, "Hold 13");
  strcpy(all_teams[13].team, "Hold 14");
  strcpy(all_teams[14].team, "Hold 15");
  strcpy(all_teams[15].team, "Hold 16");
  strcpy(all_teams[16].team, "Hold 17");
  strcpy(all_teams[17].team, "Hold 18");
  strcpy(all_teams[18].team, "Hold 19");
  strcpy(all_teams[19].team, "Hold 20");
  strcpy(all_teams[20].team, "Hold 21");

  createNewTournament(all_teams, number_of_teams, tournament, NUMBER_OF_MATCHES, number_of_fields);

  return 0;
}


void createNewTournament(team *all_teams, int number_of_teams, match_2 *tournament, int number_of_matches, int number_of_fields){
  int round_count = 0, tournament_index = 0, team_index = 0, sentinel = 0, sentinel_count = 0, grade = 0;

  for (round_count = 0; round_count < number_of_matches / number_of_fields; round_count++){
    printf("r_i: %d\n", round_count);
    for (tournament_index = round_count * number_of_fields; tournament_index < (round_count + 1) * number_of_fields; tournament_index++){
      printf("T_I: %d\n", tournament_index);

      sentinel = 0;

      while (sentinel == 0){
        team_index = rand() % number_of_teams;

        if (all_teams[team_index].games <= 6 && all_teams[team_index].level != 4){
          all_teams[team_index].games++;
          tournament[tournament_index].team_a = all_teams[team_index];
          tournament[tournament_index].field = tournament_index % number_of_fields;

          sentinel++;
        }
      }

      sentinel = 0;

      while (sentinel == 0){            /* Sidder nogle gange fast her... */
        team_index = rand() % number_of_teams;

        if (all_teams[team_index].games <= 6 && all_teams[team_index].level == tournament[tournament_index].team_a.level){
          all_teams[team_index].games++;
          tournament[tournament_index].team_b = all_teams[team_index];

          sentinel++;
        }
      }
    }

    if (evaluateRound(tournament, tournament_index, number_of_fields, &grade) > 0 && sentinel_count < 10){
      round_count--;
      sentinel_count++;
    }
  }
}

int evaluateRound(match_2 *tournament, int tournament_index, int number_of_fields, int *grade){
  int i = 0, no_go_count = 0;

  for (i = tournament_index - number_of_fields; i < tournament_index; i++){
    if (is_already_in_round (tournament, i, number_of_fields) == 1){
      no_go_count++;
    }
    if (is_in_previous_round (tournament, i, number_of_fields) == 1){
      if (is_same_field (tournament, i, number_of_fields) == 0){
        no_go_count++;
      }
    }
    else {
      *grade += 2;
    }
  }

  return no_go_count;
}

int is_already_in_round(match_2 *tournament, int tournament_index, int number_of_fields){
  int i = 0, start_of_round = 0;

  start_of_round = tournament_index - (tournament_index % number_of_fields);

  for (i = start_of_round; i < tournament_index; i++) {
    if (strcmp(tournament[i].team_a.team, tournament[tournament_index].team_a.team) == 0 ||
        strcmp(tournament[i].team_a.team, tournament[tournament_index].team_b.team) == 0 ||
        strcmp(tournament[i].team_b.team, tournament[tournament_index].team_a.team) == 0 ||
        strcmp(tournament[i].team_b.team, tournament[tournament_index].team_b.team) == 0) {
      return 1;
    }
  }

  return 0;
}

int is_in_previous_round(match_2 *tournament, int tournament_index, int number_of_fields) {
  int i = 0, start_of_previous_round = 0;

  start_of_previous_round = tournament_index - ((tournament_index % number_of_fields) + number_of_fields);

  for (i = start_of_previous_round; i < tournament_index - (tournament_index % number_of_fields); i++) {
    if (strcmp(tournament[i].team_a.team, tournament[tournament_index].team_a.team) == 0 ||
        strcmp(tournament[i].team_a.team, tournament[tournament_index].team_b.team) == 0 ||
        strcmp(tournament[i].team_b.team, tournament[tournament_index].team_a.team) == 0 ||
        strcmp(tournament[i].team_b.team, tournament[tournament_index].team_b.team) == 0) {
      return 1;
    }
  }

  return 0;
}

int is_same_field(match_2 *tournament, int tournament_index, int number_of_fields){
  if (tournament[tournament_index].field == tournament[tournament_index - number_of_fields].field) {
    return 1;
  }

  return 0;
}






/**/
