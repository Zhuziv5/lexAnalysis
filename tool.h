#ifndef __TOOL_H
#define __TOOL_H
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tokenNode
{
    struct tokenNode *pNext;
    char token[20];
    unsigned char num;
    char reserve[3];
} tNode;

char readSourceCodeToBuf(char *buf, int bufSize, void *filePath, void *accessMode);
void filterSourceCode(char *buf, int bufStringLen);
int findSubstring(char *str1, char *str2);
tNode *createList();
tNode *appendNode(tNode *head, char *token, unsigned char data);
void displayList(tNode *head);
void freeList(tNode *head);
size_t tokenAnalyser(char *cleanCode, char *token, tNode *head);
int findFieldInString(char *str, char **set, unsigned int setLen);
char isLetter(char character);
char isFigure(char character);

#define TOKEN_LEN 20
#define RESERVE_WORD_LEN 32
#define OPERATOR_BOUNDRY_LEN 36
#define IS_BOUNDRY_OR_OPERATOR(ch) \
    ch == '*' || ch == '/' || ch == ';' || ch == '(' || ch == ')' || ch == '^' || ch == ',' || ch == '\"' || ch == '\'' || ch == '~' || ch == '#' || ch == '%' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '\\' || ch == '.' || ch == '\?' || ch == ':'

char *reserveWord[32];
char *operatorOrDelimiter[36];
char *IdentifierTbl[1000];
