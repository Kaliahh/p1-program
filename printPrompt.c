# include "../p1-program/h-files/main.h"
# include "../p1-program/h-files/printPrompt.h"

/* Printer stævneplanen. Ud fra brugerens valg ved kaldet af funktionen,
   printes stævneplanen enten til "staevneplan.txt" eller til skærmen, stdout */
   /*
   Parameterne er en fil-pointer, enten filen der skal skrives til, eller stdout hvis der skal printes til terminalen,
   en turnering i form af en pointer til array af matches, en int med starttidspunkt for turneringen
   en int med antallet af runder, og en int med antallet af baner  */
int printProgram(FILE *fp, const match *tournament, const int starting_time, const int number_of_rounds, const int number_of_fields) {
  int round_index = 0;
  int match_index = 0;
  int hour = 0;
  int minute = 0;
  int time = starting_time;

  /* Chekker om et givent index i turnerings arrayet indeholder gyldige hold. Afgjort ved at navnet starter med bogstav */
  while (isalpha(tournament[match_index].team_a.team[0]) != 0 && isalpha(tournament[match_index].team_b.team[0]) != 0) {
    /* Udregner starttidspunktet for den nuværende runde */
    hour = time / 60;
    minute = time % 60;

    /* Hvis det er den første kamp i runden */
    if (match_index % number_of_fields == 0) {
      /* Printer runde nummer og tidspunktet for hvornår der skal spilles */
      fprintf(fp, "Runde %d:\n%.2d:%.2d\n", round_index + 1, hour, minute);
      /* Printer banenummer, niveau og holdene der skal spille mod hinanden */
      fprintf(fp, "Bane %2d | %c | %s vs %s\n", tournament[match_index].field + 1, translateToChar(tournament[match_index].level),
                                                tournament[match_index].team_a.team, tournament[match_index].team_b.team);

      /* Tidspunktet for den næste runde tælles op med længden af én runde */
      time += ROUND_LEN;
      round_index++;
    }

    /* Hvis det er den sidste kamp i runden */
    else if (match_index % number_of_fields == number_of_fields - 1) {
      fprintf(fp, "Bane %2d | %c | %s vs %s\n", tournament[match_index].field + 1, translateToChar(tournament[match_index].level),
                                                tournament[match_index].team_a.team, tournament[match_index].team_b.team);
      fprintf(fp, "\n");
    }

    /* Hvis det hverken er den sidste eller den første kamp i runden */
    else {
      fprintf(fp, "Bane %2d | %c | %s vs %s\n", tournament[match_index].field + 1, translateToChar(tournament[match_index].level),
                                                tournament[match_index].team_a.team, tournament[match_index].team_b.team);
    }
    match_index++;
  }
  /* Sætter filpointeren til starten af stævneplanen */
  rewind(fp);
  return 0;
}

/* Oversætter level fra int til tilsvarende char */
char translateToChar(const int level) {
  return (level == N) ? 'N' :
         (level == A) ? 'A' :
         (level == B) ? 'B' :
         (level == C) ? 'C' : 'F';
}

/* Printer alle hold i all_teams til terminalen */
void printTeams(const team *all_teams, const int number_of_teams) {
  int team_index = 0;
  char level = ' ';

  printf("\nHold: \n- - - - - - - - - - - - - -\n");
  for (team_index = 0; team_index < number_of_teams; team_index++) {
    level = translateToChar(all_teams[team_index].level);
    printf("%2d | %-20s | %c\n", team_index + 1, all_teams[team_index].team, level);
  }
  printf("\n");
}

/* Prompter brugeren for antallet af baner.
   Returnerer antallet af baner */
int promptForFields(void) {
  int number_of_fields = 0;
  printf("Indtast antal baner\n>> ");
  scanf(" %d", &number_of_fields);
  return number_of_fields;
}

/* Prompter brugeren for starttidspunkt.
   Returnerer starttidspunktet i minutter, talt fra midnat */
int promptForTime(void) {
  int minutes = 0;
  int hours = 0;
  printf("Indtast starttidspunkt (skrevet som tt:mm)\n>> ");
  scanf(" %d:%d", &hours, &minutes);
  return hours * 60 + minutes;
}

/* Prompter brugere for et navn på filen med holdlisten */
void promptForFileName(char *file_name) {
  printf("Indtast navn på fil med holdliste (afslut med .txt)\n>> ");
  scanf(" %s", file_name);
}

/* Prompter for antallet nye hold. */
int promptForNumberOfTeams(const int modifier) {
  int number_of_mod_teams = 0;

  /* Teksten der printes til terminalen, er baseret på om der skal tilføjes eller fjernes hold ved kaldstedet */
  printf("Antal hold der ønskes at %s\n>> ", (modifier == ADD) ? "tilføjes" : "fjernes");
  scanf(" %d", &number_of_mod_teams);

  return number_of_mod_teams;
}

/* Undersøger om filen blev åbnet.
   Hvis ikke skrives en fejl og programmet stoppes */
void isFileOpen(FILE *fp) {
  if(fp == NULL) {
    perror("FEJL: Filen kunne ikke åbnes");
    exit(EXIT_FAILURE);
  }
}
