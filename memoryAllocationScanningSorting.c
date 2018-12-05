# include "../p1-program/h-files/main.h"
# include "../p1-program/h-files/memoryAllocationScanningSorting.h"


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

  return number_of_teams;
}

/* Fylder et array med hold */
void fillArray(FILE *fp, team *all_teams, const char *file_name, const int number_of_teams) {
  char dump = ' ', level = ' ';

  /* Fylder alle teams med nul-tegn,
     sætter alle niveauer til EMPTY
     og antallet af spillede kampe til 0 */
  for (int k = 0; k < number_of_teams; k++) {
    all_teams[k].level = EMPTY;
    all_teams[k].games = 0;
    for (int j = 0; j < MAX_NAME_LEN; j++) {
      all_teams[k].team[j] = '\0';
    }
  }


  /* Gennemgår filen med holdnavne, og kopierer holdnavn og niveau over på de rigtige pladser i et array af structs */
  for (int i = 0; i < number_of_teams; i++) {
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



team *scanFileForTeams (FILE *fp, int number_of_teams, const int number_of_new_teams) {
  int scanres = 0, i = 0;
  char temp[200];
  char temp_teams[200];
  match temp_match;
  team temp_team_a, temp_team_b;
  char level;

  rewind(fp);

  number_of_teams += number_of_new_teams;

  team *all_teams = (team*) malloc (number_of_teams * sizeof(team));

  while (fgets(temp, 200, fp) != NULL) {
  /*  scanres = fscanf (fp, " %[-A-Za-z0-9| ]", temp);
    if (scanres != 1) {
      printf("Fejl i scanning af fil\n");
    } */
    if (strlen(temp) > MIN_LINE_LEN) {     /* Hvis har en bestemt størrelse, må den indeholde en kamp */
      scanres = sscanf(temp, " Bane %*d | %c | %[a-zA-Z0-9æøåÆØÅ ] ", &level, temp_teams);
      if(scanres != 2) {
        perror("Error scanning matches");
      }
      temp_match.level = (enum levels) level; /* typecast til levels (int), og put den i struct */
      sgetTeams(&temp_match, temp_teams);
      /* Kopier data */
      strcpy(temp_team_a.team, temp_match.team_a.team);
      temp_team_a.level = temp_match.level;
      strcpy(temp_team_b.team, temp_match.team_b.team);
      temp_team_b.level = temp_match.level;

      /* Indsæt hold, hvis de ikke er der allerede */
      if (doesTeamExist(temp_team_a, all_teams, i) == 0) {
        strcpy(all_teams[i].team, temp_team_a.team);
        all_teams[i].level = temp_team_a.level;
        i++;
      }
      if (doesTeamExist(temp_team_b, all_teams, i) == 0) {
        strcpy(all_teams[i].team, temp_team_b.team);
        all_teams[i].level = temp_team_b.level;
        i++;
      }
    }
  }

  rewind(fp);
  return all_teams;
}

/* Læser og returnerer antallet af hold i en given fil */
int getNumberOfTeamsTournament(FILE *fp) {
  int number_of_matches;
  number_of_matches = getNumberOfMatches(fp);
  /* Tidligere: (number_of_matches - 1) / 3
     Nu: */
  return number_of_matches / 3; /* Forklar udregningen */
}

/* Chekker om et givent team allerede er indsat i et givent array */
int doesTeamExist (team temp_team, team *all_teams, const int index) {
  int j = 0, exists = 0;
  for (j = 0; j < index && exists == 0; j++) {
    if (strcmp(temp_team.team, all_teams[j].team) == 0) {
      exists++;
    }
  }
  return exists;
}

/* Kopi af funktion -- skal muligvis slettes */
/* Tæller og returnerer antallet af kampe i en given fil */
int getNumberOfMatches (FILE *fp) {
  char dump[5];
  int number_of_matches = 0;

  rewind(fp); /* Gå til starten af filen */

  while (fgets (dump, 5, fp) != NULL) { /* Læser indtil der ikke er mere at læse (EOF) */
    if (strcmp(dump, "Bane") == 0) {    /* Hvis der står "bane" betyder det at der er en kamp på linjen */
      number_of_matches += 1;
    }
  }
  /* For testing purposes
  printf("%d matches\n", number_of_matches);
  */
  return number_of_matches;
}

/* */
void sgetTeams(match* match, char* teams) {
  int SENTINEL = 0;
  int length = strlen(teams), i = 0;
  while(SENTINEL == 0) {
    if(teams[i] == 'v') {   /* Hvis der er et 'v' */
      if(teams[i-1] == ' ' && teams[i+1] == 's' && teams[i+2] == ' ') {  /* Check om det er en del af " vs " */
        strncpy((*match).team_a.team, teams, i - 1); /* Kopier første team navn, uden sidste mellemrum */
        (*match).team_a.team[i - 1] = '\0';  /* Definer enden af strengen */
        strncpy((*match).team_b.team, teams + (i + 3), length - (i+2)); /* Kopier det andet team navn */
        (*match).team_b.team[length - (i+1)] = '\0';  /* Definer enden af strengen */
        SENTINEL = 1;
      }
    }
    i++;
  }
}
