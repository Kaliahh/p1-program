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
team *addTeams (FILE *, const int, team *, int *);
team *removeTeams(FILE *, const int, team *, int *);
team *updateTeams(const team *, const int);
void getNewTeams(int , int, const team *, team *);
int checkTeam(const char *, const team *, const int);
void getTeamNames(const int, char *);
void copyTeams(const team *, team *, const int, const int );
void deleteTeams(const team *, const int, const int, team *);
