# Program Executable
EXE			:=	ft_ping

# Files
SRC			:=	src/main.c \
				src/parser.c \
				src/printer.c \

# Variables
CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra -Iinclude -O2 -g3

# Makefile
all			:	${EXE}

${EXE}		:	${SRC}
				${CC} ${CFLAGS} ${SRC} -o ${EXE}

clean		:
				rm -rf ${EXE}

re			:	clean all

.PHONY		:	all clean re
