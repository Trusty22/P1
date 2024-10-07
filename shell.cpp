#include <cstring>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <unistd.h>

#define MAX_LINE 80 /* The maximum length command */

using namespace std;

void readUI(string in, char *args[]) {
  int maxL = in.length();
  istringstream iss(in);
  string s;

  while (getline(iss, s, ' ')) {
    cout << s << endl;
  }
}

int main(void) {
  char *args[MAX_LINE / 2 + 1]; /* command line arguments */
  int should_run = 1;           /* flag to determine when to exit program */
  string input = "yo my boy";

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
