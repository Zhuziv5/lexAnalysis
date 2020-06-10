#include "tool.h"

//用全局变量存储----保留字段 32个
char reserveWord[32][20] = {
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"};

//全局变量存储----界符运算符
char operatorOrDelimiter[36][10] = {
    "+", "-", "*", "/", "<", "<=", ">", ">=", "=", "==",
    "!=", ";", "(", ")", "^", ",", "\"", "\'", "#", "&",
    "&&", "|", "||", "%", "~", "<<", ">>", "[", "]", "{",
    "}", "\\", ".", "\?", ":", "!"};

//定义一个标识符数组
char IdentifierTbl[1000][50] = {""};
/**
 * read the file which contains source codes
 * and write them into array 
*/
char readSourceCodeToBuf(char *buf, int bufSize, void *filePath, void *accessMode)
{
    if (NULL == buf || NULL == filePath || NULL == accessMode)
    {
        puts("Input error!\nExit App!");
        exit(0);
    }
    FILE *sourceCode = fopen(filePath, accessMode);
    if (NULL == sourceCode)
    {
        puts("Cannot open the file!\nExit APP!");
        fclose(sourceCode);
        exit(0);
    }
    char cprt = '0';
    unsigned int i = 0;
    memset(buf, 0, bufSize);
    while (1)
    {
        cprt = fgetc(sourceCode);
        if (feof(sourceCode))
        {
            break;
        }
        buf[i++] = cprt;
        // printf("%c", cprt);
    }
    fclose(sourceCode);
    // printf("%s", buf);
    // releaseBuf();
    return 1;
}

/**
 * Preprocess of lexical analysis
 * Remove useless characters and commented parts
 * 
*/
char filterSourceCode(char *buf, int bufStringLen)
{
    char tempString[10000];
}