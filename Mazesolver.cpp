#include<bits/stdc++.h>
#include <algorithm>
using namespace std;
//Initializing the size of maze
static const int N = 20;
//Our Maze intiliazied with 0's
int Maze[N][N];
int path[N][N];
int endx,endy;

void CreateBoundary(){
    /*We create a border for the grid
      so as to have a boundary and the path
      does not go out of it
    */
    for(int i=0;i<N;i++){
        Maze[0][i]=1;
        Maze[N-1][i]=1;
        Maze[i][0]=1;
        Maze[i][N-1]=1;
    }

}

void CreateMaze(){
    //Using this vector pair as a queue of all visiting nodes
    vector<pair<int,int> >v;
    pair<int,int>p;
    //starting at a random index and applying prims algorithm
    p=make_pair(2,2);//this index could be random
    v.push_back(p);
    //Till the queue becomes null
    //i.e. all nodes in grid are observed
    while(v.size()){
        // randomly selecting a node from the queue
        int z=rand()%v.size();
        int x=v[z].first;
        int y=v[z].second;
        //checking if there is only 1 way to this node
        int count=0;
        if(Maze[x-1][y])count++;
        if(Maze[x+1][y])count++;
        if(Maze[x][y-1])count++;
        if(Maze[x][y+1])count++;
        /*if it has only 1 neighboring road,
          make a pair of indexes of walls adjacent to it
          and push it into the queue which later again
          calls through the same process.
        */
        if(count<=1){
            Maze[x][y]=1;
            if(!Maze[x-1][y])p=make_pair(x-1,y),v.push_back(p);
            if(!Maze[x+1][y])p=make_pair(x+1,y),v.push_back(p);
            if(!Maze[x][y-1])p=make_pair(x,y-1),v.push_back(p);
            if(!Maze[x][y+1])p=make_pair(x,y+1),v.push_back(p);
        }
        //then removing the block we performed this action now
        v.erase(v.begin()+z);
    }
    // this continuous process sees that all nodes are checked at least once
}

void CreateEntryEnd(){
    // This is the entry point in the graph
    Maze[2][1] = 1;
    // creating an exit point such that there is a path to it
    for (int i = N - 3; i >= 0; i--) {
		if (Maze[i][N - 3] == 1) {
			Maze[i][N - 2] = 1;
			endx=i;
			endy=N-2;
			break;
		}
    }
}

void PrintGraph(){
    /* All the nodes are printed with wall
       being a * and road being space->" ".
    */
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(i==2&&j==1){
                    cout<<" S ";
                    continue;
            }
            if(i==endx&&j==endy){
                    cout<<" E ";
                    continue;
            }
            if(Maze[i][j]) cout<<"   ";
            else cout<<" # ";
        }
        cout<<"\n";
    }
}

bool isSafe(int x, int y)
{
    // if (x, y outside maze) return false
    if (
        x > 0 && x < N-1 && y > 0
        && y < N-1 && Maze[x][y] == 1)
        return true;

    return false;
}
void printSolution(int sol[N][N])
{
    int i,j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++){
            if(i==2&&j==1){
                    cout<<" S ";
                    continue;
            }
            if(i==endx&&j==endy){
                    cout<<" E ";
                    continue;
            }
            if(sol[i][j]){
                printf(" + ");
                continue;
            }
            if(Maze[i][j]==0)cout<<" # ";
            else cout<<"   ";
        }
        printf("\n");
    }
}


bool solveMazeUtil(
    int x,
    int y, int sol[N][N])
{
    // if (x, y is goal) return true
    if (
        x == endx && y == endy
        && Maze[x][y] == 1) {
        sol[x][y] = 1;
        return true;
    }

    // Check if maze[x][y] is valid
    if (isSafe(x, y) == true) {
          // Check if the current block is already part of solution path.
          if (sol[x][y] == 1)
              return false;

        // mark x, y as part of solution path
        sol[x][y] = 1;

        /* Move forward in x direction */
        if (solveMazeUtil(
                x + 1, y, sol)
            == true)
            return true;

        /* If moving in x direction
        doesn't give solution then
        Move down in y direction */
        if (solveMazeUtil(
                x, y + 1, sol)
            == true)
            return true;

        /* If moving in y direction
        doesn't give solution then
        Move back in x direction */
        if (solveMazeUtil(
                x - 1, y, sol)
            == true)
            return true;

        /* If moving backwards in x direction
        doesn't give solution then
        Move upwards in y direction */
        if (solveMazeUtil(
                x, y - 1, sol)
            == true)
            return true;

        /* If none of the above movements
        work then BACKTRACK: unmark
        x, y as part of solution path */
        sol[x][y] = 0;
        return false;
    }

    return false;
}

bool solveMaze()
{
    int sol[N][N];
    memset(sol,0,sizeof(sol));

    if (solveMazeUtil(
            2,1, sol)
        == false) {
        printf("Solution doesn't exist");
        return false;
    }

    printSolution(sol);
    return true;
}

int main(){
    //Function to Create the Boundary of the grid
    CreateBoundary();
    //Function to create the maze
    CreateMaze();
    //Function to give a entry point and an finishing point
    CreateEntryEnd();
    //Function to print the full graph
    PrintGraph();
    //A random Maze is printed of required size with a start and end point...
    solveMaze();
    return 0;
}
