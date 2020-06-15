#include "tool.h"

/******************************************************************************
 * @brief               To take out species code from a bunch of codes
 * @param   cleanCode   the left of pure codes
 * @param   token       to save the token which has been analysed already
 * @return  delta       Return the species code's length
******************************************************************************/
int tokenAnalyser(char *cleanCode, char *token, tNode *head)
{
    if (NULL == cleanCode || NULL == token || NULL == head)
    {
        puts("Error Input!\nExit from APP!");
        exit(0);
    }
    int delta = 0;
    char data = 0;
    int index = 0;
    while (' ' == cleanCode[delta])
    {
        delta++;
    }
    memset(token, 0, TOKEN_LEN);
    if (isLetter(cleanCode[delta]) || '_' == cleanCode[delta])
    {
        token[index] = cleanCode[delta];
        index++;
        delta++;
        while (isLetter(cleanCode[delta]) || isFigure(cleanCode[delta]) || '_' == cleanCode[delta])
        {
            token[index] = cleanCode[delta];
            delta++;
            index++;
        }
        token[index] = '\0';
        data = findFieldInString(token, reserveWord, RESERVE_WORD_LEN);
        if (data < 0)
            data = 100;
        else
            data += 1;
    }
    else if (isFigure(cleanCode[delta]))
    {
        token[index] = cleanCode[delta];
        index++;
        delta++;
        while (isFigure(cleanCode[delta]))
        {
            token[index] = cleanCode[delta];
            delta++;
            index++;
        }
        token[index] = '\0';
        data = 99;
    }
    else if (IS_BOUNDRY_OR_OPERATOR(cleanCode[delta]))
    {
        token[index] = cleanCode[delta];
        index++;
        delta++;
        token[index] = '\0';
        data = findFieldInString(token, operatorOrDelimiter, OPERATOR_BOUNDRY_LEN);
        if (data < 0)
        {
            puts("FindSubString Error!\nExit from APP!");
            exit(0);
        }
        else
            data += 33;
    }
    else if ('<' == cleanCode[delta])
    {
        if ('=' == cleanCode[delta + 1])
        {
            token[index++] = cleanCode[delta++];
            token[index++] = cleanCode[delta++];
            token[index] = '\0';
            data = 38;
        }
        else if ('<' == cleanCode[delta + 1])
        {
            token[index++] = cleanCode[delta++];
            token[index++] = cleanCode[delta++];
            token[index] = '\0';
            data = 58;
        }
        else
        {
            token[index++] = cleanCode[delta++];
            token[index] = '\0';
            data = 37;
        }
    }
    else if ('>' == cleanCode[delta])
    {
        if ('=' == cleanCode[delta + 1])
        {
            token[index++] = cleanCode[delta++];
            token[index++] = cleanCode[delta++];
            token[index] = '\0';
            data = 40;
        }
        else if ('>' == cleanCode[delta + 1])
        {
            token[index++] = cleanCode[delta++];
            token[index++] = cleanCode[delta++];
            token[index] = '\0';
            data = 59;
        }
        else
        {
            token[index++] = cleanCode[delta++];
            token[index] = '\0';
            data = 39;
        }
    }
    else if ('!' == cleanCode[delta])
    {
        if ('=' == cleanCode[delta + 1])
        {
            token[index++] = cleanCode[delta++];
            token[index++] = cleanCode[delta++];
            token[index] = '\0';
            data = 43;
        }
        else
        {
            token[index++] = cleanCode[delta++];
            token[index] = '\0';
            data = 68;
        }
    }
    else if ('=' == cleanCode[delta])
    {
        if ('=' == cleanCode[delta + 1])
        {
            token[index++] = cleanCode[delta++];
            token[index++] = cleanCode[delta++];
            token[index] = '\0';
            data = 42;
        }
        else
        {
            token[index++] = cleanCode[delta++];
            token[index] = '\0';
            data = 41;
        }
    }
    else if ('\0' == cleanCode[delta])
    {
        token[index] = '\0';
        data = 0;
        delta = -1;
    }
    else
    {
        puts("Unrecognized character!\nCheck your code!\nExit from APP!");
        exit(0);
    }
    appendNode(head, token, data);
    return delta;
}

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
