#ifndef GRIT_VM
#define GRIT_VM

#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "GritVMBase.hpp"

using namespace std;

class GritVM{
public:
  GritVM();
  ~GritVM();
  STATUS load(const string filename, const vector<long> &initialMemory);
  STATUS run();
  vector<long> getDataMem(){return dataMem;};
  STATUS reset();

private:
  vector<long> dataMem;
  list<Instruction> instructMem;
  list<Instruction>::iterator currentInstruct;
  STATUS machineStatus;
  long accumulator;
};

#endif
