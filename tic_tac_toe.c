#include<stdio.h>
#include<string.h>
void display_board();
void get_move();
void display_result();
void play_tic_tac_toe();
void bot_play();
void player_play();
void find_win_pos(char,int*,int*);
char board[3][3]={'x','x','x','x','x','x','x','x','x'};
char win_char;
int main()
{
    int ch;
    printf("Player's Symbol: 0(zero)\nBot's Symbol: C(big C)\nEmpty Symbol: x(small x)");
    srand(time(NULL));
    play_tic_tac_toe();
}
void display_board()
{
    int i,j;
    for(i=0;i<3;i++)
    {

        for(j=0;j<3;j++)
        printf("%c",board[i][j]);
         printf("\n");
    }
}
//move by player
void player_play()
{
    int row,col,ck=1;
    while(ck){
    printf("\n Enter the row no(1..3): ");
    scanf("%d",&row);

    printf("\nEnter the column no(1..3): ");
    scanf("%d",&col);
    if((row<0 || row>3) || (col<0 || col>3))
    {
        printf("\nInvalid Row/Column");

    }
    else if(board[row-1][col-1]=='C' || board[row-1][col-1]=='0')
    {
        printf("\nCell Already Ocuppied.Enter Another Cell address");

    }
    else
    {
        board[row-1][col-1]='0';
        ck=0;
    }
    }
    printf("\nAfter Player Play\n");
    display_board();
}
//finding winning position so that bot play can play intelligently
void find_win_pos(char a,int *row,int *col)
{
    int i,j,empty_row,empty_col,ch_count;
    //loop through column
    for(i=0;i<3;i++)
    {
        ch_count=0;
        empty_col=-1;
        for(j=0;j<3;j++)
        {
            if(board[i][j]==a)
                ch_count++;
            else if(board[i][j]=='x')
                empty_col=j;
            if(ch_count==2 && empty_col!=-1)
            {
                *row=i;
                *col=empty_col;
                return;
            }
        }
    }
    //loop through row
    for(j=0;j<3;j++)
    {
        ch_count=0;
        empty_row=-1;
        for(i=0;i<3;i++)
        {
            if(board[i][j]==a)
                ch_count++;
            else if(board[i][j]=='x')
                empty_row=i;
            if(ch_count==2 && empty_row!=-1)
            {
                *row=empty_row;
                *col=j;
                return;
            }
        }
    }
    ch_count=0;
    empty_col=-1;
    empty_row=-1;
    //loop through diagonal
    for(i=0;i<3;i++)
    {
        if(board[i][i]==a)
            ch_count++;
        else if(board[i][i]=='x')
        {
            empty_col=empty_row=i;
        }
    }
    if(ch_count==2 && empty_row!=-1 && empty_col!=-1)
    {
        *row=empty_row;
        *col=empty_col;
        return;
    }
    ch_count=0;
    empty_col=-1;
    empty_row=-1;
    for(i=0;i<3;i++)
    {
        if(board[i][2-i]==a)
            ch_count++;
        else if(board[i][2-i]=='x')
        {
            empty_row=i;
            empty_col=2-i;
        }
    }
    if(ch_count==2 && empty_row!=-1 && empty_col!=-1)
    {
        *row=empty_row;
        *col=empty_col;
        return;
    }

}
//play by bot
void bot_play()
{
    int row=-1;
    int col=-1;
    //check if bot can win in this move
    find_win_pos('C',&row,&col);
    if(row!=-1 && col!=-1)
    {
        board[row][col]='C';
        return;
    }
    //check if player can win
    find_win_pos('0',&row,&col);
    if(row!=-1 && col!=-1)
    {
        board[row][col]='C';
        return;
    }
    //play different move

   // Corner positions
	int corners[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
	// If any one or more corners are blank
	if (board[0][0] == 'x' || board[0][2] == 'x' || board[2][0] == 'x' || board[2][2] == 'x')
	{
		// randomly select corner
		while (1)
		{
			int corner = rand () % 4;
			row = corners[corner][0];
			col = corners[corner][1];
			if (board[row][col] == 'x')
			{
				board[row][col] = 'C';
				return;
			}
		}
	}
	// Edge positions
	int edges[4][2] = {{0, 1}, {1, 0}, {1, 2}, {2, 1}};
	// if any one or more edges are blank
	if (board[0][1] == 'x' || board[1][0] == 'x' || board[1][2] == 'x' || board[2][1] == 'x')
	{
		// randomly select edge
		while (1)
		{
			int edge = rand () % 4;
			row = edges[edge][0];
			col = edges[edge][1];
			if (board[row][col] == 'x')
			{
				board[row][col] = 'C';
				return;
			}
		}
	}
   // return win;
}
//after playing either by bot or player it will check for if bot or player is won
int check_if_win()
{
    //int win=0;
    int i;
    //check across
    for(i=0;i<3;i++)
    {
        if((board[i][0]!='x')&&(board[i][0])==board[i][1] && (board[i][1]==board[i][2]))
        {
           // printf("\n\nacross\n\n");
             win_char=board[i][0];
            return 1;
        }
    }
    //check vertical
    for(i=0;i<3;i++)
    {
        if((board[0][i]!='x')&&(board[0][i]==board[1][i]) && (board[1][i]==board[2][i]))
        {
            //printf("\n\ndown\n\n");
            win_char=board[0][i];
            return 1;
        }
    }
    //check principal diagonal
    if(board[0][0]!='x' && board[0][0]==board[1][1] && board[1][1]==board[2][2])
    {
        win_char=board[0][0];
        return 1;
    }
    //check other diagonal
    if(board[0][2]!='x' && board[0][2]==board[1][1] && board[1][1]==board[2][0])
    {
        win_char=board[0][2];
        return 1;
    }
    return 0;
}
//starting of tic tac toe
void play_tic_tac_toe()
{
    int won=0;
    int i;
    for(i=0;i<9;i++)
    {
        //printf("%d",i);
        if(i%2==0)
        {
            if(i==0)
            {
                int row=rand()%3;
                int col=rand()%3;
                board[row][col]='C';
            }
            else{
            //printf("!!!!");
            bot_play();}
            printf("\nAfter Bot Play\n");
            display_board();
        }
        else
        {
            player_play();

        }
        won=check_if_win();
        //printf("\n\n %d %c\n\n",won,win_char);
        if(won==1)
        {
            if(win_char=='0')
            {
                printf("\nPlayer Win!!!");
                return;
            }
            else if(win_char=='C')
            {
                printf("\nBot Wins\nYou Loose!");
                return;
            }
        }

    }
    if(i==9)
    {
        printf("\nMATCH DRAW");
    }

}
