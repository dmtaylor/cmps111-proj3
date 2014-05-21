README

Project 3

By: Forrest Kerslager
    Nick Noto
    David Taylor
    Kevin Yeap
    Connie Yu
    
########################################################################
                            File Listing
########################################################################

hashset.c
hashset.h
meminfo.c
meminfo.h
meminfo_hash.c
meminfo_hash.h
slug_mem.c
slug_mem.h

/tests
    test1.c
    test2.c
    test3.c
    test4.c
    test5.c
    test6.c
    test7.c
    test8.c
    test9.c

README.txt
design.pdf

########################################################################
                            Build Instructions
########################################################################

To include the slug_memory suite into a given program, include

                            slug_mem.h

into whatever project you're building, and compile the following files
with your existing project.

                            hashset.c
                            meminfo.c
                            meminfo_hash.c
                            slug_mem.c
                            
To make use of the included Makefile, modify the labels at the top
to be the C source files for your project, the target object files
for your program, and the build target for your project. The make
target "all" will then attempt to compile the .c files specified with
slug memory and create the specified target.

########################################################################
                                Testing
########################################################################

Test files have been included in the distribution. These tests run the
gamut of memory usages. Feel free to use them by specifying them in the
Makefile.

########################################################################
                            Production Notes
########################################################################

#TODO

########################################################################
                             Misc. Issues
########################################################################

#TODO
