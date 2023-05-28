# --- Boilerplate things for every makefile ---

SHELL=/bin/sh
CC=cc
CFLAGS=-Wall -Wextra -Werror

# --- Main target ---

NAME=libcodamio.a
BUILD_FOLDER=build
NAME_IN_BUILD_FOLDER=${BUILD_FOLDER}/${NAME}
all: ${NAME_IN_BUILD_FOLDER}

# --- Building objects --

SRCS=io_close.c \
io_reset_buffer.c \
io_err.c \
io_signed_strlen.c \
io_f_print.c \
io_vf_print.c \
io_memset.c \
io_wrapped_malloc.c \
io_next_line.c \
io_write_char.c \
io_open_for_read.c \
io_write_numer.c \
io_out.c \
io_write_string.c

SRC_FOLDER=src

HEADERS=codam_io.h
INCLUDE_FOLDER=include
HEADERS_IN_FOLDER=${addprefix ${INCLUDE_FOLDER}/,${HEADERS}}

BINARY_FOLDER=${BUILD_FOLDER}/bin
OBJS=${addprefix ${BINARY_FOLDER}/,${SRCS:.c=.o}}

${OBJS}: ${BINARY_FOLDER}/%.o: ${SRC_FOLDER}/%.c ${HEADERS_IN_FOLDER}
	mkdir -p $(@D)
	${CC} ${CFLAGS} $< -o $@ -c -I${INCLUDE_FOLDER}

# -- Putting lib together --

${NAME_IN_BUILD_FOLDER}: ${OBJS}
	ar rc $@ $^

# -- More boilerplate things --

.PHONY: all clean fclean re

clean:
	rm -rf ${BINARY_FOLDER}

fclean: clean
	rm -f ${BUILD_FOLDER}

re: fclean all
