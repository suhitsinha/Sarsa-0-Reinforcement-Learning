#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>


int windSpeed[10] = {0,0,0,1,1,1,2,2,1,0};
int rowNum = 7;
int colNum = 10;

int up(int currX)
{
	int nextX;
	if(currX - 1 >= 0)
	{
		nextX = currX - 1;
	}
	else
	{
		nextX = 0;
	}
	return nextX;
}

int right(int currY)
{
	int nextY;
	if(currY + 1 < colNum)
	{
		nextY = currY + 1;
	}
	else
	{
		nextY = currY;
	}
	return nextY;
}

int down(int currX)
{
	int nextX;
	if(currX + 1 < rowNum)
	{
		nextX = currX + 1;
	}
	else
	{
		nextX = rowNum - 1;
	}
	return nextX;
}

int left(int currY)
{
	int nextY;
	if(currY - 1 >= 0)
	{
		nextY = currY - 1;
	}
	else
	{
		nextY = currY;
	}
	return nextY;
}


int wind(int currX, int currY)
{
	int nextX;
	double randval = ((double)rand() / (double)RAND_MAX);
	int windval, winds = windSpeed[currY];
	
	if(randval <= 1/3)
	{
		windval = winds - 1;
	}
	else if(randval <= 2/3)
	{
		windval = winds;
	}
	else
	{
		windval = winds + 1;
	}
	

	if((currX - winds) >=0 && (currX - winds) < rowNum)
	{
		nextX = currX - winds;
	}
	else if(currX - winds <0)
	{
		nextX = 0;
	}
	else
		nextX = rowNum - 1;

	return nextX;
}



int main(int argc, char **argv)
{


	int currX = 3, currY = 0, nextX, nextY, valX, valY;
	//0- UP 1- Right 2- Down 3- Left 4- NE 5- SE 6- SW 7- NW
	int actionNum = 9;
	long int i, j ,k, epi = 0;
	int goalX = 3, goalY = 7, satrtX= 3, starty = 0, currAction, nextAction;
	long int episodNum = 2000;
	long int epiByTime[episodNum];
	long int timeElapsed = 0;
	double eph = 0.35, randval, alpha = 0.35;
	if(argc > 1)
	{
		episodNum = atoi(argv[1]);	
	}

	double actionStateValue[rowNum][colNum][actionNum];

		// Initilization to zero
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

			for(i = 0; i< actionNum; i++)
			{
				if(randval < (i+1)/9)
				{
					currAction = i;
					break;
				}
			}
		}

		//printf("Action = %d\n",currAction);

		while(currX != goalX || currY != goalY )
		{
/************************************Find the next state*************************************/

			if (currAction == 0)
			{
				valX = up(currX);
				if(valX == currX)
				{
					nextX = valX;
				}
				else
				{
					nextX = wind(valX, currY);
				}
				nextY = currY;
			}

			else if (currAction == 1)
			{
				valY = right(currY);
				if(valY != currY)
				{
					nextX = wind(currX, currY);
				}
				else
					nextX = currX;
				nextY = valY;
			}

			else if (currAction == 2)
			{
				valX = down(currX);
				if(valX == currX)
				{
					nextX = valX;
				}
				else
				{
					nextX = wind(valX, currY);
				}
				nextY = currY;
			}

			else if (currAction == 3)
			{
				valY = left(currY);
				if(valY != currY)
				{
					nextX = wind(currX, currY);
				}
				else
					nextX = currX;
				nextY = valY;
			}

			else if (currAction == 4)
			{
				valX = up(currX);
				valY = right(currY);
				if (valX != currX && valX != currY)
				{
					nextX = wind(valX, currY);
					nextY = valY;
				}
				else
				{
					nextX = valX;
					nextY = valY;
				}
			}

			else if (currAction == 5)
			{
				valX = down(currX);
				valY = right(currY);
				if (valX != currX && valX != currY)
				{
					nextX = wind(valX, currY);
					nextY = valY;
				}
				else
				{
					nextX = valX;
					nextY = valY;
				}
			}

			else if (currAction == 6)
			{
				valX = down(currX);
				valY = left(currY);
				if (valX != currX && valX != currY)
				{
					nextX = wind(valX, currY);
					nextY = valY;
				}
				else
				{
					nextX = valX;
					nextY = valY;
				}
			}

			else
			{
				valX = up(currX);
				valY = left(currY);
				if (valX != currX && valX != currY)
				{
					nextX = wind(valX, currY);
					nextY = valY;
				}
				else
				{
					nextX = valX;
					nextY = valY;
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
				for(i = 0; i< actionNum; i++)
				{
					if(randval < (i+1)/9)
					{
						currAction = i;
						break;
					}
				}
			}

/*********************************End of finding next action a'****************************************/

/*********************************Fnding state action pair value using TD(0)***************************/

			actionStateValue[currX][currY][currAction] = actionStateValue[currX][currY][currAction] + 
			alpha * (-1 + actionStateValue[nextX][nextY][nextAction] - actionStateValue[currX][currY][currAction]);



/********************************END**********************************************************************/

			timeElapsed++;
			currX = nextX;
			currY = nextY;
			currAction = nextAction;

		} 
		epiByTime[epi] = timeElapsed;
		epi ++;
		
	}

	FILE *fptr;
	fptr=(fopen("8action_stochastic.txt","w"));
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





















