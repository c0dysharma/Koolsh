//derivitives
#define NUMBER_OF_STRINGS 20
#define LENGTH_OF_STRINGS 1024

//function prototypes
char** getCommand();
void fillLengthArray(char *str, int *array,int length);
void freeAndExit(int status);
void signalHandler(int sign);