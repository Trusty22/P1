#include <bits/stdc++.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LINE 80 /* The maximum length command */

using namespace std;
void printArrayEx(char *array[]) {

  cout << "--ARRAY PRINT--" << endl;
  int i;
  for (i = 0; array[i] != NULL; i++) {
    cout << array[i] << endl;
  }

  if (array[i] == NULL) {
    cout << "NULL" << endl;
  }
  cout << endl;
}

void printArray(char *array[]) {

  int i;
  for (i = 0; array[i] != NULL; i++) {
    cout << array[i] << " ";
  }

  if (array[i] == NULL) {
    cout << endl;
  } else {
    cout << "INVALID PRINT: EXITING";
    exit(0);
  }
}

void copyArray(char *args[], char *copyArgs[]) {
  int i;
  for (i = 0; args[i] != NULL; i++) {
    copyArgs[i] = args[i];
  }
  copyArgs[i] = NULL;
}

void readUI(string in, char *args[], char *copyArgs[]) {

  int maxL = 0;
  int counter = 0;
  string temp = in;

  // calculate max amount words
  stringstream stream(temp);
  string oneWord;

  while (stream >> oneWord) {
    ++maxL;
  }

  // convert the word to char* to store in *args[]

  istringstream iss(in);
  string word;

  // while there is stream to go in string before char conversion and we haven't reached string length
  while (iss >> word && counter <= maxL) {

    args[counter] = new char[word.length() + 1]; // create new space for word as a token of a char && +1 for the null terminator
    strcpy(args[counter], word.c_str());         // put token in args and end with null
    counter++;
  }
  args[counter] = NULL;

  copyArray(args, copyArgs);

  // printArray(args);
  // printArray(copyArgs);
}

int main(void) {
  char *args[MAX_LINE / 2 + 1]; /* command line arguments */
  int should_run = 1;           /* flag to determine when to exit program */
  string input = "";
  bool isFirstRun = true;

  char *copyArgs[MAX_LINE / 2 + 1];

  char *commands[] = {(char *)"!!", (char *)"|", (char *)"&", (char *)"<", (char *)">"};

  while (should_run) {
    printf("osh>");
    fflush(stdout);

    getline(cin, input);

    if (input == "exit") {
      should_run = 0;
      break;
    }
    if (input == "!!") {

      if (isFirstRun) {
        cout << "INVALID: No commands in history" << endl;
      } else {
        isFirstRun = false;
        copyArray(args, copyArgs);

        printf("osh>");
        fflush(stdout);
        printArray(copyArgs);
      }

    } else {
      readUI(input, args, copyArgs);
      isFirstRun = false;
    }
    /*
    // printArrayEx(args);
    //  send to readUI and store commands - read user input into args

    // prints

     string s1(commands[0]);
     string s2(args[0]);

     if (s1 == s2) { // if use last command !! store last command
     }

    // cout << "Stored word: " << args[0] << args[1] << endl;
    */

    //  first determin command that doesnt work like | & < > !! and redirtct to its seperate function

    if (args[0] == "exit") {
      exit(0);
    }

    /**
     * After reading user input, the steps are: DONE
     * (1) fork a child process using fork()
     * (2) the child process will invoke execvp()
     * (3) parent will invoke wait() unless command included &
     */
    cout << "start pipe" << endl;
    int pipe_fd[2];

    pipe(pipe_fd);
    int rc = fork();
    // start with fork (1)
    if (rc == 0) { // child
      cout << "child" << endl;
      close(pipe_fd[1]); // right side 0 | 1
      execvp(args[0], args);
    } else { // parent
      cout << "parent" << endl;
    }
    exit(0);
  }
  return 0;
}