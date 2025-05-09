✅ What It Does
Validates and splits the input string (init_pars, fill_the_array, HardcodeChecks).

Handles quotes, whitespace, and redirections (Handlequotes, Handlered, SkipWhiteSpaces).

Builds a word list (CommandOrnot) and token list with types (typesee).

Expands environment variables (expand_variables).

Converts tokens into structured commands with pipe/redirection handling (splitit, handle_redirection).

Print and debug utilities: print_list, print_cmd_list, print_list1.

🧩 Main Structs
pars_T: used for parsing input into tokens/words.

w_list: linked list of raw parsed words.

T_list: token list with type info (pipe, word, redirect, etc).

c_cmd: final command struct, holds array of commands and redirection file info.