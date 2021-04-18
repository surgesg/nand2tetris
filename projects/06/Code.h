#pragma once

#include <string>

class Code
{
  public:
   Code();
   std::string dest(std::string mnemonic);
   std::string comp(std::string mnemonic);
   std::string jump(std::string mnemonic);
};
