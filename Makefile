# Makefile : A makefile for slug mem suite
# By: Forrest Kerslager, Nick Noto, David Taylor, Kevin Yeap, Connie Yu

CC = cc

# SRCC are user C source files. Replace the file for custom projects
SRCC = example.c
# SRCO are user object files. This should require no modification
SRCO = ${SRCC:.c=.o}
# TARGET is the target binary file for the user project. Replace this
TARGET = example


all: ${TARGET}

${TARGET} : ${SRCO} slug_mem.o hashset.o meminfo.o meminfo_hash.o
	${CC} -o ${TARGET} ${SRCO} slug_mem.o hashset.o meminfo.o meminfo_hash.o

${TEST}: ${SRCC} slug_mem.h hashset.h meminfo.h meminfo_hash.h 
	${CC} -c ${SRCC}
	
slug_mem.o: slug_mem.c slug_mem.h hashset.h meminfo.h meminfo_hash.h
	${CC} -c slug_mem.c
	
hashset.o: hashset.c hashset.h meminfo.h meminfo_hash.h
	${CC} -c hashset.c
	
meminfo.o: meminfo.c meminfo.h
	${CC} -c meminfo.c
	
meminfo_hash.o: meminfo_hash.c meminfo_hash.h 
	${CC} -c meminfo_hash.c
	
clean: 
	- rm -f .o ${SRCO} slug_mem.o hashset.o meminfo.o meminfo_hash.o
	
spotless: clean
	- rm test

