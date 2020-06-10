/**
 * create a simple lexical analyser
 * 
*/
#include "tool.h"

int main(void)
{
    //读入某个源程序文件，并将所有源程序都写入到缓冲区buf中
    char buf[10000];
    readSourceCodeToBuf(buf, sizeof(buf), "./sourceCodeFile.c", "r");
    // printf("%s\n", buf);
    // printf("%lu\n", (long)sizeof(buf));
    // printf("%lu\n", (long)strlen(buf));
    //过滤源代码中无用的部分
    filterSourceCode(buf, strlen(buf) + 1);
}