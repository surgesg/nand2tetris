#include "Code.h"
#include <iostream>

Code::Code()
{
  
}

std::string Code::dest(std::string mnemonic)
{
   std::string ret;
   if (mnemonic.empty())
   {
      ret = "000";
   }
   else
   {
      if (mnemonic.compare("M") == 0)
      {
         ret = "001";
      }
      else if (mnemonic.compare("D") == 0)
      {
         ret = "010";
      }
      else if (mnemonic.compare("MD") == 0)
      {
         ret = "011";
      }
      else if (mnemonic.compare("A") == 0)
      {
         ret = "100";
      }
      else if (mnemonic.compare("AM") == 0)
      {
         ret = "101";
      }
      else if (mnemonic.compare("AD") == 0)
      {
         ret = "110";
      }
      else if (mnemonic.compare("AMD") == 0)
      {
         ret = "111";
      }
      else
      {
         ret = "000";
      }
   }
   // std::cout << "dest resulted in bin: " << ret << std::endl;
   return ret;
}

std::string Code::comp(std::string mnemonic)
{
   std::string ret;
   if (mnemonic.empty())
   {
      ret = "0000000";
   }
   else
   {
      if (mnemonic.compare("0") == 0)
      {
         ret = "0101010";
      }
      else if (mnemonic.compare("1") == 0)
      {
         ret = "0111111";
      }
      else if (mnemonic.compare("-1") == 0)
      {
         ret = "0111010";
      }
      else if (mnemonic.compare("D") == 0)
      {
         ret = "0001100";
      }
      else if (mnemonic.compare("A") == 0)
      {
         ret = "0110000";
      }
      else if (mnemonic.compare("!D") == 0)
      {
         ret = "0001101";
      }
      else if (mnemonic.compare("!A") == 0)
      {
         ret = "0110001";
      }
      else if (mnemonic.compare("-D") == 0)
      {
         ret = "0001111";
      }
      else if (mnemonic.compare("-A") == 0)
      {
         ret = "0110011";
      }
      else if (mnemonic.compare("D+1") == 0)
      {
         ret = "0011111";
      }
      else if (mnemonic.compare("A+1") == 0)
      {
         ret = "0110111";
      }
      else if (mnemonic.compare("D-1") == 0)
      {
         ret = "0001110";
      }
      else if (mnemonic.compare("A-1") == 0)
      {
         ret = "0110010";
      }
      else if (mnemonic.compare("D+A") == 0)
      {
         ret = "0000010";
      }
      else if (mnemonic.compare("D-A") == 0)
      {
         ret = "0010011";
      }
      else if (mnemonic.compare("A-D") == 0)
      {
         ret = "0000111";
      }
      else if (mnemonic.compare("D&A") == 0)
      {
         ret = "0000000";
      }
      else if (mnemonic.compare("D|A") == 0)
      {
         ret = "0010101";
      }
      else if (mnemonic.compare("M") == 0)
      {
         ret = "1110000";
      }
      else if (mnemonic.compare("!M") == 0)
      {
         ret = "1110001";
      }
      else if (mnemonic.compare("-M") == 0)
      {
         ret = "1110011";
      }
      else if (mnemonic.compare("M+1") == 0)
      {
         ret = "1110111";
      }
      else if (mnemonic.compare("M-1") == 0)
      {
         ret = "1110010";
      }
      else if (mnemonic.compare("D+M") == 0)
      {
         ret = "1000010";
      }
      else if (mnemonic.compare("D-M") == 0)
      {
         ret = "1010011";
      }
      else if (mnemonic.compare("M-D") == 0)
      {
         ret = "1000111";
      }
      else if (mnemonic.compare("D&M") == 0)
      {
         ret = "1000000";
      }
      else if (mnemonic.compare("D|M") == 0)
      {
         ret = "1010101";
      }
   }
   // std::cout << "comp resulted in bin: " << ret << std::endl;
   return ret;
}

std::string Code::jump(std::string mnemonic)
{
   std::string ret;
   if (mnemonic.empty())
   {
      ret = "000";
   }
   else
   {
      if (mnemonic.compare("JGT") == 0)
      {
         ret = "001";
      }
      else if (mnemonic.compare("JEQ") == 0)
      {
         ret = "010";
      }
      else if (mnemonic.compare("JGE") == 0)
      {
         ret = "011";
      }
      else if (mnemonic.compare("JLT") == 0)
      {
         ret = "100";
      }
      else if (mnemonic.compare("JNE") == 0)
      {
         ret = "101";
      }
      else if (mnemonic.compare("JLE") == 0)
      {
         ret = "110";
      }
      else if (mnemonic.compare("JMP") == 0)
      {
         ret = "111";
      }
      else
      {
         ret = "000";
      }
   }
   // std::cout << "jump resulted in bin: " << ret << std::endl;
   return ret;
}
