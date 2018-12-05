/* Prototyper */
int createNewTournament(void);
int updateTournament(FILE *);

int createTournament(team *, const int, match *, const int, const int);
int evaluateRound(const match *, const int, const int, int *);
int is_already_in_round(const match *, const int, const int);
int is_in_previous_round(const match *, const int, const int);
int is_same_field(const match *, const int, const int);
