#ifndef CORE_H
#define CORE_H
void init_reaper();

// Loads configuration from a file.
int load_config(const char* config_path);

// Logs a message to the configured log file or standard output.
void log_message(const char* message);

// Error handling utility.
void handle_error(const char* error_message);

#endif
