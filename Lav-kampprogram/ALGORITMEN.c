/* Funktioner til at sammensætte hold i kampe, og kampe i runder */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
# include <time.h>
# include "../h-files/main.h"
# define NUMBER_OF_TEAMS 21

int createMatches (team *, match *, int);
int createMatchesByLevel (team *, match *, int, int);
int compareMatches (const match match_a, const match match_b);
int evaluateTournament(match *, const int, const int);

void switchMatches(match *tournament, const int number_of_matches, const int number_of_fields);

void createTournament(const match *, const int, const int, match *);
void copyMatches(const match *, const int, match *);
void resetFields(const int, match *);

int main(void) {
  int i = 0, number_of_teams = NUMBER_OF_TEAMS;
  int number_of_fields = 2;
  int number_of_matches = (6 * number_of_teams) / 2;
  int grade = -1;
  int temp_grade = 0;
  team all_teams[NUMBER_OF_TEAMS];
  match *all_matches;
  match *tournament;  /* antal runder = antal kampe / antal baner */
  match *temp_tournament;

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

  all_matches = malloc(number_of_matches * sizeof(match));

  createMatches(all_teams, all_matches, number_of_teams);

  for (i = 0; i < (3 * number_of_teams); i++) {
    printf("%s vs %s\n", all_matches[i].team_a, all_matches[i].team_b);
  }

  printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n");

  for (i = 0; i < NUMBER_OF_TEAMS; i++){
    printf("Hold %d: %d kampe\n", i+1, all_teams[i].games);
  }

  tournament = malloc(number_of_matches * sizeof(match));
  temp_tournament = malloc(number_of_matches * sizeof(match));

  resetFields(number_of_matches, all_matches);

  for (int noget = 0; noget < 1000000; noget++) {
    createTournament(all_matches, number_of_matches, number_of_fields, temp_tournament);

    temp_grade = evaluateTournament(temp_tournament, number_of_matches, number_of_fields);

    if (temp_grade >= 0 && temp_grade > grade) { /* Check om turneringen er gyldig, og bedre (højere) end den bedste */
      copyMatches(temp_tournament, number_of_matches, tournament);
      grade = temp_grade;
    }

  }

  copyMatches(tournament, number_of_matches, temp_tournament);

  for(i = 0; i < 10; i++){
    switchMatches(temp_tournament, number_of_matches, number_of_fields);
  }
  temp_grade = evaluateTournament(temp_tournament, number_of_matches, number_of_fields);
  if(temp_grade > grade){
    printf("Ja, vi gjorde det\n");
  }
  else{
    printf("No\n");
  }

  printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n");

  for (i = 0; i < number_of_matches; i++) {
    if (i % number_of_fields == 0 && i != 0) {
      printf("- - - - - - - - - - - - - - - - - - - - - - - - -\n");
      printf("%2d | %8s vs %-10s | %d\n", i + 1, tournament[i].team_a, tournament[i].team_b, tournament[i].field);
    }

    else {
      printf("%2d | %8s vs %-10s | %d\n", i + 1, tournament[i].team_a, tournament[i].team_b, tournament[i].field);
    }
  }

  printf("Grade: %d\n", grade);

  printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n");

  for (i = 0; i < number_of_matches; i++) {
    if (i % number_of_fields == 0 && i != 0) {
      printf("- - - - - - - - - - - - - - - - - - - - - - - - -\n");
      printf("%2d | %8s vs %-10s | %d\n", i + 1, temp_tournament[i].team_a, temp_tournament[i].team_b, tournament[i].field);
    }

    else {
      printf("%2d | %8s vs %-10s | %d\n", i + 1, temp_tournament[i].team_a, temp_tournament[i].team_b, tournament[i].field);
    }
  }

  printf("Grade: %d\n", temp_grade);

  return 0;
}


int createMatches (team *all_teams, match *all_matches, int number_of_teams) {
  int i = 0, match_count = 0;
  int N_counter = 0, A_counter = 0, B_counter = 0, C_counter = 0;
  int team_pointer = 0;

  /* Tæl antallet af hold i hver niveau */
  for (i = 0; i < number_of_teams; i++) {
    if (all_teams[i].level == 0) {
      N_counter++;
    }
    else if (all_teams[i].level == 1) {
      A_counter++;
    }
    else if (all_teams[i].level == 2) {
      B_counter++;
    }
    else {
      C_counter++;
    }
  }

  /* Laver kampe for niveauerne, og tæller antallet af kampe */
  if (number_of_teams > 0) {
    if (N_counter > 0) {
      match_count = createMatchesByLevel(all_teams + team_pointer, all_matches, N_counter, match_count);
      team_pointer += N_counter;
    }
    if (A_counter > 0) {
      match_count = createMatchesByLevel(all_teams + team_pointer, all_matches, A_counter, match_count);
      team_pointer += A_counter;
    }
    if (B_counter > 0) {
      match_count = createMatchesByLevel(all_teams + team_pointer, all_matches, B_counter, match_count);
      team_pointer += B_counter;
    }
    if (C_counter > 0) {
      match_count = createMatchesByLevel(all_teams + team_pointer, all_matches, C_counter, match_count);
    }
  }
  else {
    printf("Ingen hold fundet\n");
  }

  return match_count;
}

int createMatchesByLevel (team *all_teams, match *all_matches, int level_counter, int match_count) {

  int skip = 1, team_a = 0, team_b = 0;
  int round_count = GAMES_PR_TEAM / 2;      /* Skal have sin egen kommentar */

  for (skip = 1; skip <= round_count; skip++) {
    for (team_a = 0; team_a < level_counter; team_a++) {
      if ((skip % level_counter) == 0) {
        team_b = (team_a + skip + 1) % level_counter;
      }
      else {
        team_b = (team_a + skip) % level_counter;
      }

      strcpy(all_matches[match_count].team_a, all_teams[team_a].team);
      strcpy(all_matches[match_count].team_b, all_teams[team_b].team);
      all_matches[match_count].level = all_teams[team_a].level;

      all_teams[team_a].games++;
      all_teams[team_b].games++;
      match_count++;
    }
  }

  return match_count;
}

/* Returner 0, hvis kampene har hold tilfælles, ellers returnerer den 1 */
int compareMatches (const match match_a, const match match_b) {

  if (strcmp(match_a.team_a, match_b.team_a) == 0 || strcmp(match_a.team_a, match_b.team_b) == 0 ||
      strcmp(match_a.team_b, match_b.team_a) == 0 || strcmp(match_a.team_b, match_b.team_b) == 0) {
    return 0;
  }
  else {
    return 1;
  }
}



void createTournament(const match *all_matches, const int number_of_matches, const int number_of_fields, match *tournament) {
  match *copy_of_matches;
  int tournament_index = 0;
  int match_index = 0;
  int SENTINEL = 0;

  copy_of_matches = malloc(number_of_matches * sizeof(match));

  copyMatches(all_matches, number_of_matches, copy_of_matches);

  while (SENTINEL == 0) {
    match_index = rand() % number_of_matches;

    if (copy_of_matches[match_index].field == -1) {
      copy_of_matches[match_index].field = tournament_index % number_of_fields;
      tournament[tournament_index] = copy_of_matches[match_index];
      tournament_index++;
    }

    else if (tournament_index >= number_of_matches) {
      SENTINEL = 1;
    }
  }
}

void resetFields(const int number_of_matches, match *copy_of_matches) {
  int match_index = 0;

  for (match_index = 0; match_index < number_of_matches; match_index++) {
    copy_of_matches[match_index].field = -1;
  }
}

void copyMatches(const match *all_matches, const int number_of_matches, match *copy_of_matches) {
  int match_index = 0;

  for (match_index = 0; match_index < number_of_matches; match_index++) {
    copy_of_matches[match_index] = all_matches[match_index];
  }
}

/* Bedømmer om en tournering overholder reglerne, jo højere jo bedre. */
int evaluateTournament(match *tournament, const int number_of_matches, const int number_of_fields) {
  int grade = 0;
  int round_start = 0;
  int round_index = 0;
  int number_of_rounds;
  int match_a, match_b;

  number_of_rounds = number_of_matches / number_of_fields;
  for (round_index = 0; round_index < number_of_rounds; round_index++) {

    round_start = round_index * number_of_fields;
    /* int current_round = match / number_of_fields; */
    /* int prev_round = round_start - number_of_fields; */

    /* Starter ved 1, da der ikke er stor risiko for at holdene i første kamp spillede i kampen før */
    /* Kunne gavne med et member af match structen, der sagde hviken runde den foregik i. Måske?*/
    /* Check om nogle af holdene spillede i kampen før. Bør sammenligne med hele runden før. */

    /* Gennemgår og sammenligner to runder */
    for (match_a = round_start; match_a < round_start + number_of_fields; match_a++) {
      for (match_b = round_start; match_b < round_start + number_of_fields; match_b++) {
        /* Giv bedre karakter hvis hold ikke spiller flere gange i samme runde */
        if (match_a != match_b && compareMatches(tournament[match_a], tournament[match_b]) == 0) {
          return -1;
        }
        /*else {
          grade ++;
        }*/
        /* Giv bedre karakter hvis ingen af holdene spillede i forrige runde
           ikke sikker på om det er en god måde at gøre det på */
        if (compareMatches(tournament[match_a], tournament[match_b - number_of_fields]) == 1) {
          grade += 1;
        }
        /*else if(tournament[match_a].field == tournament[match_b - number_of_fields].field) {
          grade++;
        }*/
        else if(tournament[match_a].field != tournament[match_b - number_of_fields].field){
          grade -=20;
        }
      }
    }
  }
  return grade;
}

void switchMatches(match *tournament, const int number_of_matches, const int number_of_fields){
  int number_of_rounds, i;
  int round_index;
  int round_start;
  int match_a, match_b;
  match temp;

  number_of_rounds = number_of_matches / number_of_fields;

  for (round_index = 0; round_index < number_of_rounds; round_index++) {
    round_start = round_index * number_of_fields;
    for (match_a = round_start; match_a < round_start + number_of_fields; match_a++) {
      for (match_b = round_start; match_b < round_start + number_of_fields; match_b++) {
        if (compareMatches(tournament[match_a], tournament[match_b - number_of_fields]) == 0) {
          /*Der er noget glat måske herfra, swicther dem ikke ordentligt*/
          if(tournament[match_a].field != tournament[match_b - number_of_fields].field){
            printf("Test %d\n", match_a);
            i = (rand() % number_of_fields) + (round_index * number_of_fields);
            printf("%d\n",i);
            temp = tournament[match_a];
            tournament[match_a] = tournament[i];
            tournament[i] = temp;
          }
        }
      }
    }
  }
}
