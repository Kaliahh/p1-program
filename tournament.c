# include "main.h"
# include "tournament.h"

/* Laver et turneringsarray ud fra kampene i all_matches */
void createTournament(const match *all_matches, const int number_of_matches, const int number_of_fields, match *tournament) {
  match *copy_of_matches;
  int tournament_index = 0;
  int match_index = 0;
  int SENTINEL = 0;

  copy_of_matches = malloc(number_of_matches * sizeof(match));

  copyMatches(all_matches, number_of_matches, copy_of_matches);

  while (SENTINEL == 0) {
    match_index = rand() % number_of_matches;
    /* printf("index: %d\n", match_index); */
    /* printf("%d\n", copy_of_matches[match_index].field); */

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
