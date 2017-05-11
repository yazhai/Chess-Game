# Chess-Game
The code is structured by a ternary tree. 
The board is defined with 8x8x4 [maxX x maxY x 4 directions] possible board point. 
The node on the game tree contains one of these board point, together with its previous step (as parent) and next (possible) step(s) (as children). 
Two games are possible to be play with:

Version 1- Given a starting position [x,y] (0<x,y<9), initial direction faced (W, S, N, E) on 8 x 8 square board and sequence of actions for a robot, print the outcome; direction faced and position on the board.
Allowed Actions: 
M: Move 1 square forward
L: Turn left
R: Turn right
Note: When/if robot comes to the end of the board it cannot move beyond the board boundaries. At a boundary, it can only turn left/right.  
Example input: 
Location: [2,3]
Direction faced: N
Actions: M,M,M,L,M,R,R,R
Output:
Location : [1,6]
Direction faced:S
  
Version 2- Given a starting position [x,y] (0<x,y<9), initial direction faced (W, S, N, E) on 8 x 8 square board and the target position, direction and maximum actions allowed, print all possible actions robot can make to get to that position.
Allowed Actions: 
M: Move 1 square forward
L: Turn left
R: Turn right
Note: When/if robot comes to the end of the board it cannot move beyond the board boundaries. At a boundary, it can only turn left/right.  
Example input: 
Original position: [2,3]
Original Direction faced: N
Target position: [3,4]
Target Direction: S
Maximum actions allowed: 4
Output:
Actions - 1 : M,R,M,R
No more possible actions!

