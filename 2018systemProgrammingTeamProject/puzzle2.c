#include	<stdio.h>
#include	<termios.h>
#include	<stdlib.h>

static struct termios oldt;

void restore_terminal_setting(void)
{
	tcsetattr(0, TCSANOW, &oldt);
}

void disable_terminal_return(void)
{
	struct termios newt;
	tcgetattr(0, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &newt);
	atexit(restore_terminal_setting);
}


void rotateBoard(int board[4][4])//왼쪽회전
{
	int i, j;
	int temp;
	for(i=0; i<2; i++)
	{
		for(j=i; j<4-i-1; j++)
		{
			temp = board[i][j];
			board[i][j] = board[j][4-i-1];
			board[j][4-i-1]= board[4-i-1][4-j-1];
			board[4-i-1][4-j-1] = board[4-j-1][i];
			board[4-j-1][i] = temp;
		}
	}

}


int leftSlide(int board[4][4])
{
	int i, j;
	int first=0;
	int second=0;
	int third=0;
	int fourth=0;
	int temp=0;
	int count=0;
	int ordercount=0;
	int overcount=0;
	

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			if(board[i][j]!=0)
				count++;


		}

		


		//0이 아닌 실존 숫자들을 먼저 count로 세린후
		//count 갯수만큼 0이 아닌 숫자들을 앞에서부터 추려서 first, second, third, fourth에 넣는다
		//first부터 fourth에 대해서 같으면 합치는 작업을 해서 다시 first~fourth를 채운다.
		//보드판에 first부터 다시 채워넣음으로써 이동시킨다.


		if(count==1)
		{
			for(j=0; j<4; j++)
			{
				if(board[i][j]!=0)
				{
					first=board[i][j];
					
				}
			}
		}
		else if(count==2)
		{
			for(j=0; j<4; j++)
			{
				if(board[i][j]!=0)
				{
					
					if(ordercount==0)
					{
						first=board[i][j];
						ordercount++;
					}
					else if(ordercount==1)
					{
						second=board[i][j];
					}
					
				}
			}

			//숫자가 2개이므로 1가지 경우
			if(first==second)
			{
				first+=second;
				second=0;
			}

		}
		else if(count==3)
		{
			for(j=0; j<4; j++)
			{
				if(board[i][j]!=0)
				{
					
					if(ordercount==0)
					{
						first=board[i][j];
						ordercount++;
					}
					else if(ordercount==1)
					{
						second=board[i][j];
						ordercount++;
					}
					else if(ordercount==2)
					{
						third=board[i][j];
						ordercount++;
					}
					
				}
			}


			//숫자가 3개이므로 1~2, 2~3이 같은지 확인하면 된다
			// 단 1~2가 같다면 3이 2가 된다
			


			if(first==second)
			{
				first+=second;
				second=third;
				third=0;
			}
			else if(second==third)
			{
				second+=third;
				third=0;
			}
	



		}
		else if(count==4)
		{
			for(j=0; j<4; j++)
			{
				if(board[i][j]!=0)
				{
					
					if(ordercount==0)
					{
						first=board[i][j];
						ordercount++;
					}
					else if(ordercount==1)
					{
						second=board[i][j];
						ordercount++;
					}
					else if(ordercount==2)
					{
						third=board[i][j];
						ordercount++;
					}
					else if(ordercount==3)
					{
						fourth=board[i][j];
						
					}
					
				}
			}


			//4개인 경우 4가지 경우가 있는데, 4개중 2개만 같을 경우(1-2, 2-3, 3-4) 3가지 경우
			//								4개중 2세트가 같을 경우(1-2, 3-4 모두) 1가지 경우

			// 1-2가 같은지 확인한 다음, 같다면 3-4가 같은지 먼저 확인하면 될듯
			

			//1-2가 같으면서 3-4가 같은 경우

			if(first==second && third==fourth)
			{
				first+=second;
				second=third+fourth;
				third=0;
				fourth=0;

			}
			else if(first==second)
			{
				first+=second;
				second=third;
				third=fourth;
				fourth=0;
			}
			else if(second==third)
			{
				second+=third;
				third=fourth;
				fourth=0;

			}
			else if(third==fourth)
			{
				third+=fourth;
				fourth=0;
			}

			else // 앞선 해당사항이 없다면 움직임이 불가함. 움직임 불가 카운트 +1, 4개가 되면 게임 오버
			{
				overcount++;
				if(overcount==4)
				{
					return -1;
				}

			}

		}


		
		board[i][0]=first;
		board[i][1]=second;
		board[i][2]=third;
		board[i][3]=fourth;

		ordercount=0;
		count=0;
		first=0;
		second=0;
		third=0;
		fourth=0;

	}






	return 1;

}

int main()
{
	int board[4][4];
	int i, j;
	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
			{
				board[i][j]=0;
			}



	board[0][0]=2;
	board[0][1]=2;
	board[0][2]=4;
	board[0][3]=4;
	
	board[1][0]=2;
	board[1][1]=4;
	board[1][2]=2;
	board[1][3]=4;

	board[2][0]=8;
	board[2][1]=8;
	board[2][2]=16;
	board[2][3]=2;

	board[3][0]=4;
	board[3][1]=2;
	board[3][2]=4;
	board[3][3]=2;

	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
			{
				printf("%d	", board[i][j]);
				if(j==3)
				printf("\n");
			}


		printf("//////\n");

	if(leftSlide(board)==1)
		{
			printf("success\n");
		}
		else
			printf("Over\n");

	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
			{
				printf("%d	", board[i][j]);
				if(j==3)
				printf("\n");
			}


		printf("//////\n");

	
		rotateBoard(board);

	if(leftSlide(board)==1)
		{
			printf("success\n");
		}
		else
			printf("Over\n");

	rotateBoard(board);
	rotateBoard(board);
	rotateBoard(board);
	


	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
			{
				printf("%d	", board[i][j]);
				if(j==3)
				printf("\n");
			}

		/*
		if(leftSlide(board)==1)
		{
			printf("success\n");
		}
		else
			printf("Over\n");
			*/



		getchar();

	return 0;
}
