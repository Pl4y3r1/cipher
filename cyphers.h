#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void shift(char* string, int verbose);
int getlines(FILE* stream, char*** line, int* ntot, size_t len);
char* normalize(char* string, int nflag);
void clean(char* string, int verbose);
void divideString(char* string, int n);
void debacon(char* string, int btype);
void flip(char* string);
void deHex(char* string);
void deRNA(char* string);
void xors(char* string1, char* string2);
char** atbash(FILE* stream1);
