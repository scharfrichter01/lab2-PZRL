#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define LINE_SIZE 1024

void replace_text(const char *filename, const char *old_text, const char *new_text) {
    regex_t regex;
    if (regcomp(&regex, old_text, REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    FILE *file = fopen(filename, "r+");
    if (!file) {
        perror("File opening failed");
        return;
    }

    char line[LINE_SIZE];
    while (fgets(line, sizeof(line), file)) {
        char *result = malloc(strlen(line) + 1);
        regmatch_t match;

        while (regexec(&regex, line, 1, &match, 0) == 0) {
            strncpy(result, line, match.rm_so);
            strcat(result, new_text);
            strcat(result, line + match.rm_eo);
            strcpy(line, result);
            memset(result, 0, strlen(result) + 1);  // Очищаем временную строку

        }

        fseek(file, -strlen(line), SEEK_CUR);  
        fprintf(file, "%s", line);
    }

    fclose(file);
    regfree(&regex);
}

void delete_lines(const char *filename, const char *pattern) {
    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    FILE *file = fopen(filename, "r+");
    if (!file) {
        perror("File opening failed");
        return;
    }

    char line[LINE_SIZE];
    long position;
    while (fgets(line, sizeof(line), file)) {
        position = ftell(file);

        if (regexec(&regex, line, 0, NULL, 0) != 0) {
            fseek(file, position - strlen(line), SEEK_SET);
            fprintf(file, "%s", line);
        }
    }

    fclose(file);
    regfree(&regex);
}

void insert_text_front(const char *filename, const char *text) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *file_contents = malloc(file_size + 1);
    if (file_contents == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return;
    }

    fread(file_contents, 1, file_size, file);
    file_contents[file_size] = '\0';

    fclose(file);

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        free(file_contents);
        return;
    }

    char *line = strtok(file_contents, "\n");
    while (line != NULL) {
        fprintf(file, "%s%s\n", text, line);
        line = strtok(NULL, "\n");
    }

    free(file_contents);
    fclose(file);
}

void insert_text_back(const char *filename, const char *text) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *file_contents = malloc(file_size + 1);
    if (file_contents == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return;
    }

    fread(file_contents, 1, file_size, file);
    file_contents[file_size] = '\0';

    fclose(file);

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        free(file_contents);
        return;
    }

    char *line = strtok(file_contents, "\n");
    while (line != NULL) {
        if (strstr(line, text) == NULL) {
            fprintf(file, "%s%s\n", line, text);
        } else {
            fprintf(file, "%s\n", line);
        }
        line = strtok(NULL, "\n");
    }

    free(file_contents);
    fclose(file);
}