# include "../p1-program/h-files/main.h"
# include "../p1-program/h-files/printPrompt.h"

/* Laver en template til holdnavne.txt. WIP */
void createTemplate(void) {
  FILE *fp = NULL;

  fp = fopen("holdnavne.txt", "w");
  isFileOpen(fp);
  fprintf(fp, "%s\n", "# Holdnavn, NIVEAU");

  fclose(fp);
}

/* Printer alle hold til terminalen
   Tager en pointer til et array af teams, og en int med antallet af elementer i arrayet */
void printTeams(const team *all_teams, const int number_of_teams) {
  int team_index = 0;
  char level = ' ';

  printf("\nHold: \n- - - - - - - - - - - - - -\n");
  for (team_index = 0; team_index < number_of_teams; team_index++) {
    level = translateToChar(all_teams[team_index].level);

    printf("%-20s | %c\n", all_teams[team_index].team, level);
  }
  printf("\n");
}

/* Spørger brugeren om hvad der ønskes at gøre med turneringsplanen, og kalder relevante funktioner.
   Parameterne er turneringen i form af en pointer til array af matches, en int med starttidspunkt for turneringen
   en int med antallet af runder, og en int med antallet af baner */
int printProgram(match *tournament, int starting_time, int number_of_rounds, int number_of_fields) {
  int choice = -1;

  showPrintOptions();
  while (choice != 0) {
    scanf(" %d", &choice);

    if (choice == 1) {
      printToFile(stdout, tournament, starting_time, number_of_rounds, number_of_fields);
      showPrintOptions();
    }

    else if (choice == 2) {
      FILE *fp;
      fp = fopen("turneringsplan.txt", "w");
      isFileOpen(fp);
      printToFile(fp, tournament, starting_time, number_of_rounds, number_of_fields);
      showPrintOptions();
    }

    else if (choice == 0) {
      return 0;
    }

    else {
      printf("Fejl ved indtastning. Tast 1 eller 2\n>> ");
      showPrintOptions();
    }
  }
  return 0;
}

/* Viser valgmuligheder ved print i terminalen */
void showPrintOptions(void) {
  printf("\n#####################    PRINT    #####################\n\n");
  printf("[1] Se kampprogram i terminalen \n[2] Gem kampprogram\n[0] Gå til hovedmenuen\n>> ");
}

/* Printer turneringsplan til fil
   Parameterne er en fil-pointer, enten filen der skal skrives til, eller stdout hvis der skal printes til terminalen,
   en turnering i form af en pointer til array af matches, en int med starttidspunkt for turneringen
   en int med antallet af runder, og en int med antallet af baner  */
int printToFile(FILE *fp, match *tournament, int starting_time, int number_of_rounds, int number_of_fields) {
  int round_index = 0;
  int match_index = 0;
  int hour = 0;
  int minute = 0;

  /* Chekker om et givent index i turnerings arrayet indeholder gyldige hold. Afgjort ved at navnet starter med stort bogstav */
  while (isupper(tournament[match_index].team_a.team[0]) != 0 && isupper(tournament[match_index].team_b.team[0]) != 0) {
    hour = starting_time / 60;
    minute = starting_time % 60;

    /* Hvis det er den første kamp i runden */
    if (match_index % number_of_fields == 0) {
      /* Printer runde nummer og tidspunktet for hvornår der skal spilles */
      fprintf(fp, "Runde %d:\n%.2d:%.2d\n", round_index + 1, hour, minute);
      /* Printer banenummer, niveau og holdene der skal spille mod hinanden */
      fprintf(fp, "Bane %2d | %c | %s vs %s\n", tournament[match_index].field + 1, translateToChar(tournament[match_index].level),
                                                tournament[match_index].team_a.team, tournament[match_index].team_b.team);
      starting_time += ROUND_LEN;
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
char translateToChar(int level) {
  switch(level) {
    case 0:
      return 'N';
    case 1:
      return 'A';
    case 2:
      return 'B';
    case 3:
      return 'C';
    default:
      printf("Fejl i print funktion\n");
      return 'F';
  }
}

/* Får en char, der er et niveau for et hold. Funktionen konverterer niveauet til heltal, og returner resultatet. */
int getLevel(const char level) {
  return (level == 'N') ? N :
         (level == 'A') ? A :
         (level == 'B') ? B :
         (level == 'C') ? C : EMPTY;
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
