/* Prototyper */
team* allocateMemoryTeams(const int);
match* allocateMemoryTournament(const int);
int getNumberOfTeams(FILE *);
void fillArray(FILE *, const char *, const int, team *);
void sortArrayByLevel(team *, const int);
int levelComp(const void *a, const void*b);


team *scanFileForTeams(FILE *, const int);
int getNumberOfTeamsTournament(FILE *);
int doesTeamExist(const team, const team *, const int);
int getNumberOfMatches(FILE *);
void sgetTeams(const char *, match *);
int getStartingTime(FILE *);
int getNumberOfFields(FILE *);
