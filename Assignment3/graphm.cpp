#include "graphm.h"

GraphM::GraphM()
{
    size = 0; //num of vertexes
    for(int row = 1; row < MAXNODES; row++)
    {
        for(int col = 1; col < MAXNODES; col++)
        {
            C[row][col] = INF;
            T[row][col]->visited    = false;
            T[row][col]->dist       = INF;
            T[row][col]->path       = 0;
        }
    }
}

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

bool GraphM::removeEdge(int from, int to)
{
    C[from][to] = INF;
    return true;
}

void GraphM::findShortestPath()
{
    for(int source = 1; source <= size; source++)
    {
        T[source][source]->dist = 0;
        T[source][source]->visited = true;

        //labeling each row with weights
        for(int i = 1; i <= size; i++) //iterate through every other node
        {   
            if(C[source][i] != INF)
            {
                T[source][i]->dist = C[source][i];
                T[source][i]->path = source;
            }
        }

        int suv; //shortest unvisited
        do //looking at the same row that is T[source] every iteration
        {
            int minDist = INF; //initialize with biggest integer
            suv = 0;

            for(in to = 1; to <= size; to++)
            {   
                if(!T[source][to]->visited && C[source][to] < minDist)
                {
                    minDist = C[from][to];
                    suv = to;
                }
                // at the end of for loop we'll get the shortest, unvisited connection
            }

            if(suv = 0) //adj was unchanged
                break;
            
            T[source][suv]->visited = true;

            for(int n = 1; n <= size; n++)
            {
                if(T[source][n]->visited)
                    continue;
                
                if(C[suv][n] == INF)
                    continue;

                if(suv == n)
                    continue;

                int newDist;
                newDist = T[source][suv]->dist + C[suv][n];
                if(T[source][n]->dist > newDist)
                {
                    T[source][n]->dist = newDist;
                    T[source][n]->path = suv;
                }
            }
        } while (suv != 0);
        

    }
}