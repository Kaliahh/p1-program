/* Prototyper */
int createNewTournament(void);

/*void noget(match *, team *, const int, const int, const int);
void copyTournament(match *, const int, const match *);*/
int createTournament(team *, const int, match *, const int, const int);
int evaluateRound(const match *, const int, const int);
int isAlreadyInRound(const match *, const int, const int);
int isInPreviousRound(const match *, const int, const int);
/*int is_different_match(const match *, const int, const int, const int);*/
int createRound(match *, team *, int *, int *, const int, const int, const int, const int);
int findFirstTeam(const int, const int, const int, team *, match *);
int findSecondTeam(const int, const int, team *, match *);
int checkRules(match *, const int, const int, team *, int *, int *, int *);
int compareTeams(const match *, const match *);
void resetGames(match *, team *, int, const int, const int);
/*int played_in_a_row(const match *, const int, const int, int *);*/
/*int number_of_times_played(const team *, const int);*/


/* tournamentUpdate */
int updateTournament(FILE *);

team *addTeams (FILE *, team *, int *, const int);
team *removeTeams(FILE *, team *, int *, const int);
void getNewTeams(int , int, team *, team *);
void getTeamNames(char *, int );
void copyTeams(const team *, team *, const int , const int );
team *updateTeams(team *, int);
void deleteTeams(const team *, team *, const int , const int);
int checkTeam(char *, team *, int);
