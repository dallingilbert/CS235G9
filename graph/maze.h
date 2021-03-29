/***********************************************************************
 * Component:
 *    Assignment 13, Maze
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Draw and solve a maze
 ************************************************************************/

#ifndef MAZE_H
#define MAZE_H

#include "graph.h"
#include "vector.h"

// solve the maze, the main program function
void solveMaze();

// read a maze in from a file
Graph readMaze(const char * fileName);

// display a maze on the screen
void drawMaze(const Graph & g, const custom :: vector <Vertex> & path);

#endif // MAZE_H
