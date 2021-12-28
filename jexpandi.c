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
#include <ctype.h>

#ifdef UNIX
#include <unistd.h>
#endif
#ifdef _MSDOS
#include <io.h>
#endif
#include <j_lib2.h>
#include <j_lib2m.h>

#include "jexpand.h"

/*
 * init_finfo() -- initialize out file structure
 */
void init_finfo(struct s_file_info *f)

{

  f->fp         = (FILE *) NULL;
  f->fname      = (char *) NULL;
  f->reads      = (unsigned long) 0;
  f->writes     = (unsigned long) 0;
  f->bytes      = (unsigned long) 0;
  f->open_error = (int) FALSE;

} /* init_finfo() */

/*
 * clear_work()
 */
void clear_work(struct s_work *w, char *a)

{

  w->force       = (int) FALSE;
  w->verbose     = (int) FALSE;
  w->tab_size    = (int) EXPAND_TAB_DEFAULT;
  w->prog_name   = j2_get_prgname(a, PROG_NAME);

  init_finfo(&(w->out));
  init_finfo(&(w->err));
  w->err.fp = stderr;
  w->out.fp = stdout;

} /* clear_work() */

/*
 * init() -- setup for Run
 */
void init(struct s_work *w, char **argv, int argc)

{

  clear_work(w, argv[0]);

  /* process options */
  process_arg(argc, argv, w);

} /* process_arg() */
