#ifndef __TOOL_H
#define __TOOL_H
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char readSourceCodeToBuf(char *buf, int bufSize, void *filePath, void *accessMode);

char reserveWord[32][20];
char operatorOrDelimiter[36][10];
char IdentifierTbl[1000][50];