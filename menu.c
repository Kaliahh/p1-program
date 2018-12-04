/* Menu der spørger om brugeren vil redigere et eksisterende kampprogram, eller lave et nyt kampprogram */
# include "../p1-program/h-files/main.h"

int menu(void);

int main(void) {

  menu();

  return 0;
}

int menu(void) {
  int choice = 0;

  printf("#####################  MENU  #####################\n\n");
  printf("(1) Lav et nyt kampprogram\n");
  printf("(2) Rediger et eksisterende kampprogram\n");
  printf("(3) Lav skabelon til liste af holdnavne\n");
  printf("(4) Afslut\n");
  printf("\nVælg et eller andet: ");
  scanf(" %d", &choice);

  if (choice == 1) {
    /* createNewTournament(); */
  }

  else if (choice == 2) {
    /* editMenu(); */
  }

  else if (choice == 3) {
    /* createTemplate(); */
  }

  else if (choice == 4) {
    return 0;
  }

  else {
    printf("\nUgyldigt input, prøv igen\n");
    sleep(1);
    menu();
  }

  return 0;
}
