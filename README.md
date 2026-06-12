# *This project has been created as part of the 42 curriculum by hbekka and hbelleuv*

# 1) Description 

## Summary
The goal of the mini-shell project is to reproduce the behaviour of bash'shell.
The students have to deal with redirections, pipes, environnment variables.

## Detailed workflow
- Lexer part : lexical analysis of the input
- Parsing part : transforming the lexered input into an Abstract Syntaxical Tree
- Expand part : replacing the key of the expanded token to its curren value
- Execution part : either to execute reconstructed commands (one form the seven listed in the instruction), or any other commands from getting their path
- Signal part : signal set-up with global variables and handle through all the process of execution
- Cleaning part : every malloced elements are linked to a garbage structure, so to free everything we just have to get through all the listed elements and free them.

### 1-LEXER
The lexical analyser is used to scan input text charcater by character (using **machineState** strategy). This is made in order to define clearly the token, despite of the complexity of quotes or multiple spaces.


#### Machine State :
- **DEFAUT STATE** : space, quotes, operators and char detection
- **IN_WORD** : gathering all the char until we reach a space, an operator or a quote
- **S_QUOTE/D_QUOTE** : dealing with content inside simple or doubel quote:

#### Tokens collected :
| Token | Description |
|-------|-------------|
| WORD | Mot normal |
| PIPE | `\|` |
| REDIR_IN | `<` |
| REDIR_OUT | `>` |
| REDIR_OUT_A | `>>` |
| HERE_DOC | `<<` |
| AND | `&&` |
| OR | `\|\|` |
| OPEN_PAR / CLOSE_PAR | `(` / `)` |
| EOF_TOKEN | Fin du flux |

#### Key files :
- `tokenize.c` : main loop for handling char and create accurate tokens.
- `macine_state.c` : handling transition  between different state
- `init_lexer.c` : init and create the tokens list
- `lexer_utils2.c` : quotes trimming and error handling

#### Error's handling : 
- Not closing quotes
- Not valid parenhtesis

---

### 2-PARSING

The goal of the parsing is to transofrm a token list into an **abstract syntaxical tree**(*ast*). It can be considered as a **recursive evalluator** to be abble to deal with operators such as `&&` or ` || `

#### AST Structure : 

- **SIMPLE_CMD** : simple command with arguments, and maybe redirections
- **PIPELINE** : linked chains of cmd linked by pipes
- **AND_OPER** : conjunction operator
- **OR_OPER** : disjunction operator
- **SUBESHELL** : commands written inside parenthesis.

#### Redirections handling : 

| Type | Symbole | Description |
|------|---------|-------------|
| REDIR_IN | `<` | Redirection in |
| REDIR_OUT | `>` | Redirection out (overwrite) |
| REDIR_OUT_A | `>>` | Redirection out (append) |
| HERE_DOC | `<<` | Redirection doc inline |

#### Key files : 
- `init_parser.c` : Creating all the nodes of the ast, and the redirection list
- `parser.c` : recursive and parsing and building of the AST depending on the form of the token list got in input
- `parser_utils.c` : usefull and consuming stratgey for AST parsing
- `parser_print.c` : printing functions for debugging AST construction

#### Parsing strategy : 
1. **parse_command_line()** : handling `&&` and `||` in respect to priority order
2. **parse_pipeline()** : handling `|` in respect to priority order
2. **parse_simple_cmd()** : handling simple commands and their potential arguments and redirections


---

### 3-EXPAND

The expansion phase consistes in replacing environnement variables or wildcard to their actual value (wich can create multiple tokens bu substituting *.c by all .c files for instance).

####  Different expansion types : 
| Type | Description | Example |
|------|-------------|---------|
| **Variables** | Remplacing `$VAR` by its value | `echo $HOME` |
| **Exit code** | Remplace `$?` par le code de sortie | `echo $?` |
| **Wildcards** | Expansion des `*` et `?` | `ls *.c` |
| **Quotes** | Contrôle l'expansion selon le contexte | `'$VAR'` vs `"$VAR"` |

#### Quotes rules for expansion :

| Quote | Behaviour |
|-------|-----------|
| `'single_q'` | NO litteral expansion |
| `"double_q"` | Expansion for `$` and `$?`
| `no_quote` | Full expansion + wildcard expand |

Perhaps, in **here-doc case**, no matter quotes, an environnement variable will always be substituted by its value, if it exists. 

#### Key files :
- `expending.c` : Main loop for delaing with thge expansion of tokens, with creation of new tokens if it is necessary
- `env_var_expand.c` : Expansion of environnement variables : first char = `$`
-`wildcard_expand.c` : Expansion of pattern bash likes for `*`
- `env_set_up.c` : Init and handling env structure 
- `env_utils.c` : Acess and set up for all the variables

#### Env handling : 
 - Init from `envp`
 - Linked structure `t_env`
 - Helpers for commands such as `export` or `unset`

---

### 4-EXEC

Execution lays on intepretation of the AST and execution of the cmd, either reconstructed with quotes, either by finding their path and execute them with `execve`

#### Execution worflow :

```
ft_eval()
  ├─ SIMPLE_COMMAND
  │  ├─ Built-in (echo, cd, export, etc.)
  │  └─ Commande externe (fork + execve)
  ├─ PIPELINE (deux processus + pipe)
  ├─ AND_OPER (&&) - exécution conditionnelle
  ├─ OR_OPER (||) - exécution alternative
  └─ SUBSHELL (fork + environnement copié)
```

#### Redirections :
Mainly lays on **dup2**, fd redirect and manipulation

- **IN* (`<`) : Redir from an infile
- **OUT** (`>`) : Redir to an outfile
- **APPEND** (`>>`) : Redir to an outfile (append mode)
- **HERE_DOC** (`<<`) : Input multiline interactive

#### Key files : 
`main_exec.c` : contians the main fucntion `ft_eval()` wchich handle the execution depending on the AST previously parsed
`exec_builtin_cmd.c` : detecttion and execution of the 7 built-ins functions
`exec_extern_cmd.c` : Searching for a path and `execve()`
`pipe_exec.c` : Pipe handling
`operator_exec.c` : `&&` and `||` handling
`here_doc_exec.c` : Here_doc handling
`simple_cmd_exec.c` : Execution for simple commands
`exec_utils.c` : utilis for exit_code, handling the different fd redir etc.

#### Exit code handling : 

- Capture of the exit code via `WEXITSTATUS(status)`
- Its stocked into the structure `minishell->exit_code`
- `$?` should return the exit_code

---
### 5-SIGNAL
Handling signals garantees an accurate behaviour (**bash alike**) during interruptions (`Ctrl + C`) and other forms of interactions with signals.

#### Main signals :

|Signal| Events| Treatment |
|------|-------|-----------|
|**SIGINT** (Ctrl + C) | Interrupts | New lines in interractive mode |
|**SIGQUIT** (Ctrl + \) | Quit | Ignor in interractive mode |
|**SIGCHILD** | ENd of a child process | Collecting the status |

#### States of signal : 

| Context | SIGINT | SIGQUIT |
| Interactif mode | Handler custom | SIG_IGN |
| Execution builtin | Handler custom | SIG_IGN |
| Execution other | SIG_DFL | SIG_DFL |
| Here-doc | Handler special | SIG_DFL | 


#### Expectred behaviour
 ``` bash
 # Ctrl+C in interactive → new line
minishell> ^C
minishell>

# Ctrl+C during exec → stop + exit code 130
minishell> sleep 10
^C  # → shell affiche le prompt à nouveau

# Ctrl+C in here-doc → stop + exit code 130
minishell> cat << EOF
> ^C  # → stop the typing and exit from the here_doc

 ```

#### Globale variable

```c
volatile sig_atomic_t g_signal = 0;
```

This allows a safety communication between the handler and the rest of the whole programm.

#### Focus Points :
**Recovery of the prompt** : `rl_on_new_line()` and `rl_replace_line()`
**Temporary unablement** : during `here_doc` and `fork`
**Exit code** : `shell->exit_code = 130` pour SIGINT
**Thread-safety** : by using `sig_atomic_t`


---

### 6-CLEANING (i.e Garbage Collector)

Every malloced objects are linked to pointers, so that everything can be free in only one operation :
`gc_clear()`;

#### Avantages :
- No memory leaks
- No double free
- Makes the debug phase more easy, because we only have to free only once.


#### Main functions : 
-`gc_malloc()` : malloc + pointeur + linked chains
- `gc_clear()` : free all the pointeurs through all the linked lists.


--- 
# 2) Instruction

### Compilation

```bash
make
```

### Run

```bash
./minishell
```

### Clean

```bash
make clean      # Remove object files
make fclean     # Remove executable and object files
make re         # Clean + recompile
```
To avoid to have all the leaks message due to `readline()` function we add to our valgrind command a readline.supp to get rid of those unacurrate leaks messages

```
### Compilation

```bash
make
```

### Run

```bash
./minishell
```

### Clean

```bash
make clean      # Remove object files
make fclean     # Remove executable and object files
make re         # Clean + recompile
```
### Compilation

```bash
make
```

### Run

```bash
./minishell
```

### Clean

```bash
make clean      # Remove object files
make fclean     # Remove executable and object files
make re         # Clean + recompile
```
We have to add a **.supp file** to get rid of all the error msg due to `readline()` function
```
valgrind --leak-check=full --show-leak-kinds=all --track-fds=all --suppressions=readline.supp
```
---
# 3) Ressources

Minishell project implicates a lot of preparatory work and consulting documentations.

## Manuals
Official bash reference manual: [Bash manual](https://www.gnu.org/software/bash/manual/bash.html)

## Vidoes & Blogs
Wikipedia page about Abstract Syntax Trees (very usefull for bonus part): [link](https://en.wikipedia.org/wiki/Abstract_syntax_tree)
A PDF about the different parts of the project: [link](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
A blog by former students that highlights their approaches to the project: [link](https://medium.com/@mostafa.omrane/mes-conseils-si-je-devais-recommencer-minishell-a9783c51ba1b)

## Usage of Ai
In this project, AI was used primarily to facilitate the understanding of extensive documentation and to help implement specific functions for which few examples were available online.  
All AI-generated responses were carefully reviewed, tested, and validated before being integrated into the project.

Example:
- Assistance in understanding parsing logic and edge cases (quotes, environment variables, pipes)
- Guidance on structuring the project and organizing the code
- Occasional help with debugging and identifying potential memory leaks
