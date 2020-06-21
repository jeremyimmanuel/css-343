#ifndef _GRAPH_M_
#ifndef _GRAPH_M_

#include <iostream>
#include "nodedata.h"
#include <iomanip>      //INF

using namespace std;

int const MAXNODES = 101;

class GraphM
{
    public:
        GraphM();
        ~GraphM();
        
        void buildGraph(istream& input);
        
        bool insertEdge(int form, int to, int weight);
        bool removeEdge(int from, int to);
        void findShortestPath();
        void displayAll();
        void display(int from, int to);

    private:
        struct TableType
        {
            bool visited;
            int dist;
            int path;
        };

        NodeData data[MAXNODES];            //data for graph nodes
        int C[MAXNODES][MAXNODES];          //adj matrix
        int size;                           //number of vertexes (nodes) in the graph
        TableType T[MAXNODES][MAXNODES];    //stores visited, distance, path
};
#endif
