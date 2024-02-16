bison -d grammar.y
flex flex.l
gcc -w grammar.tab.c lex.yy.c
./a.out program.cpp 
./a.out program2.cpp