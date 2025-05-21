#ifndef CONFIG_H
#define CONFIG_H

/**
 * @brief Holds configuration information parsed from command-line arguments.
 */
typedef struct {
  char *ip;  /**< IP address as a string (e.g., "127.0.0.1"). */
  int port;  /**< Port number. */
  int valid; /**< Flag indicating if the config is valid (1 = valid, 0 =
                invalid). */
} Config;

/**
 * @brief Parses command-line arguments to extract IP address and port number.
 *
 * This function expects at least two arguments:
 * - argv[1]: IP address
 * - argv[2]: Port number
 *
 * If the port is not a valid integer, the config is marked invalid.
 *
 * @param argc Argument count from main.
 * @param argv Argument vector from main.
 * @return A Config struct containing the parsed values and a validity flag.
 */
Config parseArgs(int argc, char *argv[]);

#endif
