# Program Executable
EXE			:=	ft_ping

# Files
SRC			:=	src/main.c \
				src/parser.c \
				src/printer.c \
				src/ft_ping.c \

# Variables
CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra -Iinclude -O2 -g3

# Makefile
all			:	${EXE}

${EXE}		:	${SRC}
				${CC} ${CFLAGS} ${SRC} -o ${EXE}

build:
			docker build -t ft_ping .

run:
			docker run -it ft_ping

rm:
			docker rm -f ft_ping || true
			docker rmi -f ft_ping || true

clean:
			rm -rf ${EXE}

re			:	clean all

.PHONY		:	all clean re
