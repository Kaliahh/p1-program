# include "../p1-program/h-files/main.h"
# include "../p1-program/h-files/printPrompt.h"

/* Laver en template til holdnavne.txt. WIP */
void createTemplate(void) {
  FILE *fPointer = NULL;

  fPointer = fopen("holdnavne.txt", "w");

  fprintf(fPointer, "%s\n", "# Holdnavn, NIVEAU");

  fclose(fPointer);
}

/* Spørger brugeren om hvad der ønskes at gøre med turneringsplanen */
int printProgram(match *tournament, int starting_time, int number_of_rounds, int number_of_fields) {
  int choice = -1;

  showPrintOptions();
  while (choice != 0) {
    scanf(" %d", &choice);

    if (choice == 1) {
      printToTerminal(tournament, starting_time, number_of_rounds, number_of_fields);
      showPrintOptions();
    }

    else if (choice == 2) {
      printToFile(tournament, starting_time, number_of_rounds, number_of_fields);
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

/* Viser valgmuligheder ved print */
void showPrintOptions(void) {
  printf("\n#####################    PRINT    #####################\n\n");
  printf("[1] Se kampprogram i terminalen \n[2] Gem kampprogram\n[0] Gå til hovedmenuen\n>> ");
}

/* Printer turneringsplan til fil */
int printToFile(match *tournament, int starting_time, int number_of_rounds, int number_of_fields) {
  int round_index = 0;
  int match_index = 0;
  int hour = 0;
  int minute = 0;
  FILE *fp;

  fp = fopen("turneringsplan.txt", "w");

  if (fp == NULL) { /* Check at filen er NULL */
    perror("Error opening file");
    return -1;
  }

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

/* Printer turneringsplanen til terminalen */
void printToTerminal(match *tournament, int starting_time, int number_of_rounds, int number_of_fields) {
  int round_index = 0;
  int match_index = 0;
  int hour = 0;
  int minute = 0;

  printf("\n");

  while (isupper(tournament[match_index].team_a.team[0]) != 0 && isupper(tournament[match_index].team_b.team[0]) != 0) {
    hour = starting_time / 60;
    minute = starting_time % 60;

    /* Hvis det er den første kamp i runden */
    if (match_index % number_of_fields == 0) {
      /* Printer runde nummer og tidspunktet for hvornår der skal spilles */
      printf("Runde %d:\n%.2d:%.2d\n", round_index + 1, hour, minute);
      /* Printer banenummer, niveau og holdene der skal spille mod hinanden */
      printf("Bane %2d | %c | %s vs %s\n", tournament[match_index].field + 1, translateToChar(tournament[match_index].level),
                                           tournament[match_index].team_a.team, tournament[match_index].team_b.team);
      starting_time += ROUND_LEN;
      round_index++;
    }

    /* Hvis det er den sidste kamp i runden */
    else if (match_index % number_of_fields == number_of_fields - 1) {
      printf("Bane %2d | %c | %s vs %s\n", tournament[match_index].field + 1, translateToChar(tournament[match_index].level),
                                           tournament[match_index].team_a.team, tournament[match_index].team_b.team);
      printf("\n");
    }

    else {
      printf("Bane %2d | %c | %s vs %s\n", tournament[match_index].field + 1, translateToChar(tournament[match_index].level),
                                           tournament[match_index].team_a.team, tournament[match_index].team_b.team);
    }
    match_index++;
  }
}

/* Oversætter level fra tal til bogstaver */
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
