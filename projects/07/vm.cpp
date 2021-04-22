#include <iostream>
#include <string>

#include "Parser.h"
#include "CodeWriter.h"

int main(int argc, char* argv[])
{
   if (argc < 2 || argc > 2)
   {
      std::cout << "Invalid arguments supplied" << std::endl;
   }
   else
   {
      std::string input_filename;
      std::cout << "Initializing Parser module with .vm source file: "
                << argv[1]
                << "."
                << std::endl;
      input_filename = argv[1];

      Parser parser(input_filename);

      if (parser.fileOpen())
      {
         // setup and open output file
         std::string output_filename;
         int split_pos = input_filename.find_first_of(".");
         output_filename = input_filename.substr(0, split_pos);
         output_filename += ".asm";

         CodeWriter writer(output_filename);

         if (writer.outputFileOpen())
         {
            while (parser.hasMoreCommands())
            {
               if (parser.advance())
               {
                  std::cout << "command type: "
                            << parser.commandType()
                            << std::endl;
                  if (parser.commandType() == C_PUSH ||
                      parser.commandType() == C_POP)
                  {
                     writer.writePushPop(parser.commandType(),
                                         parser.arg1(),
                                         parser.arg2());
                  }
                  else if (parser.commandType() == C_ARITHMETIC)
                  {
                     writer.writeArithmetic(parser.arg1());
                  }
               }
            }
         }
         else
         {
            
         }





      }
      else
      {
         std::cout << "Failed to open input file - Exiting" << std::endl;
      }


   }
}
