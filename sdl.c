
#include "SDL.h"
#include "clogic.h"

typedef struct
{
    Uint8 leftButtonPressed;
    Uint32 last_cursor_x;
    Uint32 last_cursor_y;
} mouseState;
mouseState mouse = { FALSE, (Uint16)-1, (Uint16)-1 };
SDL_bool done = SDL_TRUE; 	
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event event;
int initSDLWindow(int windowHeight,int windowWidth)
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0) 
	{
		if (SDL_CreateWindowAndRenderer(windowHeight+1, windowWidth+1,0, &window, &renderer) == 0) 
		{
			SDL_SetWindowTitle(window, "Game Of Life ");
			done = SDL_FALSE;
		}
	}
	return done;
}
int drawGrid(int windowHeight,int windowWidth,int M,int N)
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			SDL_Rect rect = {CSIZE*j,CSIZE*(i),CSIZE*(j+1),CSIZE*(i+1)};
			if (grid[i][j] == 0)
			{
				SDL_SetRenderDrawColor(renderer, 0,0,0, SDL_ALPHA_OPAQUE);
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 255, 165,0, SDL_ALPHA_OPAQUE);
			}
			SDL_RenderFillRect(renderer,&rect);
		}
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	for (int x = 0; x <= windowWidth; x = x+CSIZE)
	{
		SDL_RenderDrawLine(renderer,0, x, windowHeight, x);
	}
	for (int y = 0; y <= windowHeight; y = y+CSIZE)
	{
		SDL_RenderDrawLine(renderer,y,0, y, windowWidth);
	}
	SDL_RenderPresent(renderer);
	return 0;
}

int checkEvents()
{
	while (SDL_PollEvent(&event)) 
	{
		if (event.type == SDL_QUIT) 
		{
			done = SDL_TRUE;
		}
		
                 else if ( event.type == SDL_MOUSEBUTTONUP )
            {
                mouse.leftButtonPressed = FALSE;
                mouse.last_cursor_x = mouse.last_cursor_y = (Uint16)-1;
            }
            else if ( event.type == SDL_MOUSEBUTTONDOWN )
            {
                mouse.leftButtonPressed = TRUE;
            }
            if ( mouse.leftButtonPressed )
        {
            int cursor_x, cursor_y;
            SDL_GetMouseState( &cursor_x, &cursor_y );
            // change the cell state if the mouse points to a new cell
            if ( !( cursor_x /CSIZE == mouse.last_cursor_x / CSIZE && 
			cursor_y /CSIZE == mouse.last_cursor_y / CSIZE ) )
            {
            	
                Uint32 row =  cursor_y / CSIZE;
                Uint32 column = cursor_x / CSIZE;
                if(grid[row][column]==1)
                {
                grid[row][column]=0;
            	}
                else
                grid[row][column]=1;
                mouse.last_cursor_x = cursor_x;
                mouse.last_cursor_y = cursor_y;
            }
        }
            
	}
	return done;
}

int quitAll()
{
	if (renderer) 
	{
		SDL_DestroyRenderer(renderer);
	}
	if (window) 
	{
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
	return 0;
}

