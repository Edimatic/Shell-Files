#ifndef EDDI_H
#define EDDI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <stdarg.h>
#include <errno.h>

/* Maximum number of aliases */
#define MAX_ALIASES 100

/* Define structure for Alias */
typedef struct Alias 
{
    char *name;
    char *value;
} Alias;

/* Function prototypes for alias.c */
void print_aliases(Alias *aliases, int alias_count);
Alias *find_alias(Alias *aliases, int alias_count, char *name);
void set_alias(Alias *aliases, int *alias_count, char *name, char *value);
void execute_alias(char *arguments, Alias *aliases, int *alias_count);
char *custom_strdup(const char *str);
char *custom_strcpy(char *dest, const char *src);

/* Define aliases as a global variable */
extern Alias *aliases;
extern int alias_count;

/* Function prototype for variables.c */
char *replace_variables(char *command, int status, pid_t pid);
char *replace_str(char *str, const char *old_str, const char *new_str);
void itoa(int num, char *str);
void reverse_str(char *str);
int string_length(const char *str);

void execute_commands(char *command, int *running, char **envp, Alias *aliases, int *alias_count);

char *read_command(void);
void display_prompt(void);
char *read_command(void);

void execute_command(char *command, char **envp, int *running);

/* builtin function */
size_t string_length_(const char *str);
int compare_strings_(const char *str1, const char *str2);
int is_builtin(char *command);
void execute_builtin(char *command, int *running, char **envp, Alias *aliases);

/* execute function protoptype */
char *get_path(char *command, char **envp);
void print_env(char **envp);
int custom_strncmp(const char *s1, const char *s2, size_t n);


/* Environmental function */
int set_env_variable(const char *name, const char *value, char ***envp);
int unset_env_variable(const char *name, char ***envp);
size_t custom_strlen(const char *str);
void *custom_malloc(size_t size);
void custom_free(void *ptr);
int custom_snprintf(char *str, size_t size, const char *format, ...);
int custom_putenv(char *str);
int custom_unsetenv(const char *name);

/* cd_builtin function */
void cd_builtin(char *path, char ***envp);
int custom_strcmp(const char *s1, const char *s2);
void custom_fprintf_stderr(const char *format, ...);
char *custom_getcwd(char *buf, size_t size);
char *custom_getenv(const char *name, char **envp);

char *trim_whitespace(char *str);
void execute_logical_command(char *command, char **envp, int *running);
char *custom_strchr(const char *str, int ch);

/* Logical operators function */
int compare_strings(const char *str1, const char *str2);
void handle_logical_operators(char *command, char **envp, int *running);

/* Function prototype for file_input.c */
void execute_commands_file(const char *filename, char **envp, int *running);
int custom_fopen_(const char *pathname, int flags);
int custom_fclose(FILE *stream);
FILE *custom_fopen(const char *pathname, const char *mode);

/*functions builtin_common.c */
void execute_exit(int *running);
void execute_env(char **envp);
void execute_setenv(char **envp);
void execute_unsetenv(char **envp);
int snprintf_custom(char *str, size_t size, const char *format, ...);
size_t strlen_custom(const char *str);

/* Function builtin_extra.c */
void execute_cd(char **envp);
void execute_alias_command(Alias *aliases, int *alias_count);

/*Newly created Functions */
int is_whitespace(char ch);
size_t str_length(const char *str);

/* with_operators function */
void str_copy(char *dest, const char *src);
int str_compare(const char *str1, const char *str2);
void execute_command_with_operators(char *command, char **envp, int *running);

/* comment.c function */
char *find_comment_position(char *str);
void remove_comments(char *command);


#endif /* MAIN_H */

