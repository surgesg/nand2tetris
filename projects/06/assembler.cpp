#include <iostream>
#include <string>

#include "Parser.h"
#include "Code.h"

int main(int argc, char* argv[])
{
   std::string input_filename;
   std::fstream file;

   if (argc < 2 || argc > 2)
   {
      std::cout << "Invalid arguments supplied" << std::endl;
   }
   else
   {
      std::cout << "Initializing Parser module with .asm source file: "
                << argv[1]
                << "."
                << std::endl;
      input_filename = argv[1];

      Code code;
      Parser parser(input_filename);
      if (parser.fileOpen())
      {
         while (parser.hasMoreCommands())
         {
            if (parser.advance())
            {
               std::string next_word;
               if (parser.commandType() == COMMAND_TYPE::A_COMMAND ||
                   parser.commandType() == COMMAND_TYPE::L_COMMAND)
               {
                  std::string symbol = parser.symbol();
                  // check if number
                  if (symbol.find_first_not_of("0123456789") == std::string::npos)
                  {
                     int num = std::stoi(symbol);
                     next_word = std::bitset<16>(num).to_string();
                  }
                  else
                  {
                     std::cout << "symbol is name" << std::endl;
                  }
               }
               else
               {
                  next_word += "111";
                  std::string dest_str = parser.dest();
                  std::string dest_bits = code.dest(dest_str);
                  next_word += dest_bits;

                  std::string comp_str = parser.comp();
                  std::string comp_bits = code.comp(comp_str);
                  next_word += comp_bits;

                  std::string jump_str = parser.jump();
                  std::string jump_bits = code.jump(jump_str);
                  next_word += jump_bits;
               }
               std::cout << "output word: " << next_word << std::endl;
            }
         }
      }
      else
      {
         std::cout << "Failed - Exiting" << std::endl;
      }

   }

   return 0;
}
