#include "tool.h"

//用全局变量存储----保留字段 32个
char *reserveWord[32] = {
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"};

//全局变量存储----界符运算符
char *operatorOrDelimiter[36] = {
    "+", "-", "*", "/", "<", "<=", ">", ">=", "=", "==",
    "!=", ";", "(", ")", "^", ",", "\"", "\'", "#", "&",
    "&&", "|", "||", "%", "~", "<<", ">>", "[", "]", "{",
    "}", "\\", ".", "\?", ":", "!"};

//定义一个标识符数组
char *IdentifierTbl[1000] = {""};
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

/******************************************************************************
 * @brief          Save tokens analysed to a txt file
 * @param   head   the head node of the linked list 
 * @return  
 * 
******************************************************************************/
void writeTokenIntoFile(tNode *head)
{
    if (NULL == head)
    {
        printf("Empty linked list input %s: %d\n", __FILE__, __LINE__);
        exit(0);
    }
    FILE *fp = fopen("./tokenFile.txt", "w");
    if (NULL == fp)
    {
        printf("Open file error %s: %d\n", __FILE__, __LINE__);
        exit(0);
    }
    tNode *cur = head->pNext;
    while (cur != NULL)
    {
        fprintf(fp, "%s %d\n", cur->token, cur->num);
        cur = cur->pNext;
    }
    fclose(fp);
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
        while (*subLoop && *strLoop && *subLoop == *strLoop)
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

/******************************************************************************
 * @brief          Get field from a longer string
 * @param   str1   string to be searched in
 * @param   set    the collection of the specific field
 * @param   setLen the length of the collection
 * @return  num    the specific field found in the long string
 *          -1     Fail
******************************************************************************/
int findFieldInString(char *str, char **set, unsigned int setLen)
{
    if (NULL == str || NULL == set || NULL == *set || setLen <= 0)
        return -1;
    int num = -1;
    int i = 0;
    for (; i < setLen; i++)
    {
        num = findSubstring(str, *set);
        if (num >= 0)
            break;
        set++;
    }
    if (num >= 0)
        return i + 1;
    return -1;
    // printf("the method  is %s\n", *set);
}

/******************************************************************************
 * @brief          Create an empty list
 * @return  j      Return the head node of the empty tNode list
 *                 num of head represents the number of total nodes
******************************************************************************/
tNode *createList()
{
    tNode *p = NULL;
    p = (tNode *)malloc(sizeof(tNode));
    if (NULL == p)
    {
        puts("Malloc tNode error!\nExit from APP!");
        exit(0);
    }
    p->pNext = NULL;
    p->num = 0;
    return p;
}

/******************************************************************************
 * @brief          Add a new node to current list
 * @param   head   node of head
 * @param   token  new node's token
 * @param   data   new node's num
 * @return  head   Return the head of the list
******************************************************************************/
tNode *appendNode(tNode *head, char *token, unsigned char data)
{
    if (NULL == head)
    {
        puts("Node of head is null!\nCreate an empty list!");
        return createList();
    }
    tNode *p = NULL;
    tNode *pCur = head;

    p = (tNode *)malloc(sizeof(tNode));
    if (NULL == p)
    {
        puts("Malloc tNode error!\nExit from APP!");
        exit(0);
    }
    while (pCur->pNext != NULL)
    {
        pCur = pCur->pNext;
    }
    pCur->pNext = p;
    strncpy(p->token, token, 20);
    p->num = data;
    p->pNext = NULL;

    // free(p);
    // p = NULL;
    return head;
}

/******************************************************************************
 * @brief          Print each node of list
 * @param   head   node of head
 * @return  
******************************************************************************/
void displayList(tNode *head)
{
    if (NULL == head)
    {
        puts("Empty list!\nCreate a new list first!");
        return;
    }
    tNode *pCur = head->pNext;
    while (pCur != NULL)
    {
        printf("%-15s :    %d\n", pCur->token, pCur->num);
        pCur = pCur->pNext;
    }
}

/******************************************************************************
 * @brief          Free all nodes of list
 * @param   head   node of head
 * @return  
******************************************************************************/
void freeList(tNode *head)
{
    if (NULL == head)
    {
        puts("Empty list!\nNo need to free memory!");
        return;
    }
    tNode *pCur = head;
    tNode *pTmp = NULL;
    while (pCur != NULL)
    {
        pTmp = pCur;
        pCur = pCur->pNext;
        free(pTmp);
    }
    pTmp = NULL;
}

char isLetter(char character)
{
    if (character >= 'a' && character <= 'z')
        return 1;
    if (character >= 'A' && character <= 'Z')
        return 1;
    return 0;
}

char isFigure(char character)
{
    if (character >= '0' && character <= '9')
        return 1;
    return 0;
}