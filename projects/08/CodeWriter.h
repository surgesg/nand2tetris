#pragma once

#include <string>
#include <fstream>
#include "Parser.h"

class CodeWriter
{
  public:
   CodeWriter(std::string outputFilename);
   bool outputFileOpen();
   void setFilename(std::string inputFilename);
   void writeArithmetic(std::string command);
   void writePushPop(COMMAND_TYPE command, std::string segment, int index);
   void writeInit();
   void writeLabel(std::string label);
   void writeGoto(std::string label);
   void writeIf(std::string label);
   void writeCall(std::string functionName, int numArgs) {};
   void writeReturn() {};
   void writeFunction(std::string functionName, int numLocals) {};

  private:
   void decSP();
   void incSP();
   std::fstream outputFile_;
   std::string currentInputFilename_;
   int logicOpCounter_ = 0;
};
