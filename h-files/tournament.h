/* Prototyper */

/* tournamentCreate */
int createNewTournament(void);
int createTournament(const int, const int, const int, const int, team *, match *);
int createRound(const int, const int, const int, const int, int *, int *, team *, match *);
int findFirstTeam(const int, const int, const int, team *, match *);
int findSecondTeam(const int, const int, team *, match *);
int evaluateRound(const match *, const int, const int);
int isAlreadyInRound(const match *, const int, const int);
int isInPreviousRound(const match *, const int, const int);
int compareTeams(const match *, const match *);
int getNumberOfRounds(const int, const int);
int getLevel(const char);

/* tournamentUpdate */
int updateTournament(FILE *);
team *modifyTeams(FILE *, const int, const int, team *, int *, void (*)(const team *, const int, const int, team *));
team *updateTeams(const team *, const int);
void getTeams(const int, const int, const team *, const int, team *);
void getTeamNames(const int, char *);
int checkTeam(const char *, const team *, const int);
void copyTeams(const team *, const int, const int, team *);
void deleteTeams(const team *, const int, const int, team *);
