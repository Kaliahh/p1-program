# include "../p1-program/h-files/main.h"
# include "../p1-program/h-files/memoryAllocationScanningSorting.h"
# include "../p1-program/h-files/printPrompt.h"


/* Allokerer plads til et array af structs med hold.
   Tager int med antallet af teams, dvs, antallet af elementer
   Returnerer pointer til arrayet. */
team* allocateMemoryTeams(const int number_of_teams) {
  team *all_teams = malloc(number_of_teams * sizeof(team));         /* Allokerer plads. */

  if (all_teams != NULL) {                                          /* Returner pointer, hvis der kunne allokeres plads. */
    return all_teams;
  }
  else {                                                            /* Fejlhåndtering, hvis der ikke kunne allokeres plads. */
    perror("Der skete en fejl under pladsallokeringen");
    exit(EXIT_FAILURE);
  }
}

/* Allokerer plads til et array af structs med kampe.
   Tager int med antallet af matches, dvs, antallet af elementer
   Returnerer pointer til arrayet. */
match* allocateMemoryTournament(const int number_of_matches) {
  match *tournament = NULL;

  tournament = malloc(number_of_matches * sizeof(match));   /* Allokerer plads. */

  if (tournament != NULL) {                                        /* Returner pointer, hvis der kunne allokeres plads. */
    return tournament;
  }
  else {                                                            /* Fejlhåndtering, hvis der ikke kunne allokeres plads. */
    perror("Der skete en fejl under pladsallokeringen");
    exit(EXIT_FAILURE);
  }
}

/* Find og returner antallet af linjer med indhold i en fil.
   Returner -1 hvis der sker en fejl.
   Der antages at fil position er i starten af filen,
   og når funktionen er kørt ender den i slutningen af filen. */
int getNumberOfTeams(FILE *fp) {
  char tmp[MAX_NAME_LEN];
  int number_of_teams = 0;
  int has_content = 0;
  int sentinel = 0;
  int i = 0;

  /* Gennemgå hver linje i en fil.
     Returner antallet af linjer der indeholder andet end whitespace.
     Det antages at disse indeholder et holdnavn. */
  while (sentinel == 0) {
    if (fgets(tmp, MAX_NAME_LEN, fp) != NULL) {
      has_content = 0;

      for (i = 0; i < strlen(tmp); i++) {                           /* Check om linjen er tom. (Kun whitespace) */
        if (!isspace(tmp[i]) && !has_content) {
          has_content = 1;
        }
      }
      if (has_content) {                                            /* Forstør antallet hvis der er indhold på linjen */
        number_of_teams++;
      }
    }
    else {
      sentinel = 1;
    }
  }

  /* Sætter fil position til starten af filen. */
  rewind(fp);

  return number_of_teams;
}

/* Fylder et arrayet all_teams med holdnavne og niveau. */
void fillArray(FILE *fp, team *all_teams, const char *file_name, const int number_of_teams) {
  char level = ' ';
  int i, j, k;

  /* Fylder alle teams med nul-tegn,
     sætter alle niveauer til EMPTY
     og antallet af spillede kampe til 0. */
  for (k = 0; k < number_of_teams; k++) {
    all_teams[k].level = EMPTY;
    all_teams[k].games = 0;

    for (j = 0; j < MAX_NAME_LEN; j++) {
      all_teams[k].team[j] = '\0';
    }
  }


  /* Gennemgår filen med holdnavne, og kopierer holdnavn og niveau over på de rigtige pladser i et array af structs. */
  for (i = 0; i < number_of_teams; i++) {
    /* Checker om filpointeren er kommet til slutningen af filen,
       og stopper hvis det er sandt. */
    if (feof(fp)) {
      printf("EOF\nMulig fejl\n");
      break;
    }

    fscanf(fp, " %[a-zA-Z0-9 ] %*c %c", all_teams[i].team, &level);

    /* Sætter niveauet til stort. */
    level = toupper(level);
    /* Oversætter level fra char til enuem typen 'level'. */
    all_teams[i].level = getLevel(level);
  }

  rewind(fp);
}

/* Bruger qsort til at sortere arrayet af hold efter niveau. */
/*void sortArrayByLevel(team *all_teams, const int number_of_teams) {
  qsort(all_teams, number_of_teams, sizeof(team), levelComp);
}
*/
/* Sammenligningsfunktion til qsort. Sammenligner to holds niveauer. */
/*int levelComp(const void *a, const void*b) {
  team *team_a = (team*) a;
  team *team_b = (team*) b;

  return team_a->level - team_b->level;
}*/


/* Scanner et kampprogram, returnerer et array af alle hold. */
team *scanFileForTeams(FILE *fp, int number_of_teams) {
  int scanres = 0, i = 0;
  char temp[MAX_LINE_LEN];
  char temp_teams[MAX_LINE_LEN];
  match temp_match;
  team temp_team_a, temp_team_b;
  char level;
  team *all_teams = NULL;

  rewind(fp);

  all_teams = (team*) malloc (number_of_teams * sizeof(team));

  while (fgets(temp, MAX_LINE_LEN, fp) != NULL) {
    if (strlen(temp) > MIN_LINE_LEN) {                              /* Hvis har en bestemt størrelse, må den indeholde en kamp. */
      scanres = sscanf(temp, " Bane %*d | %c | %[a-zA-Z0-9æøåÆØÅ ] ", &level, temp_teams);
      if (scanres != 2) {
        perror("Error scanning matches");
      }
      temp_match.level = getLevel(level);

      sgetTeams(&temp_match, temp_teams);
      /* Kopier navne og niveau fra kampen, til holdene */
      temp_team_a = temp_match.team_a;
      temp_team_b = temp_match.team_b;
      /* De enkelte teams i temp_match, har ikke korrekt niveau */
      temp_team_a.level = temp_match.level;
      temp_team_b.level = temp_match.level;

      /* Indsæt hold, hvis de ikke er der allerede. */
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

/* Læser og returnerer antallet af hold i en given fil. */
int getNumberOfTeamsTournament(FILE *fp) {
  int number_of_matches;
  number_of_matches = getNumberOfMatches(fp);
  /* Tidligere: (number_of_matches - 1) / 3
     Nu: */
  return number_of_matches / 3; /* Forklar udregningen. */
}

/* Chekker om et givent team allerede er indsat i et givent array. */
int doesTeamExist(team temp_team, team *all_teams, const int index) {
  int j = 0, exists = 0;
  for (j = 0; j < index && exists == 0; j++) {
    if (strcmp(temp_team.team, all_teams[j].team) == 0) {
      exists++;
    }
  }
  return exists;
}

/* Tæller og returnerer antallet af kampe i en given fil. */
int getNumberOfMatches(FILE *fp) {
  char dump[5];
  int number_of_matches = 0;

  rewind(fp);                                                       /* Gå til starten af filen. */

  while (fgets (dump, 5, fp) != NULL) {                             /* Læser indtil der ikke er mere at læse (EOF). */
    if (strcmp(dump, "Bane") == 0) {                                /* Hvis der står "bane" betyder det at der er en kamp på linjen.*/
      number_of_matches += 1;
    }
  }
  return number_of_matches;
}

/* Deler en given string af formen "Hold_a vs Hold_b"
   og assigner de enkelte holdnavne, til holdene i en given match */
void sgetTeams(match* match, char* teams) {
  int sentinel = 0;
  int length = strlen(teams), i = 0;
  while (sentinel == 0) {
    if (teams[i] == 'v') {                                                /* Hvis der er et 'v'. */
      if (teams[i-1] == ' ' && teams[i+1] == 's' && teams[i+2] == ' ') {  /* Check om det er en del af " vs ". */
        strncpy((*match).team_a.team, teams, i - 1);                      /* Kopier første team navn, uden sidste mellemrum. */
        (*match).team_a.team[i - 1] = '\0';                               /* Definer enden af strengen. */
        strncpy((*match).team_b.team, teams + (i + 3), length - (i+2));   /* Kopier det andet team navn. */
        (*match).team_b.team[length - (i+1)] = '\0';                      /* Definer enden af strengen. */
        sentinel = 1;
      }
    }
    i++;
  }
}

/* Finder starttidspunktet for en eksisterende turneringsplan. */
int getStartingTime(FILE *fp) {
  int hours = 0;
  int minutes = 0;
  rewind(fp);

  fscanf(fp, "Runde 1: %d:%d", &hours, &minutes);

  rewind(fp);
  return hours * 60 + minutes;
}

/* Finder og returnerer antallet af baner der bruges i et givent kampprogram. */
int getNumberOfFields(FILE *fp) {
  char line[MAX_LINE_LEN];                                                               /* Navnet på en bane fylder 7 tegn, hvis der er under 10 baner. */
  char test[7];                                                                 /* Strengen der testes om det er en bane. */
  int number_of_fields = 0, done = 0, field_number = 0;
  rewind(fp);

  while (fgets (line, MAX_LINE_LEN, fp) != NULL && !done) {                              /* Læser indtil flag (done) er sand. */
    sscanf(line, " %s %d ", test, &field_number);
    if (strcmp(test, "Bane") == 0 && field_number == number_of_fields + 1) {    /* Hvis der står "bane" betyder det at der er en kamp på linjen. */
      number_of_fields++;
    }
    else if((strcmp(test, "Runde") == 0) && field_number == 2) {                /* Hvis scanningen er nået runde 2, afslut. */
      done = 1;
    }
  }
  return number_of_fields;
}
