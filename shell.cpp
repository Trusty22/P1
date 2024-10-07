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

  // convert the word to char* to store in *args[]

  istringstream iss(in);
  string word;

  // while there is stream to go in string before char conversion and we haven't reached string length
  while (iss >> word && counter <= maxL) {
    // create new space for word as a token of a char

    args[counter] = new char[word.length() + 1]; // +1 for the null terminator
                                                 // put token in args and end with null
    strcpy(args[counter], word.c_str());
    counter++;
  }
  args[counter] = NULL;
}

int main(void) {
  char *args[MAX_LINE / 2 + 1]; /* command line arguments */
  int should_run = 1;           /* flag to determine when to exit program */
  string input = "";

  while (should_run) {
    printf("osh>");
    fflush(stdout);

    getline(cin, input);
    // send to read and store commands
    readUI(input, args);

    // prints
    cout << "Stored word: " << args[0] << args[1] << endl;

    if (args[2] == NULL) {
      cout << "NULL" << endl;
    }
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
