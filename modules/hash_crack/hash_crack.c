#include "hash_crack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core/core.h"

void hash_crack(char* input, char* output_path, int verbose) {
    char hashcat_output_file[] = "hashcat_results.txt";
    char command[2048];
    char* wordlist_path = "/home/kieran/CLionProjects/reaper/wordlists/rockyou.txt";
    int hashcatResult = 0;

    // attempt to crack the hash(es)
    snprintf(command, sizeof(command), "hashcat -a 0 -m 0 %s %s --outfile %s --outfile-format 2 -w 3 --force > /dev/null 2>&1",
             input, wordlist_path, hashcat_output_file);

    if (verbose) {
        log_message("Verbose mode enabled.");
        log_message("Executing Hashcat command to crack hashes:");
        log_message(command);
    }

    hashcatResult = system(command);

    // If hashcatResult is 0, hashcat executed successfully, but we need to check if it's a potfile hit
    if (hashcatResult == 0) {
        snprintf(command, sizeof(command), "hashcat --show -m 0 %s > %s", input, hashcat_output_file);

        if (verbose) {
            log_message("Executing Hashcat command with --show to display cracked hashes:");
            log_message(command);
        }

        hashcatResult = system(command);
    }

    // Check if the command to show cracked hashes was successful
    if (hashcatResult != 0) {
        handle_error("Hashcat command with --show failed or no hashes were cracked.");
        return;
    }

    // Proceed to read the hashcat_results.txt file and print or save the results as needed
    FILE* fp = fopen(hashcat_output_file, "r");
    if (!fp) {
        handle_error("Unable to open Hashcat output file.");
        return;
    }

    FILE* out_fp = NULL;
    if (output_path) {
        out_fp = fopen(output_path, "w");
    }

    char line[1024];
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (out_fp) {
            fprintf(out_fp, "%s", line);
        } else {
            printf("%s", line);
        }
    }

    if (fp) fclose(fp);
    if (out_fp) fclose(out_fp);
    remove(hashcat_output_file); // Clean up the temporary file
}
