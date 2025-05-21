#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <unistd.h>

/**
 * @brief Represents a line of user input captured from standard input.
 *
 * This structure holds the content of the input, the size of the buffer
 * allocated for it, and the number of characters read from input.
 *
 * The `value` field is a dynamically allocated string. The caller is
 * responsible for freeing this memory when done.
 */
struct UserInput {
  char *value;   /**< Pointer to the user input string. Must be freed by the
                    caller. */
  size_t size;   /**< Size of the allocated buffer (as allocated by getline). */
  ssize_t count; /**< Number of characters read from input, including newline
                    before trimming. */
};

/**
 * @brief Reads a line of user input from standard input after displaying a
 * prompt.
 *
 * This function prompts the user with the given string and reads a line of
 * input from `stdin` using `getline`. The newline character at the end is
 * removed (if any). The input is returned in a `UserInput` struct that contains
 * the read string, the buffer size allocated by `getline`, and the number of
 * characters read.
 *
 * @note The returned `UserInput.value` points to dynamically allocated memory
 *       that must be freed by the caller to avoid memory leaks.
 *
 * @param prompt A null-terminated string (up to 200 characters) to display to
 * the user.
 * @return A `UserInput` struct containing:
 *         - `value`: pointer to the input string (without trailing newline),
 *         - `size`: size of the allocated buffer,
 *         - `count`: number of characters read (including the removed newline).
 *         If input fails (`getline` returns -1), all fields are zero or NULL.
 */
struct UserInput readUserInput(char prompt[200], FILE *input);

#endif
