EXEC = tictactoe
OBJS = main.o server.o client.o socketUtil.o controller.o model.o ui.o
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
	${CCFLAGS} -c main.c

server.o: sockets/server.c
	${CCFLAGS} -c sockets/server.c

client.o: sockets/client.c
	${CCFLAGS} -c sockets/client.c

socketUtil.o: sockets/socketUtil.c
	${CCFLAGS} -c sockets/socketUtil.c

controller.o: game/controller.c
	${CCFLAGS} -c game/controller.c

model.o: game/model.c
	${CCFLAGS} -c game/model.c

ui.o: game/ui.c
	${CCFLAGS} -c game/ui.c

runsp: ${EXEC}
	./${CACHE}/${EXEC} single-player-game

runcl: ${EXEC}
	./${CACHE}/${EXEC} client

runsv: ${EXEC}
	./${CACHE}/${EXEC} server

runvsp: ${EXEC}
	valgrind ./${CACHE}/${EXEC} single-player-game

runvcl: ${EXEC}
	valgrind ./${CACHE}/${EXEC} client

runvsv: ${EXEC}
	valgrind ./${CACHE}/${EXEC} server
