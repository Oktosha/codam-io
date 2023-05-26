/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   codam_io.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 23:45:38 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/05/26 01:57:15 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODAM_IO_H
# define CODAM_IO_H

# include <stdarg.h>

/** @file */

/*
______                              _
| ___ \                            | |
| |_/ /_ _ _ __ __ _ _ __ ___   ___| |_ ___ _ __ ___
|  __/ _` | '__/ _` | '_ ` _ \ / _ \ __/ _ \ '__/ __|
| | | (_| | | | (_| | | | | | |  __/ ||  __/ |  \__ \
\_|  \__,_|_|  \__,_|_| |_| |_|\___|\__\___|_|  |___/

*/

# ifndef IO_BUFFER_SIZE
/** Determines the size of the buffer used in io_next_line */
#  define IO_BUFFER_SIZE 100
# endif

# ifndef IO_FAILFAST_ON_ALLOCATION_ERROR
/** If true, unsuccessful malloc immediately exits the program */
#  define IO_FAILFAST_ON_ALLOCATION_ERROR 0
# endif

# ifndef IO_FAILFAST_ON_CLOSE_ERROR
/** If true, unsuccessful close immediately exits the program */
#  define IO_FAILFAST_ON_CLOSE_ERROR 1
# endif

# ifndef IO_FAILFAST_ON_OPEN_ERROR
/** If true, unsuccessful open immediately exits the program */
#  define IO_FAILFAST_ON_OPEN_ERROR 0
# endif

# ifndef IO_FAILFAST_ON_READ_ERROR
/**
 * If true, unsuccessful read immediately exits the program
 * Read is unsuccessful if "read" call returns negative value
 * EOF isn't considered unsuccessful
 */
#  define IO_FAILFAST_ON_READ_ERROR 1
# endif

# ifndef IO_FAILFAST_ON_WRITE_ERROR
/**
 * If true, unsuccessful write immediately exits the program
 * Write is considered unsucessful if write returns negative value
 * or a value smaller than requested number of bytes to write
*/
#  define IO_FAILFAST_ON_WRITE_ERROR 1
# endif

/*
 _____       _               _
|  _  |     | |             | |
| | | |_   _| |_ _ __  _   _| |_
| | | | | | | __| '_ \| | | | __|
\ \_/ / |_| | |_| |_) | |_| | |_
 \___/ \__,_|\__| .__/ \__,_|\__|
                | |
                |_|
*/

/**
 * @brief Write string to fd
 * @param[in] fd file descriptor
 * @param[in] s string to write
 * @returns the value returned by write
 * @note write is called once, no retries
 * @note Null string will cause bus error
*/
int							io_write_string(int fd, const char *s);

/**
 * @brief Write char to fd
 * @param[in] fd file descriptor
 * @param[in] ch character to write
 * @returns the value returned by write
*/
int							io_write_char(int fd, char ch);

/**
 * @brief Write integer to fd
 * @param[in] fd file descriptor
 * @param[in] number integer to write
 * @returns number of bytes writen or -1 on error
*/
int							io_write_number(int fd, int number);

/**
 * @brief Write formatted to stdout
 * @param[in] fmt format string; recognized format specifiers: %c %d %s
 * @param[in] ... values for format to fill
 * @returns number of bytes written or -1 on error
*/
int							io_out(const char *fmt, ...);

/**
 * @brief Write formatted to stderr
 * @param[in] fmt format string; recognized format specifiers: %c %d %s
 * @param[in] ... values for format to fill
 * @returns number of bytes written or -1 on error
*/
int							io_err(const char *fmt, ...);

/**
 * @brief Write formatted to arbitrary file descriptor
 * @param[in] fd file descriptor
 * @param[in] fmt format string; recognized format specifiers: %c %d %s
 * @param[in] ... values for format to fill
 * @returns number of bytes written or -1 on error
*/
int							io_f_print(int fd, const char *fmt, ...);

/**
 * @brief Write formatted to arbitrary file descriptor (takes va_list)
 * @param[in] fd file descriptor
 * @param[in] fmt format string; recognized format specifiers: %c %d %s
 * @param[in] ap values for format to fill
 * @returns number of bytes written or -1 on error
*/
int							io_vf_print(int fd, const char *fmt, va_list ap);

/*
 _____                  _
|_   _|                | |
  | | _ __  _ __  _   _| |_
  | || '_ \| '_ \| | | | __|
 _| || | | | |_) | |_| | |_
 \___/_| |_| .__/ \__,_|\__|
           | |
           |_|
*/

/**
 * Data structure for buffer (stores extra bytes from read)
*/
typedef struct s_io_buffer
{
	char	data[IO_BUFFER_SIZE];
	int		pos;
	int		len;
}	t_io_buffer;

/**
 * Data structure that describes an input file
 * Used to hold the buffer with read data and the file descriptor together
 * Less evil than static variables in get_next_line
*/
typedef struct s_io_input_file
{
	int			fd;
	t_io_bufer	buffer;
}	t_io_file;

typedef enum e_io_open_for_read_status
{
	IO_OPEN_FOR_READ_SUCCESS,
	IO_OPEN_FOR_READ_ERROR
}	t_io_open_for_read_status;

/**
 * @brief Opens file for reading
 * @param[in] filename path to the file
 * @param[out] file variable to store info about the opened file
 * @returns operation status (success or error)
*/
t_io_open_for_read_status	io_open_for_read(char *filename, t_io_file *file);

typedef enum e_io_next_line_status
{
	IO_NEXT_LINE_MEMORY_ERROR = -2,
	IO_NEXT_LINE_READ_ERROR = -1,
	IO_NEXT_LINE_EOF = 0,
	IO_NEXT_LINE_SUCCESS = 1
}	t_io_next_line_status;

/**
 * @brief reads next line from the given file
 * @param[in] file info about the file
 * @param[out] line variable to store the read line
 * @returns operation status (success, error, eof)
 * @note the line is allocated for you, you'll need to free it later
*/
t_io_next_line_status		io_next_line(t_io_input_file *file, char **line);

typedef enum e_io_close_status
{
	IO_CLOSE_SUCCESS,
	IO_CLOSE_ERROR
}	t_io_close_status;

/**
 * @brief closes the file
 * @param[in, out] file file to close; the data in file will be reset
 * @returns operation status (success, error)
*/
t_io_close_status			io_close(t_io_file *file);

/*
 _   _      _
| | | |    | |
| |_| | ___| |_ __   ___ _ __ ___
|  _  |/ _ \ | '_ \ / _ \ '__/ __|
| | | |  __/ | |_) |  __/ |  \__ \
\_| |_/\___|_| .__/ \___|_|  |___/
             | |
             |_|
*/

/**
 * @brief Get string length as signed value
 * @note String isn't checked for validity, if you pass NULL, you get bus error
 * @note Return value is signed because math with signed things is less evil
 * @note String terminator isn't counted (as usual) io_signed_strlen("abc") == 3
 * @param[in] s string to measure
 * @returns length of the string
*/
int							io_signed_strlen(const char *s);

/**
 * Malloc wrapper, allows to implement optional failfast behaviour
*/
void						*io_wrapped_malloc(int size);

#endif
