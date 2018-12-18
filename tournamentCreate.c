# include "../p1-program/h-files/main.h"
# include "../p1-program/h-files/memoryAllocationScanningSorting.h"
# include "../p1-program/h-files/printPrompt.h"
# include "../p1-program/h-files/tournament.h"
# include "../p1-program/h-files/menus.h"

/* Sammensætter og printer en ny stævneplan */
int createNewTournament(void) {
  FILE *fp = NULL;
  int number_of_fields = 0;
  int number_of_rounds = 0;
  int number_of_teams = 0;
  int number_of_matches = 0;
  int starting_time = 0;
  match *tournament = NULL;
  team *all_teams = NULL;
  char file_name[MAX_NAME_LEN];

  /* Prompter brugeren for antallet af baner, startidspunkt og filnavn */
  number_of_fields = promptForFields();
  starting_time = promptForTime();
  promptForFileName(file_name);

  fp = fopen(file_name, "r");

  /* Check at filen er NULL */
  isFileOpen(fp);

  /* Finder antallet af hold */
  number_of_teams = getNumberOfTeams(fp);

  /* Udregner antallet af kampe og antallet af runder */
  number_of_matches = (number_of_teams * GAMES_PR_TEAM) / 2;

  /* Finder antallet af runder */
  number_of_rounds = getNumberOfRounds(number_of_matches, number_of_fields);

  /* Allokerer plads til teams arrayet og matches arrayet */
  all_teams = calloc(number_of_teams, sizeof(team));

  /* Fylder teams arrayet med hold */
  scanTeamFile(fp, file_name, number_of_teams, all_teams);

  /* Allokerer plads til et array med plads til alle kampe der skal spilles */
  tournament = allocateMemoryMatch(number_of_matches);

  /* Sammensætter og evaluerer stævneplaner, indtil der findes en der er acceptabel */
  generateTournament(number_of_teams, number_of_matches, number_of_fields, number_of_rounds, tournament, all_teams);

  /* Printer den færdige stævneplan, enten til en fil eller til terminalen */
  printingMenu(tournament, starting_time, number_of_rounds, number_of_fields);

  /* Frigør den hukommelse der er allokeret til de forskellige arrays */
  free(all_teams);
  free(tournament);

  fclose(fp);

  return 0;
}

/* Sammensætter og evaluerer stævneplaner, indtil der findes en der er acceptabel
   Der bruges enten en hurtig metode, som bare kigger på om floorball regler bliver brudt
   eller den bedre metode som også giver point alt efter hvor god stævneplanen er */
void generateTournament(const int number_of_teams, const int number_of_matches, const int number_of_fields, const int number_of_rounds, match *tournament, team *all_teams) {
  int points = 0;
  int max_points = 0;
  int make_fast = 0;
  int no_go_count = 0;

  /* Udregner det maksimale antal point en stævneplan kan få,
     med de forudsætninger brugeren har stillet */
  max_points = number_of_matches * 6;

  /* Prompter brugeren for at vælge mellem den hurtige metode, eller finde den bedste stævneplan */
  make_fast = createMenu();

  /* Baseret på brugerens svar fra ovenstående funktion, vælges metoden til generering af stævneplanen */
  if (make_fast == FAST) {
    do {
      no_go_count = createTournament(number_of_teams, number_of_matches, number_of_fields, number_of_rounds, all_teams, tournament, &points);
    } while (no_go_count != 0);
  }

  else if (make_fast == BEST) {
    while (!(no_go_count == 0 && points > max_points - 18)) {
      points = 0;

      no_go_count = createTournament(number_of_teams, number_of_matches, number_of_fields, number_of_rounds, all_teams, tournament, &points);
    }
  }
}

/* Laver en stævneplan, og returnerer antallet af gange planen bryder med reglerne. */
int createTournament(const int number_of_teams, const int number_of_matches, const int number_of_fields, const int number_of_rounds, team *all_teams, match *tournament, int *point) {
  int field_index = 0;
  int round_count = 0;
  int end_of_round = 0;
  int start_of_round = 0;
  int start_of_next_round = 0;
  int sentinel_count = 0;
  int no_go_count = 0;
  int temp_point = 0;
  int *team_a;
  int *team_b;

  /* Allokerer plads til to arrays, der indeholder indekser
     for det første og det andet hold i alle kampe */
  team_a = malloc (number_of_fields * sizeof(int));
  team_b = malloc (number_of_fields * sizeof(int));

  /* Nulstiller antallet af kampe hver hold har spillet,
     hvis det allerede er forsøgt at generere en stævneplan */
  resetGamesPlayed(number_of_teams, all_teams);

  /* Kører igennem hver runde. */
  for (round_count = 0; round_count < number_of_rounds; round_count++) {
    start_of_round = round_count * number_of_fields;
    start_of_next_round = (round_count + 1) * number_of_fields;

    end_of_round = createRound(start_of_next_round, start_of_round, number_of_teams, number_of_fields, team_a, team_b, all_teams, tournament);

    /* Tjekker om programmet overholder reglerne. */
    no_go_count = evaluateRound(tournament, end_of_round, number_of_fields, &temp_point);

    /* Hvis reglerne ikke overholder reglerne sammensættes runden på ny. */
    if (no_go_count > 0 && sentinel_count < CHECK_NUM) {
      /* Sætter antallet af kampe tilbage til det den var før runden blev sammensat. */
      for (field_index = 0; field_index < number_of_fields; field_index++) {
        all_teams[team_a[field_index]].games--;
        all_teams[team_b[field_index]].games--;
      }

      round_count--;
      sentinel_count++;

      temp_point = 0;
    }
    else if (sentinel_count >= CHECK_NUM) {
      return 1;
    }
    else {
      *point += temp_point;

      temp_point = 0;
      sentinel_count = 0;
    }
  }

  free(team_a);
  free(team_b);

  return no_go_count;
}

/* Nulstiller antallet af kampe hvert hold har spillet */
void resetGamesPlayed(const int number_of_teams, team *all_teams) {
  int team_index = 0;

  for (team_index = 0; team_index < number_of_teams; team_index++) {
    all_teams[team_index].games = 0;
  }
}

/* Finder hold, som kan sammensættes i en kamp.  */
int createRound(const int start_of_next_round, const int start_of_round, const int number_of_teams, const int number_of_fields, int *team_a, int *team_b, team *all_teams, match *tournament) {
  int tournament_index = 0;
  int match_index = 0;

  for (tournament_index = start_of_round; tournament_index < start_of_next_round; tournament_index++) {
    team_a[match_index] = findFirstTeam(tournament_index, number_of_fields, number_of_teams, all_teams, tournament);
    team_b[match_index] = findSecondTeam(tournament_index, number_of_teams, all_teams, tournament);

    match_index++;
  }

  return tournament_index;
}

/* Finder det første hold til en kamp. */
int findFirstTeam(const int tournament_index, const int number_of_fields, const int number_of_teams, team *all_teams, match *tournament) {
  int sentinel_count = 0;
  int team_index = 0;

  while (sentinel_count < CHECK_NUM) {
    team_index = rand() % number_of_teams;

    if (all_teams[team_index].games < GAMES_PR_TEAM && all_teams[team_index].level > EMPTY) {
      tournament[tournament_index].team_a = all_teams[team_index];
      tournament[tournament_index].level = all_teams[team_index].level;
      tournament[tournament_index].field = tournament_index % number_of_fields;

      sentinel_count = CHECK_NUM;

      all_teams[team_index].games++;
    }

    sentinel_count++;
  }

  return team_index;
}

/* Finder det andet hold til en kamp, baseret på det første hold. */
int findSecondTeam(const int tournament_index, const int number_of_teams, team *all_teams, match *tournament) {
  int sentinel_count = 0;
  int team_index = 0;

  while (sentinel_count < CHECK_NUM) {
    team_index = rand() % number_of_teams;

    if (strcmp(tournament[tournament_index].team_a.team, all_teams[team_index].team) != 0 &&
        all_teams[team_index].level == tournament[tournament_index].team_a.level &&
        all_teams[team_index].games < GAMES_PR_TEAM) {

      all_teams[team_index].games++;
      tournament[tournament_index].team_b = all_teams[team_index];

      sentinel_count = CHECK_NUM;
    }

    sentinel_count++;
  }

  return team_index;
}

/* Tjekker reglerne igennem og returnerer antallet af fejl. */
int evaluateRound(const match *tournament, const int end_of_round, const int number_of_fields, int *temp_point) {
  int field_index = 0;
  int no_go_count = 0;
  int round_count = 0;

  round_count = end_of_round / number_of_fields;

  /* Kører igennem alle kampene i runden. */
  for (field_index = end_of_round - number_of_fields; field_index < end_of_round; field_index++) {
    /* Kører hvis kampen allerede er i samme runde. */
    if (isAlreadyInRound(tournament, field_index, number_of_fields) == 1) {
      no_go_count++;
    }
    /* Kører hvis det ikke er den første runde. */
    if (round_count != 0) {
      no_go_count += isInPreviousRound(tournament, field_index, number_of_fields, temp_point);

      /* Tjekker hvor mange gange hvert hold har spillet i træk */
      no_go_count += playedInARow(tournament, tournament[field_index].team_a.team, field_index, number_of_fields, temp_point);
      no_go_count += playedInARow(tournament, tournament[field_index].team_b.team, field_index, number_of_fields, temp_point);

      *temp_point += isDifferentMatch(tournament[field_index - number_of_fields], tournament[field_index]);
    }
  }

  return no_go_count;
}

/* Tjekker om et af holdene i en kamp allerede skal spille i runden. */
int isAlreadyInRound(const match *tournament, const int field_index, const int number_of_fields) {
  int comp_index = 0;
  int start_of_round = 0;

  start_of_round = field_index - (field_index % number_of_fields);

  /* Kører igennem alle de forrige kampe i runden. */
  for (comp_index = start_of_round; comp_index < field_index; comp_index++) {
    if (compareTeams(tournament + comp_index, tournament + field_index) == 1) {
      return 1;
    }
  }

  return 0;
}

/* Tjekker om et af holdene i en kamp har spillet i forrige runde. */
int isInPreviousRound(const match *tournament, const int field_index, const int number_of_fields, int *point) {
  int comp_index = 0;
  int no_go_count = 0;
  int start_of_previous_round = 0;
  int start_of_current_round = 0;

  start_of_previous_round = field_index - ((field_index % number_of_fields) + number_of_fields);
  start_of_current_round = field_index - (field_index % number_of_fields);

  /* Kører igennem for hver kamp i runden før. */
  for (comp_index = start_of_previous_round; comp_index < start_of_current_round; comp_index++) {
    /* Køres hvis der er et hold som også har spillet i runden før. */
    if (compareTeams(tournament + comp_index, tournament + field_index) == 1) {
      /* Køres hvis holdet ikke spiller på samme bane. */
      if (tournament[comp_index].field != tournament[field_index].field) {
        no_go_count++;
      }
    }
    else {
      *point += 1;
    }
  }

  return no_go_count;
}

/* Sammenligner holdnavne */
int compareTeams(const match *a, const match *b) {
  if (strcmp(a->team_a.team, b->team_a.team) == 0 ||
      strcmp(a->team_a.team, b->team_b.team) == 0 ||
      strcmp(a->team_b.team, b->team_a.team) == 0 ||
      strcmp(a->team_b.team, b->team_b.team) == 0) {
    return 1;
  }
  return 0;
}

/* Tæller antallet af gang et hold spiller i træk, og giver karakter derudfra. */
int playedInARow(const match *tournament, const char *current_team, const int field_index, int number_of_fields, int *point) {
  int field_multiplier = 1;
  int point_temp = 1;

  while (!isDifferentTeam(tournament[field_index - number_of_fields], current_team)) {
    field_multiplier++;
    point_temp--;

    number_of_fields *= field_multiplier;
  }

  if (point_temp < 0) {
    return 1;
  }

  *point += point_temp;

  return 0;
}

/* Sammenligner hold, og ser om to hold er ens. */
int isDifferentTeam(const match compare_team, const char *current_team) {
  if (strcmp(compare_team.team_a.team, current_team) == 0 ||
      strcmp(compare_team.team_b.team, current_team) == 0) {
    return 0;
  }
  else {
    return 5;
  }
}

/* Sammenligner kampe. */
int isDifferentMatch(const match compare_team, const match current_team) {
  if (isDifferentTeam(compare_team, current_team.team_a.team) == 0 &&
      isDifferentTeam(compare_team, current_team.team_b.team) == 0) {
    return 0;
  }
  return 1;
}

/* Finder antallet af runder
   Tjekker om der skal bruges en ekstra runde,
   i det tilfælde hvor den sidste runde ikke er fyldt helt ud */
int getNumberOfRounds(const int number_of_matches, const int number_of_fields) {
  if (number_of_matches % number_of_fields == 0) {
    return (number_of_matches / number_of_fields);
  }
  else {
    return (number_of_matches / number_of_fields) + 1;
  }
}

/* Får en char, der er et niveau for et hold. Funktionen konverterer niveauet til heltal, og returner resultatet. */
int getLevel(const char level) {
  return (level == 'N') ? N :
         (level == 'A') ? A :
         (level == 'B') ? B :
         (level == 'C') ? C : EMPTY;
}
