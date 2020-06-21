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

#include "graphl.h"
#include <iomanip>

/**
 * ------------------default constructor--------------
 * The default constructor of the graphL class
 * The constructor creates an array of 100 (maximum number)
 * vertexes and sets every one of them as empty vertexes
 * 
 * Parameter:
 *  None
 * ---------------------------------------------------
 */
GraphL::GraphL()
{
    size = 0;
    for(int i = 1; i < MAXNODES_L; i++)
    {
        adjList[i].visited = false;
        adjList[i].edgeHead = NULL;
        adjList[i].data = NULL;
    }
}//end of function

/**
 * ------------------destructor----------------------
 * Destructor for grpahL class
 * Uses the eraseGraph() function to clear the graph
 * 
 * Parameters:
 *  None
 * --------------------------------------------------
 */
GraphL::~GraphL()
{
    eraseGraph();
}//end of function

/**
 * ------------eraseGraph()---------------
 * eraseGraph deletes everything in the 
 * GraphL object
 * 
 * Parameters:
 *  -None
 * ---------------------------------------
 */
void GraphL::eraseGraph()
{
    //go gor each vertexes' adjacent vertex
    for(int v = 1; v <= size; v++)
    {
        adjList[v].visited = false;

        //delete the data and set to NULL for memory
        delete adjList[v].data;
        adjList[v].data = NULL;

        //if vertex has neighbours
        if(adjList[v].edgeHead != NULL)
        {   
            //stores head of list
            EdgeNode* deleteNode = adjList[v].edgeHead;
            
            //iterates through list to delete everything
            while(deleteNode != NULL)
            {
                adjList[v].edgeHead = adjList[v].edgeHead->nextEdge;
                delete deleteNode;
                deleteNode = adjList[v].edgeHead;
            }
        }
    }
}//end of function

/**
 * ------------------buildGraph()-----------------
 * buildGraph makes the hypothetical graph from 
 * the input file by putting the adjacent vertexes
 * to the adjacency matrix
 * 
 * Parameters:
 *  -ifstream& input
 *      the ifstream file of the input text file
 * -----------------------------------------------
 */
void GraphL::buildGraph(ifstream& input)
{
    int from, to;
    
    //empty graph 
    eraseGraph();

    //If ifstream is at the end of file
    if(input.eof())
        return;

    //first element of the file will the number of vertex
    input>>size;

    //when the input exceeds the assumed maximum number of vertexes (100)
    if( size >= MAXNODES_L)
    {
        cerr << "Input exceeds maximum number (100) of vertexes" << endl;
        size = 0;
        return;
    }

    //Get the store name from input file
    string vName = "";
    getline(input, vName);

    //Iterates through the adj list
    for(int v = 1; v <= size; v++)
    {
        getline(input, vName);
        NodeData* store = new NodeData(vName);
        adjList[v].data = store;
    }

    //Loops until nothing is left in the input file
    for(;;)
    {
        input >> from >> to;
        if (from == 0 && to == 0)
            return;
        
        //if vertexes of interest go out of bounds
        if(from > size || to > size) 
            return;
        
        //if one of the vertiexes is a negative number
        if(from < 0 || to < 0)
            return;
        
        //this loop stops when vertex of interest goes out bound
        if(from <= size && to <= size)
        {
            //new vertex
            if(adjList[from].edgeHead == NULL)
            {
                EdgeNode* curr = new EdgeNode;

                curr->adjGraphNode = to;
                adjList[from].edgeHead = curr;
                adjList[from].edgeHead->nextEdge = NULL;
            }
            //a vertex that already has a neigbour stored at the list
            //this implementation puts the new neighbour at the head 
            //of the list
            else
            {
                EdgeNode* curr = new EdgeNode;
                
                curr->adjGraphNode = to;
                curr->nextEdge = adjList[from].edgeHead;
                adjList[from].edgeHead = curr;
            }   
        }  
    }
}//end of function

/**
 * -------------------depthFirstSearch-------------
 * Purpose:
 *  depthFirstSearch implements a depth first search
 *  to print out the depth first path of the whole graph.
 *  This function uses a helper method to do the 
 *  actual dfs, while this functions handles the 
 *  title and setting every vertex to unvisited
 * 
 * Parameters:
 *  None
 * ------------------------------------------------
 */
void GraphL::depthFirstSearch()
{
    //Set every vertex as unvisited
    for(int i = 1; i <= size; i++)
        adjList[i].visited = false;

    cout << "Depth-first ordering: ";

    //Prints out the depth first path for each vertex
    for(int v = 1; v <= size; v++)
    {
        if(adjList[v].visited == false)
            dfsHelper(v);
    }
    
    cout << endl;
}//end of function

/**
 * ---------------dfsHelper-------------
 * Purpose:
 *  Recursive helper for depthFirstSearch()
 *  that will print out the depth first
 *  path for the whole graph
 * 
 * Parameter:
 *  -int v: the vertex number the function
 *          will go through to print its
 *          depth first path
 * --------------------------------------
*/
void GraphL::dfsHelper(int v)
{
    //set as visited
    adjList[v].visited = true;
    cout << v << " "; //print current vertex

    //iterates through each neighbour
    EdgeNode* curr = adjList[v].edgeHead;
    while(curr != NULL)
    {
        if(adjList[curr->adjGraphNode].visited == false)
            dfsHelper(curr->adjGraphNode);

        curr = curr->nextEdge;
    }
}//end of function

/**
 * ----------------displayGraph()--------------
 * The displayGraph function prints out the 
 * graph in a human-friendly format
 * 
 * Parameters:
 *  None
 * --------------------------------------------
 */
void GraphL::displayGraph()
{
    cout << endl << "Graph: " << endl;
	
    //go through each unvisited vertex
    for (int v = 1; v <= size; v++) 
    {
        //print vertex number and data
        cout << "Node" << v << "      " << *adjList[v].data << endl << endl;
		
		//prints the vertex' neighbours.
        EdgeNode* curr = adjList[v].edgeHead; 
        while (curr != NULL) 
        {
            cout << setw(7) << "edge " << v << 
				setw(2) << curr->adjGraphNode << endl;
            
			curr = curr->nextEdge;  
        }
    }
}//end of function
