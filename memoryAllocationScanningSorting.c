# include "main.h"
# include "memoryAllocationScanningSorting.h"


/* Allokerer plads til et array af structs med hold.
   Returnerer pointer til arrayet */
team* allocateMemoryTeams(const int number_of_teams) {
  team *all_teams = malloc(number_of_teams * sizeof(team)); /* Allokerer plads */
  if (all_teams != NULL) { /* Returner pointer, hvis der kunne allokeres plads */
    return all_teams;
  }
  else { /* Fejlhåndtering, hvis der ikke kunne allokeres plads */
    printf("Der skete en fejl under pladsallokeringen \n");
    return all_teams;
  }
}

/* Allokerer plads til et array af structs med kampe.
   Returnerer pointer til arrayet */
match* allocateMemoryMatches(const int number_of_matches) {
  match *all_matches = malloc(number_of_matches * sizeof(match)); /* Allokerer plads */
  if (all_matches != NULL) { /* Returner pointer, hvis der kunne allokeres plads */
    return all_matches;
  }
  else { /* Fejlhåndtering, hvis der ikke kunne allokeres plads */
    printf("Der skete en fejl under pladsallokeringen \n");
    return all_matches;
  }
}

/* Find og returner antallet af linjer med indhold i en fil.
   Returner -1 Hvis der sker en fejl. */
int getNumberOfTeams(FILE *fp) {
  char tmp[MAX_NAME_LEN];
  int number_of_teams = 0, has_content = 0, SENTINEL = 0;

  /* Gennemgå hver linje i en fil.
     Returner antallet af linjer der indeholder andet end whitespace.
     Det antages at disse indeholder et holdnavn */
  while (SENTINEL == 0) {
    if (fgets(tmp, MAX_NAME_LEN, fp) != NULL) {
      has_content = 0;
      for (int i = 0; i < strlen(tmp); i++) { /* Check om linjen er tom. (Kun whitespace) */
        if (!isspace(tmp[i]) && !has_content) {
          has_content = 1;
        }
      }
      if (has_content) { /* Forstør antallet hvis der er indhold på linjen */
        number_of_teams++;
      }
    }
    else {
      SENTINEL = 1;
    }
  }

  /* Saetter fil position til starten af filen */
  rewind(fp);

  return number_of_teams - 1;
}

/* Fylder et array med hold */
void fillArray(FILE *fp, team *all_teams, const char *file_name, const int num_of_teams) {
  char dump = ' ', level = ' ';

  /* Fylder alle teams med nul-tegn,
     sætter alle niveauer til EMPTY
     og antallet af spillede kampe til 0 */
  for (int k = 0; k < num_of_teams; k++) {
    all_teams[k].level = EMPTY;
    all_teams[k].games = 0;
    for (int j = 0; j < MAX_NAME_LEN; j++) {
      all_teams[k].team[j] = '\0';
    }
  }


  /* Gennemgår filen med holdnavne, og kopierer holdnavn og niveau over på de rigtige pladser i et array af structs */
  for (int i = 0; i < num_of_teams; i++) {
    /* Checker om filpointeren er kommet til slutningen af filen,
       og stopper hvis det er sandt */
    if (feof(fp)) {
      printf("EOF\nMulig fejl\n");
      break;
    }

    fscanf(fp, " %[abcdefghijklmnopqrstuvwxyzæøåABCDEFGHIJKLMNOPQRSTUVWXYZÆØÅ0123456789 ]" " %c" " %c", all_teams[i].team, &dump, &level);

    /* Sætter niveauet til stort */
    level = toupper(level);

    all_teams[i].level = (level == 'N') ? N :
                         (level == 'A') ? A :
                         (level == 'B') ? B :
                         (level == 'C') ? C : EMPTY;
  }

  rewind(fp);
}

/* Bruger qsort til at sortere arrayet af hold efter niveau */
void sortArrayByLevel(team *all_teams, const int number_of_teams) {
  qsort(all_teams, number_of_teams, sizeof(team), levelComp);
}

/* Sammenligningsfunktion til qsort. Sammenligner to holds niveauer */
int levelComp (const void *a, const void*b) {
  team *team_a = (team*) a;
  team *team_b = (team*) b;

  return team_a->level - team_b->level;
}
