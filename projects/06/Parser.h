#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

enum COMMAND_TYPE
{
   A_COMMAND,
   C_COMMAND,
   L_COMMAND
};

class Parser
{
  public:
   Parser(std::string filename);
   bool hasMoreCommands();
   bool fileOpen();
   bool advance();
   COMMAND_TYPE commandType();
   std::string symbol();
   std::string dest();
   std::string comp();
   std::string jump();

  private:
   std::string filename_;
   std::string currentCommand_;

   std::fstream fs_;
   bool fileOpen_ = false;
};
