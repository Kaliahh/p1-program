/* Prototyper */
team* allocateMemoryTeams(const int);
match* allocateMemoryMatches (const int);
int getNumberOfTeams(FILE *);
int fillArray(team *, const char *, int);
void sortArrayByLevel(team *, int);
int levelComp(const void *a, const void*b);
