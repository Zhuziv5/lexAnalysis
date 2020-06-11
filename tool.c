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
 * 
 * 
 * 
*/
/******************************************************************************
 * @brief   Preprocess of lexical analysis.
 *          Remove useless characters and commented parts of the given file
 * @param   buf      Input file
 * @param   bufLen   file length
 * @return  
 * 
******************************************************************************/
void filterSourceCode(char *buf, int bufStringLen)
{
    if (NULL == buf)
    {
        puts("Wrong input file!\nExit from APP!");
        exit(0);
    }
    char tempString[10000];
    int indexTmp = 0;
    char *cur = buf;
    int index = -1;
    for (int i = 0; i < bufStringLen; i++)
    {
        cur = &buf[i];
        if ('/' == buf[i] && '/' == buf[i + 1])
        {
            index = findSubstring(cur, "\n");
            if (index < 0)
            {
                puts("All codes left are comments!");
                break;
            }
            i += index;
            continue;
        }
        if ('/' == buf[i] && '*' == buf[i + 1])
        {
            index = findSubstring(cur, "*/");
            if (index < 0)
            {
                puts("Wrong comments!\nExit from APP!");
                exit(0);
            }
            i += index + 1;
            continue;
        }
        if (buf[i] != '\n' && buf[i] != '\r' && buf[i] != '\t')
            tempString[indexTmp++] = buf[i];
    }
    tempString[indexTmp] = '\0';
    strncpy(buf, tempString, indexTmp + 1);
}

/******************************************************************************
 * @brief          To find a specific substring from a longer string
 * @param   str1   main string
 * @param   str2   substring
 * @return  j      Return the first index where substring appears in main string
 *          -1     Fail
******************************************************************************/
int findSubstring(char *str1, char *str2)
{
    if (NULL == str1 || NULL == str2 || (strlen(str1) < strlen(str2)))
        return -1;
    char *mainStr = str1;
    size_t index = 0;
    char *cur = mainStr;
    while (cur)
    {
        char *strLoop = cur;
        char *subLoop = str2;
        while (subLoop && strLoop && *subLoop == *strLoop)
        {
            subLoop++;
            strLoop++;
        }
        if ('\0' == *subLoop)
            break;
        else if ('\0' == *strLoop)
            return -1;
        else
        {
            cur++;
            index++;
        }
    }
    return index;
}
