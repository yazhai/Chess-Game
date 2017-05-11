
/*
* Vertex.cpp
*
*
*/

#include "Vertex.h"

Vertex::Vertex(int ix, int iy, int idx, int idy) {
     x = ix;
     y = iy;
     dx = idx;
     dy = idy;
     ifedge = false;
};

Vertex::~Vertex() {
};



