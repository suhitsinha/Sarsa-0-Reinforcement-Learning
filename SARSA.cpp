#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>


int main(int argc, char **argv)
{

	int rowNum = 7;
	int colNum = 10;
	//0- UP 1- Right 2- Down 3- Left
	int actionNum = 4;
	long int i, j ,k, epi = 0;
	int goalX = 3, goalY = 7, satrtX= 3, starty = 0, currX = 3, currY = 0, nextX, nextY, currAction, nextAction;
	int windSpeed[10] = {0,0,0,1,1,1,2,2,1,0};
	long int episodNum = 2000;
	long int epiByTime[episodNum];
	long int timeElapsed = 0;
	double eph = 0.35, randval, alpha = 0.35;

	if(argc > 1)
	{
		episodNum = atoi(argv[1]);	
	}

	double actionStateValue[rowNum][colNum][actionNum];

	// Initilization to 0
	for (i = 0; i < rowNum ; i++ )
	{
		for (j = 0; j < colNum ; j++ )
		{
			for (k = 0; k < actionNum ; k++ )
			{
				actionStateValue[i][j][k] = 0;
			}
		}
	
	}
	
	srand( (unsigned)time( NULL ) );
	while (epi < episodNum)
	{
		currX = 3;
		currY = 0;

		//Initialize the curr action
		randval = ((double)rand() / (double)RAND_MAX);
		//printf("random value = %f\n", randval);
		if(randval > eph)
		{
			currAction = 0;
			for(i = 1; i < actionNum; i++)
			{
				if(actionStateValue[currX][currY][currAction] < actionStateValue[currX][currY][i])
					currAction = i;
			}
		}
		else
		{
			randval = ((double)rand() / (double)RAND_MAX);
			if(randval < 0.25)
				currAction = 0;
			else if(randval < 0.5)
				currAction = 1;	
			else if(randval < 0.75)
				currAction = 2;	
			else
				currAction = 3;
		}

		//printf("Action = %d\n",currAction);

		while(currX != goalX || currY != goalY )
		{
/************************************Find the next state*************************************/

			if (currAction == 0)
			{
				if(currX == 0)
				{
					nextX = 0;
					nextY = currY;
				}
				else if(currX - 1 - windSpeed[currY] >= 0)
				{
					nextX = currX - 1 - windSpeed[currY];
					nextY = currY;
					timeElapsed++;
				}
				else
				{
					nextX = 0;
					nextY = currY;
					timeElapsed++;
				}

			}

			else if (currAction == 1)
			{
				if(currY == colNum - 1)
				{
					nextY = currY;
				}
				else
				{
					nextY = currY + 1;
					timeElapsed++;
				}

				if(currY == colNum - 1)
				{
					nextX = currX;
				}
				else if(currX - windSpeed[currY] >= 0)
				{
					nextX = currX - windSpeed[currY];
				}
				else
				{
					nextX = 0;
				}
			}

			else if (currAction == 2)
			{
				if(currX == rowNum - 1)
				{
					nextX = currX;
				}
				else if(currX + 1 - windSpeed[currY] < rowNum && currX + 1 - windSpeed[currY] >= 0)
				{
					nextX = currX + 1 - windSpeed[currY];
					timeElapsed++;
				}
				else if(currX + 1 - windSpeed[currY] >= rowNum)
				{
					nextX = rowNum - 1;
					timeElapsed++;
				}
				else
				{
					nextX = 0;
					timeElapsed++;
				}
				
				nextY = currY;
			}

			else
			{
				if(currY == 0)
				{
					nextY = currY;
				}
				else
				{
					nextY = currY - 1;
					timeElapsed++;
				}
				
				if(currX - windSpeed[currY] >= 0)
				{
					nextX = currX - windSpeed[currY];
				}
				else
				{
					nextX = 0;
				}
			}

/*************************************End of finding next state****************************************************/

/*************************************Find next action a'***********************************************************/	

			if(((double)rand() / (double)RAND_MAX) > eph)
			{
				nextAction = 0;
				for(i = 1; i < actionNum; i++)
				{
					if(actionStateValue[nextX][nextY][nextAction] < actionStateValue[currX][currY][i])
						nextAction = i;
				}
			}
			else
			{
				randval = ((double)rand() / (double)RAND_MAX);
				if(randval < 0.25)
					nextAction = 0;
				else if(randval < 0.5)
					nextAction = 1;	
				else if(randval < 0.75)
					nextAction = 2;	
				else
					nextAction = 3;
			}

/*********************************End of finding next action a'****************************************/

/*********************************Fnding state action pair value using TD(0)***************************/

			actionStateValue[currX][currY][currAction] = actionStateValue[currX][currY][currAction] + 
			alpha * (-1 + actionStateValue[nextX][nextY][nextAction] - actionStateValue[currX][currY][currAction]);



/********************************END**********************************************************************/

			
			currX = nextX;
			currY = nextY;
			currAction = nextAction;

		} 
		epiByTime[epi] = timeElapsed;
		epi ++;
		
	}

	FILE *fptr;
	fptr=(fopen("4action.txt","w"));
	if(fptr==NULL){
		printf("Error!");
		exit(1);
	}
	fprintf(fptr,"0\t0\n");
	for(i = 0; i < episodNum; i++)
	{
		fprintf(fptr,"%ld\t%ld\n",i+1,epiByTime[i]);
	}


	fclose(fptr);
	return 0;
}





















