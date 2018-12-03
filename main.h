# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <ctype.h>
# include <math.h>

# define MAX_NAME_LEN 30
# define GAMES_PR_TEAM 6
# define ROUND_LEN 8

/* Struct for et hold */
typedef struct {
  char team[MAX_NAME_LEN];
  int games;
  int level;
} team;

/* Struct for en kamp */
typedef struct{
  char team_a[MAX_NAME_LEN];
  char team_b[MAX_NAME_LEN];
  int level;
  int field;
} match;

/* Enumeration for niveauer */
enum levels {N, A, B, C, EMPTY};
