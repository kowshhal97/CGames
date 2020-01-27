#include "stdafx.h"

#include "./../src/ReversiBoardUtils.h"
#include "./../src/ReversiMovesUtils.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace spec
{
	[TestClass]
	public ref class CReversiSpec
	{
	private:
		TestContext^ testContextInstance;

	public:
		/// <summary>
		///Gets or sets the test context which provides
		///information about and functionality for the current test run.
		///</summary>
		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
		{
			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
			{
				return testContextInstance;
			}
			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
			{
				testContextInstance = value;
			}
		};

#pragma region Additional test attributes
		//
		//You can use the following additional attributes as you write your tests:
		//
		//Use ClassInitialize to run code before running the first test in the class
		//[ClassInitialize()]
		//static void MyClassInitialize(TestContext^ testContext) {};
		//
		//Use ClassCleanup to run code after all tests in a class have run
		//[ClassCleanup()]
		//static void MyClassCleanup() {};
		//
		//Use TestInitialize to run code before running each test
		//[TestInitialize()]
		//void MyTestInitialize() {};
		//
		//Use TestCleanup to run code after each test has run
		//[TestCleanup()]
		//void MyTestCleanup() {};
		//
#pragma endregion 

		//Helper Functions
#define WHITE 1
#define BLACK -1

		[TestMethod, Timeout(1000)]
		void Reversi_TestCreateGame()
		{
			ReversiGame *game = NULL;
			game = createNewGame(4, 3, "praveen", "abhijith");
			if (game != NULL){
				Assert::Fail("4x3 is not square should return NULL");
			}
			game = createNewGame(4, 4, "praveen", "abhijith");
			if (game == NULL){
				Assert::Fail("4x4 is square should not return NULL");
			}
			game = createNewGame(5, 5, "praveen", "abhijith");
			if (game == NULL){
				Assert::Fail("5x5 is square should not return NULL");
			}
		};

		[TestMethod, Timeout(1000)]
		void Reversi_TestInitializeWithColor()
		{
			int rows = 8, cols = 8;
			ReversiGame *game = createNewGame(rows, cols, "praveen", "abhijith");
			char table[8][9] =
			{
				"        ",
				"        ",
				"        ",
				"   wb   ",
				"   bw   ",
				"        ",
				"        ",
				"        "
			};

			initializeReversiGame(game, (char *)table, rows, cols, WHITE);
			Assert::AreEqual(1, game->turn, L"Board Initialization", 1, 2);
			Assert::AreEqual(0, game->NumberofMoves, L"Board Initialization", 1, 2);
			Assert::AreEqual(0, game->state, L"Board Initialization", 1, 2);
			Assert::AreEqual(rows, game->rows, L"Board Initialization", 1, 2);
			Assert::AreEqual(cols, game->cols, L"Board Initialization", 1, 2);
			Assert::AreEqual(cols, game->cols, L"Board Initialization", 1, 2);
			Assert::AreEqual(2, game->whiteCount, L"Board Initialization", 1, 2);
			Assert::AreEqual(2, game->blackCount, L"Board Initialization", 1, 2);

			initializeReversiGame(game, (char *)table, rows, cols, BLACK);
			Assert::AreEqual(-1, game->turn, L"Board Initialization", 1, 2);
		};

		[TestMethod, Timeout(1000)]
		void Reversi_TestInitGameOver()
		{
			int rows = 4, cols = 4;
			ReversiGame *game = createNewGame(rows, cols, "praveen", "abhijith");
			char table[4][5] =
			{
				"wwww",
				"bbbb",
				"bbbb",
				"bbbb"
			};

			initializeReversiGame(game, (char *)table, rows, cols, WHITE);
			Assert::AreEqual(checkReversiGameOver(game), 0, L"Game Not Completed", 1, 2);
			Assert::AreEqual(1, game->state, L"Board Initialization", 1, 2);
			Assert::AreEqual(-1, game->winner, L"Board Initialization", 1, 2);
		};

		[TestMethod, Timeout(1000)]
		void Reversi_TestInitGameOverZeroCoins()
		{
			int rows = 4, cols = 4;
			ReversiGame *game = createNewGame(rows, cols, "praveen", "abhijith");
			char table1[4][5] =
			{
				"wwww",
				"    ",
				"    ",
				"    "
			};

			initializeReversiGame(game, (char *)table1, rows, cols, WHITE);
			Assert::AreEqual(checkReversiGameOver(game), 0, L"Game Not Completed", 1, 2);
			Assert::AreEqual(1, game->state, L"Board Initialization", 1, 2);
			Assert::AreEqual(1, game->winner, L"Board Initialization", 1, 2);

			char table2[4][5] =
			{
				"bbbb",
				"    ",
				"    ",
				"    "
			};

			initializeReversiGame(game, (char *)table2, rows, cols, WHITE);
			Assert::AreEqual(checkReversiGameOver(game), 0, L"Game Not Completed", 1, 2);
			Assert::AreEqual(1, game->state, L"Board Initialization", 1, 2);
			Assert::AreEqual(-1, game->winner, L"Board Initialization", 1, 2);
		};

		[TestMethod, Timeout(1000)]
		void Reversi_TestInitGameDraw()
		{
			int rows = 4, cols = 4;
			ReversiGame *game = createNewGame(rows, cols, "praveen", "abhijith");
			char table1[4][5] =
			{
				"wwww",
				"wwww",
				"bbbb",
				"bbbb"
			};

			initializeReversiGame(game, (char *)table1, rows, cols, WHITE);
			Assert::AreEqual(1, game->state, L"Board Initialization", 1, 2);
			Assert::AreEqual(0, game->winner, L"Board Initialization", 1, 2);

			char table2[4][5] =
			{
				"wwww",
				"w   ",
				"   b",
				"bbbb"
			};

			initializeReversiGame(game, (char *)table2, rows, cols, WHITE);
			Assert::AreEqual(checkReversiGameOver(game), 0, L"Game Not Completed", 1, 2);
			Assert::AreEqual(1, game->state, L"Board Initialization", 1, 2);
			Assert::AreEqual(0, game->winner, L"Board Initialization", 1, 2);

		};

		[TestMethod, Timeout(1000)]
		void Reversi_TestMoveCount()
		{
			int rows = 8, cols = 8;
			ReversiGame *game = createNewGame(rows, cols, "praveen", "abhijith");
			char table1[8][9] =
			{
				"        ",
				"        ",
				"        ",
				"   wb   ",
				"   bw   ",
				"        ",
				"        ",
				"        "
			};

			initializeReversiGame(game, (char *)table1, rows, cols, WHITE);
			playMove(game, createMove(5, 3));
			playMove(game, createMove(6, 3));
			playMove(game, createMove(7, 3));
			playMove(game, createMove(3, 4));

			Assert::AreEqual(4, game->NumberofMoves, L"Board Initialization", 1, 2);
			Assert::AreEqual(WHITE, game->turn, L"Board Initialization", 1, 2);
			Assert::AreEqual(4, game->whiteCount, L"Board Initialization", 1, 2);
			Assert::AreEqual(4, game->blackCount, L"Board Initialization", 1, 2);
		};

		[TestMethod, Timeout(1000)]
		void Reversi_TestMoveInvalid()
		{
			int rows = 8, cols = 8;
			ReversiGame *game = createNewGame(rows, cols, "praveen", "abhijith");
			char table1[8][9] =
			{
				"        ",
				"        ",
				"        ",
				"   wb   ",
				"   bw   ",
				"        ",
				"        ",
				"        "
			};

			initializeReversiGame(game, (char *)table1, rows, cols, WHITE);
			playMove(game, createMove(6, 3));

			Assert::AreEqual(0, game->NumberofMoves, L"Board Initialization", 1, 2);
			Assert::AreEqual(WHITE, game->turn, L"Board Initialization", 1, 2);
			Assert::AreEqual(2, game->whiteCount, L"Board Initialization", 1, 2);
			Assert::AreEqual(2, game->blackCount, L"Board Initialization", 1, 2);

			playMove(game, createMove(5, 3));
			playMove(game, createMove(6, 3)); //invalid

			Assert::AreEqual(3, game->blackCount, L"Board Initialization", 1, 2);
			Assert::AreEqual(3, game->whiteCount, L"Board Initialization", 1, 2);
			Assert::AreEqual(2, game->NumberofMoves, L"Board Initialization", 1, 2);

			playMove(game, createMove(6, 3)); //invalid
			Assert::AreEqual(2, game->NumberofMoves, L"Board Initialization", 1, 2);
		};

		[TestMethod, Timeout(1000)]
		void Reversi_TestFullGame1()
		{
			int rows = 4, cols = 4;
			ReversiGame *game = createNewGame(rows, cols, "pvsmpraveen", "abhijith");
			char table1[4][5] =
			{
				"    ",
				" wb ",
				" bw ",
				"    "
			};

			initializeReversiGame(game, (char *)table1, rows, cols, WHITE);

			int MoveX[] = { 2, 1, 4, 3, 1, 1, 4, 3, 2, 1, 4, 4 };
			int MoveY[] = { 4, 4, 2, 4, 3, 2, 1, 1, 1, 1, 3, 4 };
			int whiteMoveCount[] = { 4, 3, 5, 4, 6, 4, 3, 5, 3, 5, 2, 4 };
			int blackMoveCount[] = { 1, 3, 2, 4, 3, 6, 8, 7, 10, 9, 13, 12 };
			for (int i = 0; i < 12; i++){
				Assert::AreEqual(checkReversiGameOver(game), 1, L"Game Not Completed", 1, 2);
				playMove(game, createMove(MoveX[i], MoveY[i]));
				Assert::AreEqual(whiteMoveCount[i], game->whiteCount, L"Board Initialization", 1, 2);
				Assert::AreEqual(blackMoveCount[i], game->blackCount, L"Board Initialization", 1, 2);
			}
			Assert::AreEqual(checkReversiGameOver(game), 0, L"Game Not Completed", 1, 2);
			Assert::AreEqual(12, game->NumberofMoves, L"Board Initialization", 1, 2);
			Assert::AreEqual(1, game->state, L"Board Initialization", 1, 2);
			Assert::AreEqual(BLACK, game->winner, L"Board Initialization", 1, 2);
		};

		[TestMethod, Timeout(1000)]
		void Reversi_TestFullGame2()
		{
			int rows = 4, cols = 4;
			ReversiGame *game = createNewGame(rows, cols, "praveen", "abhijith");
			char table1[4][5] =
			{
				"    ",
				" wb ",
				" bw ",
				"    "
			};

			initializeReversiGame(game, (char *)table1, rows, cols, WHITE);

			int MoveX[] = { 2, 1, 4, 3, 1, 1, 4, 3, 4, 4, 2, 1 };
			int MoveY[] = { 4, 4, 2, 4, 3, 2, 1, 1, 3, 4, 1, 1 };
			int whiteMoveCount[] = { 4, 3, 5, 4, 6, 4, 3, 5, 3, 5, 2, 4 };
			int blackMoveCount[] = { 1, 3, 2, 4, 3, 6, 8, 7, 10, 9, 13, 12 };
			for (int i = 0; i < 12; i++){
				Assert::AreEqual(checkReversiGameOver(game), 1, L"Game Not Completed", 1, 2);
				playMove(game, createMove(MoveX[i], MoveY[i]));
				Assert::AreEqual(whiteMoveCount[i], game->whiteCount, L"Board Initialization", 1, 2);
				Assert::AreEqual(blackMoveCount[i], game->blackCount, L"Board Initialization", 1, 2);
			}
			Assert::AreEqual(checkReversiGameOver(game), 0, L"Game Not Completed", 1, 2);
			Assert::AreEqual(12, game->NumberofMoves, L"Board Initialization", 1, 2);
			Assert::AreEqual(1, game->state, L"Board Initialization", 1, 2);
			Assert::AreEqual(BLACK, game->winner, L"Board Initialization", 1, 2);
		};


		[TestMethod, Timeout(1000)]
		void Reversi_TestFullGame3()
		{
			int rows = 4, cols = 4;
			ReversiGame *game = createNewGame(rows, cols, "praveen", "abhijith");
			char table1[4][5] =
			{
				"    ",
				" wb ",
				" bw ",
				"    "
			};

			initializeReversiGame(game, (char *)table1, rows, cols, WHITE);

			int MoveX[] = { 4, 4, 2, 4, 1, 1, 3, 4, 1, 1, 2, 3 };
			int MoveY[] = { 2, 3, 4, 1, 4, 3, 4, 4, 2, 1, 1, 1 };
			int whiteMoveCount[] = { 4, 3, 6, 5, 3, 5, 3, 5, 2, 4, 3, 6 };
			int blackMoveCount[] = { 1, 3, 1, 3, 6, 5, 8, 7, 11, 10, 12, 10 };
			for (int i = 0; i < 12; i++){
				Assert::AreEqual(checkReversiGameOver(game), 1, L"Game Not Completed", 1, 2);
				playMove(game, createMove(MoveX[i], MoveY[i]));
				Assert::AreEqual(whiteMoveCount[i], game->whiteCount, L"Board Initialization", 1, 2);
				Assert::AreEqual(blackMoveCount[i], game->blackCount, L"Board Initialization", 1, 2);
			}
			Assert::AreEqual(checkReversiGameOver(game), 0, L"Game Not Completed", 1, 2);
			Assert::AreEqual(12, game->NumberofMoves, L"Board Initialization", 1, 2);
			Assert::AreEqual(1, game->state, L"Board Initialization", 1, 2);
			Assert::AreEqual(BLACK, game->winner, L"Board Initialization", 1, 2);
		};

		[TestMethod, Timeout(1000)]
		void Reversi_TestFullGame4()
		{
			int rows = 4, cols = 4;
			ReversiGame *game = createNewGame(rows, cols, "praveen", "abhijith");
			char table1[4][5] =
			{
				"    ",
				" wb ",
				" bw ",
				"    "
			};

			initializeReversiGame(game, (char *)table1, rows, cols, WHITE);

			int MoveX[] = { 4, 4, 2, 4, 1, 1, 3, 4, 1, 1, 3 };
			int MoveY[] = { 2, 3, 4, 1, 4, 3, 4, 4, 2, 1, 1 };
			int whiteMoveCount[] = { 4, 3, 6, 5, 3, 5, 3, 5, 2, 4, 3, };
			int blackMoveCount[] = { 1, 3, 1, 3, 6, 5, 8, 7, 11, 10, 12 };
			int turn[] = { 1, -1, 1, -1, -1, 1, -1, 1, -1, 1, -1 };

			for (int i = 0; i < 11; i++){
				Assert::AreEqual(turn[i], game->turn, L"Board Initialization", 1, 2);
				Assert::AreEqual(checkReversiGameOver(game), 1, L"Game Not Completed", 1, 2);
				playMove(game, createMove(MoveX[i], MoveY[i]));
				Assert::AreEqual(whiteMoveCount[i], game->whiteCount, L"Board Initialization", 1, 2);
				Assert::AreEqual(blackMoveCount[i], game->blackCount, L"Board Initialization", 1, 2);
			}
			Assert::AreEqual(checkReversiGameOver(game), 0, L"Game Not Completed", 1, 2);
			Assert::AreEqual(11, game->NumberofMoves, L"Board Initialization", 1, 2);
			Assert::AreEqual(1, game->state, L"Board Initialization", 1, 2);
			Assert::AreEqual(BLACK, game->winner, L"Board Initrrrialization", 1, 2);
		};

		[TestMethod, Timeout(1000)]
		void Reversi_TestHelpers1()
		{
			int rows = 4, cols = 4;
			ReversiGame *game = createNewGame(rows, cols, "praveen", "abhijith");
			char table1[4][5] =
			{
				"    ",
				" wb ",
				" bw ",
				"    "
			};

			initializeReversiGame(game, (char *)table1, rows, cols, WHITE);
			Assert::AreEqual(0,isvalidCoordinate(game,-1,4), L"IsValidCoordinate( Out Of Range )", 1,2);

			Assert::AreEqual(0, isValidMove(game,createMove(2,3)), L"IsValidMove( Not Empty Square )", 1, 2);
			Assert::AreEqual(0, isValidMove(game,createMove(-1,4)), L"IsValidMove( Out Of Range )", 1, 2);
			Assert::AreEqual(1, isValidMove(game,createMove(1,3)), L"IsValidMove( Valid )", 1, 2);
			Assert::AreEqual(0, isValidMove(game, createMove(1,2)), L"IsValidMove( Nothing to Capture )", 1, 2);
			Assert::AreEqual(1, isValidMove(game, createMove(3, 1)), L"IsValidMove( Valid )", 1, 2);
		};

		[TestMethod, Timeout(1000)]
		void Reversi_TestHelpers2()
		{
			int rows = 4, cols = 4;
			ReversiGame *game = createNewGame(rows, cols, "praveen", "abhijith");
			char table1[4][5] =
			{
				"wwww",
				"    ",
				"  wb",
				"bbbb"
			};

			initializeReversiGame(game, (char *)table1, rows, cols, WHITE);
			game->turn = WHITE;
			Assert::AreEqual(0, hasMove(game), L"hasMove( False )", 1, 2);
			game->turn = BLACK;
			Assert::AreEqual(1, hasMove(game), L"hasMove( False )", 1, 2);
			playMove(game, createMove(2, 2));
			Assert::AreEqual(1, game->NumberofMoves, L"hasMove( False )", 1, 2);
			Assert::AreEqual(WHITE, game->turn, L"Turn( White )", 1, 2);

		};

		[TestMethod, Timeout(1000)]
		void Reversi_TestHelpers3()
		{
			int rows = 4, cols = 4;
			ReversiGame *game = createNewGame(rows, cols, "praveen", "abhijith");
			char table1[4][5] =
			{
				"wwww",
				"    ",
				"  wb",
				"bbbb"
			};

			initializeReversiGame(game, (char *)table1, rows, cols, WHITE);
			
			Assert::AreEqual(BLACK, game->turn, L"hasMove( False )", 1, 2);
			Assert::AreEqual(0, game->NumberofMoves, L"MoveCount( ++ )", 1, 2);
			for (int i = 1; i <= 10; i++){
				incrementMoves(game);
				Assert::AreEqual(i, game->NumberofMoves, L"MoveCount( ++ )", 1, 2);
			}
			Assert::AreEqual(BLACK, game->turn, L"Turn", 1, 2);
			modifyTurn(game);
			Assert::AreEqual(WHITE, game->turn, L"Turn", 1, 2);
		};

		[TestMethod, Timeout(1000)]
		void Reversi_TestHelpers4()
		{
			int rows = 4, cols = 4;
			ReversiGame *game = createNewGame(rows, cols, "praveen", "abhijith");
			char table1[4][5] =
			{
				"wwww",
				"    ",
				"  wb",
				"bbbb"
			};

			initializeReversiGame(game, (char *)table1, rows, cols, WHITE);

			ReversiMove *move = createMove(5, 4);
			if (move == NULL){
				Assert::Fail("Should Not Return NULL for Valid Move");
			}

			Assert::AreEqual(0, game->state, L"Turn", 1, 2);
			Assert::AreEqual(0, game->state, L"Turn", 1, 2);
			endGame(game);
			Assert::AreEqual(1, game->state, L"Turn", 1, 2);

		};
	};

}
