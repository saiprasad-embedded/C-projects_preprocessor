#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
void remove_comments(char *filename);
void process_macros(char *filename);
void process_includes(char *filename);
#endif