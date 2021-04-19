all: assembler.o parser.o code.o symboltable.o
	g++ -o assembler assembler.o parser.o code.o symboltable.o

assembler.o: assembler.cpp Parser.h Code.h SymbolTable.h
	g++ -c assembler.cpp

parser.o: Parser.h Parser.cpp
	g++ -c Parser.cpp

code.o: Code.h Code.cpp
	g++ -c Code.cpp

symboltable.o: SymbolTable.h SymbolTable.cpp
	g++ -c SymbolTable.cpp

