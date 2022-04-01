#ifndef CalcList_h
#define CalcList_h

#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <iomanip>
#include "CalcListInterface.hpp"

using namespace std;

//Structure that stores each set of operations and total values
struct Node{
  char operation;
  double old_total; //previous total
  double new_total;
  double operand;
  Node* next;
  Node* prev;
};

//Doubly Linked list that also stores the current total value
//Inherits from CalcListInterface class
class CalcList : public CalcListInterface{
public:
  virtual double total() const;
  virtual void newOperation( const FUNCTIONS func, const double operand);
  virtual void removeLastOperation();
  virtual std::string toString(unsigned short precision) const;
private:
  Node* header = nullptr;
  double cur_total = 0;
};

#endif
