/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   codam_io.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 23:45:38 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/06/04 20:57:34 by dkolodze      ########   odam.nl         */
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
/** Determines the size of the buffer used in calls to read */
#  define IO_BUFFER_SIZE 100
# endif

# ifndef IO_PRINT_NULLSTR_NICELY
/**
 * If set to true, NULL passed to %s format is printed as "(null)"
 * By default attempt to print a NULL with %s crashes the program
 */
#  define IO_PRINT_NULLSTR_NICELY 0
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
 _____     _ _     _____           _
|  ___|   (_) |   /  __ \         | |
| |____  ___| |_  | /  \/ ___   __| | ___  ___
|  __\ \/ / | __| | |    / _ \ / _` |/ _ \/ __|
| |___>  <| | |_  | \__/\ (_) | (_| |  __/\__ \
\____/_/\_\_|\__|  \____/\___/ \__,_|\___||___/

Redefine these exit codes if you want consistency with your exit codes

*/

# ifndef IO_EXIT_ALLOCATION_ERROR
/**
 * If IO_FAILFAST_ON_ALLOCATION_ERROR is true program exits with this code
 * after unsuccessful malloc (i. e. malloc returning NULL)
*/
#  define IO_EXIT_ALLOCATION_ERROR 134
# endif

# ifndef IO_EXIT_CLOSE_ERROR
/**
 * If IO_FAILFAST_ON_CLOSE_ERROR is true program exits with this code
 * after unsuccessful close (close returns -1)
*/
#  define IO_EXIT_CLOSE_ERROR 99
# endif

# ifndef IO_EXIT_OPEN_ERROR
/**
 * If IO_FAILFAST_ON_OPEN_ERROR is true program exits with this code
 * after unsuccessful open (open returns negative value)
*/
#  define IO_EXIT_OPEN_ERROR 98
# endif

# ifndef IO_EXIT_READ_ERROR
/**
 * If IO_FAILFAST_ON_READ_ERROR is true program exits with this code
 * after unsuccessful read (read returns negative value; EOF is not an error)
*/
#  define IO_EXIT_READ_ERROR 100
# endif

# ifndef IO_EXIT_WRITE_ERROR
/**
 * If IO_FAILFAST_ON_WRITE_ERROR is true program exits with this code
 * after unsuccessful write (write writes less bytes that requested or errors)
*/
#  define IO_EXIT_WRITE_ERROR 101
# endif

# ifndef IO_EXIT_WRONG_ARGS_ERROR
/**
 * Program exits with this code if passed args are invalid
 * Examples: wrong format, request to give <= 0 memory to io_wrapped_malloc
*/
#  define IO_EXIT_WRONG_ARGS_ERROR -2
# endif

# ifndef IO_EXIT_ASSERT_FAILED
/**
 * Program exits with this code if condition passed to io_assert is false
*/
#  define IO_EXIT_ASSERT_FAILED -1
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
 * @returns 0 on success, -1 on error
 * @note write is called once, no retries
 * @note Null string will cause bus error
*/
int							io_write_string(int fd, const char *s);

/**
 * @brief Write char to fd
 * @param[in] fd file descriptor
 * @param[in] ch character to write
 * @returns 0 on success, -1 on error
*/
int							io_write_char(int fd, char ch);

/**
 * @brief Write integer to fd
 * @param[in] fd file descriptor
 * @param[in] number integer to write
 * @returns 0 on success, -1 on error
*/
int							io_write_number(int fd, int number);

/**
 * @brief Write formatted to stdout
 * @param[in] fmt format string; recognized format specifiers: %c %d %s
 * @param[in] ... values for format to fill
 * @returns 0 on success, -1 on error
*/
int							io_out(const char *fmt, ...);

/**
 * @brief Write formatted to stderr
 * @param[in] fmt format string; recognized format specifiers: %c %d %s
 * @param[in] ... values for format to fill
 * @returns 0 on success, -1 on error
*/
int							io_err(const char *fmt, ...);

/**
 * @brief Write formatted to arbitrary file descriptor
 * @param[in] fd file descriptor
 * @param[in] fmt format string; recognized format specifiers: %c %d %s
 * @param[in] ... values for format to fill
 * @returns 0 on success, -1 on error
*/
int							io_f_print(int fd, const char *fmt, ...);

/**
 * @brief Write formatted to arbitrary file descriptor (takes va_list)
 * @param[in] fd file descriptor
 * @param[in] fmt format string; recognized format specifiers: %c %d %s
 * @param[in] ap values for format to fill
 * @returns 0 on success, -1 on error
*/
int							io_vf_print(int fd, const char *fmt, va_list ap);

/**
 * @brief prints formatted message to stderr and exits if condition is false
 * message is printed bold prefixed with "Assertion failed: " written in red
 * @param[in] condition thing to check
 * @param[in] fmt format string; recognized format specifiers: %c %d %s
 * @param[in] ... values for format to fill
*/
void						io_assert(int condition, const char *fmt, ...);

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
 * Data structure that stores arbitrary bytes (including '\0' in the middle)
*/
typedef struct s_io_charz
{
	char	*data;
	int		len;
	int		capacity;
}	t_io_charz;

typedef enum e_io_read_file_status
{
	IO_READ_FILE_CLOSE_ERROR = 8,
	IO_READ_FILE_OPEN_ERROR = 4,
	IO_READ_FILE_ALLOC_ERROR = 2,
	IO_READ_FILE_READ_ERROR = 1,
	IO_READ_FILE_SUCCESS = 0
}	t_io_read_file_status;

/**
 * @brief reads all lines from a file
 * @param[in] filename filename to read from
 * @param[out] data file contents; no null-termination, check data.len
 * @return operation status (success or a mask of errors),
 * for example, IO_READ_FILE_ALLOC_ERROR | IO_READ_FILE_CLOSE_ERROR
 * check specific errors using bit operations
*/
t_io_read_file_status		io_read_file(char *filename, t_io_charz *data);

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

/**
 * Fills length bytes of memory with value
*/
void						io_memset(void *memory, int length, char value);

/**
 * Copies n_bytes from src to dst
 * dst and src should not overlap!
*/
void						io_memcpy(void *dst, void *src, int n_bytes);

/**
 * Function called by other functions in the lib to exit on error
 * Not intended for outer use
*/
void						io_impl_exit(char *func_name, int exit_code);

#endif
