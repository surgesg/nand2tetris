#include "Parser.h"
#include <string>
#include <fstream>

Parser::Parser(std::string filename)
{
   filename_ = filename;

   std::cout << "Opening " << filename_ << "... ";
   fs_.open(filename_.c_str(), std::fstream::in);

   if (fs_.is_open())
   {
      std::cout << "Success!" << std::endl;
      fileOpen_ = true;
   }
   else
   {
      std::cout << "Failed!" << std::endl;
      fileOpen_ = false;
   }
}

bool Parser::fileOpen()
{
   return fileOpen_;
}

bool Parser::hasMoreCommands()
{
   bool ret = true;
   if (fs_.eof())
   {
      ret = false;
   }
   return ret;
}

bool Parser::advance()
{
   bool line_valid = false;
   std::string cur_line;
   bool skip_line = true;
   while (skip_line)
   {
      if (hasMoreCommands())
      {
         std::getline(fs_, cur_line);

         // skip comments and empty lines
         if (cur_line.find("//") != std::string::npos)
         {
            skip_line = true;
         }
         else if (cur_line.empty())
         {
            skip_line = true;
         }
         else
         {
            skip_line = false;
            currentCommand_ = cur_line;
            std::cout << "read command: " << currentCommand_ << std::endl;
            line_valid = true;
         }
      }
      else
      {
         line_valid = false;
         currentCommand_ = "";
         std::cout << "reached end of file " << std::endl;
         break;
      }
   }
   return line_valid;
}

COMMAND_TYPE Parser::commandType()
{
   COMMAND_TYPE command_type = COMMAND_TYPE::C_COMMAND;
   // get position of first non-empty character
   int start_pos = currentCommand_.find_first_not_of(" ", 0);
   if (start_pos >= 0)
   {
      if (currentCommand_.compare(start_pos, 1, "@") == 0)
      {
         command_type = A_COMMAND;
      }
      else if (currentCommand_.compare(start_pos, 1, "\(") == 0)
      {
         command_type = L_COMMAND;
      }
   }
   return command_type;
}

std::string Parser::symbol()
{
   std::string ret;
   int start_pos;
   if (commandType() == COMMAND_TYPE::A_COMMAND)
   {
      start_pos = 1 + currentCommand_.find_first_of("@");
      ret = currentCommand_.substr(start_pos);
      // std::cout << "parsed symbol: " << ret << std::endl;
   }
   else if (commandType() == COMMAND_TYPE::L_COMMAND)
   {
      int end_pos = currentCommand_.find_first_of(")");
      start_pos = 1 + currentCommand_.find_first_of("(");
      ret = currentCommand_.substr(start_pos, end_pos - start_pos);
      // std::cout << "parsed symbol: " << ret << std::endl;
   }
   return ret;
}

std::string Parser::dest()
{
   std::string ret;
   int start_pos = currentCommand_.find_first_not_of(" ", 0);
   int end_pos = currentCommand_.find_first_of("=");
   if (end_pos >= 0)
   {
      ret = currentCommand_.substr(start_pos, end_pos - start_pos);
      // std::cout << "parsed dest: " << ret << std::endl;
   }
   return ret;
}

std::string Parser::comp()
{
   std::string ret;
   int start_pos = currentCommand_.find_first_of("=");
   int end_pos = currentCommand_.find_first_of (";");
   if (start_pos >= 0)
   {
      // probably don't need this clause
      if (end_pos >= 0)
      {
         ret = currentCommand_.substr(start_pos + 1, end_pos);
      }
      else
      {
         ret = currentCommand_.substr(start_pos + 1);
      }
   }
   else
   {
      int first_char = currentCommand_.find_first_not_of(" ", 0);
      if (first_char >= 0)
      {
         if (end_pos >= 0)
         {
            ret = currentCommand_.substr(first_char, end_pos - first_char);
         }
         else
         {
            ret = currentCommand_.substr(first_char);
         }
      }
   }
   // std::cout << "parsed comp: " << ret << std::endl;
   return ret;
}

std::string Parser::jump()
{
   std::string ret;
   int start_pos = currentCommand_.find_first_of(";");
   if (start_pos >= 0)
   {
      ret = currentCommand_.substr(start_pos + 1);
      // std::cout << "parsed jump: " << ret << std::endl;
   }
   return ret;
}
