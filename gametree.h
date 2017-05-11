#pragma once

#include "vertex.h"
#include "gamenode.h"

#include <vector>

using namespace std;

class gametree {
private:
     vector< vector< vector<Vertex*> > > boardvertex; // a 3-d vector containing the pointers to each vertex;

public:
     node* root; // initial position and direction
     node* curr; // current position and direction

     bool erasesteps(); // erase all game record (the tree and all node)
     bool initstep(int x, int y, int dir); // set the position and direction at beginning
     node* moveforward();
     node* turnright();
     node* turnleft();

     vector<node*> searchstepstotarget(int x, int y, int dir, int mxstp); // search all possible actions to the target position and direction, within max_steps.
     

     gametree(int sizeX, int sizeY);
     ~gametree();

};