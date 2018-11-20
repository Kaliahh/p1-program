/* Fyld et array med hold fra en fil */

# include "../main.h"
# include <stdio.h>
# include <string.h>
# include <ctype.h>

int fillArray(team *, const char *, int);

int main(void) {

  team all_teams[40];
  char file_name[30] = "holdnavne.txt";
  int num_of_teams = 7;

  fillArray(all_teams, file_name, num_of_teams);

  return 0;
}


int fillArray (team *all_teams, const char *file_name, int num_of_teams) {

  FILE * fP;
  char temp[30];
  int j = 0;

  fP = fopen(file_name, "r");

  if (fP == NULL) {
     perror("Error opening file");
     return -1;
  }


  for (int i = 0; i < num_of_teams; i++) {

    fgets(temp, 60, fP);

    while (temp[j] != '\n') {
      if (isalnum(temp[j]) == 0 && isspace(temp[j]) == 0) {
        strncpy(all_teams[i].team, temp, j);
      }

      j++;
    }

    printf("%s\n", all_teams[i].team);
    //printf("%s\n", temp);

    j = 0;
  }

  fclose(fP);

  return 0;
}
