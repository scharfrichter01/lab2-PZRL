#ifndef LAB2_H
#define LAB2_H

void replace_text(const char *filename, const char *old_text, const char *new_text);
void delete_lines(const char *filename, const char *pattern);
void insert_text(const char *filename, const char *text, int is_front);
void insert_text_front(const char *filename, const char *text);
void insert_text_back(const char *filename, const char *text);

#endif
