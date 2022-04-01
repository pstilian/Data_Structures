#include "NotationConverter.hpp"

using namespace std;

char BEGIN = '(';
char END = ')';
string SPACE = " ";

NotationConverter::NotationConverter(){}

NotationConverter::~NotationConverter(){}

// Reverses String
string NotationConverter::reverse( string x){
  string value;
  for( int i = (x.length() - 1) ; i >= 0 ; i--){
    value += x[i];
  }
  return value;
}

// Formats text to include spaces
string NotationConverter::sFormat( string x){
  string fString;
  int j = ((int)x.length() - 1);
  for( int i = 0 ; i < (int)x.length() - 1 ; i++){
    if( isOperand(x[i]) == true || isOperator(x[i]) == true){
      if(x[i+1] == END) fString += x[i];
      else{
        fString += x[i];
        fString += SPACE;
      }
    }
    if(x[i] == BEGIN){
      fString += x[i];
    }
    if(x[i] == END){
      if(x[i+1] == END) fString += x[i];
      else{
        fString += x[i];
        fString += SPACE;
      }
    }
    else continue;
  }
  fString += x[j];
  return fString;
}

//Determines if character is an Operator
bool NotationConverter::isOperator( char x){
  //cout << "is operator working " << x << endl;
  if ( x == '+' || x == '-' || x == '/' || x == '*') return true;
  else return false;
}

// Returns true if value is an Operand
bool NotationConverter::isOperand( char x){
  if ( (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') ) return true;
  else return false;
}

// Tests operation priority and ranks acording to PEMDAS
int NotationConverter::opPriority( string x){
  if( x == "+" || x == "-") return 1;
  else if( x == "*" || x == "/") return 2;
  else return 0;
}

// Returns all values from decque
string NotationConverter::feedFromDecque(){
  string value;
  while( DLL.isEmpty() != true){
    value.append(DLL.removeFront());
  }
  return value;
}

// checks for bad input values if found throws exception
void NotationConverter::checkInput( string x){
  for( int i = 0 ; i < (int)x.length() ; i++){
    if( isOperand(x[i]) != true && isOperator(x[i]) != true && x[i] != BEGIN && x[i] != END && x[i] != ' ') throw "Illegal Input!";
  }
}


// converts postfix to infix
string NotationConverter::postfixToInfix( string inStr){
  string infix;
  string str;
  checkInput(inStr);
//  cout << "test  = " << inStr << endl;
  for( int i = 0 ; i < (int)inStr.length() ; i++){
    //if operand adds to front of expression
    str = inStr[i];
    if(isOperand(inStr[i]) == true) DLL.addFront(str);

    //id operator is found then corrects order
    if(isOperator(inStr[i]) == true){
      string temp1 = DLL.removeFront();
      string temp2 = DLL.removeFront();
      string merge = BEGIN + temp2 + inStr[i] + temp1 + END;
      DLL.addFront(merge);
    }
    else continue;
  }
  infix = feedFromDecque();
  infix = sFormat(infix);
  return infix;
}


// converts prefix to infix
string NotationConverter::prefixToInfix( string inStr){
  string infix;
  string str;
  checkInput(inStr);

  for( int i = ( inStr.length() - 1 ) ; i >= 0 ; i--){
    //if operator is found then corrects order
    str = inStr[i];
    if(isOperator(inStr[i]) == true){
      string temp1 = DLL.removeFront();
    //  cout << " temp 1 = " << temp1 << endl;
      string temp2 = DLL.removeFront();
    //  cout << "temp 2 = " << temp2 << endl;
      //add parenthesis and operators/operands back to decque
      string merge = BEGIN  + temp1 + inStr[i] + temp2 + END;
    //  cout << "merge = " << merge << endl;
      DLL.addFront(merge);
    }
    //adds operand to front of expression
    if(isOperand(inStr[i]) == true) DLL.addFront(str);
    else continue;
  }
  infix = feedFromDecque();
  infix = sFormat(infix);

  return infix;
}


// converts infix to postfix
string NotationConverter::infixToPostfix( string inStr){
  string postfix;
  string temp;
  string str;
  checkInput(inStr);

  for(int i = 0 ; i < (int)inStr.length() ; i++){
    str = inStr[i];
    if(isOperand(inStr[i]) == true) postfix += inStr[i];
    if(inStr[i] == BEGIN) DLL.addFront("(");

    if(inStr[i] == END){
      temp = DLL.removeFront();
      while(temp != "("){
        postfix += temp;
        temp = DLL.removeFront();
      }
    }

    if(isOperator(inStr[i]) == true){
      temp = DLL.removeFront();

      if(opPriority(str) > opPriority(temp) || DLL.getSize() == 0 || temp == "("){
        DLL.addFront(temp);
        DLL.addFront(str);
      }
      while(opPriority(str) <= opPriority(temp)){
        postfix += temp;
        temp = DLL.removeFront();
      }
    }
    else continue;
    }

  postfix = sFormat(postfix);
  return postfix;
}


// converts infix to prefix
string NotationConverter::infixToPrefix( string inStr){
  string prefix;
  string temp;
  checkInput(inStr);

  inStr = reverse(inStr);

  for(int i = 0 ; i < (int)inStr.length() ; i++){
    if(inStr[i] == BEGIN){
      inStr[i] = END;
      continue;
    }
    else if(inStr[i] == END){
      inStr[i] = BEGIN;
    }
    else continue;
  }

  prefix = infixToPostfix(inStr);
  prefix = reverse(prefix);
  prefix = sFormat(prefix);

  return prefix;
}


// Uses other conversion functions to change postfix to prefix
string NotationConverter::postfixToPrefix( string inStr){
  string prefix;
  prefix = postfixToInfix(inStr);
  prefix = infixToPrefix(prefix);
  prefix = sFormat(prefix);
  return prefix;
}

// Uses other conversion functions to change prefix to postfix
string NotationConverter::prefixToPostfix( string inStr){
  string postfix;
  postfix = prefixToInfix(inStr);
  postfix = infixToPostfix(postfix);
  postfix = sFormat(postfix);
  return postfix;
}
