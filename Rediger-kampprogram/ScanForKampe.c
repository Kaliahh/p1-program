# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "../h-files/main.h"

match *scanFileForMatches (FILE *fp, const int number_of_matches);
int getNumberOfMatches (FILE *fp);

int main(void) {
  int number_of_matches = 0, i = 0;
  match *all_matches = NULL;

  FILE *fp = fopen ("turneringsplan.txt", "r");

  /* Checker om filen blev åbnet */
  if (fp == NULL) {
     perror("Error opening file");
     return -1;
  }

  number_of_matches = getNumberOfMatches(fp);
  all_matches = scanFileForMatches(fp, number_of_matches);

  for (i = 0; i < number_of_matches; i++) {
    printf("%s vs %s | %c\n", all_matches[i].team_a, all_matches[i].team_b, all_matches[i].level);
  }

  fclose (fp);
  free(all_matches);

  return 0;
}

match *scanFileForMatches (FILE *fp, const int number_of_matches) {
  int scanres = 0, dump = 0, i = 0;
  char temp[200];
  char level;

  match *all_matches = (match*) malloc(number_of_matches * sizeof (match));

  rewind(fp);
  /*
  while (feof(fp) == 0) {
    scanres = fscanf (fp, " %[-A-Za-z0-9| ]", temp);
    printf("Scanres = %d\n", scanres);
    if (scanres != 1) {
      printf ("Fejl i scanning af fil\n");
    }
    if (strlen(temp) > MIN_LINE_LEN) {
      sscanf (temp, " Bane %d | %d | %[A-Za-z0-9 ] vs %[A-Za-z0-9 ] ", &dump, &all_matches[i].level, all_matches[i].team_a, all_matches[i].team_b);
      i++;
    }
  }
*/

  while (fgets(temp, 200, fp) != NULL) {
    if (strlen(temp) > MIN_LINE_LEN) {
      scanres = sscanf(temp, " Bane %d | %c | %[a-zA-Z0-9 ] vs %[a-zA-Z0-9 ] ", &dump, &level, all_matches[i].team_a, all_matches[i].team_b);
      i++;
      printf("Scanres = %d\n", scanres);
    }
  }

  return all_matches;
}


int getNumberOfMatches (FILE *fp) {
  char dump[5];
  int number_of_matches = 0;

  while (feof(fp) == 0) {
    fgets (dump, 5, fp);

    if (strcmp(dump, "Bane") == 0) {
      number_of_matches += 1;
    }
  }
  printf("%d\n", number_of_matches);
  return number_of_matches;
}
