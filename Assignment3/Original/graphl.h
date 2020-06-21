/**
 * --------------------graphl.cpp------------------
 * Jeremy Tandjung CSS 343
 * Created:   May 6th, 2019
 * Last Modified:   May 13th, 2019
 * ------------------------------------------------
 * Purpose: GraphL is an implementation of the depth first
 *          search to get the shortest distance between
 *          two points on a graph. 
 * Assumptions:
 * 1. Input is in a text file.
 * 2. The text file is well formated; therefore, the class 
 *      doesn't need bad data handling.
 * 3. The maximum number of vertexes is 100.
 * ------------------------------------------------
 */
#ifndef __GRAPH__L__
#define __GRAPH__L__

#include <iostream>
#include <fstream>

#include "nodedata.h"

//named MAXNODES_L to diffrentiate with GraphM's MAXNODES
int const MAXNODES_L = 101;

using namespace std;

class GraphL
{
    public:

        //constructor
        GraphL();
        //destructor
        ~GraphL();

        void buildGraph(ifstream&);
        void depthFirstSearch();
        void displayGraph();

    private:
        struct EdgeNode;
        //Vertex representation
        struct GraphNode
        {
            EdgeNode* edgeHead;
            NodeData* data;
            bool visited;
        };

        //linked list to store adjacent vertexes
        struct EdgeNode
        {   
            int adjGraphNode;
            EdgeNode* nextEdge;
        };

        //size of graph (number of vertexes)
        int size;
        
        //array of GraphNodes to store all existing GraphNodes
        GraphNode adjList[MAXNODES_L];

        //HELPER METHODS
        void eraseGraph();
        void dfsHelper(int);
};

#endif