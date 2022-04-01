#include "GraphBase.hpp"
#include <map>
#include <iostream>
#include <list>
#include <utility>
#include <climits>
#include <stack>

using namespace std;

// Struct to represent Edges.
// Since it is contained inside the starting vertex this struct contains a refenece to
// the connected edge as well as the weight associated with the edge
struct Edge{
  int weight;
  string end;
};


// Struct to represent Vertex elements in the Graph
// Contains the string value used to reference this Vertex as well as a vector
// of edges to adjacent vertexs'
struct Vertex{
  string val;
  vector<Edge> Edges;
};

// Class representing the Graph
class Graph{
public:
  Graph();
  ~Graph();
  void addVertex(string label);
  void removeVertex(string label);
  void addEdge(string label1, string label2, unsigned long weight);
  void removeEdge(string label1, string label2);
  unsigned long shortestPath(string startLabel, string endLabel, vector<string> &path);

private:
  map<string, Vertex> Vlist; // used to store the vertexs with their associated reference value
  };
