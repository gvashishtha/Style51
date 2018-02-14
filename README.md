# Style51
Checks ocaml code for style errors, per [CS51 style guide](https://github.com/gvashishtha/ocaml_style/blob/master/style_guide.pdf)

##Directions:

To download, navigate within the terminal to the folder where you want to keep the file. Then type in "curl https://raw.githubusercontent.com/gvashishtha/Style51/master/style51.c > style51.c" or "wget https://raw.githubusercontent.com/gvashishtha/Style51/master/style51.c > style51.c"

You can compile the program by typing either "gcc style51.c -o style51.o" or "clang style51.c -o style51.o" (clang and gcc are C compilers). Once you compile the program, run by typing "./style51.o" followed by the path to your .ml file. If you are unsure about the path to your .ml file, just move the .o file into the same directory as your .ml file and type "./style51.o ./ps1.ml"

##Flags
(write in a group as in `-mstop` after filename):  
`-m` to silence match warnings  
`-t` to silence then warnings  
`-o` to silence warnings around mathematical operators  
`-s` to silence warnings at end-of-line semicolons
`-p` to silence warnings about spacing around parentheses

As of right now, Style51 checks the following things:

1. No more than 80 characters per line
2. No tab characters
3. If an if statement is broken across multiple lines,
the corresponding else statement should have the same indentation.
4. All '|' characters should be at the same level as their corresponding match
statements.
5. Mathematical operators should be surrounded by spaces.
6. Commas and semicolons should be followed, but not preceded, by a space.
7. Double semicolons preceded by a space.

Style 51 **does not** check for the following issues:
1. Using 2 spaces or 4 spaces inconsistently to represent tabs.
2. Keeping 'let' statements at the same indentation level.
3. Using minimal parentheses.

Additionally, Style51 marks the following things as errors, even though they are permitted by the style guide.
1. Removing space from around mathematical operators to emphasize precedence (as in 4\*3 + 1\*1).
2. Putting 'then' at the beginning of a newline in non-nested conditionals.
