parser: syntax.o syntaxtree.o semantic.o SymbolTab.o IntermedCode.o objCode.o
	gcc syntax.o syntaxtree.o semantic.o SymbolTab.o IntermedCode.o  objCode.o -lfl -o parser -g

syntax.o: syntax.tab.c syntax.tab.h lex.yy.c
	gcc -c syntax.tab.c -o syntax.o -g

SymbolTab.o: SymbolTab.c SymbolTab.h
	gcc -c SymbolTab.c -o SymbolTab.o -g


semantic.o: semantic.c semantic.h
	gcc -c semantic.c -o semantic.o -g

syntaxtree.o: syntaxtree.c syntaxtree.h
	gcc -c syntaxtree.c -o syntaxtree.o -g

IntermedCode.o: intermedCode.h intermedCode.c
	gcc -c intermedCode.c -o IntermedCode.o -g

objCode: objCode.h objCode.c
	gcc -c objCode.c -o objCode.o -g

syntax.tab.c: syntax.y
	bison -d syntax.y

lex.yy.c: lexical.l
	flex lexical.l

clean:
	rm -f syntax.o syntaxtree.o parser syntax.tab.c syntax.tab.h lex.yy.c semantic.o SymbolTab.o IntermedCode.o objCode.o

test:
	./parser ./sample.d/1.c out1.s
	./parser ./sample.d/2.c out2.s
