/*
 * Copyright (c) 2005 ... 2021 2022
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
#ifndef JEXPAND_H_REV

#define JEXPAND_H_REV "$Id: jexpand.h,v 3.1 2021/12/27 21:57:07 jmccue Exp $"

#define PROG_NAME        "jexpand"
#define EXPAND_TAB_DEFAULT 8

/*** Structures ***/

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


/*** prototypes ***/
void process_arg(int, char **, struct s_work *);
void init(struct s_work *, char **, int);
void init_finfo(struct s_file_info *);
int  show_rev(struct s_work *);
int  show_brief_help(struct s_work *);
char *get_progname(char *, char *);
void close_out(struct s_file_info *);

#endif /* JEXPAND_H_REV */
