#include "SymbolTable.h"
#include <iostream>

SymbolTable::SymbolTable()
{
   // add predefined symbols
   addEntry("SP",  0x0000);
   addEntry("LCL", 0x0001);
   addEntry("ARG", 0x0002);
   addEntry("THIS", 0x0003);
   addEntry("THAT", 0x0004);
   addEntry("R0", 0x0000);
   addEntry("R1", 0x0001);
   addEntry("R2", 0x0002);
   addEntry("R3", 0x0003);
   addEntry("R4", 0x0004);
   addEntry("R5", 0x0005);
   addEntry("R6", 0x0006);
   addEntry("R7", 0x0007);
   addEntry("R8", 0x0008);
   addEntry("R9", 0x0009);
   addEntry("R10", 0x000a);
   addEntry("R11", 0x000b);
   addEntry("R12", 0x000c);
   addEntry("R13", 0x000d);
   addEntry("R14", 0x000e);
   addEntry("R15", 0x000f);
   addEntry("SCREEN", 0x4000);
   addEntry("KBD",    0x6000);
}

void SymbolTable::addEntry(std::string symbol, int address)
{
   symbolTable_[symbol] = address;
}

bool SymbolTable::contains(std::string symbol)
{
   bool contains = false;
   if (symbolTable_.count(symbol) > 0)
   {
      contains = true;
   }
   return contains;
}

int SymbolTable::getAddress(std::string symbol)
{
   return symbolTable_[symbol];
}

void SymbolTable::printTable()
{
   std::cout << "SymbolTable:" << std::endl;
   std::cout << "************************" << std::endl;
   for (auto x : symbolTable_)
   {
      std::cout << x.first << ": " << x.second << std::endl;
   }
   std::cout << "************************" << std::endl;
}
