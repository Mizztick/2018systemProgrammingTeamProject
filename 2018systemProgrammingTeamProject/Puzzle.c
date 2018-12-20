#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <signal.h>




#define SIZE 4
uint32_t score=0;
uint8_t scheme=0;
bool gameEnd=false;

void getColor(uint8_t value, char *color, size_t length) {
	uint8_t original[] = {8,255,1,255,2,255,3,255,4,255,5,255,6,255,7,255,9,0,10,0,11,0,12,0,13,0,14,0,255,0,255,0};
	uint8_t blackwhite[] = {232,255,234,255,236,255,238,255,240,255,242,255,244,255,246,0,248,0,249,0,250,0,251,0,252,0,253,0,254,0,255,0};
	uint8_t bluered[] = {235,255,63,255,57,255,93,255,129,255,165,255,201,255,200,255,199,255,198,255,197,255,196,255,196,255,196,255,196,255,196,255};
	uint8_t *schemes[] = {original,blackwhite,bluered};
	uint8_t *background = schemes[scheme]+0;
	uint8_t *foreground = schemes[scheme]+1;
	if (value > 0) while (value--) {
		if (background+2<schemes[scheme]+sizeof(original)) {
			background+=2;
			foreground+=2;
		}
	}
	snprintf(color,length,"\033[38;5;%d;48;5;%dm",*foreground,*background);
}

void makeBoard(uint8_t board[SIZE][SIZE]) {
	
	uint8_t x,y;
	char c;
	char color[40], reset[] = "\033[m";
	printf("\033[H");

	 printf("  2222      000        44     8888     \n");
        printf(" 22  22   00   00     4 4    88  88    \n");
        printf("    22    00   00    4  4     8888     \n");
        printf("   22     00   00   444444   88  88    \n");
        printf(" 222222     000         4     8888     \n\n");

        printf("---------------------------------------\n");
        printf("---------------------------------------\n");

	for (y=0;y<SIZE;y++) {
		for (x=0;x<SIZE;x++) {
			getColor(board[x][y],color,40);
			printf("%s",color);
			printf("       ");
			printf("%s",reset);
		}
		printf("\n");
		for (x=0;x<SIZE;x++) {
			getColor(board[x][y],color,40);
			printf("%s",color);
			if (board[x][y]!=0) {
				char s[8];
				snprintf(s,8,"%u",(uint32_t)1<<board[x][y]);
				uint8_t t = 7-strlen(s);
				printf("%*s%s%*s",t-t/2,"",s,t/2,"");
			} else {
				printf("   ·   ");
			}
			printf("%s",reset);
		}
		printf("\n");
		for (x=0;x<SIZE;x++) {
			getColor(board[x][y],color,40);
			printf("%s",color);
			printf("       ");
			printf("%s",reset);
		}
		printf("\n");
	}
	printf("\n");
	printf("        ←,↑,→,↓ or q        \n");
	printf("\033[A"); // one line up
	
	/*

	int i, j;

	for(i=0; i<4; i++)
		
		{
			for(j=0; j<4; j++)
		{
			
			printf("%d	", board[i][j]);


	
		}
			printf("\n");
	}
	printf("\n\n");
		*/	
}



bool movePuzzle(uint8_t board[SIZE][SIZE]) {
	
	bool success=true;
	int i, j;
	uint8_t first=0;
	uint8_t second=0;
	uint8_t third=0;
	uint8_t fourth=0;
	uint8_t temp=0;
	uint8_t count=0;
	uint8_t ordercount=0;
	uint8_t overcount=0;
	

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
						ordercount=1;
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
				first=first+1;
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
						ordercount=1;
					}
					else if(ordercount==1)
					{
						second=board[i][j];
						ordercount=2;
					}
					else if(ordercount==2)
					{
						third=board[i][j];
						ordercount=3;
					}
					
				}
			}


			//숫자가 3개이므로 1~2, 2~3이 같은지 확인하면 된다
			// 단 1~2가 같다면 3이 2가 된다
			


			if(first==second)
			{
				first=first+1;
				second=third;
				third=0;
			}
			else if(second==third)
			{
				second=second+1;
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
						ordercount=1;
					}
					else if(ordercount==1)
					{
						second=board[i][j];
						ordercount=2;
					}
					else if(ordercount==2)
					{
						third=board[i][j];
						ordercount=3;
					}
					else if(ordercount==3)
					{
						fourth=board[i][j];
						ordercount=4;
					}
					
				}
			}


			//4개인 경우 4가지 경우가 있는데, 4개중 2개만 같을 경우(1-2, 2-3, 3-4) 3가지 경우
			//								4개중 2세트가 같을 경우(1-2, 3-4 모두) 1가지 경우

			// 1-2가 같은지 확인한 다음, 같다면 3-4가 같은지 먼저 확인하면 될듯
			

			//1-2가 같으면서 3-4가 같은 경우

			if(first==second && third==fourth)
			{
				first=first+1;
				second=third+1;
				third=0;
				fourth=0;

			}
			else if(first==second)
			{
				first=first+1;
				second=third;
				third=fourth;
				fourth=0;
			}
			else if(second==third)
			{
				second=second+1;
				third=fourth;
				fourth=0;

			}
			else if(third==fourth)
			{
				third=third+1;
				fourth=0;
			}

			else // 앞선 해당사항이 없다면 움직임이 불가함. 움직임 불가 카운트 +1, 4개가 되면 게임 오버
			{
				overcount++;
				if(overcount==4)
				{
					gameEnd=true;
					return false;
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






	return success;
}

void rotate(uint8_t board[SIZE][SIZE]) {
	uint8_t i,j,n=SIZE;
	uint8_t tmp;
	for (i=0; i<n/2; i++) {
		for (j=i; j<n-i-1; j++) {
			tmp = board[i][j];
			board[i][j] = board[j][n-i-1];
			board[j][n-i-1] = board[n-i-1][n-j-1];
			board[n-i-1][n-j-1] = board[n-j-1][i];
			board[n-j-1][i] = tmp;
		}
	}
}

bool slideUp(uint8_t board[SIZE][SIZE]) {
	bool success = false;
	
	success=movePuzzle(board);

	return success;
}

bool slideLeft(uint8_t board[SIZE][SIZE]) {
	bool success;
	rotate(board);
	
	success=movePuzzle(board);
	rotate(board);
	rotate(board);
	rotate(board);
	
	

	return success;
}

bool slideDown(uint8_t board[SIZE][SIZE]) {
	bool success;
	rotate(board);
	rotate(board);
	success=movePuzzle(board);
	rotate(board);
	rotate(board);
	
	return success;
}

bool slideRight(uint8_t board[SIZE][SIZE]) {
	bool success;
	
	rotate(board);
	rotate(board);
	rotate(board);
	success=movePuzzle(board);
	rotate(board);
	return success;
}


void addRandom(uint8_t board[SIZE][SIZE]) {
	static bool initialized = false;
	uint8_t x,y;
	uint8_t r,len=0;
	uint8_t n,list[SIZE*SIZE][2];

	if (!initialized) {
		srand(time(NULL));
		initialized = true;
	}

	for (x=0;x<SIZE;x++) {
		for (y=0;y<SIZE;y++) {
			if (board[x][y]==0) {
				list[len][0]=x;
				list[len][1]=y;
				len++;
			}
		}
	}

	if (len>0) {
		r = rand()%len;
		x = list[r][0];
		y = list[r][1];
		n = (rand()%2)+1;
		board[x][y]=n;
	}
}

void initBoard(uint8_t board[SIZE][SIZE]) {
	uint8_t x,y;
	for (x=0;x<SIZE;x++) {
		for (y=0;y<SIZE;y++) {
			board[x][y]=0;
		}
	}
	addRandom(board);
	addRandom(board);
	makeBoard(board);
	score = 0;
}

void setBufferedInput(bool enable) {
	static bool enabled = true;
	static struct termios old;
	struct termios new;

	if (enable && !enabled) {
		tcsetattr(STDIN_FILENO,TCSANOW,&old);
		enabled = true;
	} else if (!enable && enabled) {
		
		tcgetattr(STDIN_FILENO,&new);
		old = new;
		new.c_lflag &=(~ICANON & ~ECHO);
		tcsetattr(STDIN_FILENO,TCSANOW,&new);
		enabled = false;
	}
}


void signal_callback_handler(int signum) {
	printf("         TERMINATED         \n");
	setBufferedInput(true);
	printf("\033[?25h\033[m");
	exit(signum);
}

int main() {
	uint8_t board[SIZE][SIZE];
	char c;
	bool success;

	

	printf("\033[?25l\033[2J");

	// register signal handler for when ctrl-c is pressed
	signal(SIGINT, signal_callback_handler);

	initBoard(board);
	setBufferedInput(false);
	while (true) {
		c=getchar();
		if (c == -1){ //TODO: maybe replace this -1 with a pre-defined constant(if it's in one of header files)
		    	puts("\nError! Cannot read keyboard input!");
			break;
		}
		switch(c) {
			case 97:	// 'a' key
			case 104:	// 'h' key
			case 68:	// left arrow
				success = slideLeft(board);  break;
			case 100:	// 'd' key
			case 108:	// 'l' key
			case 67:	// right arrow
				success = slideRight(board); break;
			case 119:	// 'w' key
			case 107:	// 'k' key
			case 65:	// up arrow
				success = slideUp(board);    break;
			case 115:	// 's' key
			case 106:	// 'j' key
			case 66:	// down arrow
				success = slideDown(board);  break;
			default: success = false;
		}
		if (success) {
			makeBoard(board);
			usleep(150000);
			addRandom(board);
			makeBoard(board);
			if(gameEnd)
			{
	printf("         GAME OVER          \n");
				break;
			}
		}
		
			
		
		if (c=='q') {
			printf("        QUIT? (y/n)         \n");
			c=getchar();
			if (c=='y') {
				break;
			}
			makeBoard(board);
		}
		if (c=='r') {
			printf("       RESTART? (y/n)       \n");
			c=getchar();
			if (c=='y') {
				initBoard(board);
			}
			makeBoard(board);
		}
	}
	setBufferedInput(true);

	printf("\033[?25h\033[m");

	return EXIT_SUCCESS;
}
