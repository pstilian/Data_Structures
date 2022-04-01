#ifndef NotationConverter_h
#define NotationConverter_h

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <stdio.h>
#include "NotationConverterInterface.hpp"

using namespace std;

//Structure that stores one character from the equation
struct Node{
  string eStr;
  Node* next;
  Node* prev;
};

//Doubly Linked List used for storing the equation to be mainipulated
class DLinkedList{
public:
  DLinkedList();
  ~DLinkedList();
  string removeFront();
  string removeBack();
  void addFront(string x);
  void addBack(string x);
  bool isEmpty();
  int getSize();

private:
  Node* head = NULL;
  Node* tail = NULL;
  int lLength;
};


class NotationConverter : public NotationConverterInterface{
public:
  NotationConverter();
  ~NotationConverter();
  virtual string postfixToInfix( string inStr);
  virtual string postfixToPrefix( string inStr);
  virtual string infixToPostfix( string inStr);
  virtual string infixToPrefix( string inStr);
  virtual string prefixToInfix( string inStr);
  virtual string prefixToPostfix( string inStr);
  bool isOperator( char x);
  bool isOperand( char x);
  int opPriority( string x);
  string sFormat( string x);
  string reverse(string x);
  string feedFromDecque();
  void checkInput( string x);

private:
  DLinkedList DLL;
};

#endif
