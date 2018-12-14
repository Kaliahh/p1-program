/* Prototyper */
team* allocateMemoryTeams(const int);
match* allocateMemoryMatch(const int);
int getNumberOfTeams(FILE *);
void scanTeamFile(FILE *, const char *, const int, team *);
void sortArrayByLevel(team *, const int);
int levelComp(const void *a, const void*b);


team *scanFileForTeams(FILE *, const int);
int getNumberOfTeamsTournament(FILE *);
int doesTeamExist(const team, const team *, const int);
int getNumberOfMatches(FILE *);
void splitTeams(const char *, match *);
void copyNonExistingTeam(team *, team, int, int *);
int getStartingTime(FILE *);
int getNumberOfFields(FILE *);
