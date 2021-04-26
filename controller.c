
#include "SDL.h"
#include "gameoflife.h"
#include "stdio.h"
/*do not change any of this*/
extern SDL_bool done;
int M,N;
int initialState;
int main(int argc, char* argv[])
{
	initGrid();
	initSDLWindow(M*CSIZE,N*CSIZE);
	drawGrid(M*CSIZE,N*CSIZE,M,N);
	while (!done)
	{
		checkEvents();
		updateGrid();
		drawGrid(M*CSIZE,N*CSIZE,M,N);
		SDL_Delay(1000); 
	}
	save();
	quitAll();
	return 0;
}
