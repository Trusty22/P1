#include <bits/stdc++.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
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
  int andPos;
  string input = "";
  bool isFirstRun = true;
  bool hasAnd = false;
  bool hasPastCommand = false;
  bool hasRunFromFile = false;
  bool hasPutInFile = false;

  char *copyArgs[MAX_LINE / 2 + 1];

  char *commands[] = {(char *)"!!", (char *)"|", (char *)"&", (char *)"<", (char *)">"};

  while (should_run) {
    char *args[MAX_LINE / 2 + 1];
    printf("osh>");
    fflush(stdout);

    getline(cin, input);

    if (input == "exit") {
      should_run = 0;
      exit(0);
      break;
    }

    if (input.find("!!") != string::npos) {

      if (isFirstRun) {
        hasPastCommand = false;
        cout << "INVALID: No commands in history" << endl;
      } else {
        isFirstRun = false;
        hasPastCommand = true;
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

    // methodize &
    if (!isFirstRun) {
      for (int i = 0; args[i] != NULL; i++) {
        string s1(args[i]);
        string s2(commands[2]);
        string s3(commands[3]);
        string s4(commands[4]);
        if (s1 == s2) {
          hasAnd = true; // & means no parent waiting
          andPos = i;
          cout << "has &" << endl;
        }
        if (s1 == s3) {          // take command from file and run it in osh
          hasRunFromFile = true; // execlp(args[0], args[2], args[3]);
          cout << " has <" << endl;

        } else if (s1 == s4) {      // write left command to file
          cout << " has >" << endl; // execlp(args[0], args[2], args[3]);
          hasPutInFile = true;
        }
      }
    }

    //  first determin command that doesnt work like & < > !! and redirtct to its seperate function DONE

    /**
     *
     * Instructions
     * 1. Creating the child process and executing the command in the child
     * 2. Providing a history feature DONE
     * 3. Adding support of input and output redirection Detection done, Implementaion needed execlp(args[0], args[2], args[3]); left command (<,>) right command
     * 4. Allowing the parent and child processes to communicate via a pipe
     *
     * After reading user input, the steps are: DONE
     * (1) fork a child process using fork()
     * (2) the child process will invoke execvp()
     * (3) parent will invoke wait() unless command included &
     */

    // start with fork (1)
    int rc = fork();

    if (rc == 0) { // child
    //  cout << "child" << endl;
      // deal with & wait
      if (hasAnd) {
        for (int i = 0; args[i] != NULL; i++) {
          string s1(args[i]);
          if (s1 == "&") {
            args[i] = NULL;
          }
        }
      }

      execvp(args[0], args);
      cout << "uncreconized command" << endl;
      exit(0); //kill it
      return 0;

    } else { // parent & means no parent waiting
      if (!hasAnd) {
        wait(NULL);
      }

      // printf("osh>P:");
      // fflush(stdout);
    }
    if (rc < 0) {
      cerr << "Fork failed";
      exit(0);
      return 0;
    }

    if (input == "exit") {
      exit(0);
      return 0;
    }

    /*
        // pipe(pipe_fd);
        int rc = fork();
        // start with fork (1)
        if (rc == 0) { // child
          cout << "child" << endl;
          // close(pipe_fd[1]); // right side 0 | 1
          cout << "osh> child";
          execvp(args[0], args);
        } else { // parent & means no parent waiting
          cout << "parent osh> ";
          // wait(NULL); // waits till child exits
        }
        exit(0);
        return 0;
        */
  }
  return 0;
}
