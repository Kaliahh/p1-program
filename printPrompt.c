# include "../p1-program/h-files/main.h"
# include "../p1-program/h-files/printPrompt.h"

/* Printer turneringsplan til fil
   Parameterne er en fil-pointer, enten filen der skal skrives til, eller stdout hvis der skal printes til terminalen,
   en turnering i form af en pointer til array af matches, en int med starttidspunkt for turneringen
   en int med antallet af runder, og en int med antallet af baner  */
int printProgram(FILE *fp, const match *tournament, const int starting_time, const int number_of_rounds, const int number_of_fields) {
  int round_index = 0;
  int match_index = 0;
  int hour = 0;
  int minute = 0;
  int time = starting_time;

  /* Chekker om et givent index i turnerings arrayet indeholder gyldige hold. Afgjort ved at navnet starter med stort bogstav */
  while (isalpha(tournament[match_index].team_a.team[0]) != 0 && isalpha(tournament[match_index].team_b.team[0]) != 0) {
    hour = time / 60;
    minute = time % 60;

    /* Hvis det er den første kamp i runden */
    if (match_index % number_of_fields == 0) {
      /* Printer runde nummer og tidspunktet for hvornår der skal spilles */
      fprintf(fp, "Runde %d:\n%.2d:%.2d\n", round_index + 1, hour, minute);
      /* Printer banenummer, niveau og holdene der skal spille mod hinanden */
      fprintf(fp, "Bane %2d | %c | %s vs %s\n", tournament[match_index].field + 1, translateToChar(tournament[match_index].level),
                                                tournament[match_index].team_a.team, tournament[match_index].team_b.team);
      time += ROUND_LEN;
      round_index++;
    }

    /* Hvis det er den sidste kamp i runden */
    else if (match_index % number_of_fields == number_of_fields - 1) {
      fprintf(fp, "Bane %2d | %c | %s vs %s\n", tournament[match_index].field + 1, translateToChar(tournament[match_index].level),
                                                tournament[match_index].team_a.team, tournament[match_index].team_b.team);
      fprintf(fp, "\n");
    }

    else {
      fprintf(fp, "Bane %2d | %c | %s vs %s\n", tournament[match_index].field + 1, translateToChar(tournament[match_index].level),
                                                tournament[match_index].team_a.team, tournament[match_index].team_b.team);
    }
    match_index++;
  }
  return 0;
}

/* Oversætter level fra int til tilsvarende char */
char translateToChar(const int level) {
  switch(level) {
    case 1:
      return 'N';
    case 2:
      return 'A';
    case 3:
      return 'B';
    case 4:
      return 'C';
    default:
      printf("Fejl i print funktion\n");
      return 'F';
  }
}

/* Printer alle hold til terminalen
   Tager en pointer til et array af teams, og en int med antallet af elementer i arrayet */
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

/* Laver en template til holdnavne.txt. WIP */
void createTemplate(void) {
  FILE *fp = NULL;

  fp = fopen("holdnavne.txt", "w");
  isFileOpen(fp);
  fprintf(fp, "%s\n", "# Holdnavn, NIVEAU");

  fclose(fp);
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
   Returnerer starttidspunktet i minutter, fra midnat */
int promptForTime(void) {
  int minutes = 0;
  int hours = 0;
  printf("Indtast starttidspunkt (skrevet som tt:mm)\n>> ");
  scanf(" %d:%d", &hours, &minutes);
  return hours * 60 + minutes;
}

/* Prompter brugere for et filnavn */
void promptForFileName(char *file_name) {
  printf("Indtast filnavn (afslut med .txt)\n>> ");
  scanf(" %s", file_name);
}

/* Undersøger om filen blev åbnet, hvis ikke skrives en fejl og programmet lukkes
   Ellers sker der intet */
void isFileOpen(FILE *fp) {
  if(fp == NULL) {
    perror("FEJL: Filen kunne ikke åbnes");
    exit(EXIT_FAILURE);
  }
}
