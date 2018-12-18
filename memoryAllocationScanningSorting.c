# include "../p1-program/h-files/main.h"
# include "../p1-program/h-files/memoryAllocationScanningSorting.h"
# include "../p1-program/h-files/tournament.h"
# include "../p1-program/h-files/printPrompt.h"


/* Allokerer plads til et array af team structs med hold.
   Returnerer pointer til dette array. */
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

/* Allokerer plads til et array af match structs med kampe.
   Returnerer pointer til dette array. */
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

/* Finder og returner antallet af hold, ud fra antallet af linjer i filen med holdlisten.
   Returner -1 hvis der sker en fejl. */
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

  /* Gennemgår filen med holdnavne, og kopierer holdnavn og niveau over på de rigtige pladser i all_teams. */
  for (team_index = 0; team_index < number_of_teams; team_index++) {
    /* Checker om filpointeren er kommet til slutningen af filen,
       og stopper hvis det er sandt. */
    if (feof(fp)) {
      printf("EOF\nMulig fejl\n");
      break;
    }

    fscanf(fp, " %[a-zA-Z0-9 ] %*c %c", all_teams[team_index].team, &level);

    /* Ændrer niveauet til stort bogstav. */
    level = toupper(level);
    /* Oversætter level fra char til int, og gemmer denne i holdets level member */
    all_teams[team_index].level = getLevel(level);
  }

  /* Sætter filpointeren til starten af stævneplanen */
  rewind(fp);
}

/* Scanner en stævneplan, returnerer et array med alle holdene. */
team *scanFileForTeams(FILE *fp, const int number_of_teams) {
  int scanres = 0;
  int team_index = 0;
  char temp[MAX_LINE_LEN];
  char temp_teams[MAX_LINE_LEN];
  char level;
  match temp_match;
  team *all_teams = NULL;

  /* Allokerer plads til et array med alle hold */
  all_teams = allocateMemoryTeams(number_of_teams);

  while (fgets(temp, MAX_LINE_LEN, fp) != NULL) {

    /* Hvis linjen er længere end MIN_LINE_LEN, må den indeholde en kamp. */
    if (strlen(temp) > MIN_LINE_LEN) {
      scanres = sscanf(temp, " Bane %*d | %c | %[a-zA-Z0-9æøåÆØÅ ] ", &level, temp_teams);

      /* Hvis der ikke blev fundet et nivaeu og to hold i linjen */
      if (scanres != 2) {
        perror("Error scanning matches");
      }

      /* Konverterer niveauet fra char til int */
      temp_match.level = getLevel(level);

      /* Splitter holdene i strengen til to forskellige hold */
      splitTeams(temp_teams, &temp_match);

      /* Indsæt hold, hvis de ikke er i all_teams allerede. */
      copyNonExistingTeam(all_teams, temp_match.team_a, temp_match.level, &team_index);
      copyNonExistingTeam(all_teams, temp_match.team_b, temp_match.level, &team_index);
    }
  }

  /* Sætter filpointeren tilbage til starten af stævneplanen */
  rewind(fp);
  return all_teams;
}

/* Kopierer et hold fra over i all_teams, hvis det ikke er der i forvejen */
void copyNonExistingTeam(team *all_teams, team temp_team, int level, int *team_index){
  if (doesTeamExist(temp_team, all_teams, *team_index) == 0) {
    strcpy(all_teams[*team_index].team, temp_team.team);
    all_teams[*team_index].level = level;
    (*team_index)++;
  }
}

/* Chekker om et givent hold allerede er i all_teams. Returnerer 1 hvis det er */
int doesTeamExist(const team temp_team, const team *all_teams, const int team_index) {
  int comp_index = 0;

  for (comp_index = 0; comp_index < team_index; comp_index++) {
    if (strcmp(temp_team.team, all_teams[comp_index].team) == 0) {
      return 1;
    }
  }
  return 0;
}

/* Læser og returnerer antallet af hold i en fil med en stævneplan. */
int getNumberOfTeamsTournament(FILE *fp) {
  int number_of_teams = 0;
  int number_of_matches = 0;

  number_of_matches = getNumberOfMatches(fp);

  /* Antallet af hold udregnes på denne måde, da hvert hold skal have 6 kampe,
     og der indgår 2 hold i hver kamp. Derfor ganges der med 2 hold, divideres med 6 kampe,
     som forkortes til dette */
  number_of_teams = number_of_matches / 3;

  /* Sætter filpointeren til starten af stævneplanen */
  rewind(fp);

  return number_of_teams;
}

/* Tæller og returnerer antallet af kampe i en stævneplan */
int getNumberOfMatches(FILE *fp) {
  char temp[5];
  int number_of_matches = 0;

  /* Læser indtil der ikke er mere at læse (EOF). */
  while (fgets (temp, 5, fp) != NULL) {
    /* Hvis der står "Bane", betyder det at der er en kamp på linjen.*/
    if (strcmp(temp, "Bane") == 0) {
      number_of_matches += 1;
    }
  }
  /* Sætter filpointeren til starten af stævneplanen */
  rewind(fp);
  return number_of_matches;
}

/* Deler en given streng og lægger de enkelte holdnavne,
   over i en midlertidig match struct,
   der bruges til at returnere holdene tilbage til kaldstedet */
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
        match->team_a.team[i - 1] = '\0';                                       /* Definer enden af strengen med nultegnet. */
        strncpy(match->team_b.team, teams + (i + 3), length - (i + 2));         /* Kopier det andet team navn. */
        match->team_b.team[length - (i + 1)] = '\0';                            /* Definer enden af strengen med nultegnet. */
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

  fscanf(fp, "Runde 1: %d:%d", &hours, &minutes);

  /* Sætter filpointeren til starten af stævneplanen */
  rewind(fp);
  return hours * 60 + minutes;
}

/* Finder og returnerer antallet af baner der bruges i en given stævneplan. */
int getNumberOfFields(FILE *fp) {
  char line[MAX_LINE_LEN];      /* Navnet på en bane fylder 7 tegn, hvis der er højest 9 baner. */
  char temp[7];                 /* Strengen der bruges til at teste om der er en bane. */
  int number_of_fields = 0;
  int sentinel = 0;
  int field_number = 0;

  /* Læser fra filen indtil flaget sentinel er sand,
  eller filpointeren kommer til enden af filen*/
  while (fgets (line, MAX_LINE_LEN, fp) != NULL && !sentinel) {
    sscanf(line, " %s %d ", temp, &field_number);

    /* Hvis der står "bane" betyder det at der er en kamp på linjen. */
    if (strcmp(temp, "Bane") == 0 && field_number == number_of_fields + 1) {
      number_of_fields++;
    }
    /* Hvis scanningen er nået runde 2, afslut. */
    else if((strcmp(temp, "Runde") == 0) && field_number == 2) {
      sentinel = 1;
    }
  }
  /* Sætter filpointeren til starten af stævneplanen */
  rewind(fp);
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
