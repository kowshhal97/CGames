#include <stdio.h>
void Reversi_main(){
	char a[100], b[100];
	int rows = 4, cols = 4;
	/*char table1[8][9] =
	{
		"        ",
		"        ",
		"        ",
		"   wb   ",
		"   bw   ",
		"        ",
		"        ",
		"        "
	};*/
	char table1[4][5] =
	{
		"    ",
		" wb ",
		" bw ",
		"    "
	};
	printf("Enter the name of user1\n");
	scanf("%s", a);
	printf("Enter the name of user2\n");
	scanf("%s", b);
	//Create a game using  createNewGame(int,int,char *,char *) with rows,cols and  two players
	ReversiGame *game = createNewGame(rows, cols, a, b);
	//Initalize the game with table ,Pass it as (char *)table along with the turn
	initializeReversiGame(game, (char *)table1, rows, cols, 1);
	clearAndRedrawScreen(game);//First Clear and Redraw the Screen ,First Time we need to show the board right ?
	//Also call printMoves , You also need to show the whiteMoveCount and blackMoveCount and totalMoveCount.
	ReversiMove *move;
	while (game->state != 1)//Use a Loop which repeatedly takes input(Reversi Move) from User and calls playMove function 
	{
		move=inputMove(game);
		bool c=playMove(game, move);
		clearAndRedrawScreen(game);
 		printMoves(game);
	}
	printWinner(game);
}