#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ReversiGame {
	char **board;	// char 'w' for whites, 'b' for blacks ' ' for empty 
	char *player1name;
	char *player2name;
	int whiteCount = 0;
	int blackCount = 0;
	int NumberofMoves = 0;
	int rows, cols;
	int turn = 1;   //1 for white, -1 for black
	int state = 0;  //0 for unfinished, 1 for game over
	int winner = 0; //1 for white, -1 for black
}ReversiGame;


void endGame(ReversiGame *game);
int hasMove(ReversiGame *game);
void modifyTurn(ReversiGame *game);

/*

Create a new ReversiGame By allocating memory from Heap , Let it be game;
Create a 2D Array from Heap(Dynamically) with specified number of rows and cols
and copy its reference to game->board;

Note : Return NULL for Invalid Inputs
Note : Copy Rows into newlyCreatedBoard->rows , and vice versa for cols ,
Also copy player1name,player2name.
*/

ReversiGame * createNewGame(int rows, int cols, char *player1, char *player2) {
	if (rows < 0 || cols < 0||rows!=cols || player1 == NULL || player2 == NULL)
		return NULL;
	char **game = (char**)malloc(rows*sizeof(char*));
	for (int i = 0; i<rows; i++)
		game[i] = (char*)malloc(cols*sizeof(char));
	ReversiGame *newboard = (ReversiGame*)malloc(sizeof(ReversiGame));
	newboard->board = game;
	newboard->rows = rows;
	newboard->cols = cols;
	newboard->player1name = player1;
	newboard->player2name = player2;
	return newboard;
}


/*
Copy the tobeCopied Array into game->board .
Learn how to Copy a 2D array when address of first row is given.
Note this function is called in the following way

Also Initialize the turn variable, whiteCount with no of white coins and same for black.

Do Nothing for Invalid Inputs
*/
int checkReversiGameOver(ReversiGame*);
void initializeReversiGame(ReversiGame *game, char *tobeCopiedBoard, int rows, int cols, int turn) {
	int k = 0;
	int wcount = 0, bcount = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++, k++)
		{
			if (tobeCopiedBoard[i + k] == '\0')
				k++;
			game->board[i][j] = tobeCopiedBoard[i + k];
			if (game->board[i][j] == 'w')
				wcount++;
			if (game->board[i][j] == 'b')
				bcount++;
		}
		k--;
	}
	game->blackCount = bcount;
	printf("%d", game->blackCount);
	game->whiteCount = wcount;
	game->NumberofMoves = 0;
	game->state = 0;
	game->rows = rows;
	game->cols = cols;
	game->turn = turn;
	game->winner = 0;
	int c=checkReversiGameOver(game);
	if (c == 0)
	{
		endGame(game);
	}
}

/*
Check if the Current board is in End Position . 
Return 0 if the game is Ended, 1 if not .
Win Condition : Either all the squares are filled or a stalemate position (No one can Move)

*/

int checkReversiGameOver(ReversiGame *game){
	int c = hasMove(game);
	if (c == 0)
	{
		game->turn = game->turn*-1;
		c = hasMove(game);
	}
	else
		c = 1;
	if (game->whiteCount + game->blackCount == (game->cols*game->rows) || (game->whiteCount == 0 || game->blackCount == 0)||c==0)
	{
		endGame(game);
		return 0;
	}
	else
		return 1;
}

void printMoves(ReversiGame *game){
	/*
	Sample output :
	Whites Count : 5
	Black Count : 4
	Move Count : 9
	*/
	printf("\n\t\t\t\twhites Count : %d\n\t\t\t\tblack Count : %d\n\t\t\t\tMove Count : %d\n",game->whiteCount,game->blackCount,game->NumberofMoves);
	return;
}

/*
Print the Board in a Good Way.Make sure Each Number is properly formatted and Seperated, and Row lines too .
Print Empty Space when you encounter 0.Also make sure your board looks good for 5x5 or 7x7 boards too .
Use your Thinking / UI Skills .
See the link we shared for sample screenshots for inspiration.
*/

void drawBoardOnScreen(ReversiGame *game) {
	printf("\n\n");
	printf("\t\t\t\t\t\twelcome MR.%s and MR.%s to the REVERSI GAME!",game->player1name,game->player2name);
	printf("\n\n\n\n");
	printf("\t\t\t\t");
	printf("*  ");
	for (int i = 1; i <= game->cols; i++)
		printf("  %d  ",i);
	printf("\n\n");
	for (int i = 0; i < game->rows; i++)
	{
		printf("\t\t\t\t%d", i+1);
		for (int j = 0; j < game->cols; j++)
		{
			printf("  %c  ", game->board[i][j]);
		}
		printf("\n\n");
	}
	//printf("white count: %d\nblack count: %d\nnumber of moves: %d\n", game->whiteCount, game->blackCount, game->NumberofMoves);
	return;
}

/*
Clear The Screen , So that we can redraw the Board (which has modified values )
*/

void clearScreen(ReversiGame *game){
	system("cls");
}

/*
Clear the Screen and ReDraw the Board ,Call above two functions
*/

void clearAndRedrawScreen(ReversiGame *game){
	clearScreen(game);
	drawBoardOnScreen(game);
}



