


  /*int team_index = 0;
  int time = 0;
  int hour = 0;
  int minute = 0;


  *number_of_teams = getNumberOfTeamsTournament(fp);*/

  /* Hvis et hold kommer senere bedømmes turneringsplanen efter dette.
     Tager ikke højde for, hvis to hold vil komme senere.
     Der bliver først genereret et kampprogram, som passer til det første hold.
     Når der så skal genereres et kampprogram som passer til det andet hold,
     vil det overskrive det første kampprogram, og ikke tage højde for deres behov.
     (SKAL LIGE OVEREVEJES. evt. tilføje start- og sluttidspunkt i structet team.) */
  /*else if (choice == 3) {
    printf("Indtast holdnavnet på det hold der skal ændres\n>> ");
    scanf(" %[-':.,?!a-zA-Z0-9 ]", team);

    printf("Indtast startstidspunkt (med : mellem tallene)\n>> ");
    scanf(" %d:%d", &hour, &minute);

    if (hour > 60 || minute > 60) {
      printf("Ikke et gyldigt tidspunkt. Prøv igen.\n>> ");
      scanf(" %d:%d", &hour, &minute);
    }*/

    /* Kører ikke igen hvis der bliver tastet et bogstav. Bogstavet bliver læst som 0. */

  /*  time = hour * 60 + minute;

    changeStartingTime(all_teams, team, *number_of_teams, time);
  }*/
  /* Hvis et hold kommer senere bedømmes turneringsplanen efter dette.
     Tager ikke højde for, hvis to hold vil afsted tidligere.
     Se kommentar fra l. 82. Det samme gælder for denne funktion. */
  /*else if (choice == 4) {
    printf("Indtast holdnavnet på det hold der skal ændres\n>> ");
    scanf(" %[-':.,?!a-zA-Z0-9 ]", team);

    printf("Indtast sluttidspunkt (med : mellem tallene)\n>> ");
    scanf(" %d:%d", &hour, &minute);

    if (hour > 60 || minute > 60) {
      printf("Ikke et gyldigt tidspunkt. Prøv igen.\n>> ");
      scanf(" %d:%d", &hour, &minute);
    }
*/
    /* Kører ikke igen hvis der bliver tastet et bogstav. Bogstavet bliver læst som 0. */
/*
    time = hour * 60 + minute;

    changeEndingTime(all_teams, team, *number_of_teams, time);
  }
  else if (choice == 0) {
    rewind(fp);
    *number_of_teams += (number_of_new_teams > 0) ? number_of_new_teams : 0;
    return all_teams;
  }
  else {

  }

  rewind(fp);

  *number_of_teams += (number_of_new_teams > 0) ? number_of_new_teams : 0;
  return all_teams;
}*/
