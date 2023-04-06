/*
 * Copyright (c) 2005 ... 2023 2024
 *     John McCue <jmccue@jmcunx.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#ifndef JEXPAND_H

#define JEXPAND_H "INCLUDED"

#define PROG_NAME        "jexpand"
#define EXPAND_TAB_DEFAULT 8

#ifndef JLIB2_CHAR_NULL
#define NO_JLIB 1
#define JLIB2_CHAR_NULL  ((char) '\0')
#endif

#ifndef NULL
#define NULL '\0'
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef SSIZE_T
#define SSIZE_T ssize_t
#endif
#ifndef TAB_CHAR
#define TAB_CHAR 0x09
#endif

struct s_file_info
{
  FILE *fp;
  char *fname;
  int  open_error;  /* TRUE or FALSE */
  unsigned long reads;
  unsigned long writes;
  unsigned long bytes;
} ;

struct s_work
{
  char *prog_name;
  int  force;                  /* TRUE or FALSE, defaults to FALSE */
  int  verbose;                /* TRUE or FALSE, defaults to FALSE */
  int  tab_size;               /* TAB stop location, default 8     */
  struct s_file_info out;
  struct s_file_info err;
} ;

#ifdef NO_JLIB
#define ARG_ERR           'e'  /* Output Error File                  */
#define ARG_FORCE         'f'  /* force create files                 */
#define ARG_HELP          'h'  /* Show Help                          */
#define ARG_OUT           'o'  /* Output File                        */
#define ARG_TAB_SPACE     'T'  /* Expand tabs to # characters        */
#define ARG_VERBOSE       'v'  /* Verbose                            */
#define ARG_VERSION       'V'  /* Show Version Information           */
#define FILE_NAME_STDIN   "-"
#define LIT_BYTES         "Bytes"
#define LIT_FILE          "File"
#define LIT_INFO_01       "\tBuild: %s %s\n"
#define LIT_LINES_READ    "Lines Read"
#define LIT_LINES_WRITES  "Lines Written"
#define LIT_REV           "Revision"
#define LIT_STDIN         "(standard input)"
#define LIT_STDOUT        "(standard output)"
#define LIT_ULINE_10      "----------"
#define LIT_ULINE_13      "-------------"
#define LIT_ULINE_44      "-------------------------------------------"
#define MSG_ERR_E000      "Try '%s %c%c' for more information\n"
#define MSG_ERR_E002      "ERROR E002: Cannot open '%s' for write, processing aborted\n"
#define MSG_ERR_E006      "ERROR E006: '%s' is an invalid value for %c%c\n"
#define MSG_ERR_E023      "ERROR E023: Cannot allocate memory when processing file %s, file bypassed\n"
#define MSG_ERR_E025      "ERROR E025: File %s cannot be created, already exists\n"
#define MSG_WARN_W002     "W002: Open Error Bypass File '%s' : %s\n"
#define SWITCH_CHAR       '-'
#define USG_MSG_ARG_ERR           "\t%c%c file\t\t: Write errors to file 'file', default stderr\n"
#define USG_MSG_ARG_FORCE         "\t%c%c\t\t: force create of files when found\n"
#define USG_MSG_ARG_HELP          "\t%c%c\t\t: Show brief help and exit\n"
#define USG_MSG_ARG_OUT           "\t%c%c file\t\t: Write output to file 'file', default stdout\n"
#define USG_MSG_ARG_TAB_SPACE_A   "\t%c%c num\t\t: Expand tabs to 'num' spaces.\n"
#define USG_MSG_ARG_VERBOSE_5     "\t%c%c\t\t: show run stats on stderr\n"
#define USG_MSG_ARG_VERSION       "\t%c%c\t\t: Show revision information and exit\n"
#define USG_MSG_OPTIONS           "Options\n"
#define USG_MSG_USAGE             "usage:\t%s [OPTIONS] [FILES ...]\n"
#endif /* NO_JLIB */


/*** prototypes ***/
void process_arg(int, char **, struct s_work *);
void init(struct s_work *, char **, int);
void init_finfo(struct s_file_info *);
int  show_rev(struct s_work *);
int  show_brief_help(struct s_work *);
char *get_progname(char *, char *);
void close_out(struct s_file_info *);

#ifdef NO_JLIB
SSIZE_T j2_getline(char **buf, size_t *n, FILE *fp);
char *j2_get_prgname(char *argv_0, char *default_name);
int j2_expand_tab(int tab_size, size_t *out_buf_size, char **out_buf, char *in_buf);
int j2_f_exist(char *file_name);
long int j2_bye_last(char *x, char lastc);
long int j2_clr_str(char *s, char c, int size);
#define j2_bye_nl(x)    j2_bye_last((x), '\n')
#define j2_bye_ctlm(x)  j2_bye_last((x), '\r')
#endif /* NO_JLIB */

#endif /* JEXPAND_H */
