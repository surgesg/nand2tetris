all: assembler.o parser.o
	g++ -o assembler assembler.o parser.o

assembler.o: assembler.cpp Parser.h
	g++ -c assembler.cpp

parser.o: Parser.h Parser.cpp
	g++ -c Parser.cpp

