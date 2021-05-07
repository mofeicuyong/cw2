#include "unity.h"
#include<stdlib.h>
#include<string.h>
#include <stdio.h>
#include "clogic.h"



void setUp(){

}
void tearDown(){

}

void test4()
{
	int a =getNumberOfLiveNeighbors(-2,-2);
    TEST_ASSERT_EQUAL_INT_MESSAGE (-1, a,"something went wrong.");
}
void test2()
{
	readfile();
    int a=updateGrid();
    int a1 = grid[1][1];
    TEST_ASSERT_EQUAL_INT_MESSAGE (0, a,"something went wrong.");

}
void test1()
{
	readfile();
    int a1 = grid[1][1];
    TEST_ASSERT_EQUAL_INT_MESSAGE (0, a1,"can not updategrid successfully.");
}
void test3()
{
	int M=20;
	int N=20;
	int grid[20][20];
	for (int x=0 ; x<20 ; x++) 
	    {
        	for (int y=0 ; y<20 ; y++ ) 
			{
                grid[x][y] = 0 ;  
            }
        }
        int a =save();
      TEST_ASSERT_EQUAL_INT_MESSAGE (0, a,"something went wrong.");  
}
void test5()
{
	int a=readfile();
	TEST_ASSERT_EQUAL_INT_MESSAGE (0, a,"something went wrong.");  
}
int main() 
{
  UNITY_BEGIN();
  RUN_TEST(test1);
  RUN_TEST(test2);
  RUN_TEST(test3);
  RUN_TEST(test4);
  RUN_TEST(test5);
  return UNITY_END();
}
