#include "GritVM.hpp"

using namespace std;
// Constructor Function initializes program status to waiting
GritVM::GritVM(){
  machineStatus = WAITING;
  accumulator = 0;
}

// Destructor Function
GritVM::~GritVM(){}

// Function copies memory from argument address and checks for valid file input
STATUS GritVM::load(const string filename, const vector<long> &initialMemory){
  //string for reading in input sstream
  string line;
  // Opens the input file
  ifstream inFile;
  inFile.open(filename);
  // Copies input memory to getDataMem
  dataMem = initialMemory;
  // Throw eception if file does not Open
  if( inFile.is_open() != true ){
    throw invalid_argument("File did not open");
    return machineStatus;
  }

  // Adds instructions one at a time to the back of instructMem until eof ignoring comments and empty lines
  while(!inFile.eof()){
    getline(inFile, line);
    // uses parseInstructions to double check for Unkown Instructions
    if(line.front() != '#' && line.size() != 0){
      instructMem.emplace_back(GVMHelper::parseInstruction(line));
    }
  }
  inFile.close();
  machineStatus = READY;
  return machineStatus;
}

STATUS GritVM::run(){
  // Set iterator pointer to beginning of instructMem list
  currentInstruct = instructMem.begin();
  // Checks to make sure Machine Status is set to ready or else will not start running
  if(machineStatus != READY) return machineStatus;
  machineStatus = RUNNING;

  // If status is ready while loop reads through instructions until the end of instructMem or when status changes to not running
  while(machineStatus == RUNNING && currentInstruct != instructMem.end()){
    //cout << "Running: " << GVMHelper::instructionToString(currentInstruct->operation) << endl;
    switch(currentInstruct->operation){
      case CLEAR:   // Sets the accumulator to zero then increments the iterator
        accumulator = 0;
        currentInstruct++;
        break;
      case AT:    // Sets accumulator value to the stored value at dataMem[operation]
        accumulator = dataMem.at(currentInstruct->argument);
        currentInstruct++;
        break;
      case SET:   // Sets value stored at dataMem[argument] to the current value of the accumulator
        dataMem.at(currentInstruct->argument) = accumulator;
        currentInstruct++;
        break;
      case INSERT:  // Inserts the value of accumulator in the location dataMem[operation]
        long x;
        x = currentInstruct->argument;
        dataMem.insert(dataMem.begin() + x, accumulator);
        //cout << "INSERT " << x << " and DataMem value stored is " << dataMem.at(x) << endl;
        currentInstruct++;
        break;
      case ERASE:   // Erases location corresponding to argument location in dataMem then increments currentInstruct iterator
        dataMem.erase(dataMem.begin() + currentInstruct->argument);
        currentInstruct++;
        break;
      case ADDCONST:  // Adds argument to accumulator value then increments currentInstruct iterator
        accumulator += currentInstruct->argument;
        currentInstruct++;
        break;
      case SUBCONST:  // Subtracts argument value from accumulator value then increments currentInstruct iterator
        accumulator -= currentInstruct->argument;
        currentInstruct++;
        break;
      case MULCONST: // Multiplies accumulator value by the argument value then increments currentInstruct iterator
        accumulator = accumulator * currentInstruct->argument;
        currentInstruct++;
        break;
      case DIVCONST:  // Divides accumulator value by the argument value then increments currentInstruct iterator
        accumulator = accumulator / currentInstruct->argument;
        currentInstruct++;
        break;
      case ADDMEM:  // Adds value from dataMem[argument] location to the accumulator
        accumulator += dataMem.at(currentInstruct->argument);
        currentInstruct++;
        break;
      case SUBMEM:  // Subtracts value from dataMem[argument] location to the accumulator
        accumulator -= dataMem.at(currentInstruct->argument);
        currentInstruct++;
        break;
      case MULMEM:  // Multiplies accumulator by the value from dataMem[argument]
        accumulator = accumulator * dataMem.at(currentInstruct->argument);
        currentInstruct++;
        break;
      case DIVMEM:  // Divides accumulator by the value from dataMem[argument]
        accumulator = accumulator / dataMem.at(currentInstruct->argument);
        currentInstruct++;
        break;
      case JUMPREL: // Jumps number of instructions equal to argument ( Argument can be negative )
        long iCount;
        iCount = currentInstruct->argument;
        // if counter is positive while loop increments iterator
        while(iCount > 0){
          currentInstruct++;
          iCount--;
        }
        //if counter is negative increments iterator in reverse
        while(iCount < 0){
          currentInstruct--;
          iCount++;
        }
        break;
      // If accumulator is == to zero function jumps a number of instructions = to the operator else iterates to next instruction
      case JUMPZERO:  // If accumulator = 0 goes forward or backwards number of instructions equal to argument otherwise only jumps one instruction
        if(accumulator == 0){
          long iCount1;
          iCount1 = currentInstruct->argument;
          while(iCount1 > 0){  // if counter is positive while loop increments iterator
            currentInstruct++;
            iCount1--;
          }
          while(iCount1 < 0){  //if counter is negative increments iterator in reverse
            currentInstruct--;
            iCount1++;
          }
        }
        else currentInstruct++; // if accumulator = 0 increments 1 instruction
        break;
      // If accumulator is != to zero function jumps a number of instructions = to the operator else iterates tothe next instruction
      case JUMPNZERO:
        long iCount2;
        iCount2 = currentInstruct->argument;
        if(accumulator != 0){
          while(iCount2 > 0){  // if counter is positive while loop increments iterator
            currentInstruct++;
            iCount2--;
          }
          while(iCount2 < 0){  //if counter is negative increments iterator in reverse
            currentInstruct--;
            iCount2++;
          }
        }
        else currentInstruct++; // if accumulator = 0 increments 1 instruction
        break;
      case NOOP:  // Iterates to next instruction but does nothing
        currentInstruct++;
        break;
      case HALT:  // Halts the program from running
        machineStatus = HALTED;
        break;
      case OUTPUT:  // Outputs the accumulator value to the terminal window
        cout << accumulator <<endl;
        currentInstruct++;
        break;
      case CHECKMEM: // Checks to see if dataMem is the same size as operation. If not changes status to ERRORED else increments the iterator
        if( (long)dataMem.size() != currentInstruct->argument){
          machineStatus = ERRORED;
        }
        else{
          currentInstruct++;
          continue;
        }
        break;
      case UNKNOWN_INSTRUCTION: // If instruction is unknown program goes into errored state
        machineStatus = ERRORED;
        break;
    }
  }
  // When end of instructions reached program halts
  machineStatus = HALTED; // Stops the program and waits for the reset method to be called.
  return machineStatus;
}

// Resets the program to waiting and clears all memory
STATUS GritVM::reset(){
  accumulator = 0;
  dataMem.clear();
  instructMem.clear();
  machineStatus = WAITING;
  return machineStatus;
}
