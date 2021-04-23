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
         std::string input_filename_split = input_filename.substr(0, split_pos);
         output_filename = input_filename_split;
         output_filename += ".asm";

         CodeWriter writer(output_filename);
         // remove directory path
         split_pos = input_filename_split.find_last_of("/");
         input_filename_split = input_filename_split.substr(split_pos + 1);
         writer.setFilename(input_filename_split);

         if (writer.outputFileOpen())
         {
            while (parser.hasMoreCommands())
            {
               if (parser.advance())
               {
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
            std::cout << "Failed to open output file - Exiting" << std::endl;
         }
      }
      else
      {
         std::cout << "Failed to open input file - Exiting" << std::endl;
      }
   }
}
