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

  private:
   void decSP();
   void incSP();
   std::fstream outputFile_;
   std::string currentInputFilename_;
   int logicOpCounter_ = 0;
};
