# include "../p1-program/h-files/main.h"
# include "../p1-program/h-files/memoryAllocationScanningSorting.h"
# include "../p1-program/h-files/tournament.h"
# include "../p1-program/h-files/printPrompt.h"


/* Allokerer plads til et array af structs med hold.
   Tager int med antallet af teams, dvs, antallet af elementer
   Returnerer pointer til arrayet. */
team* allocateMemoryTeams(const int number_of_teams) {
  team *teams = malloc(number_of_teams * sizeof(team));             /* Allokerer plads. */

  if (teams != NULL) {                                              /* Returner pointer, hvis der kunne allokeres plads. */
    return teams;
  }
  else {                                                            /* Fejlhåndtering, hvis der ikke kunne allokeres plads. */
    perror("Der skete en fejl under pladsallokeringen");
    exit(EXIT_FAILURE);
  }
}

/* Allokerer plads til et array af structs med kampe.
   Tager int med antallet af matches, dvs, antallet af elementer
   Returnerer pointer til arrayet. */
match* allocateMemoryMatch(const int number_of_matches) {
  match *tournament = NULL;

  tournament = malloc(number_of_matches * sizeof(match));           /* Allokerer plads. */

  if (tournament != NULL) {                                         /* Returner pointer, hvis der kunne allokeres plads. */
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
  int char_index = 0;

  /* Gennemgå hver linje i en fil.
     Returner antallet af linjer der indeholder andet end whitespace.
     Det antages at disse indeholder et holdnavn. */
  while (sentinel == 0) {
    if (fgets(tmp, MAX_NAME_LEN, fp) != NULL) {
      has_content = 0;

      for (char_index = 0; char_index < strlen(tmp); char_index++) {                           /* Check om linjen er tom. (Kun whitespace) */
        if (!isspace(tmp[char_index]) && !has_content) {
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
void scanTeamFile(FILE *fp, const char *file_name, const int number_of_teams, team *all_teams) {
  char level = ' ';
  int team_index = 0;

  /* Gennemgår filen med holdnavne, og kopierer holdnavn og niveau over på de rigtige pladser i et array af structs. */
  for (team_index = 0; team_index < number_of_teams; team_index++) {
    /* Checker om filpointeren er kommet til slutningen af filen,
       og stopper hvis det er sandt. */
    if (feof(fp)) {
      printf("EOF\nMulig fejl\n");
      break;
    }

    fscanf(fp, " %[a-zA-Z0-9 ] %*c %c", all_teams[team_index].team, &level);

    /* Sætter niveauet til stort. */
    level = toupper(level);
    /* Oversætter level fra char til enuem typen 'level'. */
    all_teams[team_index].level = getLevel(level);
  }

  rewind(fp);
}

/* Scanner en stævneplan, returnerer et array af alle hold. */
team *scanFileForTeams(FILE *fp, const int number_of_teams) {
  int scanres = 0;
  int team_index = 0;
  char temp[MAX_LINE_LEN];
  char temp_teams[MAX_LINE_LEN];
  char level;
  match temp_match;
  team *all_teams = NULL;

  rewind(fp);

  all_teams = allocateMemoryTeams(number_of_teams);

  while (fgets(temp, MAX_LINE_LEN, fp) != NULL) {

    if (strlen(temp) > MIN_LINE_LEN) {                                          /* Hvis har en bestemt størrelse, må den indeholde en kamp. */
      scanres = sscanf(temp, " Bane %*d | %c | %[a-zA-Z0-9æøåÆØÅ ] ", &level, temp_teams);

      if (scanres != 2) {
        perror("Error scanning matches");
      }

      temp_match.level = getLevel(level);

      splitTeams(temp_teams, &temp_match);

      /* Indsæt hold, hvis de ikke er der allerede. */
      copyNonExistingTeam(all_teams, temp_match.team_a, temp_match.level, &team_index);
      copyNonExistingTeam(all_teams, temp_match.team_b, temp_match.level, &team_index);
    }
  }

  rewind(fp);
  return all_teams;
}

/* gør noget */
void copyNonExistingTeam(team *all_teams, team temp_team, int level, int *team_index){
  if (doesTeamExist(temp_team, all_teams, *team_index) == 0) {
    strcpy(all_teams[*team_index].team, temp_team.team);
    all_teams[*team_index].level = level;
    (*team_index)++;
  }
}

/* Læser og returnerer antallet af hold i en given fil. */
int getNumberOfTeamsTournament(FILE *fp) {
  int number_of_teams = 0;
  int number_of_matches = 0;

  number_of_matches = getNumberOfMatches(fp);

  /* Antallet af hold udregnes på denne måde, da hvert hold skal have 6 kampe,
     og der indgår 2 hold i hver kamp. Derfor ganges der med 2 hold, divideres med 6 kampe,
     som forkortes til dette */
  number_of_teams = number_of_matches / 3;

  return number_of_teams;
}

/* Chekker om et givent team allerede er indsat i et givent array. */
int doesTeamExist(const team temp_team, const team *all_teams, const int team_index) {
  int comp_index = 0;

  for (comp_index = 0; comp_index < team_index; comp_index++) {
    if (strcmp(temp_team.team, all_teams[comp_index].team) == 0) {
      return 1;
    }
  }
  return 0;
}

/* Tæller og returnerer antallet af kampe i en given fil. */
int getNumberOfMatches(FILE *fp) {
  char temp[5];
  int number_of_matches = 0;

  /* Gå til starten af filen. */
  rewind(fp);

  /* Læser indtil der ikke er mere at læse (EOF). */
  while (fgets (temp, 5, fp) != NULL) {
    /* Hvis der står "bane" betyder det at der er en kamp på linjen.*/
    if (strcmp(temp, "Bane") == 0) {
      number_of_matches += 1;
    }
  }
  return number_of_matches;
}

/* Deler en given string af formen "Hold_a vs Hold_b"
   og assigner de enkelte holdnavne, til holdene i en given match */
void splitTeams(const char *teams, match *match) {
  int sentinel = 0;
  int length = strlen(teams);
  int i = 0;

  /* i er indekset for et tegn i teams arrayet,
     som er en streng på denne form: Bane x | Y | Hold s vs Hold t */
  while (sentinel == 0) {
    if (teams[i] == 'v') {                                                      /* Hvis der er et 'v'. */
      if (teams[i - 1] == ' ' && teams[i + 1] == 's' && teams[i + 2] == ' ') {  /* Check om det er en del af " vs ". */
        strncpy(match->team_a.team, teams, i - 1);                              /* Kopier første team navn, uden sidste mellemrum. */
        match->team_a.team[i - 1] = '\0';                                       /* Definer enden af strengen. */
        strncpy(match->team_b.team, teams + (i + 3), length - (i + 2));         /* Kopier det andet team navn. */
        match->team_b.team[length - (i + 1)] = '\0';                            /* Definer enden af strengen. */
        sentinel = 1;
      }
    }
    i++;
  }
}

/* Finder starttidspunktet for en eksisterende stævneplan. */
int getStartingTime(FILE *fp) {
  int hours = 0;
  int minutes = 0;

  rewind(fp);

  fscanf(fp, "Runde 1: %d:%d", &hours, &minutes);

  rewind(fp);
  return hours * 60 + minutes;
}

/* Finder og returnerer antallet af baner der bruges i en given stævneplan. */
int getNumberOfFields(FILE *fp) {
  char line[MAX_LINE_LEN];                                                      /* Navnet på en bane fylder 7 tegn, hvis der er under 10 baner. */
  char temp[7];                                                                 /* Strengen der testes om det er en bane. */
  int number_of_fields = 0;
  int done = 0;
  int field_number = 0;
  rewind(fp);

  while (fgets (line, MAX_LINE_LEN, fp) != NULL && !done) {                     /* Læser indtil flag (done) er sand. */
    sscanf(line, " %s %d ", temp, &field_number);
    if (strcmp(temp, "Bane") == 0 && field_number == number_of_fields + 1) {    /* Hvis der står "bane" betyder det at der er en kamp på linjen. */
      number_of_fields++;
    }
    else if((strcmp(temp, "Runde") == 0) && field_number == 2) {                /* Hvis scanningen er nået runde 2, afslut. */
      done = 1;
    }
  }
  return number_of_fields;
}

/* Bruger qsort til at sortere hold med niveauet EMPTY til bunden af all_teams. */
void sortArrayByLevel(team *all_teams, const int number_of_teams) {
  qsort(all_teams, number_of_teams, sizeof(team), levelComp);
}

/* Sammenligningsfunktion til qsort.
   Sorterer EMPTY til bunden af all_teams */
int levelComp(const void *a, const void*b) {
  team *team_a = (team*) a;
  team *team_b = (team*) b;

  if (team_a->level == EMPTY) {
    return 1;
  }

  else if (team_b->level == EMPTY) {
    return -1;
  }
  return 0;
}
