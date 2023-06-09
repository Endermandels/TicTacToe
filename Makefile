EXEC = tictactoe
OBJS = main.o
CCFLAGS = gcc -Wall
CACHE = .cache

${EXEC}: ${OBJS}
	${CCFLAGS} -o ${EXEC} ${OBJS} -lncurses
	make cache

# if the cache does not exist, create it
cache: | ${CACHE}
	mv ${OBJS} ${EXEC} ${CACHE}

# $@ refers to the name of this command, ${CACHE}
# -p creates the directory if it doesn't exist
#	and does not return an error if it does exist
${CACHE}:
	mkdir -p $@

main.o: main.c
	${CCFLAGS} -c main.c -o main.o

run: ${EXEC}
	./${CACHE}/${EXEC}

runv: ${EXEC}
	valgrind ./${CACHE}/${EXEC}

runvc: ${EXEC}
	valgrind --leak-check=full ./${CACHE}/${EXEC}
