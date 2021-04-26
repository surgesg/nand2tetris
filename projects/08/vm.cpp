#include <iostream>
#include <string>
#include <vector>

#include <sys/stat.h>
#include <dirent.h>

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
      bool path_err = false;
      std::string input_path;
      std::cout << "Initializing Parser module with .vm source file: "
                << argv[1]
                << "."
                << std::endl;
      input_path = argv[1];

      // get list of files
      std::vector<std::string> src_files;
      struct stat stat_buf;
      if (stat(input_path.c_str(), &stat_buf) != 0)
      {
         std::cout << "ERROR" << std::endl;
         path_err = true;
      }
      int dir_res = S_ISDIR(stat_buf.st_mode);
      // check if directory
      if (dir_res > 0)
      {
         std::cout << "Path is a directory" << std::endl;
         struct dirent* entry;
         DIR* dir = opendir(input_path.c_str());
         if (dir == NULL)
         {
            path_err = true;
         }

         while ((entry = readdir(dir)) != NULL)
         {
            std::string new_fname = entry->d_name;
            if (new_fname.find(".vm") != std::string::npos)
            {
               src_files.push_back(new_fname);
            }
         }
      }
      else
      {
         std::cout << "Path is a single file" << std::endl;
         src_files.push_back(input_path);
      }

      std::cout << "Files to process:" << std::endl;
      for (int f = 0; f < src_files.size(); ++f)
      {
         std::cout << "\t" << src_files[f] << std::endl;
      }

      if (!path_err)
      {
         // setup and open output file
         std::string output_filename;
         int split_pos = input_path.find_first_of(".");
         std::string input_filename_split = input_path.substr(0, split_pos);
         output_filename = input_filename_split;
         output_filename += ".asm";

         CodeWriter writer(output_filename);

         if (writer.outputFileOpen())
         {
            for (auto file_path : src_files)
            {
               Parser parser(file_path);

               if (parser.fileOpen())
               {
                  // remove directory path
                  split_pos = input_filename_split.find_last_of("/");
                  input_filename_split = input_filename_split.substr(split_pos + 1);
                  writer.setFilename(input_filename_split);

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
                  std::cout << "Failed to open input file - Exiting" << std::endl;
               }
            }
         }
         else
         {
            std::cout << "Failed to open output file - Exiting" << std::endl;
         }
      }
   }
}
