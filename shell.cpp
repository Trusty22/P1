#include <bits/stdc++.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <unistd.h>

#define MAX_LINE 80 /* The maximum length command */

using namespace std;

void readUI(string in, char *args[]) {

  int maxL = 0;
  int counter = 0;
  string temp = in;

  // calculate max amount words
  stringstream stream(temp);
  string oneWord;

  while (stream >> oneWord) {
    ++maxL;
  }
  cout << maxL << endl;

  // convert the word to char* to store in args

  istringstream iss(in);
  string word;

  *args = new char[maxL - 1];
  while (iss >> word) {

    if (counter < maxL) {
      // strcpy(*args, );
      
      *args[counter] = *word.c_str();

      
      counter++;

    } else {
      break;
    }
  }

  cout << "khkj" << endl;
  for (int i = 0; i <= maxL; i++) {
    cout << args[i] << endl;
  }
}

int main(void) {
  char *args[MAX_LINE / 2 + 1]; /* command line arguments */
  int should_run = 1;           /* flag to determine when to exit program */
  string input = "ls -l";

  while (should_run) {
    printf("osh>");
    fflush(stdout);
    if (input == "") {
      return 0;
    }
    // send to read and store commands
    cout << input << endl;
    readUI(input, args);
    return 0;

    /**
     * After reading user input, the steps are:
     * (1) fork a child process using fork()
     * (2) the child process will invoke execvp()
     * (3) parent will invoke wait() unless command included &
     */

    fork();
  }
  return 0;
}
