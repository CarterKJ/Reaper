#include "modules/hash_crack/hash_crack.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    int verbose = 0;
    char *input = NULL;
    char *output_path = NULL;

    // start loop at 1, because first argument is always "crack"
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        } else if (!input) {
            input = argv[i];
        } else if (!output_path && strcmp(argv[i-1], "-v") != 0) {
            output_path = argv[i];
        }
    }

    if (!input) {
        fprintf(stderr, "Usage: %s crack <hash_or_file_of_hashes> [output_file] [-v]\n", argv[0]);
        return 1;
    }
    hash_crack(input, output_path, verbose);
    return 0;
}
