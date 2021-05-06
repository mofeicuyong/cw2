
#ifndef GAMEOFLIFE_H_
#define GAMEOFLIFE_H_

#include <stdint.h>
#define FALSE 0
#define TRUE 1

#define CSIZE 10  
#define maxm 1080
#define maxn 1080
int grid[maxm][maxn];
int getNumberOfLiveNeighbors(int x, int y);
int updateGrid();
int startgame();
int drawGrid(int windowHeight,int windowWidth,int M,int N);
int initSDLWindow(int windowHeight,int windowWidth);
int quitAll();
int checkEvents();
int save();
#endif 
