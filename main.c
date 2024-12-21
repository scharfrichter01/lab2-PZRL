#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "lab2.h"

void process_command(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: ./sed_simplified <file> <operation> <args>\n");
        return;
    }

    const char *filename = argv[1];
    const char *operation = argv[2];

    if (strcmp(operation, "-r") == 0) {
        if (argc < 5) {
            fprintf(stderr, "Usage: ./sed_simplified <file> -r <old_text> <new_text>\n");
            return;
        }
        replace_text(filename, argv[3], argv[4]);
    }
    else if (strcmp(operation, "-d") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Usage: ./sed_simplified <file> -d <pattern>\n");
            return;
        }
        delete_lines(filename, argv[3]);
    }
    else if (strcmp(operation, "-i") == 0) {
        if (argc < 5) {
            fprintf(stderr, "Usage: ./sed_simplified <file> -i <option> <text>\n");
            return;
        }
        if (strcmp(argv[3], "-f") == 0) {
            insert_text_front(filename, argv[4]);
        } else if (strcmp(argv[3], "-b") == 0) {
            insert_text_back(filename, argv[4]);
        } else {
            fprintf(stderr, "Usage: ./sed_simplified <file> -i -f <text> or -b <text>\n");
        }
    } else {
        fprintf(stderr, "Unknown operation: %s\n", operation);
    }
}

int main(int argc, char *argv[]) {
    process_command(argc, argv);
    return 0;
}
