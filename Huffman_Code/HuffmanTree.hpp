#include <string>
#include <map>
#include <stack>
#include "HeapQueue.hpp"
#include "HuffmanBase.hpp"

using namespace std;

class HuffmanTree{
  private: // Initialization of program maps
  map<char, size_t> HMAP; // map used for storing character and frequency pairs
  map<const char, string> SMAP; // map used for storing
  stack<HuffmanNode*> DBUFF; // Linked list used for decompression
  HuffmanNode* root;
  HuffmanNode* pos;

  protected: // The queue and string used in our serialization function
  HeapQueue<HuffmanNode *, HuffmanNode::Compare> ProcessQueue;
  string serializeString;

  public: // Functions used for compression, serialization and decompression of the
  HuffmanTree(){root = nullptr; pos = nullptr;};
  ~HuffmanTree(){RecursiveDeletion(root);};
  void RecursiveDeletion(HuffmanNode* x);
  string compress(string inputStr);
  string serializeTree();
  string decompress(string inputCode, string serializedTree);
  void CodedString(HuffmanNode* L, string outStr);
  void SerializePostTransversal(HuffmanNode* M, string outStr);
};
