#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global Environment */
extern char **environ;
/* Global program name */
char *name;
/* Global history counter */
int hist;

/**
 * struct alias_s - struct to define alias
 * @name: alias name
 * @value: value of alias
 * @next: Pointer to another struct alias
 */

typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/**
 * struct list_s - struct that defines a linked list
 * @dir: directory path
 * @next: pointer to struct list_s
 */

typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - new type struct that defines builtin commands
 * @name: name of builtin commands
 * @f: function pointer to the builtin command function
 */

typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/* Helpers */
/* Main Helpers */
char *_itoa(int num);
int execute(char **args, char **front);
char *get_location(char *command);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_list(list_t *head);
list_t *get_path_dir(char *path);
char **_strtok(char *line, char *delim);

/* Input Helpers */
void call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
void handle_line(char **line, ssize_t read);
char get_args(char *line, int *exe_ret);
void variable_replacement(char **args, int *exe_ret);
int check_args(char **args);
int handle_args(int *exe_ret);
char **replace_aliases(char **args);
void free_args(char **args, char **front);

/* Builtins */
int (*get_builtin(char *command))(char ***args, char **front);
int shell_env(char **args, char __attribute__((__unused__)) **front);
int shell_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_help(char **args, char __attribute__((__unused__)) **front);
int shell_alias(char **args, char __attribute__((__unused__)) **front);
int shell_cd(char **args, char __attribute__((__unused__)) **front);
int shell_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shell_exit(char **args, char **front);

/* String Functions */
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/* Builtin Helpers */
int create_error(char **args, int err);
char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);

/* Linkedlist Helpers */
list_t *add_node_end(list_t **head, char **dir);
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
void free_list(list_t *head);

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

int proc_file_commands(char *file_path, int *exe_ret);
#endif /* -SHELL_H_ */

