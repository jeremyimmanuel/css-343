/**
 * ----------------------graphm.cpp---------------------
 * Jeremy Tandjung CSS 343
 * Created:     05/06/2019
 * Last Modified: 05/13/2019
 * 
 * Purpose:
 *  This class is an implementation one of many graph algorithms;
 *  Dijkstra's algorithm. This classes uses the Dijkstra's
 *  algorithm to find the shortes path between two vertexes.
 * 
 * Assumptions:
 * 1. The maximum number of vertexes in a graph is 100
 * 2. The class represent unconnected vertex with a 
 *      distance weight of INF, which we defined as 
 *      2147483647
 * 3. The class assume the input file will be well 
 *      formatted like the example shown in the
 *      instructions document. Therefore, the class
 *      does not handle bad input
 * -----------------------------------------------------
 */
#ifndef __GRAPH__M__
#define __GRAPH__M__

#include <fstream>
#include <iostream>
#include "nodedata.h"

//define INF as a representation of non-adjacent vertexes
//maximum number for 32-bit computer
#define INF 2147483647

//A graph can only hold at most 100 nodes.
const int MAXNODES = 101;

using namespace std; 

class GraphM {
    public:   
        //constructor  
        GraphM();
        //destructor
        ~GraphM();

        //build hypothetical graph from input 
        void buildGraph(istream&);

        //insert 
        bool insertEdge(int, int, int);
        bool removeEdge(int, int);
        void findShortestPath();
        void displayAll();
        void display(int, int);

    private:       
        
        struct TableType
        {
            bool visited;
            int dist;
            int path;
        };
        
        NodeData data[MAXNODES];                //data for graph nodes        
        int C[MAXNODES][MAXNODES];              //the adjacency matrix       
        int size;                               //number of vertexes in the graph       
        TableType T[MAXNODES][MAXNODES];        //stores visited, distance, path 

        //HELPER METHOD
        void printPath(int, int);
        void printPathData(int, int);
        
    }; 

   #endif