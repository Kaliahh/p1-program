# include "../p1-program/h-files/main.h"
# include "../p1-program/h-files/memoryAllocationScanningSorting.h"
# include "../p1-program/h-files/printPrompt.h"
# include "../p1-program/h-files/tournament.h"
# include "../p1-program/h-files/menus.h"
# include <time.h>

/* Sammensætter og printer en ny stævneplan fra bunden */
void createNewTournament(void) {
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

  /* Check at filen blev fundet */
  isFileOpen(fp);

  /* Finder antallet af hold */
  number_of_teams = getNumberOfTeams(fp);

  /* Udregner antallet af kampe */
  number_of_matches = (number_of_teams * GAMES_PR_TEAM) / 2;

  /* Finder antallet af runder */
  number_of_rounds = getNumberOfRounds(number_of_matches, number_of_fields);

  /* Allokerer plads til et array af alle hold */
  all_teams = allocateMemoryTeams(number_of_teams);

  /* Finder holdnavne og niveau i den åbne fil,
     og lægger dem over i all_teams */
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

  return;
}

/* Sammensætter og evaluerer stævneplaner, indtil der findes en der er acceptabel
   Der bruges enten en hurtig metode, som bare kigger på om floorball regler bliver brudt
   eller den bedre metode som yderligere giver point alt efter hvor god stævneplanen er */
void generateTournament(const int number_of_teams, const int number_of_matches, const int number_of_fields, const int number_of_rounds, match *tournament, team *all_teams) {
  int points = 0;
  int max_points = 0;
  int make_fast = 0;
  int no_go_count = 0;
  FILE *fp = NULL;



  if (fp == NULL) {
    perror("Hey! ");
  }

  /* Udregner det maksimale antal point en stævneplan kan få,
     med de forudsætninger brugeren har stillet.
     Sætter derudover en fejlmargen på 5% */
  max_points = (number_of_matches * (number_of_fields + 3)) * 0.95;

  /* Prompter brugeren for at vælge mellem den hurtige metode, eller finde den bedste stævneplan */
  make_fast = createMenu();

  for (int timer = 0; timer < 100; timer++) {
    points = 0;
    fp = fopen("tider-RETTET.txt", "a");
    clock_t begin = clock();
    /* Baseret på brugerens svar fra ovenstående funktion, vælges metoden til generering af stævneplanen */
    if (make_fast == FAST) {
      do {
        no_go_count = createTournament(number_of_teams, number_of_matches, number_of_fields, number_of_rounds, all_teams, tournament, &points);
      } while (no_go_count != 0);
    }

    else if (make_fast == BEST) {
      while (!(no_go_count == 0 && points > max_points)) {

        points = 0;

        no_go_count = createTournament(number_of_teams, number_of_matches, number_of_fields, number_of_rounds, all_teams, tournament, &points);
      }
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%3d | Tid: %lf\n", timer, time_spent);
    fprintf(fp, "%lf\n", time_spent);
    fclose(fp);
  }

}

/* Sammensætter en stævneplan, og returnerer antallet af gange planen bryder med floorball reglerne. */
int createTournament(const int number_of_teams, const int number_of_matches, const int number_of_fields, const int number_of_rounds, team *all_teams, match *tournament, int *points) {
  int field_index = 0;
  int round_count = 0;
  int end_of_round = 0;
  int start_of_round = 0;
  int start_of_next_round = 0;
  int sentinel_count = 0;
  int no_go_count = 0;
  int temp_points = 0;
  int *team_a;
  int *team_b;

  /* Allokerer plads til to arrays, der indeholder indekser
     for det første og det andet hold i alle kampe */
  team_a = malloc (number_of_fields * sizeof(int));
  team_b = malloc (number_of_fields * sizeof(int));

  /* Nulstiller antallet af kampe hvert hold har spillet,
     hvis det allerede er forsøgt at generere en stævneplan */
  resetGamesPlayed(number_of_teams, all_teams);

  /* Sammensætter alle runder, en af gangen,
     og tjekker om de har brudt med regler, og hvor mange point de får */
  for (round_count = 0; round_count < number_of_rounds; round_count++) {
    start_of_round = round_count * number_of_fields;
    start_of_next_round = (round_count + 1) * number_of_fields;

    /* Sammensætter en enkelt runder, og returnerer indekset for den sidste kamp i runden */
    end_of_round = createRound(start_of_next_round, start_of_round, number_of_teams, number_of_fields, team_a, team_b, all_teams, tournament);

    /* Tjekker om runder overholder reglerne. */
    no_go_count = evaluateRound(tournament, end_of_round, number_of_fields, &temp_points);

    /* Hvis runden ikke overholder reglerne sammensættes den på ny,
       indtil det er blevet forsøgt mere end CHECK_NUM gange */
    if (no_go_count > 0 && sentinel_count < CHECK_NUM) {
      /* Sætter antallet af kampe tilbage til det den var før runden blev sammensat. */
      for (field_index = 0; field_index < number_of_fields; field_index++) {
        all_teams[team_a[field_index]].games--;
        all_teams[team_b[field_index]].games--;
      }

      /* Går én runde tilbage, og tæller flaget,
         der holder øje med antallet af forsøg, op med én */
      round_count--;
      sentinel_count++;

      /* Pointene runden fik, sættes tilbage til nul */
      temp_points = 0;
    }
    /* Hvis det er forsøgt tilstrækkeligt mange gange, at sætte runden sammen,
       returneres 1, så der prøves igen fra starten */
    else if (sentinel_count >= CHECK_NUM) {
      return 1;
    }
    /* Eller må det betyde at runden er gået igennem,
       og antallet af point den nuværende stævneplan har fået, tælles op */
    else {
      *points += temp_points;
      temp_points = 0;
      sentinel_count = 0;
    }
  }

  free(team_a);
  free(team_b);

  /* Til sidst returners antallet af gange, en floorball regel blev brudt */
  return no_go_count;
}

/* Nulstiller antallet af kampe hvert hold i all_teams har spillet */
void resetGamesPlayed(const int number_of_teams, team *all_teams) {
  int team_index = 0;

  for (team_index = 0; team_index < number_of_teams; team_index++) {
    all_teams[team_index].games = 0;
  }
}

/* Sammensætter en runde  */
int createRound(const int start_of_next_round, const int start_of_round, const int number_of_teams, const int number_of_fields, int *team_a, int *team_b, team *all_teams, match *tournament) {
  int tournament_index = 0;
  int match_index = 0;

  /* Gennemgår de kampe der skal være i runden, og finder to hold der passer ind */
  for (tournament_index = start_of_round; tournament_index < start_of_next_round; tournament_index++) {
    team_a[match_index] = findFirstTeam(tournament_index, number_of_fields, number_of_teams, all_teams, tournament);
    team_b[match_index] = findSecondTeam(tournament_index, number_of_teams, all_teams, tournament);

    match_index++;
  }

  /* Returnerer det indeks runden stoppede ved */
  return tournament_index;
}

/* Finder det første hold til en kamp. */
int findFirstTeam(const int tournament_index, const int number_of_fields, const int number_of_teams, team *all_teams, match *tournament) {
  int sentinel_count = 0;
  int team_index = 0;

  /* Bliver ved med at lede efter et hold, indtil det er sikkert
     at der ikke kan findes et hold der passer med kriterierne */
  while (sentinel_count < CHECK_NUM) {
    /* Finder indekset til et tilfældigt hold i all_teams */
    team_index = rand() % number_of_teams;

    /* Tjekker om holdet der er fundet, har spillet under 6 kampe
       og dets niveau ikke er EMPTY, altså fjernet */
    if (all_teams[team_index].games < GAMES_PR_TEAM && all_teams[team_index].level > EMPTY) {
      /* Hvis dette er sandt, kopieres det over i kampen, og dets indeks returneres */
      tournament[tournament_index].team_a = all_teams[team_index];
      tournament[tournament_index].level = all_teams[team_index].level;
      tournament[tournament_index].field = tournament_index % number_of_fields;
      all_teams[team_index].games++;
      return team_index;
    }
    sentinel_count++;
  }

  /* Hvis det ikke var muligt at finde et hold der passede,
     returneres indekset for det hold der nu er */
  return team_index;
}

/* Finder det andet hold til en kamp, baseret på det første hold. */
int findSecondTeam(const int tournament_index, const int number_of_teams, team *all_teams, match *tournament) {
  int sentinel_count = 0;
  int team_index = 0;

  /* Bliver ved med at lede efter et hold, indtil det er sikkert
     at der ikke kan findes et hold der passer med kriterierne */
  while (sentinel_count < CHECK_NUM) {
    /* Finder indekset til et tilfældigt hold i all_teams */
    team_index = rand() % number_of_teams;

    /* Tjekker om holdet er det samme som det første hold der blev fundet,
       om holdene er samme niveau, og om holdet har spillet under 6 kampe */
    if (strcmp(tournament[tournament_index].team_a.team, all_teams[team_index].team) != 0 &&
        all_teams[team_index].level == tournament[tournament_index].team_a.level &&
        all_teams[team_index].games < GAMES_PR_TEAM) {
      /* Hvis dette er sandt, kopieres holdnavnet over i kampen */
      all_teams[team_index].games++;
      tournament[tournament_index].team_b = all_teams[team_index];

      return team_index;
    }
    sentinel_count++;
  }
  /* Hvis det ikke var muligt at finde et hold der passede,
     returneres indekset for det hold der nu er */
  return team_index;
}

/* Tjekker reglerne igennem, og returnerer antallet af fejl. */
int evaluateRound(const match *tournament, const int end_of_round, const int number_of_fields, int *temp_point) {
  int field_index = 0;
  int no_go_count = 0;
  int round_count = 0;

  round_count = end_of_round / number_of_fields;

  /* Kører igennem alle kampene i runden. */
  for (field_index = end_of_round - number_of_fields; field_index < end_of_round; field_index++) {
    /* Kører hvis kampen allerede er i samme runde. */
    if (isAlreadyInRound(tournament, field_index, number_of_fields) == 1) {
      return 1;
    }
    /* Kører hvis det ikke er den første runde. */
    if (round_count != 0) {
      no_go_count = isInPreviousRound(tournament, field_index, number_of_fields, temp_point);

      if (no_go_count > 0) {
        return 1;
      }

      /* Tjekker hvor mange gange hvert hold har spillet i træk */
      no_go_count = playedInARow(tournament, tournament[field_index].team_a.team, field_index, number_of_fields, temp_point);

      if (no_go_count > 0) {
        return 1;
      }

      no_go_count = playedInARow(tournament, tournament[field_index].team_b.team, field_index, number_of_fields, temp_point);

      if (no_go_count > 0) {
        return 1;
      }

      /* Giver point for at kampen der blev spillet i sidste runde er forskellig */
      *temp_point += isDifferentMatch(tournament[field_index - number_of_fields], tournament[field_index]);
    }
  }

  return 0;
}

/* Tjekker om et af holdene i en kamp allerede skal spille i runden. */
int isAlreadyInRound(const match *tournament, const int field_index, const int number_of_fields) {
  int comp_index = 0;
  int start_of_round = 0;

  /* Indekset for starten af runden udregnes */
  start_of_round = field_index - (field_index % number_of_fields);

  /* Kører igennem alle de forrige kampe i runden. */
  for (comp_index = start_of_round; comp_index < field_index; comp_index++) {
    /* Hvis holdet allerede har spillet i runden, returneres en fejl */
    if (compareTeams(tournament + comp_index, tournament + field_index) == 1) {
      return 1;
    }
  }

  return 0;
}

/* Tjekker om et af holdene i en kamp har spillet i forrige runde. */
int isInPreviousRound(const match *tournament, const int field_index, const int number_of_fields, int *points) {
  int comp_index = 0;
  int no_go_count = 0;
  int start_of_previous_round = 0;
  int start_of_current_round = 0;

  /* Udregner indekser for starten på den forrige runde, og starten på den nuværende runde */
  start_of_previous_round = field_index - ((field_index % number_of_fields) + number_of_fields);
  start_of_current_round = field_index - (field_index % number_of_fields);

  /* Gennemgår hver kamp i runden før. */
  for (comp_index = start_of_previous_round; comp_index < start_of_current_round; comp_index++) {
    /* Tjekker om der er et hold i kampen der har spillet i runden før. */
    if (compareTeams(tournament + comp_index, tournament + field_index) == 1) {
      /* Tjekker om holdet spillede på den samme bane. */
      if (tournament[comp_index].field != tournament[field_index].field) {
        /* Hvis dette ikke er sandt, returneres en fejl */
        no_go_count++;
      }
    }
    /* Hvis ingen af holdene spillede i runden før, gives der point */
    else {
      *points += 1;
    }
  }

  return no_go_count;
}

/* Sammenligner holdnavne. Returnerer 1 hvis der er nogen der er ens */
int compareTeams(const match *a, const match *b) {
  if (strcmp(a->team_a.team, b->team_a.team) == 0 ||
      strcmp(a->team_a.team, b->team_b.team) == 0 ||
      strcmp(a->team_b.team, b->team_a.team) == 0 ||
      strcmp(a->team_b.team, b->team_b.team) == 0) {
    return 1;
  }
  return 0;
}

/* Tæller antallet af gang et hold spiller i træk, og giver point derudfra. */
int playedInARow(const match *tournament, const char *current_team, const int field_index, int number_of_fields, int *points) {
  int rewind_count = number_of_fields;
  int point_temp = 1;

  /* Kører så længe holdet der sammenlignes med er i den forrige runde. */
  while (isDifferentTeam(tournament[field_index - rewind_count], current_team) == 0 && field_index - rewind_count > 0) {
    point_temp--;

    rewind_count += number_of_fields;
  }

  /* Køres hvis holdet har spillet mere end to runder i træk */
  if (point_temp < 0) {
    return 1;
  }

  *points += point_temp;

  return 0;
}

/* Sammenligner hold, og ser om de er ens. */
int isDifferentTeam(const match compare_team, const char *current_team) {
  if (strcmp(compare_team.team_a.team, current_team) == 0 ||
      strcmp(compare_team.team_b.team, current_team) == 0) {
    return 0;
  }
  else {
    return 1;
  }
}

/* Sammenligner kampe, og giver point hvis de ikke er ens. */
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

/* Konverterer niveauet til fra char til int. */
int getLevel(const char level) {
  return (level == 'N') ? N :
         (level == 'A') ? A :
         (level == 'B') ? B :
         (level == 'C') ? C : EMPTY;
}
