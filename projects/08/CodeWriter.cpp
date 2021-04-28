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
      else
      {
         if (segment.compare("argument") == 0)
         {
            // store value in D
            outputFile_ << "@ARG"  << std::endl;
            outputFile_ << "D=M"   << std::endl;
            outputFile_ << "@"     << index << std::endl;
            outputFile_ << "A=D+A" << std::endl;
            outputFile_ << "D=M"   << std::endl;

            // push onto stack
            outputFile_ << "@SP" << std::endl;
            outputFile_ << "A=M" << std::endl;
            outputFile_ << "M=D" << std::endl;

            incSP();
         }
         else if (segment.compare("local") == 0)
         {
            // store value in D
            outputFile_ << "@LCL"  << std::endl;
            outputFile_ << "D=M"   << std::endl;
            outputFile_ << "@"     << index << std::endl;
            outputFile_ << "A=D+A" << std::endl;
            outputFile_ << "D=M"   << std::endl; 

            // push onto stack
            outputFile_ << "@SP" << std::endl;
            outputFile_ << "A=M" << std::endl;
            outputFile_ << "M=D" << std::endl;

            incSP();
         }
         else if (segment.compare("static") == 0)
         {
            // store value in D
            outputFile_ << "@" << currentInputFilename_ << "." << index << std::endl;
            outputFile_ << "D=M"   << std::endl;

            // push onto stack
            outputFile_ << "@SP" << std::endl;
            outputFile_ << "A=M" << std::endl;
            outputFile_ << "M=D" << std::endl;

            incSP();
         }
         else if (segment.compare("this") == 0)
         {
            // store value in D
            outputFile_ << "@THIS"  << std::endl;
            outputFile_ << "D=M"   << std::endl;
            outputFile_ << "@"     << index << std::endl;
            outputFile_ << "A=D+A" << std::endl;
            outputFile_ << "D=M"   << std::endl;

            // push onto stack
            outputFile_ << "@SP" << std::endl;
            outputFile_ << "A=M" << std::endl;
            outputFile_ << "M=D" << std::endl;

            incSP();
         }
         else if (segment.compare("that") == 0)
         {
            // store value in D
            outputFile_ << "@THAT"  << std::endl;
            outputFile_ << "D=M"   << std::endl;
            outputFile_ << "@"     << index << std::endl;
            outputFile_ << "A=D+A" << std::endl;
            outputFile_ << "D=M"   << std::endl;

            // push onto stack
            outputFile_ << "@SP" << std::endl;
            outputFile_ << "A=M" << std::endl;
            outputFile_ << "M=D" << std::endl;

            incSP();




         }
         else if (segment.compare("pointer") == 0)
         {
            // store value in D                                     
            outputFile_ << "@R3"  << std::endl;
            outputFile_ << "D=A"   << std::endl;
            outputFile_ << "@"     << index << std::endl;
            outputFile_ << "A=D+A" << std::endl;
            outputFile_ << "D=M"   << std::endl;

            // push onto stack
            outputFile_ << "@SP" << std::endl;
            outputFile_ << "A=M" << std::endl;
            outputFile_ << "M=D" << std::endl;

            incSP();







         }
         else if (segment.compare("temp") == 0)
         {
            // store value in D
            outputFile_ << "@R5"   << std::endl;
            outputFile_ << "D=A"   << std::endl;
            outputFile_ << "@"     << index << std::endl;
            outputFile_ << "A=D+A" << std::endl;
            outputFile_ << "D=M"   << std::endl;

            // push onto stack
            outputFile_ << "@SP" << std::endl;
            outputFile_ << "A=M" << std::endl;
            outputFile_ << "M=D" << std::endl;

            incSP();
         }
      }
   }
   else if (command == C_POP)
   {
      if (segment.compare("local") == 0)
      {
         // store addr in R13
         outputFile_ << "@LCL" << std::endl;
         outputFile_ << "D=M" << std::endl;
         outputFile_ << "@" << index << std::endl;
         outputFile_ << "D=D+A" << std::endl;
         outputFile_ << "@R13"  << std::endl;
         outputFile_ << "M=D"  << std::endl;

         decSP();

         // load value from stack into D
         outputFile_ << "@SP" << std::endl;
         outputFile_ << "A=M" << std::endl;
         outputFile_ << "D=M" << std::endl;

         // load value from D into addr at R13
         outputFile_ << "@R13"  << std::endl;
         outputFile_ << "A=M" << std::endl;
         outputFile_ << "M=D"  << std::endl;
      }
      else if (segment.compare("argument") == 0)
      {
         // store addr in R13
         outputFile_ << "@ARG" << std::endl;
         outputFile_ << "D=M" << std::endl;
         outputFile_ << "@" << index << std::endl;
         outputFile_ << "D=D+A" << std::endl;
         outputFile_ << "@R13"  << std::endl;
         outputFile_ << "M=D"  << std::endl;

         decSP();

         // load value from stack into D
         outputFile_ << "@SP" << std::endl;
         outputFile_ << "A=M" << std::endl;
         outputFile_ << "D=M" << std::endl;

         // load value from D into addr at R13
         outputFile_ << "@R13"  << std::endl;
         outputFile_ << "A=M" << std::endl;
         outputFile_ << "M=D"  << std::endl;
      }
      else if (segment.compare("static") == 0)
      {
         decSP();

         // load value from stack into D
         outputFile_ << "@SP" << std::endl;
         outputFile_ << "A=M" << std::endl;
         outputFile_ << "D=M" << std::endl;

         // load value from D into static var
         outputFile_ << "@" << currentInputFilename_ << "." << index << std::endl;
         outputFile_ << "M=D"  << std::endl;
      }
      else if (segment.compare("this") == 0)
      {
         // store addr in R13
         outputFile_ << "@THIS" << std::endl;
         outputFile_ << "D=M" << std::endl;
         outputFile_ << "@" << index << std::endl;
         outputFile_ << "D=D+A" << std::endl;
         outputFile_ << "@R13"  << std::endl;
         outputFile_ << "M=D"  << std::endl;

         decSP();

         // load value from stack into D
         outputFile_ << "@SP" << std::endl;
         outputFile_ << "A=M" << std::endl;
         outputFile_ << "D=M" << std::endl;

         // load value from D into addr at R13
         outputFile_ << "@R13"  << std::endl;
         outputFile_ << "A=M" << std::endl;
         outputFile_ << "M=D"  << std::endl;
      }
      else if (segment.compare("that") == 0)
      {
         // store addr in R13
         outputFile_ << "@THAT" << std::endl;
         outputFile_ << "D=M" << std::endl;
         outputFile_ << "@" << index << std::endl;
         outputFile_ << "D=D+A" << std::endl;
         outputFile_ << "@R13"  << std::endl;
         outputFile_ << "M=D"  << std::endl;

         decSP();

         // load value from stack into D
         outputFile_ << "@SP" << std::endl;
         outputFile_ << "A=M" << std::endl;
         outputFile_ << "D=M" << std::endl;

         // load value from D into addr at R13
         outputFile_ << "@R13"  << std::endl;
         outputFile_ << "A=M" << std::endl;
         outputFile_ << "M=D"  << std::endl;
      }
      else if (segment.compare("pointer") == 0)
      {
         // store addr in R13
         outputFile_ << "@R3" << std::endl;
         outputFile_ << "D=A" << std::endl;
         outputFile_ << "@" << index << std::endl;
         outputFile_ << "D=D+A" << std::endl;
         outputFile_ << "@R13"  << std::endl;
         outputFile_ << "M=D"  << std::endl;

         decSP();

         // load value from stack into D
         outputFile_ << "@SP" << std::endl;
         outputFile_ << "A=M" << std::endl;
         outputFile_ << "D=M" << std::endl;

         // load value from D into addr at R13
         outputFile_ << "@R13"  << std::endl;
         outputFile_ << "A=M" << std::endl;
         outputFile_ << "M=D"  << std::endl;
      }
      else if (segment.compare("temp") == 0)
      {
         // store addr in R13
         outputFile_ << "@R5" << std::endl;
         outputFile_ << "D=A" << std::endl;
         outputFile_ << "@" << index << std::endl;
         outputFile_ << "D=D+A" << std::endl;
         outputFile_ << "@R13"  << std::endl;
         outputFile_ << "M=D"  << std::endl;

         decSP();

         // load value from stack into D
         outputFile_ << "@SP" << std::endl;
         outputFile_ << "A=M" << std::endl;
         outputFile_ << "D=M" << std::endl;

         // load value from D into addr at R13
         outputFile_ << "@R13"  << std::endl;
         outputFile_ << "A=M" << std::endl;
         outputFile_ << "M=D"  << std::endl;
      }
   }
}

void CodeWriter::decSP()
{
   outputFile_ << "@SP" << std::endl;
   outputFile_ << "M=M-1" << std::endl;
}

void CodeWriter::incSP()
{
   outputFile_ << "@SP" << std::endl;
   outputFile_ << "M=M+1" << std::endl;
}

void CodeWriter::writeArithmetic(std::string command)
{
   decSP();

   if (command.compare("add") == 0)
   {
      // load first arg from top of stack into d
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "A=M" << std::endl;
      outputFile_ << "D=M" << std::endl;

      decSP();

      // add D and data pointed to by A
      outputFile_ << "@SP"   << std::endl;
      outputFile_ << "A=M"   << std::endl;
      outputFile_ << "M=D+M" << std::endl;
   }
   else if (command.compare("sub") == 0)
   {
      // load first arg from top of stack into d
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "A=M" << std::endl;
      outputFile_ << "D=M" << std::endl;

      decSP();

      // add D and data pointed to by A
      outputFile_ << "@SP"   << std::endl;
      outputFile_ << "A=M"   << std::endl;
      outputFile_ << "M=M-D" << std::endl;
   }
   else if (command.compare("and") == 0)
   {
      // load first arg from top of stack into d
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "A=M" << std::endl;
      outputFile_ << "D=M" << std::endl;

      decSP();

      // and D and data pointed to by A
      outputFile_ << "@SP"   << std::endl;
      outputFile_ << "A=M"   << std::endl;
      outputFile_ << "M=D&M" << std::endl;
   }
   else if (command.compare("or") == 0)
   {
      // load first arg from top of stack into d
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "A=M" << std::endl;
      outputFile_ << "D=M" << std::endl;

      decSP();

      // and D and data pointed to by A
      outputFile_ << "@SP"   << std::endl;
      outputFile_ << "A=M"   << std::endl;
      outputFile_ << "M=D|M" << std::endl;
   }
   else if (command.compare("neg") == 0)
   {
      // load first arg from top of stack into d
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "A=M" << std::endl;

      // 2s complement negation
      outputFile_ << "M=!M" << std::endl;
      outputFile_ << "M=M+1" << std::endl;
   }
   else if (command.compare("not") == 0)
   {
      // load first arg from top of stack 
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "A=M" << std::endl;

      // not
      outputFile_ << "M=!M" << std::endl;
   }
   else if (command.compare("eq") == 0)
   {
      // load first arg from top of stack into d
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "A=M" << std::endl;
      outputFile_ << "D=M" << std::endl;

      decSP();

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

      ++logicOpCounter_;
   }
   else if (command.compare("lt") == 0)
   {
      // load first arg from top of stack into d
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "A=M" << std::endl;
      outputFile_ << "D=M" << std::endl;

      decSP();

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

      ++logicOpCounter_;
   }
   else if (command.compare("gt") == 0)
   {
      // load first arg from top of stack into d
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "A=M" << std::endl;
      outputFile_ << "D=M" << std::endl;

      decSP();

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

      ++logicOpCounter_;
   }

   incSP();
}

void CodeWriter::writeLabel(std::string label)
{
   outputFile_ << "("
               << currentInputFilename_
               << "."
               << label
               << ")"
               << std::endl;
}

void CodeWriter::writeGoto(std::string label)
{
   outputFile_ << "@"
               << currentInputFilename_
               << "."
               << label
               << std::endl;
   outputFile_ << "0;JMP" << std::endl;
}

void CodeWriter::writeIf(std::string label)
{
   decSP();
   outputFile_ << "@SP" << std::endl;
   outputFile_ << "A=M" << std::endl;
   outputFile_ << "D=M" << std::endl;
   outputFile_ << "@"
               << currentInputFilename_
               << "."
               << label
               << std::endl;
   outputFile_ << "D;JGT" << std::endl;
}

void CodeWriter::writeFunction(std::string functionName, int numLocals)
{
   outputFile_ << "("
               << currentInputFilename_
               << "."
               << functionName
               << ")"
               << std::endl;

   // push local variables onto stack
   for (int i = 0; i < numLocals; ++i)
   {
      outputFile_ << "@SP" << std::endl;
      outputFile_ << "A=M" << std::endl;
      outputFile_ << "M=0" << std::endl;

      incSP();
   }
}

void CodeWriter::writeCall(std::string functionName, int numArgs)
{
   std::string return_addr = currentInputFilename_
      + "-return-address-"
      + std::to_string(returnAddrCounter_++);

   // push return addr
   outputFile_ << "@" << return_addr << std::endl;
   outputFile_ << "D=A" << std::endl;

   outputFile_ << "@SP" << std::endl;
   outputFile_ << "A=M" << std::endl;
   outputFile_ << "M=D" << std::endl;

   incSP();

   // push LCL
   outputFile_ << "@LCL" << std::endl;
   outputFile_ << "D=M" << std::endl;

   outputFile_ << "@SP" << std::endl;
   outputFile_ << "A=M" << std::endl;
   outputFile_ << "M=D" << std::endl;

   incSP();

   // push ARG
   outputFile_ << "@ARG" << std::endl;
   outputFile_ << "D=M" << std::endl;

   outputFile_ << "@SP" << std::endl;
   outputFile_ << "A=M" << std::endl;
   outputFile_ << "M=D" << std::endl;

   incSP();

   // push THIS
   outputFile_ << "@THIS" << std::endl;
   outputFile_ << "D=M" << std::endl;

   outputFile_ << "@SP" << std::endl;
   outputFile_ << "A=M" << std::endl;
   outputFile_ << "M=D" << std::endl;

   incSP();

   // push THAT
   outputFile_ << "@THAT" << std::endl;
   outputFile_ << "D=M" << std::endl;

   outputFile_ << "@SP" << std::endl;
   outputFile_ << "A=M" << std::endl;
   outputFile_ << "M=D" << std::endl;

   incSP();

   // reposition ARG
   outputFile_ << "@SP" << std::endl;
   outputFile_ << "D=M" << std::endl;

   outputFile_ << "@" << numArgs << std::endl;
   outputFile_ << "D=D-A" << std::endl;

   outputFile_ << "@5" << std::endl;
   outputFile_ << "D=D-A" << std::endl;

   outputFile_ << "@ARG" << std::endl;
   outputFile_ << "M=D" << std::endl;

   // reposition LCL
   outputFile_ << "@SP" << std::endl;
   outputFile_ << "D=M" << std::endl;

   outputFile_ << "@LCL" << std::endl;
   outputFile_ << "M=D" << std::endl;

   // goto f
   outputFile_ << "@"
               << currentInputFilename_
               << "."
               << functionName
               << std::endl;
   outputFile_ << "0;JMP" << std::endl;

   // label function return point
   outputFile_ << "("
               << return_addr
               << ")"
               << std::endl;
}

void CodeWriter::writeReturn()
{
   // FRAME in R13
   outputFile_ << "@LCL" << std::endl;
   outputFile_ << "D=M" << std::endl;
   outputFile_ << "@R13" << std::endl;
   outputFile_ << "M=D" << std::endl;

   // RET in R14
   outputFile_ << "@5" << std::endl;
   outputFile_ << "D=A" << std::endl;
   outputFile_ << "@R13" << std::endl;
   outputFile_ << "D=M-D" << std::endl;
   outputFile_ << "A=D" << std::endl;
   outputFile_ << "D=M" << std::endl;
   outputFile_ << "@R14" << std::endl;
   outputFile_ << "M=D" << std::endl;

   // reposition the return value for the caller
   // load first arg from top of stack into d
   decSP();

   outputFile_ << "@SP" << std::endl;
   outputFile_ << "A=M" << std::endl;
   outputFile_ << "D=M" << std::endl;

   // store return value in R15
   outputFile_ << "@R15" << std::endl;
   outputFile_ << "M=D" << std::endl;

   // restore SP of the caller
   outputFile_ << "@ARG" << std::endl;
   outputFile_ << "D=M+1" << std::endl;
   outputFile_ << "@SP" << std::endl;
   outputFile_ << "M=D" << std::endl;

   // store return value in ARG
   outputFile_ << "@R15" << std::endl;
   outputFile_ << "D=M" << std::endl;
   outputFile_ << "@ARG" << std::endl;
   outputFile_ << "A=M" << std::endl;
   outputFile_ << "M=D" << std::endl;

   // restore THAT of the caller
   outputFile_ << "@1" << std::endl;
   outputFile_ << "D=A" << std::endl;
   outputFile_ << "@R13" << std::endl;
   outputFile_ << "D=M-D" << std::endl;
   outputFile_ << "A=D" << std::endl;
   outputFile_ << "D=M" << std::endl;
   outputFile_ << "@THAT" << std::endl;
   outputFile_ << "M=D" << std::endl;

   // restore THIS of the caller
   outputFile_ << "@2" << std::endl;
   outputFile_ << "D=A" << std::endl;
   outputFile_ << "@R13" << std::endl;
   outputFile_ << "D=M-D" << std::endl;
   outputFile_ << "A=D" << std::endl;
   outputFile_ << "D=M" << std::endl;
   outputFile_ << "@THIS" << std::endl;
   outputFile_ << "M=D" << std::endl;

   // restore ARG of the caller
   outputFile_ << "@3" << std::endl;
   outputFile_ << "D=A" << std::endl;
   outputFile_ << "@R13" << std::endl;
   outputFile_ << "D=M-D" << std::endl;
   outputFile_ << "A=D" << std::endl;
   outputFile_ << "D=M" << std::endl;
   outputFile_ << "@ARG" << std::endl;
   outputFile_ << "M=D" << std::endl;

   // restore LCL of the caller
   outputFile_ << "@4" << std::endl;
   outputFile_ << "D=A" << std::endl;
   outputFile_ << "@R13" << std::endl;
   outputFile_ << "D=M-D" << std::endl;
   outputFile_ << "A=D" << std::endl;
   outputFile_ << "D=M" << std::endl;
   outputFile_ << "@LCL" << std::endl;
   outputFile_ << "M=D" << std::endl;

   // goto RET
   outputFile_ << "@R14" << std::endl;
   outputFile_ << "A=M" << std::endl;
   outputFile_ << "0;JMP" << std::endl;
}



void CodeWriter::writeInit()
{
   outputFile_ << "@256" << std::endl;
   outputFile_ << "D=A" << std::endl;
   outputFile_ << "@SP" << std::endl;
   outputFile_ << "M=D" << std::endl;

   writeCall("Sys.init", 0);
}
