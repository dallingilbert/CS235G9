/*****************************************************
 * Graph
 * Header: Graph
 * Definition: This is our graph class
 *****************************************************/
#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
#include "vertex.h"
#include "set.h"
#include "list.h"

#ifndef GRAPH_H
#define GRAPH_H

class Graph
{

private:
    // member variables
    bool *matrix;
    int numElements;

public:

    // non-default constructor
    Graph(int n)
    {
        matrix = NULL;
        
        matrix = new bool [n * n];

        for (int i = 0; i < (n * n); i++)
        {
            matrix[i] = false;
        }

        numElements = n;
    }

    // destructor
    ~Graph()
    {
        if (matrix != NULL)
            delete matrix;
    }

    // copy constructor
    Graph(const Graph& rhs)
    {
        matrix = rhs.matrix;
        numElements = rhs.numElements;
    }

    // assignment operator
    Graph &operator=(Graph &rhs)
    {   
        matrix = rhs.matrix;
        numElements = rhs.numElements;

        return *this;
    }

    // member methods
    int size() const;
    bool empty();
    int capacity();
    void clear();
    void add(Vertex v1, Vertex v2);
    bool isEdge(Vertex v1, Vertex v2) const;

    template <class T>
    custom::set<T> findEdges(Vertex v);

    template <class T>
    custom::list<T> findPath(Vertex v1, Vertex v2);

};

#endif // GRAPH_H
