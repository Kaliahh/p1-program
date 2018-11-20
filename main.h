# define MAX_NAME_LEN 30

typedef struct team {
  char team[MAX_NAME_LEN];
  int games;
  int level;
} team;

enum levels {N, A, B, C, EMPTY};
