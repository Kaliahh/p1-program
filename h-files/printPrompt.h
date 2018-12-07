/* Prototyper */
void createTemplate(void);
void printTeams(const team *, const int);
int printToFile(FILE *, match *, int, int, int);
int printProgram(match *, int, int, int);
char translateToChar(int);
int getLevel(const char);
int promptForFields(void);
int promptForTime(void);
void promptForFileName(char *);
void showPrintOptions(void);
void isFileOpen(FILE *);
