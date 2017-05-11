#pragma once

#include <vector>
#include "vertex.h"


class node {
private:
     Vertex* pos;  // a pointer towards the vertex which defines the location and direction

public:
     node* parent; // To the previous step node
     vector<node*> children;  // To the node of the next step ; index 0 = forward, 1 = left, 2 = right
     int childidx; // index indicating the next step, using together with above vector: 0 : next step is the forward child of this node; 1 : left child ; 2 : right child


     int depth; // the depth from the root to this node ( can be regarded as number of steps
     int parentidx; // an index indicating the child relation towards the parent:
                    // -1: no parent ; 0: this node is the forward child of its parent; 1: is the left child of its parent; 2: the right child.

     // functions returning the 
     int getX();
     int getY();
     int getdX();
     int getdY();
     bool getifedge();

     node(Vertex* pos);
     ~node();

};
