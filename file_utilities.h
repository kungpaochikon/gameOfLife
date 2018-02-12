#ifndef FILE_UTILITIES_H
#define FILE_UTILITIES_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
int read_file( char *filename, char **buffer );
int write_file( char *filename, char *buffer, int size);
int main(int argc, char **argv);

#endif
