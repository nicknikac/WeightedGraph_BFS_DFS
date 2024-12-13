/*

Nikola Nikac
Program 5
CS 250

// Program implements a weighted graph and does DFS/BFS traversals starting at E.
// added a function to find paths between vertices

*/
#include <iostream>
#include "Vertex.h"
#include "WeightedGraph.h"
using namespace std;

int main() {
    WeightedGraph myGraph(10);
    Vertex* startNode;
    Vertex* aVertex;

    aVertex = new Vertex("A");  // node 0
    myGraph.addVertex(aVertex);
    Vertex* vertexA = aVertex;

    aVertex = new Vertex("B");  // node 1
    myGraph.addVertex(aVertex);
    Vertex* vertexB = aVertex;

    aVertex = new Vertex("C");  // node 2
    myGraph.addVertex(aVertex);
    Vertex* vertexC = aVertex;

    aVertex = new Vertex("D");  // node 3
    myGraph.addVertex(aVertex);
    Vertex* vertexD = aVertex;

    startNode = new Vertex("E");  // node 4
    myGraph.addVertex(startNode);

    myGraph.addEdge(4,0,7);
    myGraph.addEdge(0,1,10);
    myGraph.addEdge(0,2,12);
    myGraph.addEdge(0,3,60);
    myGraph.addEdge(2,1,20);
    myGraph.addEdge(2,3,32);

    cout << "Depth First search: ";
    myGraph.DFS(startNode);
    cout << endl;

    cout << "Breadth First Search: ";
    myGraph.BFS(startNode);
    cout << endl;

    cout << "Testing paths:" << endl;
    myGraph.findPath(startNode, vertexB);
    cout << endl;
    myGraph.findPath(startNode, vertexD);

    return 0;
}
