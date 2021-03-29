#include "graph.h"

int Graph::size() const
{
    return numElements;
}

bool Graph::empty()
{
    if (size() == 0)
        return true;
    else
        return false;
}

int Graph::capacity()
{
    return 0;
}

void Graph::clear()
{
    return;
}

void Graph::add(Vertex v1, Vertex v2)
{
    return;
}

bool Graph::isEdge(Vertex v1, Vertex v2) const
{
    return false;
}

template <class T>
custom::set<T> findEdges(Vertex v)
{
}

template <class T>
custom::list<T> findPath(Vertex v1, Vertex v2)
{
}