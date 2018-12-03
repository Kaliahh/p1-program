/* Prototyper */
team* allocateMemoryTeams(const int);
match* allocateMemoryMatches (const int);
int getNumberOfTeams(FILE *);
void fillArray(FILE *fp, team *, const char *, const int);
void sortArrayByLevel(team *, const int);
int levelComp(const void *a, const void*b);
