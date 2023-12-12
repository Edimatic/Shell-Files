#include "eddi.h"

/**
 * custom_strncmp - Custom implementation of strncmp function.
 * @s1: The first string.
 * @s2: The second string.
 * @n: The number of characters to compare.
 *
 * Return: 0 if strings are equal, positive if s1 > s2, negative if s1 < s2.
 */
int custom_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && *s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * get_path - Get the full path of the command using the PATH envt variable.
 * @command: The command to search for.
 * @envp: The environment variables.
 *
 * Return: The full path of the command or NULL if not found.
 */
char *get_path(char *command, char **envp)
{
		char *path_env = NULL;
		char *token;
		char *path;
		size_t path_len;

/* Search for the PATH variable in the environment */
while (*envp != NULL)
{
	if  (custom_strncmp(*envp, "PATH=", 5) == 0)
	{
		path_env = *envp + 5;
		break;
	}
	envp++;
}

if (path_env == NULL)
	return (NULL);

/* Tokenize the PATH variable */
	token = strtok(path_env, ":");
	while (token != NULL)
	{
	path_len = strlen_custom(token) + strlen_custom(command) + 2;
	path = malloc(path_len);
	if (path == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
snprintf_custom(path, path_len, "%s/%s", token, command);
if (access(path, X_OK) == 0)/*Check if the command exists at the path*/
return (path);
	free(path); /* Free the memory allocated for the path */
	token = strtok(NULL, ":");/* Move to the next token */
	}
	return (NULL);
}

/**
 * execute_command - Execute the given command using execvp.
 * @command: The command to be executed.
 * @envp: The environment variables.
 * @running: A pointer to a flag indicating whether the shell is running.
 */
void execute_command(char *command, char **envp, int *running)
{
		pid_t child_pid;
		int status, i = 0;

	if (is_builtin(command))
	{
	execute_builtin(command, running, envp, aliases);
		return;
}
		child_pid = fork();
	if (child_pid == -1)
{
	perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
{
		char *token, *args[64];/* Child process */
	token = strtok(command, " \t\n");/* Tokenize the command string */
	while (token != NULL)
	{
		args[i++] = token;
	token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	/* Search for the command in the PATH */
		execvp(args[0], args);

		perror("execvp");/* If execvp fails, print an error message */
		exit(EXIT_FAILURE);
	}
	else
	{
	waitpid(child_pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	custom_fprintf_stderr("Error executing command: %s\n", command);
	}
}

