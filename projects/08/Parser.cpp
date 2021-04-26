#include "Parser.h"
#include <string>
#include <fstream>
#include <sstream>

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
         currentCommand_.clear();
         std::getline(fs_, cur_line);

         // skip comments and empty lines
         // remove comments

         std::stringstream string_to_split(cur_line);
         std::string token;
         while (std::getline(string_to_split, token, ' '))
         {
            // check for comment, break if one found
            if (token.find("//") == std::string::npos)
            {
               currentCommand_.push_back(token);
            }
            else
            {
               break;
            }
         }

         if (currentCommand_.size() > 0)
         {
            std::cout << "parsed command: [";
            for (int i = 0; i < currentCommand_.size(); ++i)
            {
               std::cout << currentCommand_[i] << ", ";
            }
            std::cout << "]" << std::endl;
            line_valid = true;
            break;
         }
      }
      else
      {
         line_valid = false;
         currentCommand_.clear();
         std::cout << "reached end of file " << std::endl;
         break;
      }
   }
   return line_valid;
}

std::string Parser::arg1()
{
   std::string ret;
   if (commandType() == C_ARITHMETIC)
   {
      ret = currentCommand_[0];
   }
   else
   {
      ret = currentCommand_[1];
   }
   return ret;
}

int Parser::arg2()
{
   int ret;
   if (currentCommand_.size() >= 2)
   {
      ret = std::stoi(currentCommand_[2]);
   }
   return ret;
}

void Parser::reset()
{
   fs_.clear();
   fs_.seekp(0);
}

COMMAND_TYPE Parser::commandType()
{
   COMMAND_TYPE command_type;
   if (currentCommand_[0].compare("push") == 0)
   {
      command_type = C_PUSH;
   }
   else if (currentCommand_[0].compare("pop") == 0)
   {
      command_type = C_POP;
   }
   else if (currentCommand_[0].compare("add") == 0)
   {
      command_type = C_ARITHMETIC;
   }
   else if (currentCommand_[0].compare("sub") == 0)
   {
      command_type = C_ARITHMETIC;
   }
   else if (currentCommand_[0].compare("neg") == 0)
   {
      command_type = C_ARITHMETIC;
   }
   else if (currentCommand_[0].compare("eq") == 0)
   {
      command_type = C_ARITHMETIC;
   }
   else if (currentCommand_[0].compare("gt") == 0)
   {
      command_type = C_ARITHMETIC;
   }
   else if (currentCommand_[0].compare("lt") == 0)
   {
      command_type = C_ARITHMETIC;
   }
   else if (currentCommand_[0].compare("and") == 0)
   {
      command_type = C_ARITHMETIC;
   }
   else if (currentCommand_[0].compare("or") == 0)
   {
      command_type = C_ARITHMETIC;
   }
   else if (currentCommand_[0].compare("not") == 0)
   {
      command_type = C_ARITHMETIC;
   }
   else if (currentCommand_[0].compare("label") == 0)
   {
      command_type = C_LABEL;
   }
   else if (currentCommand_[0].compare("goto") == 0)
   {
      command_type = C_GOTO;
   }
   else if (currentCommand_[0].compare("if-goto") == 0)
   {
      command_type = C_IF;
   }
   else if (currentCommand_[0].compare("function") == 0)
   {
      command_type = C_FUNCTION;
   }
   else if (currentCommand_[0].compare("return") == 0)
   {
      command_type = C_RETURN;
   }
   else if (currentCommand_[0].compare("call") == 0)
   {
      command_type = C_CALL;
   }

   return command_type;
}
