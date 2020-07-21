#include "main.h"
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int numberOfStrings;
char **command;
int *lengthOfWordsArray;

int main(int argc, char const *argv[]) {
  int exit = false;
  // signal(SIGINT, signalHandler);
  while (!exit) {
    int status;
    printf("$ ");
    char **command = getCommand();
    pid_t pid = fork();
    pid_t rpid;

    if (pid != 0) {
      printf("I am parent\n");
      rpid = waitpid(pid, &status, WUNTRACED);
      // main(NULL, NULL);
    }

    else {
      printf("I am child\n");
      execvp(command[0], command);
    }
    free(command);
    free(lengthOfWordsArray);
  }
  // freeAndExit(EXIT_SUCCESS);
  return 0;
}

char **getCommand() {

  // Getting the input from stdin
  numberOfStrings = 0;
  int strLen = NUMBER_OF_STRINGS * LENGTH_OF_STRINGS;
  char string[strLen];
  fgets(string, strLen, stdin);

  // Repalcing newline&space charater with Null charcter
  if (*string != '\n') {
    char *str = string;
    while (*str != '\n') {
      if (*str == ' ') {
        *str = '\0';
        numberOfStrings++;
        str++;
      } else
        str++;
    }
    *str = '\0';
    numberOfStrings++;
  }

  // Finding length of each word
  int *lengthOfWordsArray =
      calloc(numberOfStrings + 1,
             sizeof(int)); // 1 extra for terminating null character
  fillLengthArray(string, lengthOfWordsArray, numberOfStrings);

  // Allocating memory for dynamic array with store command
  command = calloc(numberOfStrings + 1,
                   sizeof(char *)); // 1 extra for terminating null character
  if (command != NULL) {
    for (int i = 0; i < numberOfStrings + 1; i++) {
      command[i] = malloc(sizeof(char) * lengthOfWordsArray[i] + 1);
      if (command[i] == NULL)
        freeAndExit(EXIT_FAILURE);
    }
  } else
    freeAndExit(EXIT_FAILURE);

  // copying command into dyamic array
  int stringIndex = 0;
  for (int j = 0; j < numberOfStrings; j++) {
    int commandIndex = 0;
    while (*(string + stringIndex) != '\0') {
      command[j][commandIndex++] = string[stringIndex++];
    }
    *(string + stringIndex) = '\0';
    stringIndex++;
  }
  command[numberOfStrings] = '\0'; // ending the array with \o
  return command;
}

void fillLengthArray(char *str, int *array, int length) {
  int i = 0;
  int index = -1;
  while (i < length) {
    index++;
    int j = 0;
    while (*(str + index) != '\0') {
      index++;
      j++;
    }
    array[i++] = j;
  }
}

void freeAndExit(int status) {
  free(command);
  free(lengthOfWordsArray);
  if (status == EXIT_FAILURE)
    perror("KOOLSH");
  exit(status);
}

void signalHandler(int sign) {
  // signal(SIGINT, signalHandler);
  printf("\n Exiting \n");
  fflush(stdout);
}