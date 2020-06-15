/**
 * create a simple lexical analyser
 * 
*/
#include "tool.h"

int main(void)
{
    char buf[10000];
    //读入某个源程序文件，并将所有源程序都写入到缓冲区buf中
    readSourceCodeToBuf(buf, sizeof(buf), "./sourceCodeFile.c", "r");

    //过滤源代码中无用的部分
    filterSourceCode(buf, strlen(buf) + 1);
    // printf("%s\n", buf);
    char *tmp = buf;
    printf("buf is %s\n", buf);
    //size_t i = 0;
    char tokenTmp[20];
    int delta = 0;
    tNode *head = createList();
    //delta < 0表示找到了'\0'
    while (delta >= 0)
    {
        delta = tokenAnalyser(tmp, tokenTmp, head);
        tmp += delta;
    }
    displayList(head);
}