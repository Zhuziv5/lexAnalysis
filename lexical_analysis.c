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
}