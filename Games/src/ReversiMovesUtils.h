/*
This struct denotes the move played by user, X means the x cordinate and Y means y cordinate.
*/
typedef struct ReversiMove {
	int x, y,play=0;
}ReversiMove;

/*
Create a ReversiMove struct (malloc/calloc etc) and return it.
Assign parameters x and y to its fields.
*/
ReversiMove *createMove(int x, int y) {
	ReversiMove *move = (ReversiMove*)malloc(sizeof(ReversiMove));
	move->x = x-1;
	move->y = y-1;
	return move;
}

/*
	Take Only Valid Input x, y two integers . If Invalid input is entered ,Take input again . Keep Taking input until its valid
	Hint : Use While Loop and isValidInput function
	Cordinates are 1 indexed. Ie first row/column is denoted by 1 while giving input.
*/
int isvalidCoordinate(ReversiGame*, int, int);
ReversiMove *inputMove(ReversiGame *game) {
	int x, y;
	while (true)
	{
		printf("\n\n\t\t\tenter the place(X,Y) where you want to place your coin, ");
		if (game->turn == 1)
			printf("Its white's move:");
		else
			printf("Its black's move:");
		scanf("%d%d", &x, &y);
		int check=isvalidCoordinate(game, x, y);
		if (check == 0)
			continue;
		break;
	}
	ReversiMove *move=createMove(x,y);
	return move;
}


/*
	To check the validity of coordinate on the board 
*/

int isvalidCoordinate(ReversiGame *game, int x, int y) {
	if((x<=game->rows+1)&&(y<=game->cols+1)&&(x>0&&x<=9)&&(y>0&&y<=9))
	return 1;
	return 0;
}

/*
Check if the move can be placed, if its going to make a valid capture to the opponent coins
*/

int checkvalid(ReversiGame *game, ReversiMove *move, int x, int y, int play)
{
	char check;
	int turn;
	int count;
	int pos;
	int pos1=0;
	int pos2=0;
	char replace;
	if (game->turn == -1)
	{
		check = 'b';
		replace = 'b';
	}
	else
	{
		check = 'w';
		replace = 'w';
	}
	if (x == move->x&&y == move->y + 1)
	{
		count = 0;
		for (int i = y; i < game->cols; i++)
		{
			if (game->board[x][i] == check)
			{
				if (move->play == 0)
					return 1;
				count++;
				pos = i;
				break;
			}
		}
		if (count > 0)
		{
			for (int i = move->y; i <= pos; i++)
				game->board[x][i] = replace;
		}
		return 0;
	}
	if (x == move->x&&y == move->y - 1)
	{
		count = 0;
		for (int i = y; i >= 0; i--)
		{
			if (game->board[x][i] == check)
			{
				if (move->play == 0)
					return 1;
				count++;
				pos = i;
				break;
			}
		}
		if (count > 0)
		{
			for (int i = move->y; i >= pos; i--)
				game->board[x][i] = replace;

		}
		return 0;
	}
	if (x == move->x +1 && y == move->y)
	{
		count = 0;
		for (int i = x; i < game->rows; i++)
		{
			if (game->board[i][y] == check)
			{
				if (move->play == 0)
					return 1;
				count++;
				pos = i;
				break;
			}
		}
		if (count > 0)
		{
			
			for (int i = move->x; i <= pos; i++)
			{
				game->board[i][y] = replace;
			}
		}
		return 0;
	}
	if (x == move->x - 1 && y == move->y)
	{
		count = 0;
		for (int i = x; i >= 0; i--)
		{
			if (game->board[i][y] == check)
			{
				if (move->play == 0)
					return 1;
				count++;
				pos = i;
				break;
			}
		}
		if (count > 0)
		{
			for (int i = move->x; i >=pos; i--)
				game->board[i][y] = replace;
		}
		return 0;
	}
	if (x == move->x + 1 && y == move->y + 1)
	{
		count = 0;
		for (int i = x , j = y; i < game->rows&& j < game->cols; i++, j++)
		{
			if (game->board[i][j] == check)
			{
				if (move->play == 0)
					return 1;
				count++;
				pos1 = i;
				pos2 = j;
				break;
			}
		}
		if (count > 0)
		{
			for (int i = move->x, j = move->y; i <= pos1&& j <= pos2; i++, j++)
			{
				game->board[i][j] = replace;
			}
		}
		return 0;
	}
	if (x == move->x + 1 && y == move->y - 1)
	{
		for (int i = x, j = y; i < game->rows&& j >= 0; i++, j--)
		{
			count = 0;
			if (game->board[i][j] == check)
			{
				if (move->play == 0)
					return 1;
				count++;
				pos1 = i;
				pos2 = j;
				break;
			}
		}
		if (count > 0)
		{
			for (int i = move->x, j = move->y; i <= pos1&& j >= pos2; i++, j--)
			{
				game->board[i][j] = replace;
			}
		}
		return 0;
	}
	if (x == move->x - 1 && y == move->y + 1)
	{
		count = 0;
		for (int i = x, j = y; i >= 0&& j < game->cols; i--, j++)
		{
			if (game->board[i][j] == check)
			{
				if (move->play == 0)
					return 1;
				count++;
				pos1 = i;
				pos2 = j;
				break;
			}
		}
		if (count > 0)
		{
			for (int i = move->x, j = move->y; i >= pos1&& j <= pos2; i--, j++)
			{
				game->board[i][j] = replace;
			}
		}
		return 0;
	}
	if (x == move->x - 1 && y == move->y - 1)
	{
		count = 0;
		for (int i = x, j = y; i >= 0&& j >= 0; i--, j--)
		{
			if (game->board[i][j] == check)
			{
				if (move->play == 0)
					return 1;
				count++;
				pos1 = i;
				pos2 = j;
				break;
			}
		}
		if (count > 0)
		{
			for (int i = move->x, j = move->y; i >= pos1&& j >= pos2; i--, j--)
			{
				game->board[i][j] = replace;
			}
		}
		return 0;
	}
}
int isValidMove(ReversiGame *game, ReversiMove *move) {
	char t; int check=0;
	if (game->turn == 1)
		t = 'b';
	else
	t = 'w';
	if (move->play != 1)
		move->play = 0;
	if (move->x < 0 || move->y < 0)
		return 0;
	if (game->board[move->x][move->y] != ' ')
	{
		return 0;
	}
	else
	{
		if (move->x == 0 && move->y == 0)
		{

			if (game->board[move->x + 1][move->y] == t)
				check = checkvalid(game, move, move->x + 1, move->y, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x + 1][move->y + 1] == t)
				check = checkvalid(game, move, move->x + 1, move->y + 1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x][move->y + 1] == t)
				check = checkvalid(game, move, move->x, move->y + 1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
		}
		if (move->x == game->rows - 1&&move->y==0)
		{
				if (game->board[move->x - 1][move->y] == t)
					check = checkvalid(game, move, move->x - 1, move->y, move->play);
				if (check == 1 && move->play == 0)
					return 1;
				if (game->board[move->x - 1][move->y + 1] == t)
					check = checkvalid(game, move, move->x - 1, move->y + 1, move->play);
				if (check == 1 && move->play == 0)
					return 1;
				if (game->board[move->x][move->y + 1] == t)
					check = checkvalid(game, move, move->x, move->y + 1, move->play);
				if (check == 1 && move->play == 0)
					return 1;
		}
		if (move->x == 0 && move->y == game->cols - 1)
		{
				if (game->board[move->x + 1][move->y] == t)
					check = checkvalid(game, move, move->x + 1, move->y, move->play);
				if (check == 1 && move->play == 0)
					return 1;
				if (game->board[move->x + 1][move->y - 1] == t)
					check = checkvalid(game, move, move->x + 1, move->y - 1, move->play);
				if (check == 1 && move->play == 0)
					return 1;
				if (game->board[move->x][move->y - 1] == t)
					check = checkvalid(game, move, move->x, move->y - 1, move->play);
				if (check == 1 && move->play == 0)
					return 1;
		}
		if (move->x == game->rows-1 && move->y == game->cols - 1)
		{
			if (game->board[move->x - 1][move->y] == t)
				check = checkvalid(game, move, move->x - 1, move->y, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x - 1][move->y - 1] == t)
				check = checkvalid(game, move, move->x - 1, move->y - 1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x][move->y - 1] == t)
				check = checkvalid(game, move, move->x, move->y - 1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
		}
		if (move->x == 0&&move->y!=0&&move->y!=game->cols-1)
		{
			if (game->board[move->x][move->y+1] == t)
				check = checkvalid(game, move, move->x, move->y + 1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x+1][move->y] == t)
				check = checkvalid(game, move, move->x + 1, move->y, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x+1][move->y-1] == t)
				check = checkvalid(game, move, move->x + 1, move->y - 1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x][move->y-1] == t)
				check = checkvalid(game, move, move->x, move->y-1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x + 1][move->y+1] == t)
				check = checkvalid(game, move, move->x + 1, move->y + 1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
		}
		if (move->y == 0&&move->x!=0&&move->x!=game->rows-1)
		{
			if (game->board[move->x][move->y + 1] == t)
				check = checkvalid(game, move, move->x, move->y + 1, move->play);
			if (check == 1 && move->play == 0)
			return 1;
			if (game->board[move->x + 1][move->y] == t)
				check = checkvalid(game, move, move->x + 1, move->y, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x + 1][move->y + 1] == t)
				check = checkvalid(game, move, move->x + 1, move->y + 1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x-1][move->y] == t)
				check = checkvalid(game, move, move->x - 1, move->y, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x - 1][move->y + 1] == t)
				check = checkvalid(game, move, move->x - 1, move->y + 1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
		}
		if (move->x == game->rows - 1 && move->y != 0 && move->y != game->cols - 1)
		{
			if (game->board[move->x][move->y + 1] == t)
			check = checkvalid(game, move, move->x, move->y + 1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x - 1][move->y] == t)
				check = checkvalid(game, move, move->x - 1, move->y, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x - 1][move->y - 1] == t)
				check = checkvalid(game, move, move->x - 1, move->y - 1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x][move->y-1] == t)
				check = checkvalid(game, move, move->x, move->y - 1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x - 1][move->y + 1] == t)
				check = checkvalid(game, move, move->x - 1, move->y + 1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
		}
		if (move->y == game->cols - 1 && move->x != 0 && move->x != game->rows - 1)
		{
			if (game->board[move->x][move->y - 1] == t)
				check = checkvalid(game, move, move->x, move->y - 1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x + 1][move->y] == t)
				check = checkvalid(game, move, move->x + 1, move->y, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x + 1][move->y - 1] == t)
				check = checkvalid(game, move, move->x + 1, move->y - 1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x-1][move->y - 1] == t)
				check = checkvalid(game, move, move->x - 1, move->y - 1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x - 1][move->y] == t)
				check = checkvalid(game, move, move->x - 1, move->y, move->play);
			if (check == 1 && move->play == 0)
				return 1;
		}
		 if (move->x != 0 && move->x != game->rows - 1 && move->y != 0 && move->y != game->cols - 1)
		{
			if (game->board[move->x][move->y+1] == t)
			check = checkvalid(game, move, move->x, move->y + 1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x][move->y-1] == t)
				check = checkvalid(game, move, move->x, move->y-1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x + 1][move->y] == t)
				check = checkvalid(game, move, move->x + 1, move->y, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x-1][move->y] == t)
				check = checkvalid(game, move, move->x-1, move->y, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x + 1][move->y+1] == t)
				check = checkvalid(game, move, move->x+1, move->y+1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x-1][move->y + 1] == t)
				check = checkvalid(game, move, move->x-1, move->y+1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x - 1][move->y-1] == t)
				check = checkvalid(game, move, move->x-1, move->y-1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
			if (game->board[move->x + 1][move->y - 1] == t)
				check = checkvalid(game, move, move->x + 1, move->y - 1, move->play);
			if (check == 1 && move->play == 0)
				return 1;
		}
	}
	return 0;
}


/*
Check if the player can move , if the player is not able to move, he looses the turn
and the opponent gets the chance to play.
If both players are not able to make a move, then the game ends.
*/

int hasMove(ReversiGame *game){
	int check = 0;
	int count = 0;
	ReversiMove *move = (ReversiMove*)malloc(sizeof(ReversiMove));
	for (int i = 0; i < game->rows; i++)
	{
		for (int j = 0; j < game->cols; j++)
		{
			move->x = i;
			move->y = j;
			move->play = 0;
			check = isValidMove(game, move);
			if (check == 1)
				return 1;
		}
		/*if (i == game->rows - 1)
		{
			count++;
			if (count == 1)
			{
				game->turn *= -1;
				i = 0;
			}
			else
			{
				game->state = 1;
				endGame(game);
				return 0;
			}
		}*/
	}
	return 0;
}

/*
Increment the number of moves in ReversiGame struct.
*/
void incrementMoves(ReversiGame *game) {
	game->blackCount = 0, game->whiteCount = 0;
	for (int i = 0; i < game->rows; i++)
	{
		for (int j = 0; j < game->cols; j++)
		{
			if (game->board[i][j] == 'w')
				game->whiteCount++;
			else if (game->board[i][j] == 'b')
				game->blackCount++;
		}
	}
	game->NumberofMoves++;
}

/*
Toggle the turn in Reversi Game.
This function is to be called when you want to change the turn.
*/
void modifyTurn(ReversiGame *game) {
	game->turn *= -1;
	return;
}

/*
End Reversi Game.
Populate game->winner field accordingly with who won. 1 for white, -1 for black.
This function is to be called when the game is ended.
*/
void endGame(ReversiGame *game) {
	game->state = 1;
		if (game->whiteCount > game->blackCount)
		{
			game->winner = 1;
		}
		else if (game->whiteCount < game->blackCount)
			game->winner = -1;
	return;
}

/*
	Wrapper function you will call only modify to increment moves and modify the turn.
*/

void modify(ReversiGame *game) {
	incrementMoves(game);
	modifyTurn(game);
}


/*
	This function performs move action on the board
	Note : call validity check performs using above functions before making a move
	returns :
	true on move sucess
	false if move is invalid
*/

bool playMove(ReversiGame *game, ReversiMove *move) {
	
	int c=hasMove(game);
	if (c == 0)
	{
		game->turn *= -1;
		c = hasMove(game);
		
	}
	if (c == 0)
	{
		game->state = 1;
		endGame(game);
	}
	else
	{
		int check = isValidMove(game, move);
		if (check == 0)
			return false;
		else
		{
			move->play = 1;
			isValidMove(game, move);
			modify(game);
			int c1 = checkReversiGameOver(game);
			if (c1 == 0)
				endGame(game);
		}
		return true;
	}
	
}


void printWinner(ReversiGame *game) {
	if (game->winner == 1)
		printf("\n\t\t\t\tresult: %s has won.", game->player1name);
	else if (game->winner == -1)
		printf("\n\t\t\t\tresult: %s has won", game->player2name);
	else
		printf("\n\t\t\t\tgame is Drawn");
	/*
	Sample output :
	Result Praveen has won. / Game is Drawn.
	*/
}