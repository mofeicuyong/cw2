
#include "stdio.h"
#include "clogic.h"
int M,N;
int grid[maxm][maxn]; 
      
int readfile() ; 

int startgame()
{      
	int initialState;
       for (int x=0 ; x<M ; x++) 
	    {
        	for (int y=0 ; y<N ; y++ ) 
			{
                grid[x][y] = 0 ;  
            }
        }
        printf("please choose:\n");
		printf("1)start a new world\n");
		printf("2)continue the old world\n");
		printf("your choice:");
		scanf("%d",&initialState);
     	if(initialState==2)
	   	{
    		readfile() ; 	            
      	}  
      	if(initialState==1)
      	{
      		printf("decide the row:");
			scanf("%d",&M);
			printf("decide the col:");
			scanf("%d",&N);
		}
       return 0;
}



int getNumberOfLiveNeighbors(int x, int y)
{        
   int neighbors = 0 ;            
   for(int i=x-1 ; i<=x+1 ; i++)
   {  
       for(int j=y-1 ; j<=y+1 ; j++)
	   {  
           if(!(i==x && j==y)&&(x>=0) && (y>=0)&& x<M && y<N)
		   {
               if(grid[i][j]==1)
			   {                   
                 neighbors ++ ;    		        
              }	
  	      }		
       }	 
    }	
    return neighbors;

}


int updateGrid()
{

   int neighbor[M][N];
   neighbor[M][N] = 0;                                  
   for(int x=0 ; x<M ; x++)
   {
       for(int y=0 ; y<N ; y++)
	   {
	   neighbor[x][y] = getNumberOfLiveNeighbors(x,y);   
       }
   } 
    for(int x=0 ; x<M ; x++)
	{
       for(int y=0; y<N ; y++)
	   {	
		   
	    if(grid[x][y]==1)
		{             
		
			if(neighbor[x][y]==1 || neighbor[x][y]==0 || neighbor[x][y]>3)
			{          
				grid[x][y]=0 ;             
				
			}
			 else if (neighbor[x][y]==3 || neighbor[x][y]==2)
			{                       
				grid[x][y]=1 ;            	
			}
	  

        }
		else if(grid[x][y]==0)
		{      
            if(neighbor[x][y]==3)
			{                                                   
	          grid[x][y]=1 ; 	     
	        }	   
        }		 
    	}
    }
   return 0;
}





void save()
{
	FILE *fp;
	fp=fopen("file.txt","w+");
	fprintf(fp,"%d %d",M,N);
	fprintf(fp,"\n");
	for (int x=0 ; x<M ; x++) 
	    {
        	for (int y=0 ; y<N ; y++ ) 
			{
				fprintf(fp,"%d ",grid[x][y]);
            }
            fprintf(fp,"\n");
        }	
    
} 




int readfile()
{ 
	FILE *fp;
	fp=fopen("file.txt","a+");
	fscanf(fp,"%d",&M);
	fscanf(fp,"%d",&N);
	for (int x=0 ; x<M ; x++) 
	    {
        	for (int y=0 ; y<N ; y++ ) 
			{
				fscanf(fp,"%d",&grid[x][y]);

            }
        }

}
	 
	 
	
	




















