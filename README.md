# Style51
Checks ocaml code for style errors, per [CS51 style guide](https://github.com/gvashishtha/ocaml_style/blob/master/style_guide.pdf)

As of right now, Style51 checks the following things:

1. No more than 80 characters per line
2. No double newlines
3. No tab characters
4. If an if statement is broken across multiple lines,
the corresponding else statement should have the same indentation.
5. All '|' characters should be at the same level as their corresponding match
statements.
6. Mathematical operators should be surrounded by spaces.
7. Commas and semicolons should be followed, but not preceded, by a space.

Style 51 **does not** check for the following issues:
1. Using 2 spaces or 4 spaces inconsistently to represent tabs.
2. Keeping 'let' statements at the same indentation level.
3. Using minimal parentheses.

Additionally, Style51 marks the following things as errors, even though they are permitted by the style guide.
1. Removing space from around mathematical operators to emphasize precedence (as in 4\*3 + 1\*1).
2. Putting 'then' at the beginning of a newline in non-nested conditionals.
