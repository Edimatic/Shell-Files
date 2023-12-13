#ifndef _EDDI_HEADER_FILE
#define _EDDI_HEADER_FILE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2


#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;



typedef struct liststr
{
	char *rop;
	struct liststr *after;
	int figure;
} regis_t;


typedef struct updatepass
{
	char *logic;
	char **argv;
	char *direct;
	int argc;
	unsigned int check_score;
	int nums_mistek;
	int edgesum_up;
	char *file_tag;
	regis_t *env;
	regis_t *history;
	regis_t *alias;
	char **environ;
	int ranking;
	int pro_envt;

	char **grip_bufa;
	int grip_bufa_dash;
	int fildes_output;
	int pass_note;
} update_p;

#define UPDATE_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}


typedef struct builtin
{

	char *dash;
	int (*role)(update_p *);

} builtin_submit;


int hsh(update_p *, char **);
int asset_builtin(update_p *);
void asset_cmd(update_p *);
void furk_cmd(update_p *);
int mult_cmd(update_p *, char *);
char *dupli_chars(char *, int, int);
char *asset_path(update_p *, char *, char *);
int loophsh(char **);
void _funcputs(char *);
int _funcputchar(char ch);
int _putfildes(char chr, int fildes);
int _puts_fildes(char *strn, int fildes);
int _strlen_(char *);
int _strcmp_(char *, char *);
char *begin_on(const char *, const char *);
char *_strcat_(char *, char *);
char *_strcpy_(char *, char *);
char *_strdup_(const char *);
void _puts_(char *);
int _putchar(char);
char *_strncpy_(char *, char *, int);
char *_strncat_(char *, char *, int);
char *_strchr_(char *, char);
char **strtop_k(char *, char *);
char **strto_k(char *, char);
char *_wmanpro(char *, char, unsigned int);
void f_empty(char **);
void *_allocate(void *, unsigned int, unsigned int);
int pro_free(void **);
int opt_conjoint(update_p *);
int opt_deli(char, char *);
int opt_alphabet(int);
int opt_atoi(char *);
int _erro_out(char *);
void show_error(update_p *, char *);
int show_dir(int, int);
char *change_numz(long int, int, int);
void take_out_comments(char *);
int _proexit(update_p *);
int _procd(update_p *);
int _prohelp(update_p *);
int _prohistory_(update_p *);
int _proalias_(update_p *);
ssize_t wax_input(update_p *);
int wax_get_line(update_p *, char **, size_t *);
void sigl_Handler(int);
void remove_update(update_p *);
void make_update(update_p *, char **);
void discharge_update(update_p *, int);
char *opt_envir(update_p *, const char *);
int _proenvt(update_p *);
int _prosetenvt(update_p *);
int _prounsetenvt(update_p *);
int pop_envt_regis(update_p *);
char **_pro_environ(update_p *);
int _pro_unsetenvt(update_p *, char *);
int proset_envt(update_p *, char *, char *);
char *get_chron_doc(update_p *update);
int document_chron(update_p *update);
int present_chron(update_p *update);
int produce_chron_reg(update_p *update, char *bufa, int cordcount);
int renums_chron(update_p *update);
regis_t *attach_node(regis_t **, const char *, int);
regis_t *attach_node_end(regis_t **, const char *, int);
size_t output_reg_strn(const regis_t *);
int remov_node_via_roll(regis_t **, unsigned int);
void empty_register(regis_t **);
size_t register_extent(const regis_t *);
char **register_via_strn(regis_t *);
size_t output_register(const regis_t *);
regis_t *node_begin_on(regis_t *, char *, char);
ssize_t bring_node_roll(regis_t *, regis_t *);
int pro_chan(update_p *, char *, size_t *);
void confi_chan(update_p *, char *, size_t *, size_t, size_t);
int reassign_alias(update_p *);
int reassign_vars(update_p *);
int reassign_strn(char **, char *);

#endif

