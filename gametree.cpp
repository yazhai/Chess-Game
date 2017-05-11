#include "vertex.h"
#include "gamenode.h"
#include "gametree.h"

#include <vector>
#include <queue>

using namespace std;

extern int dir2idx(int x, int y);

gametree::gametree(int sizeX, int sizeY) {
     // initialize the board
     for(int ii=0;ii<sizeX;ii++){
          vector<vector<Vertex*>> col;
          for (int jj = 0; jj < sizeY;jj++) {
               vector<Vertex*> dim;
               Vertex* E = new Vertex(ii, jj , 1, 0);
               Vertex* S = new Vertex(ii, jj, 0, -1);
               Vertex* W = new Vertex(ii, jj, -1, 0);
               Vertex* N = new Vertex(ii, jj, 0, 1);
               dim.push_back(E);
               dim.push_back(S);
               dim.push_back(W);
               dim.push_back(N);
               col.push_back(dim);
          }
          boardvertex.push_back(col);
     }

     for (int ii = 0;ii < sizeX;ii++) {
          boardvertex[ii][0][1]->ifedge = true;
          boardvertex[ii][sizeY - 1][3]->ifedge = true;
     }
     for (int jj = 0; jj < sizeY;jj++) {
          boardvertex[0][jj][2]->ifedge = true;
          boardvertex[sizeX-1][jj][0]->ifedge = true;
     }

     // initialize the beginning position and direction, default to the (1,1) towards E;
     root = nullptr;
     curr = nullptr;
}

gametree::~gametree() {
     erasesteps();
     for (int ii = 0;ii<boardvertex.size();ii++) {
          for (int jj = 0; jj < boardvertex[ii].size();jj++) {
               for (int kk = 0; kk < 4; kk++) {
                    delete boardvertex[ii][jj][kk];
               }
          }
     }
}

bool gametree::erasesteps() {
     curr = nullptr;
     delete root;
     return true;
}

bool gametree::initstep(int ix, int iy, int id){
     erasesteps();
     ix--;  // note: input coordinate on chessboard is [1 8][1 8], while in the code is [0 7][0 7]
     iy--;
     if (boardvertex[ix][iy][id]) {
          root = new node(boardvertex[ix][iy][id]);
          curr = root;
          return true;
     }
     return false;
}

node* gametree::moveforward() {
     // move forwards action is based on curr*
     // test if it is the edge; if not, create a new node in the direction and move the curr* towards it
     // save the parent/child relation, and increase the depth in the meantime.
     if (!curr->getifedge()) {
          int x = curr->getX();
          int y = curr->getY();
          int dx = curr->getdX();
          int dy = curr->getdY();
          int idx = dir2idx(dx, dy);
          node* tmp = new node(boardvertex[x + dx][y + dy][idx]);
          curr->childidx = 0;
          curr->children[curr->childidx] = tmp;
          tmp->parent = curr;
          tmp->depth = curr->depth+1;
          tmp->parentidx = 0;
          curr = tmp;
          return curr;
     }
     return curr;
}

node* gametree::turnleft() {
     // turn left action is based on curr*
     // create a new node in the left direction and move the curr* towards it
     // save the parent/child relation, and increase the depth in the meantime.
     int x = curr->getX();
     int y = curr->getY();
     int dx = curr->getdX();
     int dy = curr->getdY();
     int idx = dir2idx(dx, dy);
     idx--;
     if (idx == -1) { idx = 3; };
     node* tmp = new node(boardvertex[x ][y ][idx]);
     curr->childidx = 1;
     curr->children[curr->childidx] = tmp;
     tmp->parent = curr;
     tmp->depth = curr->depth + 1;
     tmp->parentidx = 1;
     curr = tmp;
     return curr;
}

node* gametree::turnright() {
     // turn right action is based on curr*
     // create a new node in the right direction and move the curr* towards it
     // save the parent/child relation, and increase the depth in the meantime.
     int x = curr->getX();
     int y = curr->getY();
     int dx = curr->getdX();
     int dy = curr->getdY();
     int idx = dir2idx(dx, dy);
     idx++;
     if (idx == 4) { idx = 0; };
     node* tmp = new node(boardvertex[x][y][idx]);
     curr->childidx = 2;
     curr->children[curr->childidx] = tmp;
     tmp->parent = curr;
     tmp->depth = curr->depth + 1;
     tmp->parentidx = 2;
     curr = tmp;
     return curr;
}

vector<node*> gametree::searchstepstotarget(int tox, int toy, int todir, int mxstp) {
     // search ALL possible actions to the target node, including recurrence steps, such as four leftturns at one position
     tox--;  // note: input coordinate on chessboard is [1 8][1 8], while in the code is [0 7][0 7]
     toy--;

     // To return: the result vector
     vector<node*> searchresults;
     searchresults.clear();
     if ((root->getX() == tox) && (root->getY() == toy) && (dir2idx(root->getdX(), root->getdY()) == todir)) {
          searchresults.push_back(root);
     }

     // This is the nodes queue that needs to be checked.
     queue<node*> checklist;
     checklist.push(root);

     // By a BFS, the node's possible left/forward/right children are pushed into this lists, unless if the child hits target node, or exceeds max_stp
     while (!checklist.empty()) {
          // Pop front from the queue
          node* tmp = checklist.front();
          checklist.pop();

          // check forward child
          curr = tmp;
          node* fwd = moveforward();
          if (fwd != tmp) {
               int fx = fwd->getX();
               int fy = fwd->getY();
               int fdx = fwd->getdX();
               int fdy = fwd->getdY();
               int fidx = dir2idx(fdx, fdy);
               if ((fx == tox) && (fy == toy) && (fidx == todir)) {
                    // hits target, then save to result list
                    searchresults.push_back(fwd);
               }
               else {
                    if (fwd->depth < mxstp) {
                         // otherwise, push to check list if not exceeds max_stp
                         checklist.push(fwd);
                    }
               }
          }

          curr = tmp;
          node* lft = turnleft(); // the left child should always exist
          if (lft) {
               int fx = lft->getX();
               int fy = lft->getY();
               int fdx = lft->getdX();
               int fdy = lft->getdY();
               int fidx = dir2idx(fdx, fdy);
               if ((fx == tox) && (fy == toy) && (fidx == todir)) {
                    // hits target, then save to result list
                    searchresults.push_back(lft);
               }
               else {
                    if (lft->depth < mxstp) {
                         // otherwise, push to check list if not exceeds max_stp
                         checklist.push(lft);
                    }
               }
          }

          curr = tmp;
          node* rgt = turnright(); // redo for right child
          if (rgt) {
               int fx = rgt->getX();
               int fy = rgt->getY();
               int fdx = rgt->getdX();
               int fdy = rgt->getdY();
               int fidx = dir2idx(fdx, fdy);
               if ((fx == tox) && (fy == toy) && (fidx == todir)) {
                    // hits target, then save to result list
                    searchresults.push_back(rgt);
               }
               else {
                    if (rgt->depth < mxstp) {
                         // otherwise, push to check list if not exceeds max_stp
                         checklist.push(rgt);
                    }
               }
          }
     }
     return searchresults;
}