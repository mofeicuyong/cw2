
#include "SDL.h"
#include "clogic.h"

typedef struct
{
    Uint8 leftButtonPressed;
    Uint32 last_cursor_x;
    Uint32 last_cursor_y;
} mouseState;
typedef struct {
    Uint8 kButtonDown;
    Uint8 upButtonDown;
    Uint8 downButtonDown;
} buttons;

uint8_t paused = FALSE;
buttons keys = { FALSE };
int living_cells = 0;
int times;
Uint32 last_update_time = 0;
Uint32 ticks_per_lifecycle = 1000;
void update_button_states( buttons *bts, SDL_Event e, Uint8 isKeydown );
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

int checkEvents(int M,int N,int time)
{
	if ( !( ( SDL_GetTicks( ) - last_update_time ) < ticks_per_lifecycle ) && !paused&&times<time )
        {
        	times++;
            living_cells = updateGrid();
            last_update_time = SDL_GetTicks( );
        }
	while (SDL_PollEvent(&event)) 
	{
		if (event.type == SDL_QUIT) 
		{
			done = SDL_TRUE;
		}
		else if ( event.type == SDL_KEYDOWN || event.type == SDL_KEYUP )
            {
                Uint8 isKeydown = event.type == SDL_KEYDOWN;
                update_button_states( &keys, event, isKeydown);
                switch ( event.key.keysym.scancode )
                {
                case SDL_SCANCODE_SPACE:
                    paused = isKeydown ^ paused;
                    break;
                case SDL_SCANCODE_Q:
                    done = SDL_TRUE;
                    break;
                }

            }
		if ( keys.kButtonDown )
        {
            for (int x=0 ; x<M ; x++) 
	    	{
        		for (int y=0 ; y<N ; y++ ) 
				{
                	grid[x][y] = 0 ;  
           		}
        	}
            keys.kButtonDown = FALSE;
        }
		if ( keys.upButtonDown )
        {
            if ( ticks_per_lifecycle > 100 )
            {
                ticks_per_lifecycle -= 100;
            }
        }
        if ( keys.downButtonDown )
        {
            if ( ticks_per_lifecycle < 10000 )
            {
                ticks_per_lifecycle += 100;
            }
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


void update_button_states( buttons *bts, SDL_Event e, Uint8 isKeydown )
{
  switch ( e.key.keysym.scancode )
    {
    case SDL_SCANCODE_UP:
      bts->upButtonDown = isKeydown;
      break;
    case SDL_SCANCODE_DOWN:
      bts->downButtonDown = isKeydown;
      break;
    case SDL_SCANCODE_K:
      bts->kButtonDown = isKeydown;
      break;
    }
}
