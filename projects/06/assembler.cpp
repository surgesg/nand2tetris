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
            parser.advance();
            if (parser.commandType() == COMMAND_TYPE::A_COMMAND ||
                parser.commandType() == COMMAND_TYPE::L_COMMAND)
            {
               parser.symbol();
            }
            else
            {
               std::string dest_str = parser.dest();
               code.dest(dest_str);
               std::string comp_str = parser.comp();
               code.comp(comp_str);
               parser.jump();
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
