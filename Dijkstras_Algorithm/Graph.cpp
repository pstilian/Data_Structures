#include "Graph.hpp"

// Function adds a new vertex to the graph
void Graph::addVertex(string label){
  Vertex newVertex;
  newVertex.val = label;
  Vlist.emplace(label, newVertex);
}

// Function removes a vertex from the graph
void Graph::removeVertex(string label){
  // search and remove all associated edges first
  // x iterator represents the vertex iterator and y iterates throught the edges
  for( auto x = Vlist.begin() ; x != Vlist.end() ; x++){
    for( auto y = x->second.Edges.begin() ; y != x->second.Edges.end() ; y++){
      if( y->end == label){
        x->second.Edges.erase(y);
        break;
      }
    }
  }
  // Remove vertex structure
  Vlist.erase(label);
}

// Function to add Edges to the graph
void Graph::addEdge(string label1, string label2, unsigned long weight){
  // Adds new edge specified to both vertexes that contain the edge
    Edge temp;
    temp.end = label2;
    temp.weight = weight;
    Vlist.at(label1).Edges.emplace_back(temp);

    Edge temp2;
    temp2.end = label1;
    temp2.weight = weight;
    Vlist.at(label2).Edges.emplace_back(temp2);
}

// Function removes an Edge from the graph
void Graph::removeEdge(string label1, string label2){
  // Iterates through all vertexs and the edges they contain
  for( auto i = Vlist.begin() ; i != Vlist.end() ; i++){
    vector<Edge>::iterator eIter;
    for( eIter = i->second.Edges.begin() ; eIter != i->second.Edges.end() ; eIter++){
      // Deletes all representations of the edge to be remove (aka from either direction)
      if(i->first == label1 && eIter->end == label2){
        i->second.Edges.erase(eIter);
        break;
      }
    }
  }
}



unsigned long Graph::shortestPath(string startLabel, string endLabel, vector<string> &path){
  // Initalize the maps for handling this function
  map<string, int> distance;
  map<string, bool> visited;
  map<string, string> previous;
  unsigned long retVal; // The return value for distance
  stack<string> temp;   // Used to correct the order of return path from backtrace to in-order
  string trace = endLabel;

  //Ititalize my graph and set distances to zero and all Vertexs as not visited
  for(auto i = Vlist.begin() ; i != Vlist.end() ; i++){
    distance.emplace(i->first, INT_MAX);
    visited.emplace(i->first, false);
    previous.emplace(i->first, "");
  }

  // Set all nodes visited flag to false as well as initializes the first visited node as the start node
  bool allVisit = false;
  distance.at(startLabel) = 0;
  Vertex cur = Vlist.at(startLabel);


    // Beginning of implementation of Djikstra's Algorithm
    while( allVisit != true){
      // Marking current Vertex as visited
      visited.at(cur.val) = true;

      for( auto i = cur.Edges.begin() ; i != cur.Edges.end() ; i++){
        // If current adjacent vertex has not been visited proceed otherwise ignore
        if( visited.at(i->end) == false){
          int newWeight = distance.at(cur.val) + i->weight;
          if( newWeight < distance.at(i->end)){
            distance.at(i->end) = newWeight;
            previous.at(i->end) = cur.val;
          }
        }
      }

      // The next 2 loops are used to continue searching unvisited vertexes
      for( auto i = distance.begin() ; i != distance.end() ; i++){
        if(i->second > 0 && visited.at(i->first) == false){
          cur = Vlist.at(i->first);
        }
      }

      for( auto i = distance.begin() ; i != distance.end() ; i++){
        if(i->second > 0 && visited.at(i->first) == false && i->second < distance.at(cur.val)){
          cur = Vlist.at(i->first);
        }
      }

      // Check to see if all vertexes have been visited
      allVisit = true;
      for(auto i = visited.begin(); i != visited.end(); i++){
          if(i->second == false) {allVisit = false;}
      }

      // Checks to see if the goal vertex has been reached if so the loop exits
      if(cur.val == endLabel) {allVisit = true;}
    }

    // This while loop runs back through the previously visited vertexs to find the shortest shortestPath
    // Essentially runs a backtrace
    while( trace != startLabel){
      temp.push(trace);
      trace = previous.at(trace);
    }
    temp.push(startLabel);

    // Stack is used to feed the path from beginning to end into the return path
    while(temp.size() != 0){
      path.push_back(temp.top());
      temp.pop();
    }

    retVal = distance.at(endLabel);
    return retVal;
}

Graph::Graph(){}

Graph::~Graph(){
  vector<string> destr;
  // Loop feeds all vertex names into the destructor vertex
  for(auto i = Vlist.begin() ; i != Vlist.end() ; i++){
    destr.emplace_back(i->first);
  }
  //removes all vertexes
  for( auto i = destr.begin() ; i != destr.end() ; i++){
    removeVertex(*i);
  }
}
