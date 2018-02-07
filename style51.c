/*
* style51.C
*
* Gopal K. Vashishtha
* gopalvashishtha@college.harvard.edu
*
* Checks Ocaml source code for correct style, per the CS51 style guide
* Guide here:
* https://github.com/gvashishtha/ocaml_style/blob/master/style_guide.pdf
* Usage: ./<object_filename> <path to ocaml source> <space_length>
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define BOLDRED     "\033[1m\033[31m"

int error_count = 0;
bool errors_generated = false;
int line_counter = 1; int char_counter = 1;


void print_error(char* message, char cur_char, int offset) {
  printf(BOLDRED "%i:%i" ANSI_COLOR_RESET ANSI_COLOR_RED " - %s%c"
  ANSI_COLOR_RESET "\n", line_counter, char_counter + offset, message, cur_char);
  errors_generated = true;
  error_count++;
}

int main (int argc, const char** argv) {
  if (argc != 2) {
    printf("Usage: ./spaces.o <path to filename>\n");
    return -1;
  }
  FILE* infile = fopen(argv[1], "r");
  if (infile == NULL) {
    printf("Filename invalid\n");
    return -1;
  }
  char prev_char = '\0';
  char cur_char = fgetc(infile);
  char next_char = fgetc(infile);
  char buffer[50] = "Spacing incorrect around ";
  char chr[3] = "";
  bool comment, second, if_line, else_line, seen_char, double_c = false;
  int if_count, match_count = -1;
  int space_count = 0;
  int c;

  while ((c = fgetc(infile)) != EOF) {
    chr[0] = '\0'; chr[1] = '\0';
    if (!comment && cur_char == ' ' && !seen_char) {
      space_count++;
    }
    if (cur_char == '\n') {
      line_counter += 1;
      char_counter = 0; space_count = 0;
      second = false; if_line = false; else_line = false; seen_char = false;
    }
    if (char_counter > 80 && !second) {
      print_error((char*) "More than 80 characters", '!', 0);
      second = true;
    }
    if (cur_char == '(' && next_char == '*') {
      comment = true;
    }
    if (cur_char == '\t') {
      print_error((char*) "No tab characters allowed", '!', 0);
    }

    // Deal with expressions like (x -1)
    if (!comment && next_char == '-' && isalpha(prev_char)) {\
      if (c != ' ' && isdigit(c)) {
        print_error((char*) "Incorrect spacing around ", '-', 0);
      }
    }

    //Single character things to be padded by spaces
    if (!comment && (cur_char == ':' || cur_char == '+' || cur_char == '*' ||
    cur_char == '/' || (cur_char == '-' && !isdigit(next_char))
    || cur_char == '>' || cur_char == '<' || cur_char == '='
    || cur_char == '^')) {
      char temp_prev = prev_char;
      // check if we need to advance by one
      if (next_char == ':' || next_char == '=' ||
      next_char == '>' || next_char == '*' || next_char == '.' ) {
        char temp_c = fgetc(infile);
        prev_char = cur_char;
        cur_char = next_char;
        next_char = c;
        c = temp_c;
        char_counter++;
        chr[0] = prev_char;
      }
      if ((next_char != ' ' && next_char != '\n') || temp_prev != ' ') {
        buffer[25] = '\0';
        print_error((char*) strcat(buffer, chr), cur_char, 0);

      }
    }
    if (!comment && cur_char == ','&& prev_char != ' ' && next_char != ' ') {
      print_error((char*) "Spacing incorrect around ", cur_char, 0);
    }

    if (!comment && cur_char == ';') {
      // this is a double semi-colon
      if (next_char == ';') {
        if (prev_char != ' ' || c != '\n') {
            print_error((char*) "Spacing incorrect around ;", cur_char, 0);
        }
        char temp_c = fgetc(infile);
        prev_char = cur_char;
        cur_char = next_char;
        next_char = c;
        c = temp_c;
        char_counter++;

      }
      else if (prev_char == ' ' || (next_char != ' ' && next_char != '\n')){
        print_error((char*) "Spacing incorrect at ", cur_char, 0);
      }
    }

    // this is an if
    if (!else_line && !comment && (prev_char == '\n' || prev_char == ' ' ||
     prev_char == '>') && cur_char == 'i' && next_char == 'f' && c == ' ') {
      if_count = char_counter;
      if_line = true;
    }
    if (!comment && !if_line && !else_line &&
      (prev_char == ' ' || prev_char == '\n') && cur_char == 'e'
      && next_char == 'l' && c == 's') {

        //advance to confirm it is an else
        char temp_c = fgetc(infile);
        char temp1_c = fgetc(infile);
        if (temp_c  == 'e' && temp1_c == ' ') {
          else_line = true;
          if (char_counter != if_count) {
            print_error((char*) "Mis-aligned els", 'e', 0);
          }
        }
        ungetc(temp1_c, infile); ungetc(temp_c, infile);
    }
    if (!comment && !if_line && !else_line &&
      (prev_char == '\n' || prev_char == ' ') && cur_char == 't'
      && next_char == 'h' && c == 'e') {

        //advance to confirm it is a then
        char temp_c = fgetc(infile); char temp1_c = fgetc(infile);
        if (temp_c == 'n' && temp1_c == ' ') {
          print_error((char*) "\'Then\' should be on previous lin", 'e',-1);
        }
        ungetc(temp1_c, infile); ungetc(temp1_c, infile);
    }
    if (!comment && (prev_char == '\n' || prev_char == ' ') && cur_char == 'm'
      && next_char == 'a' && c == 't') {

        //advance to confirm it is a match
        char temp0 = fgetc(infile); char temp1 = fgetc(infile);
        char temp2 = fgetc(infile);
        if (temp0 == 'c' && temp1 == 'h' && temp2 == ' ') {
          match_count = char_counter;
        }
        ungetc(temp2, infile); ungetc(temp1, infile); ungetc(temp0, infile);
    }
    if (!comment && cur_char == '|' && match_count != char_counter) {
      print_error((char*) "Mis-aligned match delimite", 'r', 0);
    }
    if (comment && cur_char == '*' && next_char == ')') {
      comment = false;
    }
    prev_char = cur_char;
    cur_char = next_char;
    next_char = c;
    char_counter++;
  }
  fclose(infile);
  if (errors_generated) {
    char plural[3] = "es";
    if (error_count == 1) {
      plural[1] = '\0';
    }
    printf(ANSI_COLOR_YELLOW "%i issu%s detected - see above"
      ANSI_COLOR_RESET "\n", error_count, plural);
  }
  else {
    printf(ANSI_COLOR_GREEN "Your code looks great! You should still check that\n\
    - All top-level function definitions have type definitions\n\
    - You pattern-match within function arguments when possible\n\
    - You've followed the correct naming conventions" ANSI_COLOR_RESET "\n");
  }
}
