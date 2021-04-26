all: vm.o parser.o codewriter.o
	g++ -o vm vm.o parser.o codewriter.o

vm.o: vm.cpp Parser.h CodeWriter.h
	g++ -c vm.cpp

parser.o: Parser.h Parser.cpp
	g++ -c Parser.cpp

codewriter.o: CodeWriter.h CodeWriter.cpp
	g++ -c CodeWriter.cpp





