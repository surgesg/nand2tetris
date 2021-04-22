#include "CodeWriter.h"
#include <string>

CodeWriter::CodeWriter(std::string outputFilename)
{
   std::cout << "Opening output file: "
             << outputFilename
             << "...";

   outputFile_.open(outputFilename.c_str(),
                    std::fstream::out | std::fstream::trunc);

   if (outputFile_.is_open())
   {
      std::cout << "Success!" << std::endl;
   }
}

bool CodeWriter::outputFileOpen()
{
   return outputFile_.is_open();
}

void CodeWriter::setFilename(std::string inputFilename)
{
   currentInputFilename_ = inputFilename;
}

void CodeWriter::writePushPop(COMMAND_TYPE command, std::string segment, int index)
{
   if (command == C_PUSH)
   {
      if (segment.compare("constant") == 0)
      {
         outputFile_ << "@" << index << std::endl; // load constant into A
         outputFile_ << "D=A" << std::endl; // store in D
         outputFile_ << "@SP" << std::endl; // load stack ptr addr into A
         outputFile_ << "A=M" << std::endl; // deref ptr into A
         outputFile_ << "M=D" << std::endl; // store constant from D into memory pointer to by stack ptr
         outputFile_ << "@SP" << std::endl;
         outputFile_ << "M=M+1" << std::endl;
      }
   }
   else if (command == C_POP)
   {

   }
}

void CodeWriter::writeArithmetic(std::string command)
{
   if (command.compare("add") == 0)
   {
      // decrement sp
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "M=M-1" << std::endl;

      // load first arg from top of stack into d
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "A=M" << std::endl;
      outputFile_ << "D=M" << std::endl;

      // decrement sp
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "M=M-1" << std::endl;

      // add D and data pointed to by A
      outputFile_ << "@SP"   << std::endl;
      outputFile_ << "A=M"   << std::endl;
      outputFile_ << "M=D+M" << std::endl;

      // increment sp
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "M=M+1" << std::endl;

   }
   else if (command.compare("sub") == 0)
   {
      // decrement sp
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "M=M-1" << std::endl;

      // load first arg from top of stack into d
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "A=M" << std::endl;
      outputFile_ << "D=M" << std::endl;

      // decrement sp
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "M=M-1" << std::endl;

      // add D and data pointed to by A
      outputFile_ << "@SP"   << std::endl;
      outputFile_ << "A=M"   << std::endl;
      outputFile_ << "M=M-D" << std::endl;

      // increment sp
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "M=M+1" << std::endl;
   }
   else if (command.compare("and") == 0)
   {
      // decrement sp
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "M=M-1" << std::endl;

      // load first arg from top of stack into d
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "A=M" << std::endl;
      outputFile_ << "D=M" << std::endl;

      // decrement sp
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "M=M-1" << std::endl;

      // and D and data pointed to by A
      outputFile_ << "@SP"   << std::endl;
      outputFile_ << "A=M"   << std::endl;
      outputFile_ << "M=D&M" << std::endl;

      // increment sp
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "M=M+1" << std::endl;
   }
   else if (command.compare("or") == 0)
   {
      // decrement sp
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "M=M-1" << std::endl;

      // load first arg from top of stack into d
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "A=M" << std::endl;
      outputFile_ << "D=M" << std::endl;

      // decrement sp
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "M=M-1" << std::endl;

      // and D and data pointed to by A
      outputFile_ << "@SP"   << std::endl;
      outputFile_ << "A=M"   << std::endl;
      outputFile_ << "M=D|M" << std::endl;

      // increment sp
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "M=M+1" << std::endl;
   }
   else if (command.compare("neg") == 0)
   {
      // decrement sp
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "M=M-1" << std::endl;

      // load first arg from top of stack into d
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "A=M" << std::endl;

      // 2s complement negation
      outputFile_ << "M=!M" << std::endl;
      outputFile_ << "M=M+1" << std::endl;

      // increment sp
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "M=M+1" << std::endl;
   }
   else if (command.compare("not") == 0)
   {
      // decrement sp
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "M=M-1" << std::endl;

      // load first arg from top of stack 
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "A=M" << std::endl;

      // not
      outputFile_ << "M=!M" << std::endl;

      // increment sp
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "M=M+1" << std::endl;
   }
   else if (command.compare("eq") == 0)
   {
       // decrement sp
       outputFile_ << "@SP" << std::endl;
       outputFile_ << "M=M-1" << std::endl;

       // load first arg from top of stack into d
       outputFile_ << "@SP" << std::endl;
       outputFile_ << "A=M" << std::endl;
       outputFile_ << "D=M" << std::endl;

       // decrement sp
       outputFile_ << "@SP" << std::endl;
       outputFile_ << "M=M-1" << std::endl;

       // compare D and data pointed to by A
       outputFile_ << "@SP"   << std::endl;
       outputFile_ << "A=M"   << std::endl;
       outputFile_ << "D=D-M" << std::endl;

       // jump if sub result == 0
       outputFile_ << "@TRUE." << logicOpCounter_ << std::endl;
       outputFile_ << "D;JEQ" << std::endl;

       // write false result
       outputFile_ << "@SP" << std::endl;
       outputFile_ << "A=M"   << std::endl;
       outputFile_ << "M=0" << std::endl;
       outputFile_ << "@END." << logicOpCounter_ << std::endl;
       outputFile_ << "0;JMP" << std::endl;

       // write true result
       outputFile_ << "(TRUE." << logicOpCounter_ << ")" << std::endl;
       outputFile_ << "@SP" << std::endl;
       outputFile_ << "A=M"   << std::endl;
       outputFile_ << "M=-1" << std::endl;

       outputFile_ << "(END." << logicOpCounter_ << ")" << std::endl;

       // increment sp
       outputFile_ << "@SP" << std::endl;
       outputFile_ << "M=M+1" << std::endl;

       ++logicOpCounter_;
   }
   else if (command.compare("lt") == 0)
   {
      // decrement sp
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "M=M-1" << std::endl;

      // load first arg from top of stack into d
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "A=M" << std::endl;
      outputFile_ << "D=M" << std::endl;

      // decrement sp
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "M=M-1" << std::endl;

      // compare D and data pointed to by A
      outputFile_ << "@SP"   << std::endl;
      outputFile_ << "A=M"   << std::endl;
      outputFile_ << "D=D-M" << std::endl;

      // jump if sub result (x-y) < 0
      outputFile_ << "@TRUE." << logicOpCounter_ << std::endl;
      outputFile_ << "D;JGT" << std::endl;

      // write false result
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "A=M"   << std::endl;
      outputFile_ << "M=0" << std::endl;
      outputFile_ << "@END." << logicOpCounter_ << std::endl;
      outputFile_ << "0;JMP" << std::endl;

      // write true result
      outputFile_ << "(TRUE." << logicOpCounter_ << ")" << std::endl;
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "A=M"   << std::endl;
      outputFile_ << "M=-1" << std::endl;

      outputFile_ << "(END." << logicOpCounter_ << ")" << std::endl;

      // increment sp
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "M=M+1" << std::endl;

      ++logicOpCounter_;
   }
   else if (command.compare("gt") == 0)
   {
      // decrement sp
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "M=M-1" << std::endl;

      // load first arg from top of stack into d
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "A=M" << std::endl;
      outputFile_ << "D=M" << std::endl;

      // decrement sp
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "M=M-1" << std::endl;

      // compare D and data pointed to by A
      outputFile_ << "@SP"   << std::endl;
      outputFile_ << "A=M"   << std::endl;
      outputFile_ << "D=D-M" << std::endl;

      // jump if sub result (x-y) > 0
      outputFile_ << "@TRUE." << logicOpCounter_ << std::endl;
      outputFile_ << "D;JLT" << std::endl;

      // write false result
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "A=M"   << std::endl;
      outputFile_ << "M=0" << std::endl;
      outputFile_ << "@END." << logicOpCounter_ << std::endl;
      outputFile_ << "0;JMP" << std::endl;

      // write true result
      outputFile_ << "(TRUE." << logicOpCounter_ << ")" << std::endl;
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "A=M"   << std::endl;
      outputFile_ << "M=-1" << std::endl;

      outputFile_ << "(END." << logicOpCounter_ << ")" << std::endl;

      // increment sp
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "M=M+1" << std::endl;

      ++logicOpCounter_;
   }
















}
