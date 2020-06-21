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

#include "graphm.h"
#include "nodedata.h"
#include <iomanip>

/**
 * ------------------default constructor---------------
 * Purpose:
 *  The default constructor acts as the inilaizatior 
 *  of the GraphM object.
 * 
 * Parameters:
 *  -None
 * 
 */
GraphM::GraphM()
{
    size = 0;
    for (int row = 1; row < MAXNODES; row++)
    {
        for (int col = 1; col < MAXNODES; col++)
        {
            C[row][col] = INF;
            T[row][col].visited = false;
            T[row][col].dist = INF;
            T[row][col].path = 0;
        }
    }
}//end of function

/**
 * ----------------------destructor--------------------
 * Purpose:
 *  Destructor for the GraphM class
 * 
 * Parameters:
 *  None
 * ----------------------------------------------------
 */
GraphM::~GraphM()
{
    
}//end of function

/**
 * --------------------buildGraph------------------
 * Purpose:
 *  buildGraph reads the input file and builds the 
 *  hypothetical graph from the input
 * 
 * Parameters:
 *  -istream& input
 *      The istream object of the read text file
 * ------------------------------------------------
 */
void GraphM::buildGraph(istream& input)
{
    //initialize from, to, weight
    int from, to, weight;
    
    //first elemenf from the input file is the size of the graph
    input >> size;
    //checks if input size is in bound
    if(size >= MAXNODES)
    {
        cerr << "Number of vertexes in graph exceeds the maximum number of vertex allowed" << endl;
        size = 0;
        return;
    }    

    //when there's nothing left to read, stop
    if(input.eof())
        return;
    
    string line;
    getline(input, line);

    for(int i = 1; i <= size; i++)
        data[i].setData(input);

    //Goes through a loop that will stop 
    for(;;)
    {
        //gets the from and to value from input file
        input >> from >> to;
        //gets the weight from the input file;
        input >> weight;

        if(from == 0 && to == 0)
            return;

        //insert vertex to graph
        insertEdge(from, to, weight);
    }
}//end of function

/**
 * --------------------insertEdge---------------------
 * Purpose:
 *  insertEdge inserts values, based on the input text
 *  file, to the C 2d matrix which represents the 
 *  adjacency matrix.
 * 
 * Parameters:
 *  -int from:
 *      The starting point vertex
 *  -int to:
 *      The end point vertex
 *  -int weight
 *      The weight the distance from to to cost
 * ---------------------------------------------------
 */
bool GraphM::insertEdge(int from, int to, int weight)
{
    //Node can only be from 1 - 100
    //check if nodes are inbound or not
    if(size == 0)
        return false;

    if(from < 1 || to < 1)
        return false;
    
    //check if weight is bigger than 0
    if(weight <= 0)
        return false;
    
    //when inserting, from noded cannot be the same as to node
    if(from == to)
        return false;
    
    //Edge succesfully inserted
    C[from][to] = weight;
    return true;
}//end of function

/**
 * ------------------removeEdge----------------------
 * Purpose:
 *  removeEdge represents the act of removing a connection
 *  between two node. In this implementation, we assume
 *  that two nodes are not connected when they have a 
 *  distance value of INF, which is defined at the 
 *  beginning of the file
 * 
 * Parameter:
 *  -int from
 *      The starting point vertex 
 *  -int to
 *      The ending point vertex
 * -------------------------------------------------------
 */
bool GraphM::removeEdge(int from, int to)
{
    return insertEdge(from, to , INF);
}//end of function

/**
 * ------------findShortestPath-------------
 * Purpose:
 *  Applies the dijkstra's shortest path algorithm
 *  to put the shortest distance value in the 
 *  corresponding cell of all froms and tos vertexes
 *  They will be stored in the T matrix
 * 
 * Parameter:
 *  -None
 * ----------------------------------------
 */
void GraphM::findShortestPath()
{
    for(int from = 1; from <= size; from++)
    {
        T[from][from].dist = 0;
        T[from][from].visited = true;

        //get adjacency vector list from C
        for(int to = 1; to <= size; to++)
        {
            if(C[from][to] != INF)
            {
                T[from][to].dist = C[from][to];
                T[from][to].path = from;
            }
        }
        
        int adj;
        do
        {
            int minDist = INF;
            adj = -99;

            for(int to = 1; to <= size; to++)
            {
                if(!T[from][to].visited && C[from][to] < minDist)
                {
                    minDist = C[from][to];
                    adj = to;
                }
            }

            if(adj == -99) //when 
                break;
            
            //mark vertex as visited
            T[from][adj].visited = true;

            //n for neighbours
            for(int n = 1; n <= size; n++)
            {
                //skip for these cases
                //vertex already visited
                if(T[from][n].visited)
                    continue;
                if(C[adj][n] == INF)
                    continue;
                if(adj == n)
                    continue;
                
                int newDist;
                newDist = T[from][adj].dist + C[adj][n];
                if (T[from][n].dist > newDist)
                    {
                        T[from][n].dist = newDist;
                        T[from][n].path = adj;
                    }
            }
        }
        while (adj != -99); 
    }
}//end of function

/**
 * ---------------displayAll-------------------
 * Purpose:
 *  displayAll prints out the the current known
 *  distance between two vertexes, while also
 *  printing the starting vertex and ending
 *  vertex. Uses printPath() to do the printing
 * 
 *  This functions prints all distances from
 *  each vertex to every other vertexes. For
 *  individual path from two vertexes, refer to display()
 * 
 * Parameters:
 *  None
 * --------------------------------------------
 */
void GraphM::displayAll()
{
    cout << "Description" << setw(20) << "From node" << setw(10) << "To node"
        << setw(14) << "Dijkstra's" << setw(7) << "Path" << endl;

    for (int from = 1; from <= size; from++)
    {
        cout << data[from] << endl << endl;
        for (int to = 1; to <= size; to++)
        {
			//only print for different vertexes connection
            if (T[from][to].dist != 0)
            {
                cout << setw(27) << from;   
                cout << setw(10) << to;     

				//when there's no connection between the two vertexes
                if (T[from][to].dist == INF)
                    cout << setw(12) << "---" << endl; 
                else
                {
                    //prints the weight of the distance between vertexes
                    cout << setw(12) << T[from][to].dist;   
					cout << setw(10);
                    //prints the path of the shortest distance
                    printPath(from, to); 
                    cout << endl;
                }
            }
        }
    }
}//end of function

/**
 * ------------------display---------------------
 * Purpose:
 *  similar to displayAll, it prints out the current
 *  known distance between two vertexes (from, to)
 * 
 * Parameters:
 *  -int from
 *      the starting point vertex
 *  -int to
 *      the ending point vertex
 * ----------------------------------------------
 */
void GraphM::display(int from, int to)
{
	if ((from > size || from < 0) || (to > size || to < 0)) 
	{
		cout << setw(7) << from << setw(7) << to;  
		cout << setw(15) << "---" << endl; 
		return;
	}

	cout << setw(7) << from << setw(7) << to;  

	//when two vertexes are adjacent
	if (T[from][to].dist != INF)   
	{
		cout << setw(12) << T[from][to].dist << setw(15); 
		printPath(from, to);
        cout << endl; 
		printPathData(from, to); 
	}
	else    
		cout << setw(15) << "---" << endl;

	cout << endl;
}//end of function

/**
 * ----------------printPath------------------
 * Purpose:
 *  Helper method to print the path between
 *  two vertexes
 * 
 * Parameter
 *  -int from
 *      the starting point vertex
 *  -int to
 *      the end point vertex
 * ------------------------------------------
 */
void GraphM::printPath(int from, int to)
{
    //when two vertexes are not connected directly
	if (T[from][to].dist == INF)
        return;
    //when two vertexes are the same
    if (from == to)
    {
        cout << to << " ";  
        return;
    }

    int pathData = to; 
    printPath(from, T[from][to].path);
    cout << pathData << " ";   
}//end of function


/**
 * ------------------printPathData--------------  
 * Purpose:
 *  Similar to printPath but prints the data
 *  of the vertexes instead
 * 
 * Parameter:
 *  -int from
 *      the starting point vertex
 *  -int to
 *      the end point vertex
 * ---------------------------------------------
 */
void GraphM::printPathData(int from, int to)
{
	//When from and to are not connected
    if (T[from][to].dist == INF)
        return; 

    //when from and to are the same vertex
    if (from == to)
    {
        cout << data[to] << endl; 
        return;
    }

    int nodeData = to; 
    //Recursive part to print all data in path
    printPathData(from, T[from][to].path); 
    cout << data[nodeData] << endl << endl;  
}//end of function
