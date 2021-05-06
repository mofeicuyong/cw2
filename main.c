

#include "clogic.h"
#include "stdio.h"
#include "SDL.h"
/*do not change any of this*/
extern SDL_bool done;
int M,N;
int a;
int initialState;
int time;
int main(int argc, char* argv[])
{
printf("1£©choose how many number of steps could be taken.\n");
printf("2) keeps evolving until it is terminate\n");
printf("Your choice:");
scanf("%d",&a);
switch(a)
{
	case 1:
		printf("How many number of steps could be taken:");
		scanf("%d",&time);
		break;
	case 2:
		time=maxtime;
		break;
	default :
	printf("Invalid input\n");
}
	startgame();
	initSDLWindow(M*CSIZE,N*CSIZE);
	drawGrid(M*CSIZE,N*CSIZE,M,N);
	while (!done)
	{
		checkEvents(M,N,time);
		drawGrid(M*CSIZE,N*CSIZE,M,N);
	}
	save();
	quitAll();
	return 0;
}
