#include <iostream>
#include <string>

#include "Parser.h"
#include "Code.h"
#include "SymbolTable.h"

int main(int argc, char* argv[])
{
   std::string input_filename;
   std::fstream output_file;

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
      SymbolTable symbol_table;
      Parser parser(input_filename);

      if (parser.fileOpen())
      {
         // setup and open output file
         std::string output_filename;
         int split_pos = input_filename.find_first_of(".");
         output_filename = input_filename.substr(0, split_pos);
         output_filename += ".hack";
         std::cout << "Opening output file: "
                   << output_filename
                   << "...";
         output_file.open(output_filename.c_str(), std::fstream::out | std::fstream::trunc);

         if (output_file.is_open())
         {
            std::cout << "Success!" << std::endl;

            // populate symbol table
            int rom_addr = 0;
            std::cout << "Performing SymbolTable first pass..." << std::endl;
            while (parser.hasMoreCommands())
            {
               if (parser.advance())
               {
                  if (parser.commandType() == COMMAND_TYPE::C_COMMAND ||
                      parser.commandType() == COMMAND_TYPE::A_COMMAND)
                  {
                     rom_addr++;
                  }
                  else if (parser.commandType() == COMMAND_TYPE::L_COMMAND)
                  {
                     symbol_table.addEntry(parser.symbol(), rom_addr);
                  }
               }
            }
            symbol_table.printTable();

            parser.reset();

            int next_ram_addr = 0x10;
            while (parser.hasMoreCommands())
            {
               if (parser.advance())
               {
                  std::string next_word;
                  if (parser.commandType() == COMMAND_TYPE::A_COMMAND) // ||
                     // parser.commandType() == COMMAND_TYPE::L_COMMAND)
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
                        if (symbol_table.contains(symbol))
                        {
                           next_word = std::bitset<16>(symbol_table.getAddress(symbol)).to_string();
                        }
                        else
                        {
                           symbol_table.addEntry(symbol, next_ram_addr++);
                           next_word = std::bitset<16>(symbol_table.getAddress(symbol)).to_string();
                        }
                     }
                  }
                  else if (parser.commandType() == COMMAND_TYPE::C_COMMAND)
                  {
                     next_word += "111";
                     std::string comp_str = parser.comp();
                     std::string comp_bits = code.comp(comp_str);
                     next_word += comp_bits;

                     std::string dest_str = parser.dest();
                     std::string dest_bits = code.dest(dest_str);
                     next_word += dest_bits;

                     std::string jump_str = parser.jump();
                     std::string jump_bits = code.jump(jump_str);
                     next_word += jump_bits;
                  }
                  if (!next_word.empty())
                  {
                     std::cout << "output word: " << next_word << std::endl;
                     output_file << next_word << std::endl;
                  }
               }
            }
            output_file.close();
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

   return 0;
}
