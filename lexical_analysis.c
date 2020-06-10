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
    printf("%s\n", buf);
}