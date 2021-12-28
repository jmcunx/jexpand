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
#include <stdlib.h>
#include <j_lib2.h>
#include <j_lib2m.h>

#include "jexpand.h"

#define MSG_HELP_11 "Expand TABS to spaces, creating out file"

/*
 * show_rev() -- Show Module Revisions
 */
int show_rev(struct s_work *w)

{

  fprintf(w->out.fp,"%s %s:\n", w->prog_name, LIT_REV);

#ifdef J_LIB2_H
  fprintf(w->out.fp, "\t%s %s\n", LIT_INFO_02, j2_get_build());
#endif

#ifdef OSTYPE
  fprintf(w->out.fp,"\t%s\n",OSTYPE);
#endif  /* OSTYPE  */
#ifdef PRETTY_NAME
  fprintf(w->out.fp,"\t%s\n",PRETTY_NAME);
#endif  /* PRETTY_NAME  */
  fprintf(w->out.fp, LIT_INFO_01, __DATE__, __TIME__);

  return(EXIT_FAILURE);

} /* show_rev() */

/*
 * show_brief_help() -- Show Brief help
 */
int show_brief_help(struct s_work *w)

{

  fprintf(w->out.fp, USG_MSG_USAGE, w->prog_name);
  fprintf(w->out.fp, "\t%s\n", MSG_HELP_11);
  fprintf(w->out.fp, USG_MSG_OPTIONS);
  fprintf(w->out.fp, USG_MSG_ARG_ERR,         SWITCH_CHAR, ARG_ERR);
  fprintf(w->out.fp, USG_MSG_ARG_FORCE,       SWITCH_CHAR, ARG_FORCE);

  fprintf(w->out.fp, USG_MSG_ARG_HELP,        SWITCH_CHAR, ARG_HELP);
  fprintf(w->out.fp, USG_MSG_ARG_OUT,         SWITCH_CHAR, ARG_OUT);
  fprintf(w->out.fp, USG_MSG_ARG_TAB_SPACE_A, SWITCH_CHAR, ARG_TAB_SPACE);
  fprintf(w->out.fp, USG_MSG_ARG_VERBOSE_5,   SWITCH_CHAR, ARG_VERBOSE);
  fprintf(w->out.fp, USG_MSG_ARG_VERSION,     SWITCH_CHAR, ARG_VERSION);

  return(EXIT_FAILURE);

} /* show_brief_help() */
