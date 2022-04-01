#include "CalcList.hpp"
#include "CalcListInterface.hpp"

using namespace std;

double CalcList::total() const{
  return cur_total;
}

void CalcList::newOperation( const FUNCTIONS func, const double operand){
  Node* current = new Node;
  current->prev = nullptr;
  current->next = nullptr;

  switch(func){
    case ADDITION:
      current->operation = '+';
      current->operand = operand;

      //Handles operation if it is the fist operation in the program
      if(header == NULL){
        current->old_total = 0;
        current->new_total = 0 + operand;
        header = current;
      }

      else{
        Node* newNode = header;
        while(newNode->next != NULL){
          newNode = newNode->next;
        }
        newNode->next = current;
        current->prev = newNode;
        current->old_total = newNode->new_total;
        current->new_total = current->old_total + operand;
      }
      cur_total = current->new_total;
      break;

    case SUBTRACTION:
      current->operation = '-';
      current->operand = operand;

      //Handles operation if it is the fist operation in the program
      if(header == NULL){
        current->old_total = 0;
        current->new_total = 0 - operand;
        header = current;
      }

      else{
        Node* newNode = header;
        while(newNode->next != NULL){
          newNode = newNode->next;
        }
        newNode->next = current;
        current->prev = newNode;
        current->old_total = newNode->new_total;
        current->new_total = current->old_total - operand;
      }
      cur_total = current->new_total;
      break;

    case MULTIPLICATION:
      current->operation = '*';
      current->operand = operand;

      //Handles operation if it is the fist operation in the program
      if(header == NULL){
        current->old_total = 0;
        current->new_total = 0;
        header = current;
      }

      else{
        Node* newNode = header;
        while(newNode->next != NULL){
          newNode = newNode->next;
        }
        newNode->next = current;
        current->prev = newNode;
        current->old_total = newNode->new_total;
        current->new_total = current->old_total * operand;
      }
      cur_total = current->new_total;
      break;

    case DIVISION:
      current->operation = '/';
      current->operand = operand;

      //Handles operation if it is the fist operation in the program
      if(header == NULL){
        current->old_total = 0;
        current->new_total = 0;
        header = current;
      }

      if( current->operand == 0){
        throw "Division by Zero!!";
      }

      else{
        Node* newNode = header;
        while(newNode->next != NULL){
          newNode = newNode->next;
        }
        newNode->next = current;
        current->prev = newNode;
        current->old_total = newNode->new_total;
        current->new_total = current->old_total / operand;
      }
      cur_total = current->new_total;
      break;
    }
}

void CalcList::removeLastOperation(){

  //test for empty CalcList
  try{
    if(header == nullptr){
    throw "Empty List";
    return;
    }
  }
  catch(...){
    return;
  }
  //Checks to see if there is only one object in list
  if(header->next == NULL){
    cur_total = header->old_total;
    header = nullptr;
    return;
  }

//Index used to move to the end of the list and remove last entry
  Node* index = header;
  while(index->next != NULL){
    index = index->next;
  }
  index = index->prev;
  delete(index->next);
  index->next = nullptr;
  cur_total = index->new_total;
  delete index;
  return;
}

string CalcList::toString(unsigned short precision) const{
  string xprint;
  int count = 1;

  if(header == NULL){
    return "No Operations have been preformed yet!";
  }
  //String Stream used to store full return value of multiple lines
  ostringstream oss;
  oss << setprecision(precision) << fixed;
  Node* current = header;

  while(current->next != NULL){
    current = current->next;
    count++;
  }

  while(current != NULL){
    oss << count << ": " << current->old_total << current->operation << current->operand << "=" << current->new_total << endl;
    current = current->prev;
    count--;
  }
  xprint = oss.str();
  return xprint;

//return xprint;
}
