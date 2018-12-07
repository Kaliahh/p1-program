/* Prototyper */
int createNewTournament(void);


/*void noget(match *, team *, const int, const int, const int);
void copyTournament(match *, const int, const match *);*/
int createTournament(team *, const int, match *, const int, const int);
void findFirstTeam(const int, const int, const int, team *, match *);
void findSecondTeam(const int, const int, team *, match *);
int checkRules(const int, const int, const int, match *, team *, int *, int *, int *);
int compareTeams(const match *, const match *);
int evaluateRound(const match *, const int, const int, int *);
int is_already_in_round(const match *, const int, const int);
int is_in_previous_round(const match *, const int, const int, int *);
/* int is_different_match(const match *, const int, const int, const int); */
void resetGames(match *, team *, int, const int, const int);
/*int played_in_a_row(const match *, const int, const int, int *);*/
/*int number_of_times_played(const team *, const int);*/

/* tournamentUpdate */
int updateTournament(FILE *);

void addTeams (FILE *, team *, int *);
void getNewTeams(team *, int , team *);
void getTeamNames(char *, int );
void copyTeams(const team *, team *, const int , const int );

void removeTeams(FILE *, team *, int *);
void deleteTeams(const team *, team *, const int , const int);
