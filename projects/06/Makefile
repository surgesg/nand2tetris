all: assembler.o parser.o code.o
	g++ -o assembler assembler.o parser.o code.o

assembler.o: assembler.cpp Parser.h Code.h
	g++ -c assembler.cpp

parser.o: Parser.h Parser.cpp
	g++ -c Parser.cpp

code.o: Code.h Code.cpp
	g++ -c Code.cpp

