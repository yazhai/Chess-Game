#include "vertex.h"
#include "gamenode.h"

using namespace std;

node::node(Vertex* atpos) {
     pos = atpos;
     parent = nullptr;

     children.assign(3, nullptr);

     depth = 0;
     childidx = -1;
     parentidx = -1;
}

node::~node() {
     if (children[0]) { delete children[0]; }
     if (children[1]) { delete children[1]; }
     if (children[2]) { delete children[2]; }
}

int node::getX() {
     return pos->x;
}

int node::getY() {
     return pos->y;
}

int node::getdX() {
     return pos->dx;
}

int node::getdY() {
     return pos->dy;
}

bool node::getifedge() {
     return pos->ifedge;
}