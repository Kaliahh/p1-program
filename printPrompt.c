# include "../p1-program/h-files/main.h"
# include "../p1-program/h-files/printPrompt.h"

/* Spørger brugeren om hvad der ønskes at gøre med turneringsplanen */
void printProgram(match *tournament, int starting_time, int number_of_rounds, int number_of_fields) {
  int choice = 0;

  printf("Print til terminalen - tast 1. Print til fil - tast 2:\n");
  scanf(" %d", &choice);

  if(choice == 1) {
    printToTerminal(tournament, starting_time, number_of_rounds, number_of_fields);

    printf("\nEr det i orden? Skal den printes til en fil - tast 1. Er det ikke i orden - tast 0\n");
    scanf(" %d", &choice);

    if (choice == 1) {
      printToFile(tournament, starting_time, number_of_rounds, number_of_fields);
    }

    else if (choice == 0) {
      printProgram(tournament, starting_time, number_of_rounds, number_of_fields);
    }

    else {
      printf("Fejl ved indtastning. Tast 1 eller 2\n");
      printProgram(tournament, starting_time, number_of_rounds, number_of_fields);
    }
  }
  else if(choice == 2) {
    printToFile(tournament, starting_time, number_of_rounds, number_of_fields);
  }
  else {
    printf("Fejl ved indtastning. Tast 1 eller 2\n");
    printProgram(tournament, starting_time, number_of_rounds, number_of_fields);
  }
}

/* Printer turneringsplanen til en fil */
void printToFile(match *tournament, int starting_time, int number_of_rounds, int number_of_fields) {
  int i = 0, j = 0, time = starting_time;
  int hour = 0, minute = 0;
  FILE *fp = fopen("turneringsplan.txt", "w");

  for (i = 0; i < number_of_rounds * number_of_fields; i += number_of_fields) {
    /* Oversætter tiden fra minutter til timer og minutter */
    hour = time / 60;
    minute = time % 60;

    /* Printer runde nummer og tidspunktet for hvornår der skal spilles */
    fprintf (fp, "Runde %d:\n%.2d:%.2d\n", (i / number_of_fields) + 1, hour, minute);

    /* Printer banenummer, niveau og de to hold, som skal spille mod hinanden */
    for (j = 0; j < number_of_fields; j++) {
      fprintf(fp, "Bane %2d | %c | %s vs %s\n", tournament[i + j].field + 1, translateToChar(tournament[i + j].level),
                                               tournament[i + j].team_a, tournament[i + j].team_b);
    }

    fprintf(fp, "\n");

    time += ROUND_LEN;
  }
}

/* Printer turneringsplanen til terminalen */
void printToTerminal(match *tournament, int starting_time, int number_of_rounds, int number_of_fields) {
  int round_index = 0;
  int field_index = 0;
  int match_index = 0;
  int hour = 0;
  int minute = 0;
  int SENTINEL = 0;

  /*
  while (SENTINEL == 0) {
    if (isupper(tournament[match_index].team_a[0]) != 0 && isupper(tournament[match_index].team_b[0]) != 0) {

    }
  }
  */

  while (SENTINEL == 0) {
    if (isupper(tournament[round_index + field_index].team_a[0]) != 0 && isupper(tournament[round_index + field_index].team_b[0]) != 0) {
      hour = starting_time / 60;
      minute = starting_time % 60;

      /* Printer runde nummer og tidspunktet for hvornår der skal spilles */
      printf("Runde %d:\n%.2d:%.2d\n", (round_index / number_of_fields) + 1, hour, minute);

      /* Printer banenummer, niveau og de to hold som skal spille mod hinanden */
      for (field_index = 0; field_index < number_of_fields && SENTINEL == 0; field_index++) {
        printf("Bane %2d | %c | %s vs %s\n", tournament[round_index + field_index].field + 1, translateToChar(tournament[round_index + field_index].level),
                                             tournament[round_index + field_index].team_a, tournament[round_index + field_index].team_b);
        /*
        if (isupper(tournament[round_index + field_index].team_a[0]) != 0 && isupper(tournament[round_index + field_index].team_b[0]) != 0) {

        }
        else {
          SENTINEL = 1;
        }
        */
      }
      printf("\n");
      starting_time += ROUND_LEN;
    }

    else {
      SENTINEL = 1;
    }

    round_index += number_of_fields;
  }

  for (round_index = 0; round_index < number_of_rounds * number_of_fields; round_index += number_of_fields) {
    /* Oversætter tiden fra minutter til timer og minutter */
    hour = starting_time / 60;
    minute = starting_time % 60;


    /* printer bane, niveau, og de to hold, som skal spille mod hinanden */


    starting_time += ROUND_LEN;
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
  printf("Indtast antal baner: ");
  scanf(" %d", &number_of_fields);
  return number_of_fields;
}

/* Prompter brugeren for starttidspunkt.
   Returnerer starttidspunktet i minutter, fra midnat */
int promptForTime(void) {
  int minutes = 0;
  int hours = 0;
  printf("Indtast starttidspunkt (skrevet som tt:mm): ");
  scanf(" %d:%d", &hours, &minutes);
  return hours * 60 + minutes;
}

/* Prompter brugere for et filnavn */
void promptForFileName(char *file_name) {
  printf("Indtast filnavn (afslut med .txt): ");
  scanf(" %s", file_name);
}
