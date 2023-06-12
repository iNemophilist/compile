# Compile
A compiler for LittleC, a simplified C-like language (implements lexical analysis, syntax analysis, outputs MIPS assembly code, creates symbol tables, does not implement type checking).
## The code is written in VS and uses GB2312 encoding. If unknown errors occur during program execution, please save the document again in GB2312 format.
## Files use document-based input and output. 
### test.txt stores the source code.
### result.txt stores the lexical analysis results.
### result_parser.txt stores the syntax analysis results (a serialized syntax tree).
### test_parser_result.txt stores the result of deserialization and re-serialization of the syntax analysis results, to verify the correctness of serialization and deserialization.
### final_result.txt stores the MIPS assembly code, the correctness of the assembly code was verified through the mars4_5 simulator.
## sourceProgram1-8 are eight test source codes of LittleC.
## The specific grammar definition is as follows:
Based on C syntax design, the source language LittleC.

### Structural and semantic description:
1. A program in this language consists only of a block structure, which contains two parts: optional declaration statements and mandatory execution statements. Declaration statements are used to declare variables, and execution statements are used to express the computing process, using these variables to store internal data and calculation results.
2. The language supports two data types: integer and boolean. Integer data takes up 4 bytes, boolean data takes up 1 byte. Integer data constants are integer constants, and boolean data constants are true and false.
3. Integer data supports +, -, *, / four arithmetic operations, the result is an integer value. Integer data can be combined with >, >=... and other six relational operators, the result is a boolean value.
4. Boolean data supports ||, &&, ! three logical operations, the result is a boolean constant.
5. Integer variables and constants can be combined with arithmetic operators to form arithmetic expressions, the value is an integer constant; Boolean variables and constants can be combined with logical operators to form boolean expressions, the value is a boolean constant; Arithmetic expressions can be added with relational operators to construct boolean expressions.
6. Integer constants and arithmetic expressions can be used for integer variable assignment, boolean constants and boolean expressions can be used for boolean variable assignment; the two are incompatible (different assignment operators are used in grammar to distinguish).
7. The precedence and combination rules of various operators refer to the syntax of the C language.
8. The control condition in the control flow statement is limited to 1 boolean variable, which should be defined before reference.
9. The language does not support complex data types such as arrays, structs, pointers, etc.
10. The language does not have a subroutine structure and does not support procedure calls.
11. The language has simple I/O functions: the read command can read 1 integer constant from the keyboard, and the write command can print 1 integer constant to the screen.

### Grammar definition:
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

### Lexical rules
1. Identifiers: Strings starting with a letter and followed by any combination of letters, digits; length does not exceed 8; case-insensitive; treat underscore as the 27th letter.
2. Integer constants: Strings entirely composed of numbers; positive numbers and 0 do not have a sign in front, negative numbers are formed by adding - in front of positive numbers; length does not exceed 8.
3. Boolean constants: true and false.
4. Keywords, operators, separators only include terminal symbols that have appeared in the grammar definition. Keywords are reserved.
5. The alphabet is defined as the set of characters that appear in the above rules; symbols not in this set are treated as illegal characters.
6. Single-line comments and multi-line comments can appear in the source program, the format refers to the design of the C language.
