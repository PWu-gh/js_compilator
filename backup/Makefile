###### Windows 
ifeq ($(OS),Windows_NT) 
RM = del /Q /F
###### Linux
else
RM = rm -rf
endif


prog :
	bison -d parseur.y
	flex lexeur.l
	gcc -Wall -o prog main.c parseur.tab.c lex.yy.c
	make clean
	./prog  test.txt

clean : 
	-$(RM) *.o  *.tab.c lex.yy.c

clear : 
	-$(RM) *.o *.tab.c lex.yy.c *.exe 

