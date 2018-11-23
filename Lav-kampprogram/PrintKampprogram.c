/* Printer sjovt nok kampprogrammet */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../main.h"
#define ROUND_LGT 8

void printToFile(match *tournament, int starting_time, int number_of_rounds, int number_of_fields);
void printToTerminal(match *tournament, int starting_time, int number_of_rounds, int number_of_fields);
void printProgram(match *tournament, int starting_time, int number_of_rounds, int number_of_fields);
char translateToChar(int level);

/*
int main(void) {
  int number_of_fields = 2, number_of_rounds = 6, starting_time = 570;
  match tournament[12];

  strcpy(tournament[0].team_a, "Hold 1");
  strcpy(tournament[1].team_a, "Hold 2");
  strcpy(tournament[2].team_a, "Hold 3");
  strcpy(tournament[3].team_a, "Hold 1");
  strcpy(tournament[4].team_a, "Hold 2");
  strcpy(tournament[5].team_a, "Hold 3");
  strcpy(tournament[6].team_a, "Hold 1");
  strcpy(tournament[7].team_a, "Hold 2");
  strcpy(tournament[8].team_a, "Hold 3");
  strcpy(tournament[9].team_a, "Hold 1");
  strcpy(tournament[10].team_a, "Hold 2");
  strcpy(tournament[11].team_a, "Hold 2");


  strcpy(tournament[0].team_b, "Hold 2");
  strcpy(tournament[1].team_b, "Hold 3");
  strcpy(tournament[2].team_b, "Hold 1");
  strcpy(tournament[3].team_b, "Hold 2");
  strcpy(tournament[4].team_b, "Hold 3");
  strcpy(tournament[5].team_b, "Hold 1");
  strcpy(tournament[6].team_b, "Hold 2");
  strcpy(tournament[7].team_b, "Hold 3");
  strcpy(tournament[8].team_b, "Hold 1");
  strcpy(tournament[9].team_b, "Hold 2");
  strcpy(tournament[10].team_b, "Hold 3");
  strcpy(tournament[11].team_b, "Hold 3");


  tournament[0].level = 0;
  tournament[1].level = 0;
  tournament[2].level = 0;
  tournament[3].level = 0;
  tournament[4].level = 1;
  tournament[5].level = 1;
  tournament[6].level = 1;
  tournament[7].level = 2;
  tournament[8].level = 2;
  tournament[9].level = 2;
  tournament[10].level = 2;
  tournament[11].level = 2;

  tournament[0].field = 1;
  tournament[1].field = 2;
  tournament[2].field = 1;
  tournament[3].field = 2;
  tournament[4].field = 1;
  tournament[5].field = 2;
  tournament[6].field = 1;
  tournament[7].field = 2;
  tournament[8].field = 1;
  tournament[9].field = 2;
  tournament[10].field = 1;
  tournament[11].field = 2;

  printProgram(tournament, starting_time, number_of_rounds, number_of_fields);

  return 0;
}
*/

/* Spørger brugeren om hvad der ønskes at gøre med turneringsplanen */
void printProgram(match *tournament, int starting_time, int number_of_rounds, int number_of_fields) {
  int n = 0;

  printf("Print til terminalen - tast 1. Print til fil - tast 2:\n");
  scanf(" %d", &n);

  if(n == 1) {
    printToTerminal(tournament, starting_time, number_of_rounds, number_of_fields);

    printf("\nEr det i orden? Skal den printes til en fil - tast 1. Er det ikke i orden - tast Q\n");
    scanf(" %d", &n);

    if (n == 1) {
      printToFile(tournament, starting_time, number_of_rounds, number_of_fields);
    }
  }
  else if(n == 2) {
    printToFile(tournament, starting_time, number_of_rounds, number_of_fields);
  }
  else {
    printf("Fejl\n");
    printProgram(tournament, starting_time, number_of_rounds, number_of_fields);
  }
}

/* Printer turneringsplanen til en fil */
void printToFile (match *tournament, int starting_time, int number_of_rounds, int number_of_fields) {                       
  int i = 0, j = 0, time = starting_time;
  int hour = 0, minute = 0;
  FILE *fp = fopen("tournamentPlan.txt", "w");

  for (i = 0; i < number_of_rounds * number_of_fields; i += number_of_fields) {
    /* oversætter tiden fra minutter til timer og minutter */
    hour = time / 60;
    minute = time % 60;

    /* printer runde nummer og tidspunktet for hvornår der skal spilles */
    fprintf (fp, "Runde %d:\n%.2d:%.2d\n", (i / number_of_fields) + 1, hour, minute);

    /* printer bane nummer, niveau, og de to hold, som skal spille mod hinanden */
    for (j = 0; j < number_of_fields; j++) {
      fprintf(fp, "Bane %d | %c | %s vs %s\n", tournament[i + j].field + 1, translateToChar(tournament[i + j].level), 
                                               tournament[i + j].team_a, tournament[i + j].team_b);
    }

    fprintf(fp, "\n");

    time += ROUND_LGT;
  }
}

/* Printer turneringsplanen til terminalen */
void printToTerminal (match *tournament, int starting_time, int number_of_rounds, int number_of_fields) {                       
  int i = 0, j = 0, time = starting_time;
  int hour = 0, minute = 0;

  for (i = 0; i < number_of_rounds * number_of_fields; i += number_of_fields) {
    /* oversætter tiden fra minutter til timer og minutter */
    hour = time / 60;
    minute = time % 60;

    /* printer runde nummer og tidspunktet for hvornår der skal spilles */
    printf("Runde %d:\n%.2d:%.2d\n", (i / number_of_fields) + 1, hour, minute);

    /* printer bane, niveau, og de to hold, som skal spille mod hinanden */
    for (j = 0; j < number_of_fields; j++) {
      printf("Bane %d | %c | %s vs %s\n", tournament[i + j].field + 1, translateToChar(tournament[i + j].level), 
                                          tournament[i + j].team_a, tournament[i + j].team_b);
    }

    printf("\n");

    time += ROUND_LGT;
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
      printf("Fejl\n");
      return 'E';
  }
}
