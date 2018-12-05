/* Funktioner til at sammensætte hold i kampe, og kampe i runder */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
# include <time.h>
# include "../h-files/main.h"
# define NUMBER_OF_MATCHES 63
# define CHECK_NUM 100000


int createTournament_2(team *, const int, match *, const int, const int);
int evaluateRound(const match *, const int, const int, int *);
int is_already_in_round(const match *, const int, const int);
int is_in_previous_round(const match *, const int, const int);
int is_same_field(const match *, const int, const int);


int main(void){
  int i = 0;
  int number_of_teams = 20;
  int number_of_fields = 3;
  int no_go_count = 0;
  match tournament[NUMBER_OF_MATCHES];
  team all_teams[21];

  time_t t;
  /* Initialiserer rand. */
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

  /* Nulstil all_team.games, hvis funktionen skal køres mere end 1 gang. */

  /* Laver en turneringsplan, og returnerer antallet af gange planen bryder med reglerne. */
  no_go_count = createTournament_2(all_teams, number_of_teams, tournament, NUMBER_OF_MATCHES, number_of_fields);

  for (i = 0; i < NUMBER_OF_MATCHES; i++) {
    if (i % number_of_fields == 0 && i != 0) {
      printf("- - - - - - - - - - - - - - - - - - - - - - - - -\n");
      printf("%2d | %8s vs %-10s | %d\n", i + 1, tournament[i].team_a.team, tournament[i].team_b.team, tournament[i].field + 1);
    }

    else {
      printf("%2d | %8s vs %-10s | %d\n", i + 1, tournament[i].team_a.team, tournament[i].team_b.team, tournament[i].field + 1);
    }
  }

  printf("No_go_count: %d\n", no_go_count);

  return 0;
}

/* Laver en turneringsplan, som returnerer antallet af gange planen bryder med reglerne. */
int createTournament_2(team *all_teams, const int number_of_teams, match *tournament, 
                        const int number_of_matches, const int number_of_fields){
  int i = 0;
  int round_count = 0;
  int tournament_index = 0;
  int team_index = 0;
  int sentinel_count = 0;
  int sentinel_count_2 = 0;
  int grade = 0;
  int no_go_count = 0;
  int team_a[number_of_fields];
  int team_b[number_of_fields];

  /* Kører igennem hver runde. */
  for (round_count = 0; round_count < number_of_matches / number_of_fields; round_count++){
    /* Kører igennem kampene i en runde */
    for (i = 0, tournament_index = round_count * number_of_fields; tournament_index < (round_count + 1) * number_of_fields; tournament_index++){

      sentinel_count = 0;

      /* Finder et hold a. */
      while (sentinel_count < CHECK_NUM){
        team_index = rand() % number_of_teams;

        if (all_teams[team_index].games <= 6 && all_teams[team_index].level != 4){
          all_teams[team_index].games++;
          tournament[tournament_index].team_a = all_teams[team_index];
          tournament[tournament_index].field = tournament_index % number_of_fields;

          sentinel_count = CHECK_NUM;
          team_a[i] = team_index;
        }

        sentinel_count++;
      }

      sentinel_count = 0;

      /* Finder et hold b. */
      while (sentinel_count < CHECK_NUM){            
        team_index = (rand() + 1) % number_of_teams;

        if (all_teams[team_index].games <= 6 && all_teams[team_index].level == tournament[tournament_index].team_a.level && strcmp(tournament[tournament_index].team_a.team, all_teams[team_index].team) != 0){
          all_teams[team_index].games++;
          tournament[tournament_index].team_b = all_teams[team_index];

          sentinel_count = CHECK_NUM;
          team_b[i] = team_index;
          i++;
        }

        sentinel_count++;
      }
    }

    /* Tjekker om programmet overholder reglerne. */
    no_go_count = evaluateRound(tournament, tournament_index, number_of_fields, &grade);
    /* Hvis reglerne ikke overholder reglerne sammensættes runden på ny. */
    if (no_go_count > 0 && sentinel_count_2 != CHECK_NUM){
      round_count--;
      sentinel_count_2++;

      /* Sætter antallet af kampe tilbage til det den var før runden blev sammensat. */
      for (i = 0; i < number_of_fields; i++){
        all_teams[team_a[i]].games--;
        all_teams[team_b[i]].games--;
      }
    }
    else if (sentinel_count_2 == CHECK_NUM){
      return 100;
    }
  }


  return no_go_count;
}

int evaluateRound(const match *tournament, const int tournament_index, const int number_of_fields, int *grade){
  int i = 0, no_go_count = 0;
  int round_count = 0;

  round_count = tournament_index / number_of_fields;

  /* Kører igennem alle kampene i runden. */
  for (i = tournament_index - number_of_fields; i < tournament_index; i++){
    /* Kører hvis kampen allerede er i samme runde. */
    if (is_already_in_round(tournament, i, number_of_fields) == 1){
      no_go_count++;
    }
    /* Kører hvis det ikke er den første runde. */
    if (round_count != 0){
      no_go_count += is_in_previous_round(tournament, i, number_of_fields);
      printf("%d\n", no_go_count);
    }
    /* Hvis holdene ikke er i den forrige runde gives der en bedre karakter. */
    else if (round_count != 0){
      *grade += 2;
    }
  }

  return no_go_count;
}

/* Tjekker om et af holdene i en kamp allerede skal spille i runden. */
int is_already_in_round(const match *tournament, const int tournament_index, const int number_of_fields){
  int i = 0, start_of_round = 0;

  start_of_round = tournament_index - (tournament_index % number_of_fields);

  /* Kører igennem alle de forrige kampe i runden. */
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

/* Tjekker om et af holdene i en kamp har spillet i forrige runde. */
int is_in_previous_round(const match *tournament, const int match_index, const int number_of_fields) {
  int i = 0;
  int no_go_count = 0;
  int start_of_previous_round = 0;

  start_of_previous_round = match_index - ((match_index % number_of_fields) + number_of_fields);

  /* Kører igennem for hver kamp i runden før. */
  for (i = start_of_previous_round; i < match_index - (match_index % number_of_fields); i++) {
    /* Køres hvis der er et hold som også har spillet i runden før. */
    if (strcmp(tournament[i].team_a.team, tournament[match_index].team_a.team) == 0 ||
        strcmp(tournament[i].team_a.team, tournament[match_index].team_b.team) == 0 ||
        strcmp(tournament[i].team_b.team, tournament[match_index].team_a.team) == 0 ||
        strcmp(tournament[i].team_b.team, tournament[match_index].team_b.team) == 0) {
      /* Køres hvis holdet ikke spiller på samme bane. */
      if (is_same_field(tournament, match_index, number_of_fields) == 0){
        no_go_count++;
      }
    }
  }

  return no_go_count;
}

/* Tjekker om et hold spiller på den samme bane i begge runder. */
int is_same_field(const match *tournament, const int match_index, const int number_of_fields){
  if (strcmp(tournament[match_index - number_of_fields].team_a.team, tournament[match_index].team_a.team) == 0 &&
      strcmp(tournament[match_index - number_of_fields].team_b.team, tournament[match_index].team_b.team) != 0) {
    return 1;
  }
  else if(strcmp(tournament[match_index - number_of_fields].team_a.team, tournament[match_index].team_b.team) == 0 &&
      strcmp(tournament[match_index - number_of_fields].team_b.team, tournament[match_index].team_a.team) != 0){
    return 1;
  }
  else if (strcmp(tournament[match_index - number_of_fields].team_b.team, tournament[match_index].team_a.team) == 0 &&
           strcmp(tournament[match_index - number_of_fields].team_a.team, tournament[match_index].team_b.team) != 0){
    return 1;
  }
  else if (strcmp(tournament[match_index - number_of_fields].team_b.team, tournament[match_index].team_b.team) == 0 &&
           strcmp(tournament[match_index - number_of_fields].team_a.team, tournament[match_index].team_a.team) != 0){
    return 1;
  }

  return 0;
}




/**/
