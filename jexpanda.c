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

#ifndef _WIN32
#ifndef MSDOS
#include <sys/param.h>
#endif
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

#ifdef UNIX
#include <unistd.h>
#endif
#ifdef _MSDOS
#include <getopt.h>
#endif

#include <j_lib2.h>
#include <j_lib2m.h>
#include "jexpand.h"

/*
 * open_out() -- save the file name and check status
 */
int open_out(FILE *wfp, struct s_file_info *f, char *fname, int force)

{

  int errsave;

  if (fname == (char *) NULL)
    return((int) TRUE);

  if (force == (int) FALSE)
    {
      if ( j2_f_exist(fname) )
	{
	  fprintf(wfp, MSG_ERR_E025, fname);
	  return((int) FALSE);
	}
    }


  f->fp = fopen(fname, "w");
  errsave = errno;

  if (f->fp == (FILE *) NULL)
    {
      f->fp = stderr;  /* needs to be something */
      fprintf(wfp, MSG_ERR_E002, fname);
      fprintf(wfp, "\t%s\n", strerror(errsave));
      return((int) FALSE);
    }

  /*** success, save file name ***/
  f->fname = strdup(fname);
  return((int) TRUE);

} /* open_out() */

/*
 * process_arg() -- process arguments
 */
void process_arg(int argc, char **argv, struct s_work *w)

{
  char ckarg[80];
  int opt;
  int ok;
  char *fout = (char *) NULL; 
  char *ferr = (char *) NULL; 
  int display_help = (int) FALSE;
  int display_rev  = (int) FALSE;

  sprintf(ckarg, "%c%c%c%c%c:%c:%c:", 
                 ARG_FORCE, ARG_HELP, ARG_VERBOSE, ARG_VERSION,
                 ARG_TAB_SPACE, ARG_ERR, ARG_OUT);

  while ((opt = getopt(argc, argv, ckarg)) != -1)
    {
      switch (opt)
	{
	  case ARG_TAB_SPACE:
	    w->tab_size = atoi(optarg);
	    if (w->tab_size < 1)
	      {
		fprintf(w->err.fp, MSG_ERR_E006, optarg, SWITCH_CHAR, ARG_TAB_SPACE);
		fprintf(w->err.fp, MSG_ERR_E000, w->prog_name, SWITCH_CHAR, ARG_HELP);
		exit(EXIT_FAILURE);
	      }
	    break;
	  case ARG_FORCE:
	    w->force = (int) TRUE;
	    break;
	  case ARG_HELP:
	    display_help = (int) TRUE;
	    break;
	  case ARG_VERBOSE:
	    w->verbose = (int) TRUE;
	    break;
	  case ARG_VERSION:
	    display_rev = (int) TRUE;
	    break;
	  case ARG_ERR:
	    ferr = optarg;
	    break;
	  case ARG_OUT:
	    fout = optarg;
	    break;
	  default:
	    fprintf(w->err.fp, MSG_ERR_E000, w->prog_name, SWITCH_CHAR, ARG_HELP);
	    exit(EXIT_FAILURE);
	    break;
	}
    }

  /*** save stdout/err files and open ***/
  ok = open_out(stderr, &(w->err), ferr, w->force);
  if ( ok )
    ok = open_out(w->err.fp, &(w->out), fout, w->force);
  if ( ! ok )
    {
      fprintf(w->err.fp, MSG_ERR_E000, w->prog_name, SWITCH_CHAR, ARG_HELP);
      exit(EXIT_FAILURE);
    }

  /*** show help/rev and exit ? ***/
  ok = EXIT_SUCCESS;
  if (display_help)
    ok = show_brief_help(w);
  if (display_rev)
    ok = show_rev(w);
  if (ok != EXIT_SUCCESS)
  {
    close_out(&(w->out));
    close_out(&(w->err));
    exit(ok);
  }

} /* process_arg() */

