## jexpand - clone of head(1)

jexpand is a clone of expand(1) for systems that
do not have expand(1).

If expand(1) exists on your system, you should use that instead.
It will be much faster.

To build, execute build.sh to generate a Makefile from
Makefile.template on most BSD/Linux systems and IBM AIX.
For MS-DOS, it should be rather easy to create a Makefile.

This requires [j\_lib2](https://github.com/jmcunx/j_lib2) to build.

[GNU automake](https://en.wikipedia.org/wiki/Automake)
only confuses me, so I came up with my own method which
is a real hack.  But works for me.
