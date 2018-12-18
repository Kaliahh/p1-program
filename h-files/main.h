# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <ctype.h>
# include <math.h>

# define MAX_NAME_LEN 30
# define GAMES_PR_TEAM 6
# define ROUND_LEN 8
# define MIN_LINE_LEN 16
# define MAX_LINE_LEN 200
# define CHECK_NUM 100000
# define FIRST 0

# define LOWERCASE "abcdefghijklmnopqrstuvwxzyæøå"
# define UPPERCASE "ABCDEFGHIJKLMNOPQRSTUVWXZYÆØÅ"
# define SPECIAL "-':.,?!"
# define NUMBERS "0123456789"

/* Struct for et hold */
typedef struct {
  char team[MAX_NAME_LEN];
  int games;
  int level;
  int starting_time;
  int ending_time;
} team;

/* Struct for en kamp */
typedef struct{
  team team_a;
  team team_b;
  int level;
  int field;
} match;

/* Enumeration for niveauer */
enum levels {EMPTY, N, A, B, C};

/* Enumerationer for ændringer */
enum modifiers {REMOVE, ADD};

/* Enumerationer for kvaliteten af stævneplanen */
enum quality {FAST = 1, BEST};
