#include <stdio.h>
#include<time.h>
void c15Puzzle_main(){
	printf("enter user name:");
	char name[100];
	scanf("%s", name);
	User *user =createUser(name);

	int rows=4, cols=4;
	int A[][4] = { 1, 2, 3, 4 , 5, 6, 7, 8, 9, 10, 11, 12,13, 14, 0, 15 };
	//intitializeRandom(A);
   	printf("\t\t\t\t\t\t*WELCOME TO THE GAME OF PUZZlE*\n");
	printf("\nGiven a Random Board of 15 Pieces.You need to move the pieces in such a way that all pieces will be in ascending order or correct order\n");
	printf("\nenter control to move a piece into the space\n");
	Board *board=createBoard(rows, cols);

	initializeBoard(board, (int *)A, rows, cols);//Initalize the board with table ,Pass it as (int *)table

		drawBoardOnScreen(board);//First Clear and Redraw the Screen ,First Time we need to show the board right ?

		printUser(user);//Also call printUser , You also need to show ,his name and movesCount.

		while (checkBoard(board) != 1)//Use a Loop which repeatedly takes input from User and calls playMove function
		{
			char choice=takeInput();
			playMove(board, user, choice);
			if (checkBoard(board) == 1)
				break;
			clearAndRedrawScreen(board);
			printUser(user);
			printf("\nYour Move Has been Successful!\nWhat is your next Move?\n");
		}
		printf("\n\t\t\tGame is completed in %d moves ,good work %s\n", user->movesCount, user->name);
}
