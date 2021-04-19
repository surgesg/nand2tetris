#pragma once

#include <unordered_map>
#include <string>

class SymbolTable
{
  public:
   SymbolTable();
   void addEntry(std::string symbol, int address);
   bool contains(std::string symbol);
   int getAddress(std::string symbol);
   void printTable();

  private:
   std::unordered_map<std::string, int> symbolTable_;
};
