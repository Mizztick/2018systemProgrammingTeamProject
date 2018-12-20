/*2011097075_whwogus_makeboard_and_color*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 4

int score=0;


//make 4x4 board & pts
void makeboard(int board[SIZE][SIZE]){
        int x, y;
        int c;

        printf("  2222      000        44     8888     \n");
        printf(" 22  22   00   00     4 4    88  88    \n");
        printf("    22    00   00    4  4     8888     \n");
        printf("   22     00   00   444444   88  88    \n");
        printf(" 222222     000         4     8888     \n\n");

        printf("       ------------\n");
        printf("       |          |\n");
        printf("       |    %d pts | \n", score);
        printf("       ------------\n");






        for (y=0;y<SIZE;y++) {
                for (x=0;x<SIZE;x++) {
                        printf("       ");
                }
                printf("\n");
                for (x=0;x<SIZE;x++) {
                        if (board[x][y]!=0) {
                                char s[8];
                                int t = 7-(int)strlen(s);
                                printf("%*s%s%*s",t-t/2,"",s,t/2,"");
                        } else {
                                printf("   +   ");
                        }
                }
                printf("\n");
                for (x=0;x<SIZE;x++) {
                        printf("       ");
                }
                printf("\n");

        }
        printf("\n");
        printf("   MOVE: ←,↑,→,↓  QUIT: q     \n");
        printf("\033[A");
}

/*int findTarget(int array[SIZE],int x,int stop) {
        int t;
        if (x==0) {
                return x;
        }
        for(t=x-1;t>=0;t--) {
                if (array[t]!=0) {
                        if (array[t]!=array[x]) {
                                return t+1;
                        }
                        return t;
                } else {
                        if (t==stop) {
                                return t;
                        }
                }
        }
        return x;
}*/

/*void addRandom(int board[SIZE][SIZE]) {
        static bool initialized = false;
        int x,y;
        int r,len=0;
        int n,list[SIZE*SIZE][2];

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
                n = (rand()%10)/9+1;
                board[x][y]=n;
        }
}*/

//initialize the board before starting the game
void initboard(int board[SIZE][SIZE]) {
        int x,y;
        for (x=0;x<SIZE;x++) {
                for (y=0;y<SIZE;y++) {
                        board[x][y]=0;
                }
        }
       // addRandom(board);
       // addRandom(board);
        makeboard(board);
        score = 0;
}

//main 
int main(int argc, char *argv[]){
        int board[SIZE][SIZE];
        char c;

        initboard(board);
        while(1){
                c=getchar();
                if(c==-1){
                        printf("key error!\n");
                        break;
                }
                else{
                        makeboard(board);
                        usleep(15000);
                        makeboard(board);
                }
                if(c=='q'){
                        break;
                }
        }

        return EXIT_SUCCESS;
}
  

