#include "NotationConverter.hpp"

using namespace std;

DLinkedList::DLinkedList(){
  lLength = 0;
  head = new Node;
  tail = head;
  head->prev = head;
  tail->next = tail;
  head->next = tail;
  tail->prev = head;
}

DLinkedList::~DLinkedList(){
  while( !isEmpty() )removeFront();
  delete head;
  delete tail;
}

bool DLinkedList::isEmpty(){
  if(lLength == 0) return true;
  else return false;
}

string DLinkedList::removeFront(){
  Node* temp = new Node;
  string x;
  x = head->eStr;
  temp = head;
  head = head->next;
  lLength--;
  delete temp;
  return (string)x;
}

string DLinkedList::removeBack(){
  Node* temp = new Node;
  string x;
  if (lLength == 0){
    throw "merp";
  }
  else{
    x = tail->eStr;
    temp = tail;
    tail = tail->prev;
    lLength--;
    delete temp;
    return (string)x;
  }
}

void DLinkedList::addFront( string x){
  Node* newNode = new Node;
  lLength++;
  newNode->eStr = x;
  //cout << "adding front " << newNode->eStr << endl;
  newNode->next = head;
  head = newNode;
}

void DLinkedList::addBack( string x){
  Node* newNode = new Node;
  lLength++;
  newNode->eStr = x;
  //cout << "adding back " << newNode->eStr << endl;
  newNode->prev = tail;
  tail->next = newNode;
  tail = newNode;
}

int DLinkedList::getSize(){
  return lLength;
}
