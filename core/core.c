#include "core.h"
#include <stdio.h>
#include <stdlib.h>

void init_reaper() {
    load_config("reaper.cfg");
    log_message("Reaper initialized.");
}

int load_config(const char* config_path) {
    // Open the configuration file and read settings
    FILE* file = fopen(config_path, "r");
    if (!file) {
        handle_error("Failed to open configuration file.");
        return -1;
    }
    fclose(file);
    return 0;
}

void log_message(const char* message) {
    printf("LOG: %s\n", message);
}

void handle_error(const char* error_message) {
    fprintf(stderr, "ERROR: %s\n", error_message);
}
