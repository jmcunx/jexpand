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

#ifndef _WIN32
#ifndef _MSDOS
#include <sys/param.h>
#endif
#endif

#include <stdio.h>
#include <string.h>
#include <errno.h>

#ifndef INIX
#include <stdlib.h>
#ifndef _MSDOS
#include <unistd.h>
#endif
#endif

#ifdef _MSDOS
#include <getopt.h>
#include <io.h>
#endif

#ifdef OpenBSD
#include <err.h>
#endif

#include <j_lib2.h>
#include <j_lib2m.h>
#include "jexpand.h"

/*
 * close_out() -- close output
 */
void close_out(struct s_file_info *f)
{

  if (f->fname != (char *) NULL)
    {
      fclose(f->fp);
      free(f->fname);
      f->fname = (char *) NULL;
    }

} /* close_out() */

/*
 * close_in() -- Open an input file
 */
void close_in(struct s_file_info *f)

{
  if (f->fname == (char *) NULL)
    return;
  if (strcmp(f->fname, FILE_NAME_STDIN) == 0)
    return;
  
  if (f->fp != (FILE *) NULL)
    {
      fclose(f->fp);
      f->fp = (FILE *) NULL;
    }

} /* close_in() */

/*
 * open_in() -- open in file
 */
int open_in(FILE **in, char *fname, FILE *fp_err)

{

  int errsave;

  if (fname == (char *) NULL)
    {
      (*in) = stdin;
      return((int) TRUE);
    }
  if (strcmp(fname, FILE_NAME_STDIN) == 0)
    {
      (*in) = stdin;
      return((int) TRUE);
    }

  (*in) = fopen(fname, "r");
  errsave = errno;

  if ((*in) == (FILE *) NULL)
    {
      fprintf(fp_err, MSG_WARN_W002, fname, strerror(errsave));
      return((int) FALSE);
    }

  return((int) TRUE);

} /* open_in() */

/*
 * show_stats() -- Show run stats
 */
void show_stats(FILE *fp, struct s_file_info *f)
{

  static int show_heading = (int) TRUE;

  if (show_heading)
    {
      fprintf(fp, "%-10s %-13s %-10s %s\n",
              LIT_LINES_READ, LIT_LINES_WRITES, LIT_BYTES, LIT_FILE);
      fprintf(fp, "%s %s %s %s\n",
              LIT_ULINE_10, LIT_ULINE_13, LIT_ULINE_10, LIT_ULINE_44);
      show_heading = (int) FALSE;
    }

  fprintf(fp, "%10lu %13lu %10lu", f->reads, f->writes, f->bytes);

  if (f->fname == (char *) NULL)
    fprintf(fp, " %s\n", LIT_STDOUT);
  else
    {
      if (strcmp(f->fname, FILE_NAME_STDIN) == 0)
	fprintf(fp, " %s\n", LIT_STDIN);
      else
	fprintf(fp, " %s\n", f->fname);
    }

} /* show_stats() */

/*
 * eoj() -- End of Job
 */
void eoj(struct s_work *w)
{

  if (w->verbose == (int) TRUE)
    show_stats(w->err.fp, &(w->out));

  close_out(&(w->err));
  close_out(&(w->out));

} /* eoj() */

/*
 * process_a_file()
 */
void process_a_file(struct s_work *w, char *fname, struct s_file_info *f)
{
  static char *buf = (char *) NULL;
  static size_t buf_size = 0;
  char *expanded = (char *) NULL;
  size_t out_size = 0;
  int err_expand = TRUE;

  expanded = (char *) NULL;
  buf      = (char *) NULL;
  f->fname = fname;

  if ( ! open_in(&(f->fp), f->fname, w->err.fp) )
    return;

  while (j2_getline(&buf, &buf_size, f->fp) > -1)
    {
      (f->reads)++;
      if (err_expand == TRUE)
        {
          f->bytes += (strlen(buf));
          j2_bye_nl(buf);
          err_expand = j2_expand_tab(w->tab_size, &out_size, &expanded, buf);
          fprintf(w->out.fp, "%s\n", expanded);
          w->out.bytes += (strlen(expanded) + 1);  /* +1 for new line */
          (w->out.writes)++;
        }
    }

  if (strcmp(f->fname, FILE_NAME_STDIN) != 0)
    close_in(f);

  if (expanded != (char *) NULL)
    free(expanded);

  if (err_expand != TRUE)
    fprintf(w->err.fp, MSG_ERR_E023, f->fname);

} /* process_a_file() */

/*
 * process_one_file()
 */
void process_one_file(struct s_work *w, char *fname)
{
  struct s_file_info in;

  init_finfo(&in);

  process_a_file(w, fname, &in);

  if (w->verbose == (int) TRUE)
    show_stats(w->err.fp, &in);

} /* process_one_file() */

/*
 * main()
 */
int main(int argc, char **argv)
{
  struct s_work w;
  int i;

#ifdef OpenBSD
  if(pledge("stdio rpath wpath cpath",NULL) == -1)
    err(1,"pledge\n");
#endif

  init(&w, argv, argc);

  /*** process all files ***/
  for (i = optind; i < argc; i++)
    process_one_file(&w, argv[i]);
  if (i == optind)
    process_one_file(&w, FILE_NAME_STDIN);

  eoj(&w);
  exit(EXIT_SUCCESS);

}  /* main() */
