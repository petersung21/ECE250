#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <iostream>
#include <limits>
#include "Exception.h"

/****************************************
 * UW User ID: phsung
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

class Weighted_graph {
	private:
		static const double INF;
        int numberofEdges;
        int sizeofGraph;
        double **graph_matrix;
        int *degreeofVertices;
        int *checkedNodes;

    
        struct Data {
            double weight;
            int vertex;
            Data(double w, int v)
            {
                weight = w;
                vertex = v;
            }
            Data()
            {
                
            }
        };
    
    
        Data *priorityQueue;
        int itemsInQueue;
        Data pop();
        void clearHeap();
        void heapify(int i);
        void insertHeap(double weight, int vertex);
    

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double minimum_spanning_tree( int );
		bool is_connected();

		void insert( int, int, double );


	friend std::ostream &operator << ( std::ostream &, Weighted_graph const & );
};

//Construct a weighted undirected graph with n vertices. Throw illegal_argument exception if the argument is less than 0.
Weighted_graph::Weighted_graph(int n)
{
    if (n < 0)
    {
        throw illegal_argument();
    }
    numberofEdges = 0;
    sizeofGraph = n;
    priorityQueue = new Data[n*n];
    degreeofVertices = new int[n]();
    checkedNodes = new int[n]();
    itemsInQueue = 0;
    graph_matrix = new double*[n];
    for (int i = 0; i < n ; i++)
    {
        graph_matrix[i] = new double[n];
    }
}

//Destructor. Clean up any allocated memory
Weighted_graph::~Weighted_graph()
{
    for (int i = 0; i<sizeofGraph ;i++)
    {
        delete[] graph_matrix[i];
    }
    sizeofGraph = 0;
    numberofEdges = 0;
    itemsInQueue = 0;
    delete[] graph_matrix;
    delete[] priorityQueue;
    delete[] degreeofVertices;
    delete[] checkedNodes;
}

//Pops the top of the heap (the minimum value) or in other words the priority queue
Weighted_graph::Data Weighted_graph::pop()
{
    if (itemsInQueue > 0)
    {
        Data root = priorityQueue[0];
        priorityQueue[0] = priorityQueue[itemsInQueue - 1];
        itemsInQueue = itemsInQueue - 1;
        heapify(0);
        return root;
    }
    return Data();
}

//Inserts an element into the heap. Receives the weight and vertex as parameters
void Weighted_graph::insertHeap(double w, int v)
{
    priorityQueue[itemsInQueue] = Data(w,v);
    
    
    itemsInQueue++;
    
    for (int i = itemsInQueue/2 - 1; i>=0 ;i--)
    {
        heapify(i);
    }
    
    
}


//Heapifies the array. Receives the index as a parameter
void Weighted_graph::heapify(int i)
{
    int smallestChild;
    
    Data root = priorityQueue[i];
    
    while(i < itemsInQueue/2)
    {
        int lChild = 2 * i + 1;
        int rChild = lChild + 1;
        
        if (priorityQueue[lChild].weight > priorityQueue[rChild].weight && rChild < itemsInQueue && lChild < itemsInQueue)
        {
            smallestChild = rChild;
        }
        else
        {
            smallestChild = lChild;
        }
        
        if (root.weight <= priorityQueue[smallestChild].weight)
        {
            break;
        }
        
        priorityQueue[i] = priorityQueue[smallestChild];
        i = smallestChild;
        
    }
    
    priorityQueue[i] = root;
    
}

//Sets the value of infinity to be used in the graph
const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

//Returns the degree of the vertex n. Throw illegal_argument exception if the argument does not correspond to an existing vertex
//Runs in O(1) time
int Weighted_graph::degree(int n) const
{
    if(n >= sizeofGraph || n < 0)
    {
        throw illegal_argument();
    }
    return degreeofVertices[n];
}

//Returns the weight of the edge connecting vertices m and n. If the vertices are equal, return 0.
//If the vertices are not adjacent, return infinity
//Runs in O(1) time
double Weighted_graph::adjacent(int m, int n) const
{
    if(m>=sizeofGraph || n >= sizeofGraph || m < 0 || n < 0)
    {
        throw illegal_argument();
    }
    if(m==n)
    {
        return 0;
    }
    if(graph_matrix[m][n] == 0)
    {
        return INF;
    }
    
    return graph_matrix[m][n];
    
}

//Returns the size of the minimum spanning tree of those nodes which are connected to vertex m.
//Throw an illegal_argument exception if the arguments do not correspond to existing vertices.
//Runs in O(n^2lgn) time. nlgn for the heap * n vertices
double Weighted_graph::minimum_spanning_tree(int m)
{
    if(m>=sizeofGraph || m < 0)
    {
        throw illegal_argument();
    }
    
    double size = 0;
    
    for (int i = 0; i < sizeofGraph ;i++)
    {
        if (graph_matrix[m][i] > 0)
        {
            insertHeap(graph_matrix[m][i],i);
        }
    }
    
    checkedNodes[m] = 1;
    
    while(itemsInQueue > 0)
    {
        Data nextNode = pop();
        for (int i=0; i<sizeofGraph ;i++)
        {
            if (graph_matrix[nextNode.vertex][i] > 0 && checkedNodes[i] != 1)
            {
                insertHeap(graph_matrix[nextNode.vertex][i],i);
            }
        }
        if (checkedNodes[nextNode.vertex] != 1)
        {
            size = size + nextNode.weight;
        }
        checkedNodes[nextNode.vertex] = 1;
    }
    
    clearHeap();
    
    return size;
}

//Clears the heap after use
void Weighted_graph::clearHeap()
{
    for(int i = 0; i<sizeofGraph ;i++)
    {
        checkedNodes[i] = 0;
        priorityQueue[i] = Data();
    }
    itemsInQueue = 0;
}

//Returns true if the graph is connected. False otherwise
//Runs in O(n^2lgn) time. nlgn for the heap * n vertices
bool Weighted_graph::is_connected()
{
    bool isConnected = true;
    
    if (sizeofGraph <= 0)
    {
        return false;
    }
    
    for (int i = 0; i < sizeofGraph ;i++)
    {
        if (graph_matrix[0][i] > 0)
        {
            insertHeap(graph_matrix[0][i],i);
        }
    }
    
    checkedNodes[0] = 1;
    
    while(itemsInQueue > 0)
    {
        Data nextNode = pop();
        for (int i=0; i<sizeofGraph ;i++)
        {
            if (graph_matrix[nextNode.vertex][i] > 0 && checkedNodes[i] != 1)
            {
                insertHeap(graph_matrix[nextNode.vertex][i],i);
            }
        }
        checkedNodes[nextNode.vertex] = 1;
    }
    
    for (int i=0; i<sizeofGraph ;i++ )
    {
        if(checkedNodes[i] == 0)
        {
            isConnected = false;
            break;
        }
    }
    
    clearHeap();
    
    return isConnected;
}



//Returns the number of edges in the graph.
int Weighted_graph::edge_count() const
{
    return numberofEdges;
}

//If the weight w < 0 or w = ∞, throw illegal_argument exception.
//If the weight w is 0, remove any edge between m and n (if any).
//Otherwise, add an edge between vertices m and n with weight w.
//If an edge already exists, replace the weight of the edge with the new weight.
//If the vertices do not exist or are equal, throw illegal_argument exception.
//Runs in O(1) time
void Weighted_graph::insert(int m, int n, double w)
{
    if (w < 0 || w == INF)
    {
        throw illegal_argument();
    }
    
    if(m == n || m>=sizeofGraph || n >= sizeofGraph || m < 0 || n < 0)
    {
        throw illegal_argument();
    }
    if (w == 0)
    {
        degreeofVertices[m] = degreeofVertices[m] - 1;
        degreeofVertices[n] = degreeofVertices[n] - 1;
        numberofEdges--;
    }
    else if (graph_matrix[m][n] == 0 || graph_matrix[n][m] == 0)
    {
        degreeofVertices[m] = degreeofVertices[m] + 1;
        degreeofVertices[n] = degreeofVertices[n] + 1;
        numberofEdges++;
    }
    
    graph_matrix[m][n] = w;
    graph_matrix[n][m] = w;
    
    
    
    
}

std::ostream &operator << ( std::ostream &out, Weighted_graph const &graph ) {

	return out;
}

#endif
