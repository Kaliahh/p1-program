/* Prototyper */
int createNewTournament(void);
int updateTournament(FILE *);

/*void noget(match *, team *, const int, const int, const int);
void copyTournament(match *, const int, const match *);*/
int createTournament(team *, const int, match *, const int, const int);
int evaluateRound(const match *, const int, const int, int *);
int is_already_in_round(const match *, const int, const int);
int is_in_previous_round(const match *, const int, const int, int *);
//int is_different_match(const match *, const int, const int, const int);
void resetGames(match *tournament, team *, int, const int, const int);
/*int played_in_a_row(const match *, const int, const int, int *);*/
/*int number_of_times_played(const team *, const int);*/


