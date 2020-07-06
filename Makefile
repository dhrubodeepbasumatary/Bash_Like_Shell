CFLAGS = ­g ­Wall

CC = gcc

all: mathop

mathop: main.o calc.o ownCommand.o input.o i_o_redirection.o pipe.o background_process.o
	${CC} main.o calc.o ownCommand.o input.o i_o_redirection.o pipe.o background_process.o -o mathop -lreadline
main.o: calc.h ownCommand.h input.h i_o_redirection.h pipe.h main.c
	${CC} -c main.c
background_process.o: background_process.h background_process.c
	${CC} -c background_process.c
pipe.o: pipe.h pipe.c
	${CC} -c pipe.c
i_o_redirection.o: i_o_redirection.h i_o_redirection.c
	${CC} -c i_o_redirection.c
input.o: input.h input.c
	${CC} -c input.c
ownCommand.o: ownCommand.h ownCommand.c
	${CC} -c ownCommand.c
calc.o: calc.h calc.c
	${CC} -c calc.c
clean:
	rm -rf *o mathop