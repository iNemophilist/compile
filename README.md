# compile
LitteleC这种类C简单语言的编译器（实现了词法分析、语法分析、输出mips汇编代码、创建符号表未实现类型检查）

## 具体文法定义如下：
基于C语法设计的源语言LittleC

### 结构和语义说明：
1. 该语言的一个程序由且仅由一个块结构组成，该块中包含两部分：可选的声明语句和必须的执行语句。声明语句用于声明变量，执行语句用于表达计算过程，过程中使用这些变量来存储内部数据和计算结果。
2. 该语言支持两种数据类型：整型和布尔型。整型数据占4个字节，布尔型占1个字节。整型数据的常量是整常数，布尔型数据的常量是 true 和 false 。
3. 整型数据支持 +、-、*、/ 四种算术运算，运算结果为整型值。整型数据可与>、>=...等六个关系运算符结合，运算结果为布尔型值。
4. 布尔型数据支持 || 、&& 、！三种逻辑运算，运算结果为布尔常量。
5. 整型的变量和常量可以用算术运算符组合成算术表达式，其值为整常数；布尔型的变量和常量可以用逻辑运算符组成成布尔表达式，其值为布尔常量；算术表达式可以加上关系运算符构造出布尔表达式。
6. 整常数和算术表达式可以用于整型变量赋值，布尔常量和布尔表达式可以用于布尔型变量赋值；两者不兼容（文法中使用不同的赋值运算符以示区别）。
7. 各种运算符的优先级和结合规则参照C语言语法理解。
8. 控制流语句中的控制条件限定为1个布尔型变量，该量应该在引用之前定值。
9. 该语言不支持数组、结构体、指针等复杂数据类型。
10. 该语言不含有子程序结构，也不支持过程调用。
11. 该语言有简单的I/O功能：使用read指令能够从键盘读入1个整常数，使用write指令能向屏幕打印输出1个整常数。

### 文法定义：
- PROG        →    {  DECLS  STMTS  }
- DECLS       →    DECLS  DECL    |   empty
- DECL         →    int  NAMES  ;  |  bool  NAMES  ; 
- NAMES     →    NAMES ,  NAME  |  NAME
- NAME       →    id
- STMTS    →    STMTS  STMT  |   STMT          
- STMT      →    id  =  EXPR ;    |   id := BOOL ;
- STMT      →    if  id   then  STMT
- STMT      →    if   id   then  STMT  else STMT
- STMT      →    while   id  do  STMT
- STMT      →    {  STMTS   STMT  }
- STMT      →    read  id  ;
- STMT      →    write  id  ;
- EXPR    →    EXPR  ADD  TERM  |  TERM
- ADD     →    + | -
- TERM    →    TERM  MUL NEGA  |  NEGA
- MUL     →    * | /
- NEGA   →    FACTOR  |  - FACTOR  
- FACTOR→    (  EXPR ) |  id  |  number 
- BOOL    →    BOOL  ||  JOIN    |    JOIN
- JOIN     →    JOIN   &&   NOT  |   NOT
- NOT      →    REL   |  ! REL
- REL       →    EXPR   ROP  EXPR 
- ROP      →     >  |  >=  |  <  |  <=  |  ==  |   !=

### 词法规则
1. 标识符：由字母打头后跟字母、数字任意组合的字符串；长度不超过8；不区分大小写；把下划线看作第27个字母；
2. 整常数：完全由数字组成的字符串；正数和0前面不加符号，负数在正数前面加-构成；长度不超过8；
3. 布尔常量：true 和 false 。
4. 关键字、运算符、分隔符仅包含在文法定义中出现过的终结符。关键字保留。
5. 字母表定义为上述规则中出现的字符的集合；不在该集合中的符号都以非法字符对待；
6. 源程序中可以出现单行注释和多行注释，其格式参考C语言设计。