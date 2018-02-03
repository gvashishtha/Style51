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
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define BOLDRED     "\033[1m\033[31m"

int error_count = 0;
bool errors_generated = false;

void print_error(char* message, char cur_char,
  int char_counter, int line_counter) {
  printf(BOLDRED "%i:%i" ANSI_COLOR_RESET ANSI_COLOR_RED " - %s%c"
  ANSI_COLOR_RESET "\n", line_counter, char_counter, message, cur_char);
  errors_generated = true;
  error_count++;
}

int main (int argc, const char** argv) {
  if (argc < 2) {
    printf("Usage: ./spaces.o <path to filename> [<# of spaces in a tab>]\n");
    return -1;
  }
  if (argc > 2) {
    int space_length = atoi(argv[1]);
  }

  int line_counter = 1;
  FILE* infile = fopen(argv[1], "r");
  if (infile == NULL) {
    printf("Filename invalid\n");
    return -1;
  }
  char prev_char = fgetc(infile);
  char cur_char = fgetc(infile);
  char next_char = fgetc(infile);
  bool comment, second, if_line, else_line = false;
  int char_counter = 2;
  int if_count = -1;

  int c;
  while ((c = fgetc(infile)) != EOF) {

    if (prev_char == '\n') {
      line_counter += 1;
      char_counter = 1;
      second = false; if_line = false; else_line = false;
    }
    if (char_counter > 80 && !second) {
      print_error((char*) "More than 80 characters", '!', char_counter,
       line_counter);
      second = true;
    }
    if (prev_char == '(' && cur_char == '*') {
      comment = true;
    }
    if (cur_char == '\t') {
      print_error((char*) "No tab characters allowed", '!', char_counter,
        line_counter);
    }

    //Single character things to be padded by spaces
    if (!comment && (cur_char == ':' || cur_char == '+' || cur_char == '*' ||
    cur_char == '/' || cur_char == '-' || cur_char == '>' || cur_char == '<'
    || cur_char == '=')) {
      char to_check = prev_char;

      // check if we need to advance by one
      if (next_char == ':' || next_char == '=' || next_char == '\n' ||
      next_char == '>' || next_char == '*' || next_char == '.' ) {
        prev_char = cur_char;
        cur_char = next_char;
        next_char = c;
        c = fgetc(infile);
        char_counter++;
      }
      if (cur_char == '\n') {
        continue;
      }
      if (next_char != ' ' || to_check != ' ') {
        print_error((char*) "Incorrect spacing around ", cur_char,
        char_counter, line_counter);
      }
    }
    if (! comment && (cur_char == ',' || cur_char == ';')) {
      if (next_char != ' ' && next_char != ';' && next_char != '\n') {
        print_error((char*) "Not enough space after ", cur_char, char_counter,
          line_counter);
      }
    }



    // this is an if with high likelihood
    if (!else_line && !comment && prev_char == 'i' && cur_char == 'f'
    && next_char == ' ') {
      if_count = char_counter;
      if_line = true;
    }
    if (!comment && !if_line && prev_char == 'e' && cur_char == 'l'
      && next_char == 's') {
        //advance to confirm it is an else
        char temp_prev = cur_char;
        char temp_cur = next_char;
        char temp_next = c;
        char temp_c = fgetc(infile);
        temp_prev = temp_cur;
        temp_cur = temp_next;
        temp_next = temp_c;
        //temp_c = fgetc(infile);
        if (temp_cur == 'e' && temp_next == ' ') {
          else_line = true;
          if (char_counter != if_count) {
            print_error((char*) "Mis-aligned els", 'e', (char_counter - 1),
            line_counter);
          }
        }
        ungetc(temp_c, infile);
    }
    if (!comment && !if_line && !else_line && prev_char == 't'
      && cur_char == 'h' && next_char == 'e') {
        //advance to confirm it is a then
        char temp_prev = cur_char;
        char temp_cur = next_char;
        char temp_next = c;
        char temp_c = fgetc(infile);
        temp_prev = temp_cur;
        temp_cur = temp_next;
        temp_next = temp_c;
        //temp_c = fgetc(infile);
        if (temp_cur == 'n' && temp_next == ' ') {
          //else_line = true;
          print_error((char*) "Then should be on previous lin", 'e',
            (char_counter - 1),line_counter);
        }
        ungetc(temp_c, infile);
    }
    if (comment && cur_char == '*' && next_char == ')') {
      comment = false;
    }
    //printf("DEBUG: char is %c position %i ifcount is %i\n", cur_char, char_counter, if_count);
    prev_char = cur_char;
    cur_char = next_char;
    next_char = c;
    char_counter++;

  }
  fclose(infile);
  if (errors_generated) {
    char plural[3] = "rs";
    if (error_count == 1) {
      plural[1] = '\0';
    }
    printf(ANSI_COLOR_YELLOW "%i erro%s detected - see above"
      ANSI_COLOR_RESET "\n", error_count, plural);
  }
  else {
    printf(ANSI_COLOR_GREEN "Your code looks great!" ANSI_COLOR_RESET "\n");
  }
}
