#pragma once

/*
* Vertex.h
*
* Define class Vertex, representing the point on the board with the facing direction 
* List of var: 
* x,y = location of the vertex
* dx, dy = the direction
*
*/

#ifndef VERTEX_H
#define VERTEX_H

using namespace std;

class Vertex {
private:
 
public:
     int x, y;  // the location 
     int dx, dy;  // the facing direction
     bool ifedge; // if it is the edge of the board
     
     Vertex(int xx, int yy, int dxx, int dyy);  // constructor 
     ~Vertex();
};

#endif