/* Prototyper */
team* allocateMemoryTeams(const int);
match* allocateMemoryMatches (const int);
int getNumberOfTeams(FILE *);
void fillArray(FILE *, team *, const char *, const int);
void sortArrayByLevel(team *, const int);
int levelComp(const void *a, const void*b);


team *scanFileForTeams(FILE *, int, const int);
int getNumberOfTeamsTournament(FILE *);
int doesTeamExist(team, team *, const int);
int getNumberOfMatches(FILE *);
void sgetTeams(match *, char *);
int getStartingTime(FILE *);
