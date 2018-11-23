/* Prompt brugeren for antal baner og starttidspunkt */
#include <stdio.h>
#include <stdlib.h>
#include "../main.h"

int promptForFields();
int promptForTime();

int main(void) {
  int number_of_fields = 0, starting_time = 0;

  number_of_fields = promptForFields();
  starting_time = promptForTime();

  /* printf("Baner: %d, minutter: %d\n", number_of_fields, starting_time); */

}

int promptForFields() {
  int antal_baner = 0;
  printf("Indtast antal baner: ");
  scanf(" %d", number_of_fields);
  return antal_baner;
}

int promptForTime() {
  int minutter = 0, timer = 0;
  printf("Indtast starttidspunkt (skrevet som tt:mm): ");
  scanf(" %d:%d", &timer, &minutter);

  return timer * 60 + minutter;
}
