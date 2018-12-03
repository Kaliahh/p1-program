/* Funktioner til at sammensætte hold i kampe, og kampe i runder */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
# include <time.h>
# include "../main.h"

int createMatches (team *, match *, int);
int createMatchesByLevel (team *, match *, int, int);
int compareMatches (const match match_a, const match match_b);
match* createRandomTournament(match *, int, const int);
void removeElement(match *, const int, const int);
int evaluateTournament(match *, const int, const int);

void createTournament(const match *, const int, const int, match *);
void copyMatches(const match *, const int, match *);
void resetFields(const int, match *);

int main(void) {
  int i = 0, number_of_teams = 11;
  int number_of_fields = 2;
  int number_of_matches = (6 * number_of_teams) / 2;
  int grade = 0;
  int temp_grade = 0;
  team all_teams[11];
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
  all_teams[5].level = 1;
  all_teams[6].level = 1;
  all_teams[7].level = 1;
  all_teams[8].level = 1;
  all_teams[9].level = 1;
  all_teams[10].level = 1;

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

  all_matches = malloc(number_of_matches * sizeof(match));

  createMatches(all_teams, all_matches, number_of_teams);

  for (i = 0; i < (3 * number_of_teams); i++) {
    printf("%s vs %s\n", all_matches[i].team_a, all_matches[i].team_b);
  }

  printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n");

  for (i = 0; i < 11; i++){
    printf("Hold %d: %d kampe\n", i+1, all_teams[i].games);
  }

  tournament = malloc(number_of_matches * sizeof(match));
  temp_tournament = malloc(number_of_matches * sizeof(match));

  resetFields(number_of_matches, all_matches);

  for (int noget = 0; noget < 1000000; noget++) {
    createTournament(all_matches, number_of_matches, number_of_fields, temp_tournament);

    temp_grade = evaluateTournament(temp_tournament, number_of_matches, number_of_fields);

    if (temp_grade > grade) {
      copyMatches(temp_tournament, number_of_matches, tournament);
      grade = temp_grade;
    }

  }


  printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n");

  for (i = 0; i < number_of_matches; i++) {
    if (i % number_of_fields == 0 && i != 0) {
      printf("- - - - - - - - - - - - - - - - - - - - - - - - -\n");
      printf("%2d | %8s vs %-10s\n", i + 1, tournament[i].team_a, tournament[i].team_b);
    }

    else {
      printf("%2d | %8s vs %-10s\n", i + 1, tournament[i].team_a, tournament[i].team_b);
    }
  }

  printf("%d\n", grade);

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

int compareMatches (const match match_a, const match match_b) {

  if (strcmp(match_a.team_a, match_b.team_a) == 0 || strcmp(match_a.team_a, match_b.team_b) == 0 ||
      strcmp(match_a.team_b, match_b.team_a) == 0 || strcmp(match_a.team_b, match_b.team_b) == 0) {
    return 0;
  }
  else {
    return 1;
  }
}



/* Laver en tilfældig tournering af tvivlsom kvalitet */
match *createRandomTournament(match *all_matches, int number_of_matches, const int number_of_fields) {
  match *tournament = malloc(number_of_matches * sizeof(match));
  match *copy_matches = all_matches;
  int remaning_matches = number_of_matches;

  int field = 0, picked;
  for(int match = 0; match < number_of_matches; match++) {
    picked = rand() % remaning_matches;
    field = (field + 1) % 3;                                 /* Usikker på beregningen */
    tournament[match] = all_matches[picked];                 /* sæt en tilfældig kamp på */
    tournament[match].field = field;                         /* Fastlæg bane */
    removeElement(copy_matches, remaning_matches, picked);   /* Fjern kampen, så den ikke kan sættes ind flere gange */
    remaning_matches--;
    field++;
  }
  return tournament;
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
      copy_of_matches[match_index].field = match_index % number_of_fields;
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

/* Bedømmer om en tournering overholder reglerne */
int evaluateTournament(match *tournament, const int number_of_matches, const int number_of_fields) {
  int grade = 0;
  int round_start = 0; /* Usikker på beregningen */
  int round_index = 0;

  for (round_index = 0; round_index < number_of_matches / number_of_fields; round_index++) {

    round_start = round_index * number_of_fields;
    /* int current_round = match / number_of_fields; */
    /* int prev_round = round_start - number_of_fields; */

    /* Starter ved 1, da der ikke er stor risiko for at holdene i første kamp spillede i kampen før */
    /* Kunne gavne med et member af match structen, der sagde hviken runde den foregik i. Måske?*/
    /* Check om nogle af holdene spillede i kampen før. Bør sammenligne med hele runden før. */

    /* Gennemgår og sammenligner to runder */
    for (int match1 = round_start; match1 < round_start + number_of_fields; match1++) {
      for (int match2 = round_start; match2 < round_start + number_of_fields; match2++) {
        /* Giv bedre karakter hvis hold ikke spiller flere gange i samme runde */
        if (match1 != match2 && compareMatches(tournament[match1], tournament[match2]) == 1) {
          grade++;
        }
        /* Giv bedre karakter hvis ingen af holdene spillede i forrige runde
           ikke sikker på om det er en god måde at gøre det på */
        if (compareMatches(tournament[match1], tournament[match2 - number_of_fields]) == 0) {
          grade -= 2;
          if(tournament[match1].field == tournament[match2 - number_of_fields].field) {
            grade++;
          }
        }
      }
    }
  }

  return grade;
}

/* Fjern element fra array */
void removeElement(match *matches, const int size, const int element) {
  for(int i = element; i <= size; i++) {
    matches[i] = matches[i+1];
  }
}
