CC = cc
# Change TEST and TESTC to change test file
TEST = malloc_replace_test.o
TESTC = malloc_replace_test.c


test: ${TEST} slug_mem.o hashset.o meminfo.o meminfo_hash.o
	${CC} -o test ${TEST} slug_mem.o hashset.o meminfo.o meminfo_hash.o

${TEST}: ${TESTC} slug_mem.h hashset.h meminfo.h meminfo_hash.h 
	${CC} -c ${TESTC}
slug_mem.o: slug_mem.c slug_mem.h hashset.h meminfo.h meminfo_hash.h
	${CC} -c slug_mem.c
hashset.o: hashset.c hashset.h meminfo.h meminfo_hash.h
	${CC} -c hashset.c
meminfo.o: meminfo.c meminfo.h
	${CC} -c meminfo.c
meminfo_hash.o: meminfo_hash.c meminfo_hash.h 
	${CC} -c meminfo_hash.c
clean: 
	rm -f .o ${TEST} slug_mem.o hashset.o meminfo.o meminfo_hash.o test

