/* Prompt brugeren for antal baner og starttidspunkt */
#include <stdio.h>
#include <stdlib.h>
#include "../main.h"

void promptNumberOfFieldsAndStartingTime(int *number_of_fields, int *starting_time);

int main(void) {
  int number_of_fields = 0, starting_time = 0;

  promptNumberOfFieldsAndStartingTime(&number_of_fields, &starting_time);

  /* printf("Baner: %d, minutter: %d\n", number_of_fields, starting_time); */
  
}

void promptNumberOfFieldsAndStartingTime(int *number_of_fields, int *starting_time) {
  int minutter = 0, timer = 0;

  printf("Indtast antal baner: ");
  scanf(" %d", number_of_fields);

  printf("Indtast starttidspunkt (skrevet som tt:mm): ");
  scanf(" %d:%d", &timer, &minutter);

  *starting_time = timer * 60 + minutter;
}
