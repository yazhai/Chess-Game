
// Code for playing a board game:
// A robot standing on a 8X8 board with one facing direction , and may have following actions:
// M: Move 1 square forward (no exceeding edges)
// L: Turn left
// R : Turn right
//
// Two kind of games:
// 1. Give a sequence of order (M,L,R) and print out the final position and facing
// 2. Give the final location, facing direction and max allowed steps, 
// print out all possible steps.
//
// The code is written as:
// 1. Generate a game board ( a 8x8x4 vertex , 
//        as each direction is represented by a different vertex);
// 2. Generate a game history tree (a ternary tree). 
//        The node on the tree reflects ONE (possible or actual) action of the robot: 
//        the location and its facing after N steps. 
//        So the node contains information: 
//             the correpsonding location and facing (the vertex)
//             the previous step
//             the next step, or possible steps
//             total steps until current step
// 3. In playing Game 1, insert the correct node after current node.
//        Results are given out by printing current vertex location and facing.
// 4. In playing Game 2, do a BFS within max_steps with all possible next steps at one node.
//        Note it is possible for the robot to take a recurrent route, such as inserting
//        left turn 4 times at one location. 
//        If the robot is not allowed to get to the same location with same facing direction
//        in one search, simply add a flag indicating if the node has been visited or not.
//        Results are printing out by reversed BFS result.
      
// Yaoguang Zhai
// 2017.04.17

#include "vertex.h"
#include "gamenode.h"
#include "gametree.h"

#include <list>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

extern char idx2dirName(int idx);
extern char dir2dirName(int x, int y);
extern int dir2idx(int x, int y);
extern int dirName2idx(char s);

int main() {

     int gametyp;
     int sizex, sizey;
     int ix, iy;
     char inidir;


     cout << "Welcome to the mini Robot Game" << endl;
     cout << "Please select the game to play:" << endl;
     cout << "  1: Move a robot on a chess board (default)" << endl;
     cout << "  2: Check all possible moves from one point to another" << endl;
     cin >> gametyp;

     cout << "Please specify the maximum dimension of x and y:" << endl;
     cin >> sizex >> sizey;

     if (gametyp == 1) {
          // Game  1
          bool restart = true;
          while (restart) {
               restart = false;
               cout << " =====  Game 1 starts ===== " << endl;
               cout << "Please specify the initial location of x/y: " << endl;
               cin >> ix >> iy;

               while ((ix > sizex) || (iy > sizey)) {
                    cout << "The initial location is out of range! Reinput initial x/y:" << endl;
                    cin >> ix >> iy;
               }

               cout << "Please specify the initial direction [N S E W] :" << endl;
               cin >> inidir;
               cin.ignore();

               gametree gamehist(sizex, sizey); // start the game 
               gamehist.initstep(ix, iy, dirName2idx(inidir));  // initialize the beginning status

               cout << "Please type in the command [M,L,R] / restart / quit :" << endl;
               string input;
               while ((getline(cin, input)) && (input != "quit") && (input != "Quit") && (input != "QUIT") && (input != "Q") && (input != "q") && (input != "restart") && (input != "RESTART") && (input != "Restart"))
               {
                    int i = 0;
                    for (auto it = input.begin(); it != input.end();it++)
                    {
                         if ((*it == 'M') || (*it == 'm')) {
                              gamehist.moveforward();
                         }
                         else if ((*it == 'L') || (*it == 'l')) {
                              gamehist.turnleft();
                         }
                         else if ((*it == 'R') || (*it == 'r')) {
                              gamehist.turnright();
                         }
                    }
                    cout << "After these steps, the robot is at : " << endl;
                    cout << " [ " << gamehist.curr->getX() + 1 << " , " << gamehist.curr->getY() + 1 << " ] , facing " << dir2dirName(gamehist.curr->getdX(), gamehist.curr->getdY()) << " direction. " << endl;
               }

               cout << "Good bye!" << endl;

               if ((input == "restart") || (input == "Restart") || (input == "RESTART")) {
                    restart = true;
               }
          }

     }
     else {
          // Game 2
          bool restart = true;
          while (restart) {
               restart = false;
               cout << " =====  Game 2 starts ===== " << endl;
               cout << "Please specify the initial location of x/y: " << endl;
               cin >> ix >> iy;

               while ((ix > sizex) || (iy > sizey)) {
                    cout << "The initial location is out of range! Reinput initial x/y:" << endl;
                    cin >> ix >> iy;
               }

               cout << "Please specify the initial direction [N S E W] :" << endl;
               cin >> inidir;
               cin.ignore();


               int ox, oy, maxstp;
               char odir;
               cout << "Please specify the target location of x/y: " << endl;
               cin >> ox >> oy;

               while ((ox > sizex) || (oy > sizey)) {
                    cout << "The target location is out of range! Reinput initial x/y:" << endl;
                    cin >> ox >> oy;
               }

               cout << "Please specify the target direction [N S E W] :" << endl;
               cin >> odir;

               cout << "Please specify max allowed step number: " << endl;
               cin >> maxstp;


               gametree gamehist(sizex, sizey); // start the game 
               gamehist.initstep(ix, iy, dirName2idx(inidir));  // initialize the beginning status
               vector<node*> searchresults = gamehist.searchstepstotarget(ox, oy, dirName2idx(odir), maxstp);

               int i = 0;
               for (auto oneresult = searchresults.begin(); oneresult != searchresults.end(); oneresult++) {
                    i++;
                    list<char> actions;
                    auto res = *oneresult;

                    while (res->parentidx >= 0)
                    {
                         if (res->parentidx == 0) {
                              actions.push_front('M');
                         }
                         else if (res->parentidx == 1) {
                              actions.push_front('L');
                         }
                         else if (res->parentidx == 2) {
                              actions.push_front('R');
                         }
                         res = res->parent;
                    }
                    cout << " Action - " << i << " : ";
                    for (auto it = actions.begin(); it != actions.end(); it++) {
                         cout << *it << " ";
                    }
                    cout << endl;
               }
               cout << "No more possible actions" << endl;
               cout << "Please tell me what to do next: restart / quit :" << endl;
               cin.ignore();
               string input;
               if ( (getline(cin, input)) && ((input == "restart") || (input == "Restart") || (input == "RESTART") || (input == "r") || (input == "R")) ) {
                    restart = true;
               }
               else {
                    cout << "Good bye !" << endl;
               };
          }
     }
}


