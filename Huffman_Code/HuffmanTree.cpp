#include "HuffmanTree.hpp"

using namespace std;

// Recursive function for deleting all nodes in a tree
void HuffmanTree::RecursiveDeletion(HuffmanNode* node){
  if(node == NULL){return;}
  if(node->isBranch()){
    RecursiveDeletion(node->left);
    RecursiveDeletion(node->right);
  }
  if(node != nullptr) free(node);
  else return;
}

// This function is used to created the compressed version of the input string by converting it to 1's and 0's
void HuffmanTree::CodedString(HuffmanNode* L, string outStr){
  // If it's a leaf insert into SMAP with character
  if(L->isLeaf()) {SMAP.insert({L->getCharacter(),outStr});}
  // If L add 0 to code string
  if(L->left != nullptr) {CodedString(L->left, outStr + "0");}
  // If right add 1 to code string
  if(L->right != nullptr) {CodedString(L->right, outStr + "1");}
}

string HuffmanTree::compress(string inputStr){
  // Create queue for compression
  HeapQueue<HuffmanNode *, HuffmanNode::Compare> CompressionQueue;

  // Range based for loop that iterates through all characters in the input CodedString
  for(const auto ch1 : inputStr){
    // Adds the character to the HMAP and adds 1 to characters frequecy
    HMAP[ch1]++;
  }

  // Range based loop inserts each entry from HMAP into the compression queue
  for(const auto charcount : HMAP){
    // creates HuffmanNodes from each entry in HMAP and inserts into the queue
    HuffmanNode* Temp = new HuffmanNode(charcount.first, charcount.second);
    CompressionQueue.insert(Temp);
  }

  // Loop runs all processes for encoding the string until the compression queue is empty
  while (CompressionQueue.size() != 1){

    // This sets temp1 to the minimum node, then removes min node
    HuffmanNode* temp1 = CompressionQueue.min();
    CompressionQueue.removeMin();

    // This sets temp2 to the next minimum node, then removes the node
    HuffmanNode* temp2 = CompressionQueue.min();
    CompressionQueue.removeMin();

    // Generates a new node theat will hold the frequency of temp1 and temp2 combines and a null characters
    size_t num = temp1->getFrequency() + temp2->getFrequency();
    HuffmanNode* temp3 = new HuffmanNode('\0', num);

    // Temp nodes are linked together
    temp3->left = temp1;
    temp3->right = temp2;
    temp1->parent = temp3;
    temp2->parent = temp3;
    // Temp nodes reinserted into the compression queue for next iteration
    CompressionQueue.insert(temp3);
  }

  // CompressionQueue copied over to ProcessQueue to be used for decompression
  ProcessQueue = CompressionQueue;
  string outputString = "";

  // Function for serializing the string
  CodedString(CompressionQueue.min(), outputString);

  // For each entry in the string find it's map value and insert the correct code
  for(const auto maps : inputStr){
    outputString += SMAP[maps];
  }
  return outputString;
}

// Functions navigates the tree in a Postorder Transversal and produces a serialized string
void HuffmanTree::SerializePostTransversal(HuffmanNode* M, string outStr){
  // If the nodes left child exists function recurses to it.
  if(M->left != nullptr){SerializePostTransversal(M->left, outStr);}
  // If the nodes right child exists function recurses.
  if(M->right != nullptr){SerializePostTransversal(M->right, outStr);}
  // If the node is a branch add a "B" char to the serial string
  if(M->isBranch()){serializeString += "B";}
  // If the node is a leaf an "L" char is added to the serial string followed by the character.
  if(M->isLeaf()){
    serializeString += "L";
    serializeString += M->getCharacter();
  }
}

string HuffmanTree::serializeTree(){
  // Creates a node that points to the root of my queue for processing the string.
  string output = "";
  HuffmanNode* tmp = ProcessQueue.min();
  // Run the tree through the recursive transversal function
  SerializePostTransversal(tmp, output);
  // Returns the serialized string
  return serializeString;
}

string HuffmanTree::decompress(string inputCode, string serializedTree){
  string outputString;
  // This loop creates nodes containing all character values in the array and links them to huffman buffer nodes
  for(unsigned int i = 0 ; i < serializedTree.length() ; i++){
      char pchar = serializedTree[i]; // character variable pchar represents the current character in string
      // If L iterate postchar and add character values to a new node
      //if(pchar != 'L' && pchar != 'B'){
      if(pchar == 'L'){
        // Next 2 lines handle the issue of the current pchar being 'B'
        ++i;
        pchar = serializedTree[i];

        HuffmanNode* newNode = new HuffmanNode(pchar, 0, nullptr, nullptr, nullptr);
        DBUFF.push(newNode);
      }
      // If B then link nodes with buffer and reinsert into buffer similar to postfix to infix conversion
      //if(pchar == 'B'){
      else{
        HuffmanNode* right = DBUFF.top();
        DBUFF.pop();
        HuffmanNode* left = DBUFF.top();
        DBUFF.pop();
        HuffmanNode* blank = new HuffmanNode('\0', 0, nullptr, left, right);
        DBUFF.push(blank);
      }
  }

  // Create new root node and position pointer for the huffman tree
  root = DBUFF.top();
  unsigned int i = 0;
  bool flag = false;

  // Loop is used to iterate through the tree from root until a leaf is found
  // If code is '1' travel right if code is '0' travel to left child
  while( i < inputCode.length()){
    if(flag){
      if(pos->isLeaf()){
        outputString.push_back(pos->getCharacter());
        flag = false; // Set to false in order to initialize the position node to root
      }
      else{
        if(inputCode[i] == '1'){
          pos = pos->right; // moves positon to right child if '1'
        }
        else{pos = pos->left;} // moves position to left child if '0'
        i++; // Iterates to next character value of either '0' or '1'
      }
    }
    else{ //returns position to root node
      pos = root;
      flag = true;
    }
  }
  outputString.push_back(pos->getCharacter());

  return outputString;
}
