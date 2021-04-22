#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

enum COMMAND_TYPE
{
  C_ARITHMETIC,
  C_PUSH,
  C_POP,
  C_LABEL,
  C_GOTO,
  C_IF,
  C_FUNCTION,
  C_RETURN,
  C_CALL
};

class Parser
{
  public:
   Parser(std::string filename);
   bool hasMoreCommands();
   bool fileOpen();
   bool advance();
   COMMAND_TYPE commandType();
   void reset();
   std::string arg1();
   int arg2();

  private:
   std::string filename_;
   std::vector<std::string> currentCommand_;

   std::fstream fs_;
   bool fileOpen_ = false;
};
