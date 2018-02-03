/*
* space_checker.C
*
* Gopal K. Vashishtha
* gopalvashishtha@college.harvard.edu
*
* Checks Ocaml source code for correct spacing, per the CS51 style guide
* Usage: ./<object_filename> <path to ocaml source>
*/


#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define BOLDRED     "\033[1m\033[31m"

int main (int argc, const char** argv) {
  int line_counter = 1;
  FILE* infile = fopen(argv[1], "r");
  char prev_char = fgetc(infile);
  //printf("%c",prev_char);
  char cur_char = fgetc(infile);
  char next_char = fgetc(infile);
  bool comment = false;
  bool first = false;
  bool errors_generated = false;
  int char_counter = 2;
  int c;
  while ((c = fgetc(infile)) != EOF) {
    //printf("%c",c);
    char_counter++;
    if (prev_char == '\n') {
      line_counter += 1;
      char_counter = 0;
    }

    if (prev_char == '(' && cur_char == '*') {
      //printf("entering comment on line %i",line_counter);
      comment = true;
    }
    // TODO: We're currently getting -> and cons as errors, also new lines after =

    //Single character things to be padded by spaces
    if (!comment && (cur_char == ':' || cur_char == '+' || cur_char == '*' ||
    cur_char == '/' || cur_char == '-' || cur_char == '>' || cur_char == '<'
    || cur_char == '=')) {
      //printf("triggered for cur_char %c on line %i\n", cur_char, line_counter);
      char to_check = prev_char;
      // check if we need to advance by one
      if (next_char == ':' || next_char == '=' || next_char == '\n' ||
      next_char == '>' || next_char == '*' || next_char == '.' ) {
        prev_char = cur_char;
        cur_char = next_char;
        next_char = c;
        c = fgetc(infile);
      }
      if (cur_char == '\n') {
        continue;
      }
      //printf("cur char is %c on line %i", cur_char, line_counter);
      if (next_char != ' ' || to_check != ' ') {
        printf(ANSI_COLOR_RED
          "Incorrect spacing around %c at position %i on line" ANSI_COLOR_RESET
          BOLDRED " %i"  ANSI_COLOR_RESET "\n", cur_char, char_counter, line_counter);
        errors_generated = true;
      }
    }
    if (! comment && (cur_char == ',' || cur_char == ';')) {
      if (next_char != ' ' && next_char != ';' && next_char != '\n') {
        printf(ANSI_COLOR_RED "Missing space after %c at position %i on line"
        ANSI_COLOR_RESET BOLDRED " %i"
        ANSI_COLOR_RESET"\n", cur_char, char_counter, line_counter);
        errors_generated = true;
      }
    }
    if (comment && cur_char == '*' && next_char == ')') {
      comment = false;
    }
    prev_char = cur_char;
    cur_char = next_char;
    next_char = c;
  }
  fclose(infile);
  if (errors_generated) {
    printf(ANSI_COLOR_YELLOW "Errors detected - see above" ANSI_COLOR_RESET "\n");
  }
  else {
    printf(ANSI_COLOR_GREEN "Your code looks great!" ANSI_COLOR_RESET "\n");
  }
}
