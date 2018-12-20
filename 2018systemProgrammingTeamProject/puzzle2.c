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


void rotateBoard(int board[4][4])//����ȸ��
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

		


		//0�� �ƴ� ���� ���ڵ��� ���� count�� ������
		//count ������ŭ 0�� �ƴ� ���ڵ��� �տ������� �߷��� first, second, third, fourth�� �ִ´�
		//first���� fourth�� ���ؼ� ������ ��ġ�� �۾��� �ؼ� �ٽ� first~fourth�� ä���.
		//�����ǿ� first���� �ٽ� ä���������ν� �̵���Ų��.


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

			//���ڰ� 2���̹Ƿ� 1���� ���
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


			//���ڰ� 3���̹Ƿ� 1~2, 2~3�� ������ Ȯ���ϸ� �ȴ�
			// �� 1~2�� ���ٸ� 3�� 2�� �ȴ�
			


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


			//4���� ��� 4���� ��찡 �ִµ�, 4���� 2���� ���� ���(1-2, 2-3, 3-4) 3���� ���
			//								4���� 2��Ʈ�� ���� ���(1-2, 3-4 ���) 1���� ���

			// 1-2�� ������ Ȯ���� ����, ���ٸ� 3-4�� ������ ���� Ȯ���ϸ� �ɵ�
			

			//1-2�� �����鼭 3-4�� ���� ���

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

			else // �ռ� �ش������ ���ٸ� �������� �Ұ���. ������ �Ұ� ī��Ʈ +1, 4���� �Ǹ� ���� ����
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
