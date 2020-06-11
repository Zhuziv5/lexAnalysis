#include <stdio.h>

//This is a comment
int main(void)
{
    puts("Hello World!");
    /*A great amout of comments! */
}
/*
 词法分析程序
首先定义种别码
 
第一类：标识符   (letter | '_')(letter | digit | '_')*  无穷集
                此处简化为 letter(letter | digit)* 无穷集
第二类：常数    (digit)+  无穷集 这里简化为都是整数
第三类：保留字(32)
 auto       break    case     char        const      continue
 default    do       double   else        enum       extern
 float      for      goto     if          int        long
 register   return   short    signed      sizeof     static
 struct     switch   typedef  union       unsigned   void
 volatile    while

第四类：界符  ‘/*’、‘//’、 () { } [ ] " "  '
第五类：运算符 <、<=、>、>=、=、+、-、*、/、^、

对所有可数符号进行编码：
<$,0>
<auto,1>
 ...
<while,32>
<+，33>
<-,34>
<*,35>
</,36>
<<,37>
<<=,38>
<>,39>
<>=,40>
<=,41>
<==,42>
<!=,43>
<;,44>
<(,45>
<),46>
<^,47>
<,,48>
<",49>
<',50>
<#,51>
<&,52>
<&&,53>
<|,54>
<||,55>
<%,56>
<~,57>
<<<,58>左移
<>>,59>右移
<[,60>
<],61>
<{,62>
<},63>
<\,64>
<.,65>
<?,66>
<:,67>
<!,68>
"[","]","{","}"
<常数99  ,数值>
<标识符100 ，标识符指针>
*/