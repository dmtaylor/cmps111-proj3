# Makefile : A makefile for slug mem suite
# By: Forrest Kerslager, Nick Noto, David Taylor, Kevin Yeap, Connie Yu

CC = cc
CFLAGS = -lm -g -Wall -Wextra

# SRCC are user C source files. Replace the file for custom projects
SRCC = example.c
# SRCO are user object files. This should require no modification
SRCO = ${SRCC:.c=.o}
# TARGET is the target binary file for the user project. Replace this
TARGET = example


all: ${TARGET}

${TARGET} : ${SRCO} slug_mem.o hashset.o meminfo.o meminfo_hash.o
	${CC} ${CFLAGS} -o ${TARGET} ${SRCO} slug_mem.o hashset.o meminfo.o meminfo_hash.o

${SRCO}: ${SRCC}
	${CC} -c ${SRCC}
	
slug_mem.o: slug_mem.c
	${CC} -c slug_mem.c
	
hashset.o: hashset.c
	${CC} -c hashset.c
	
meminfo.o: meminfo.c
	${CC} -c meminfo.c
	
meminfo_hash.o: meminfo_hash.c
	${CC} -c meminfo_hash.c
	
clean: 
	- rm -f ${SRCO} slug_mem.o hashset.o meminfo.o meminfo_hash.o
  
spotless:
  -rm ${TARGET}
