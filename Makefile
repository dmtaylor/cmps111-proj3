# Makefile : A makefile for slug mem suite
# By: Forrest Kerslager, Nick Noto, David Taylor, Kevin Yeap, Connie Yu

CC = cc
CFLAGS = -g -Wall -Wextra

# SRCC are user C source files. Replace the file for custom projects
SRCC = example.c
# SRCO are user object files. This should require no modification
SRCO = ${SRCC:.c=.o}
# TARGET is the target binary file for the user project. Replace this
TARGET = example


all: ${TARGET}

${TARGET} : ${SRCO} slug_mem.o hashset.o meminfo.o meminfo_hash.o
	${CC} ${CFLAGS} -o ${TARGET} ${SRCO} slug_mem.o hashset.o meminfo.o meminfo_hash.o

${TEST}: ${SRCC}
	${CC} ${CFLAGS} -c ${SRCC}
	
slug_mem.o: slug_mem.c
	${CC} ${CFLAGS} -c slug_mem.c
	
hashset.o: hashset.c
	${CC} ${CFLAGS} -c hashset.c
	
meminfo.o: meminfo.c
	${CC} ${CFLAGS} -c meminfo.c
	
meminfo_hash.o: meminfo_hash.c
	${CC} ${CFLAGS} -c meminfo_hash.c
	
clean: 
	- rm -f ${TARGET} ${SRCO} slug_mem.o hashset.o meminfo.o meminfo_hash.o