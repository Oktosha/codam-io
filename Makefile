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

SRCS=
HEADER=codam_io.h

SRC_FOLDER=src
BINARY_FOLDER=${BUILD_FOLDER}/bin


# -- More boilerplate things --

.PHONY: all clean fclean re

clean:
	rm -rf ${BINARY_FOLDER}

fclean: clean
	rm -f ${BUILD_FOLDER}

re: fclean all