#include "stdafx.h"
#include "./../src/C15BoardUtils.h"
#include "./../src/C15UserUtils.h"
#include "./../src/C15MovesUtils.h"


using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace spec
{
	[TestClass]
	public ref class C15PuzzleSpec
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
		void checkTable(int **actualArr, int *expectedArr, int rows, int cols){
			int i = 0;
			int j = 0;
			for (i = 0; i < rows; i++){
				for (j = 0; j < cols; j++){
					int expected = *((expectedArr + i*cols) + j);
					int actual = actualArr[i][j];
					System::String^ errorStr = gcnew System::String("Expected :" + expected + " Actual :" + actual + " at [" + i + "][" + j + "]");
					Assert::AreEqual(expected, actual, errorStr, 1, 2);
				}
			}
		}
		void checkTable(int **expectedArr, int **actualArr, int rows, int cols){
			int i = 0;
			int j = 0;
			for (i = 0; i < rows; i++){
				for (j = 0; j < cols; j++){
					int expected = expectedArr[i][j];
					int actual = actualArr[i][j];
					System::String^ errorStr = gcnew System::String("Expected :" + expected + " Actual :" + actual + " at [" + i + "][" + j + "]");
					Assert::AreEqual(expected, actual, errorStr, 1, 2);
				}
			}
		}
		[TestMethod, Timeout(1000)]
		void C15Puzzle_TestCreateBoardNegetiveTests()
		{
			Board *b = createBoard(-1, -1);
			if (b != NULL){
				Assert::Fail("Create Board for -1/0 rows or cols should have returned NULL");
			}
			b = createBoard(-1, 1);
			if (b != NULL){
				Assert::Fail("Create Board for -1/0 rows or cols should have returned NULL");
			}
			b = createBoard(0, 0);
			if (b != NULL){
				Assert::Fail("Create Board for -1/0 rows or cols should have returned NULL");
			}
		};

		[TestMethod, Timeout(1000)]
		void C15Puzzle_TestCreateBoardPositiveTest1()
		{
			int rows = 4;
			int cols = 4;
			Board *b = createBoard(rows, cols);
			if (b == NULL){
				Assert::Fail("Create Board for 4/4 rows or cols should not have returned NULL");
			}

			if (b->table == NULL){
				Assert::Fail("Failed to Allocatted Memory properly for board->table ,Use Malloc Properly");
			}

			//Testing Access
			b->table[2][3] = 0;

			Assert::AreEqual(4, b->rows, L"board->rows should be 4", 1, 2);
			Assert::AreEqual(4, b->cols, L"board->cols should be 4", 1, 2);
			Assert::AreEqual(0, b->emptyTileCol, L"board->emptyTileCol should be 0", 1, 2);
			Assert::AreEqual(0, b->emptyTileRow, L"board->emptyTileRow should be 0", 1, 2);

		};

		[TestMethod, Timeout(1000)]
		void C15Puzzle_TestInitializeBoardNegetive()
		{
			Board *board = createBoard(4, 4);
			initializeBoard(NULL, NULL, -1, -1);


		};

		[TestMethod, Timeout(1000)]
		void C15Puzzle_TestInitializeBoardPostive()
		{
			int rows = 4;
			int cols = 4;
			Board *board = createBoard(rows, cols);
			int table[][4] = { 1, 2, 3, 4, 5, 7, 0, 8, 9, 6, 11, 12, 13, 10, 14, 15 };
			initializeBoard(board, (int *)table, rows, cols);

			if (board == NULL){
				Assert::Fail("Create Board for 4/4 rows or cols should not have returned NULL");
			}
			
			if (board->table == NULL){
				Assert::Fail("Failed to Allocatted Memory properly for board->table ,Use Malloc Properly");
			}

			checkTable(board->table, (int *)table, rows, cols);

		};


		[TestMethod, Timeout(1000)]
		void C15Puzzle_TestCheckBoardNegetive()
		{
			int rows = 4;
			int cols = 4;
			Board *board = createBoard(rows, cols);
			int table[][4] = { 1, 2, 3, 4, 5, 7, 0, 8, 9, 6, 11, 12, 13, 10, 14, 15 };
			initializeBoard(board, (int *)table, rows, cols);

			if (board == NULL){
				Assert::Fail("Create Board for 4/4 rows or cols should not have returned NULL");
			}

			if (board->table == NULL){
				Assert::Fail("Failed to Allocatted Memory properly for board->table ,Use Malloc Properly");
			}

			int check = checkBoard(board);

			Assert::AreEqual(0, check, "checkBoard should return 0", 1, 2);

		};


		[TestMethod, Timeout(1000)]
		void C15Puzzle_TestCheckBoardPositive()
		{
			int rows = 4;
			int cols = 4;
			Board *board = createBoard(rows, cols);
			int table[][4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0 };
			initializeBoard(board, (int *)table, rows, cols);

			if (board == NULL){
				Assert::Fail("Create Board for 4/4 rows or cols should not have returned NULL");
			}

			if (board->table == NULL){
				Assert::Fail("Failed to Allocatted Memory properly for board->table ,Use Malloc Properly");
			}

			int check = checkBoard(board);

			Assert::AreEqual(1, check, "checkBoard should return 1", 1, 2);

		};
		//UserTesting Helpers
		void compareUser(User *expectedUser, User *actualUser){

			compareStrings(expectedUser->name, actualUser->name);

			Assert::AreEqual(expectedUser->movesCount, actualUser->movesCount, "Moves Count not properly Modified", 1, 2);

		}

		//UserTesting
		[TestMethod, Timeout(1000)]
		void C15Puzzle_TestCreateUser(){
			char *name = "Abhijith";
			User *actualUser = createUser(name);

			compareStrings(actualUser->name, name);

			Assert::AreEqual(0, actualUser->movesCount, "Moves Count not properly Modified ,It Should be 0", 1, 2);
		}

		[TestMethod, Timeout(1000)]
		void C15Puzzle_TestModifyMoveCountBasedOnProccessInput(){
			char *name = "Abhijith";
			User *actualUser = createUser(name);
			modifyMoveCountBasedOnProccessInput(actualUser, 0);
			compareStrings(actualUser->name, name);

			Assert::AreEqual(0, actualUser->movesCount, "Moves Count not properly Modified ,It Should be 0", 1, 2);

			modifyMoveCountBasedOnProccessInput(actualUser, 1);

			Assert::AreEqual(1, actualUser->movesCount, "Moves Count not properly Modified ,It Should be 1", 1, 2);
		}
		//MovesTestingHelpers
		void validateBoard(Board *board){
			if (board == NULL){
				Assert::Fail("Board should be NULL");
			}

			if (board->table == NULL){
				Assert::Fail("Failed to Allocatted Memory properly for board->table ,Use Malloc Properly");
			}
		}

		void checkRows(Board *expectedBoard, Board *actualBoard){
			Assert::AreEqual(expectedBoard->rows, actualBoard->rows, L"Rows mismatch", 1, 2);
		}

		void checkColumns(Board *expectedBoard, Board *actualBoard){
			Assert::AreEqual(expectedBoard->cols, actualBoard->cols, L"Cols mismatch", 1, 2);
		}

		void checkEmptyTileRow(Board *expectedBoard, Board *actualBoard){
			Assert::AreEqual(expectedBoard->emptyTileRow, actualBoard->emptyTileRow, L"Empty Tile Row Mismatch", 1, 2);
		}

		void checkEmptyTileCol(Board *expectedBoard, Board *actualBoard){
			Assert::AreEqual(expectedBoard->emptyTileCol, actualBoard->emptyTileCol, L"Empty Tile Cols mismatch", 1, 2);
		}

		void checkEmptyTilePosition(Board *expectedBoard, Board *actualBoard){
			checkEmptyTileRow(expectedBoard, actualBoard);
			checkEmptyTileCol(expectedBoard, actualBoard);
		}

		void compareBoards(Board *expectedBoard, Board *actualBoard){
			validateBoard(expectedBoard);
			validateBoard(actualBoard);
			checkRows(expectedBoard, actualBoard);
			checkColumns(expectedBoard, actualBoard);
			checkEmptyTilePosition(expectedBoard, actualBoard);
		}

		Board * createBoardSpec(int *table, int rows, int cols){
			Board *board = createBoard(rows, cols);
			initializeBoard(board, table, rows, cols);
			return board;
		}


		void compareStrings(char *expectedStr, char *actualStr){
			int i = 0;
			char NULL_CHAR = '\0';
			while (expectedStr[i] != NULL_CHAR){
				Assert::AreEqual(expectedStr[i], actualStr[i], "User names mismatch", 1, 2);
				i++;
			}
			Assert::AreEqual(expectedStr[i], actualStr[i], "User names mismatch", 1, 2);

		}


		void compareBoardAndUsers(Board *expectedBoard, Board *actualBoard, User *expectedUser, User *actualUser){
			compareBoards(expectedBoard, actualBoard);
			compareUser(expectedUser, actualUser);
		}

		void testMove(int *sourceTable, int *expectedTable, int rows, int cols, int expectedMoves, char *name, char moveMade){
			Board *board = createBoardSpec((int *)sourceTable, rows, cols);
			Board *expectedBoard = createBoardSpec((int *)expectedTable, rows, cols);

			User *user = createUser(name);
			User *expectedUser = createUser(name);
			expectedUser->movesCount = expectedMoves;

			playMove(board, user, moveMade);

			compareBoardAndUsers(expectedBoard, board, expectedUser, user);
		}

		void testMoves(int *sourceTable, int *expectedTable, int rows, int cols, int expectedMoves, char *name, char *movesMade){
			Board *board = createBoardSpec((int *)sourceTable, rows, cols);
			Board *expectedBoard = createBoardSpec((int *)expectedTable, rows, cols);

			User *user = createUser(name);
			User *expectedUser = createUser(name);
			expectedUser->movesCount = expectedMoves;

			int index = 0;
			while (movesMade[index] != '\0'){
				char moveMade = movesMade[index];
				playMove(board, user, moveMade);
				index++;
			}

			compareBoardAndUsers(expectedBoard, board, expectedUser, user);
		}


		//Moves Testing
		[TestMethod, Timeout(1000)]
		void C15Puzzle_TestMoveRightValid()
		{
			int rows = 4;
			int cols = 4;

			int sourceTable[][4] = { 1, 2, 3, 4,
				5, 7, 0, 8,
				9, 6, 11, 12,
				13, 10, 14, 15 };
			int expectedTable[][4] = {
				{ 1, 2, 3, 4 },
				{ 5, 0, 7, 8 },
				{ 9, 6, 11, 12 },
				{ 13, 10, 14, 15 }
			};

			int expectedMoves = 1;
			char moveMade = 'D';

			testMove((int *)sourceTable, (int *)expectedTable, rows, cols, expectedMoves, "Abhijith", moveMade);

		};

		[TestMethod, Timeout(1000)]
		void C15Puzzle_TestMoveRightInValid()
		{
			int rows = 4;
			int cols = 4;

			int sourceTable[][4] = { 1, 2, 3, 4,
				0, 5, 7, 8,
				9, 6, 11, 12,
				13, 10, 14, 15 };
			int expectedTable[][4] = {
				{ 1, 2, 3, 4 },
				{ 0, 5, 7, 8 },
				{ 9, 6, 11, 12 },
				{ 13, 10, 14, 15 }
			};

			int expectedMoves = 0;
			char moveMade = 'd';

			testMove((int *)sourceTable, (int *)expectedTable, rows, cols, expectedMoves, "Abhijith", moveMade);

		};

		[TestMethod, Timeout(1000)]
		void C15Puzzle_TestMoveLeftValid()
		{
			int rows = 4;
			int cols = 4;

			int sourceTable[][4] = { 1, 2, 3, 4,
				5, 7, 0, 8,
				9, 6, 11, 12,
				13, 10, 14, 15 };
			int expectedTable[][4] = {
				{ 1, 2, 3, 4 },
				{ 5, 7, 8, 0 },
				{ 9, 6, 11, 12 },
				{ 13, 10, 14, 15 }
			};

			int expectedMoves = 1;
			char moveMade = 'a';

			testMove((int *)sourceTable, (int *)expectedTable, rows, cols, expectedMoves, "Abhijith", moveMade);

		};

		[TestMethod, Timeout(1000)]
		void C15Puzzle_TestMoveLeftInValid()
		{
			int rows = 4;
			int cols = 4;

			int sourceTable[][4] = {
				{ 1, 2, 3, 4 },
				{ 5, 7, 8, 12 },
				{ 9, 6, 11, 15 },
				{ 13, 10, 14, 0 }
			};

			int expectedTable[][4] = {
				{ 1, 2, 3, 4 },
				{ 5, 7, 8, 12 },
				{ 9, 6, 11, 15 },
				{ 13, 10, 14, 0 }
			};

			int expectedMoves = 0;
			char moveMade = 'A';

			testMove((int *)sourceTable, (int *)expectedTable, rows, cols, expectedMoves, "Abhijith", moveMade);

		};

		[TestMethod, Timeout(1000)]
		void C15Puzzle_TestMoveUpInValid()
		{
			int rows = 4;
			int cols = 4;

			int sourceTable[][4] = {
				{ 1, 2, 3, 4 },
				{ 5, 7, 8, 12 },
				{ 9, 6, 11, 15 },
				{ 13, 10, 14, 0 }
			};

			int expectedTable[][4] = {
				{ 1, 2, 3, 4 },
				{ 5, 7, 8, 12 },
				{ 9, 6, 11, 15 },
				{ 13, 10, 14, 0 }
			};

			int expectedMoves = 0;
			char moveMade = 'W';

			testMove((int *)sourceTable, (int *)expectedTable, rows, cols, expectedMoves, "Abhijith", moveMade);

		};

		[TestMethod, Timeout(1000)]
		void C15Puzzle_TestMoveUpValid()
		{
			int rows = 4;
			int cols = 4;

			int sourceTable[][4] = {
				{ 1, 2, 3, 4 },
				{ 5, 7, 8, 12 },
				{ 9, 6, 11, 0 },
				{ 13, 10, 14, 15 }
			};

			int expectedTable[][4] = {
				{ 1, 2, 3, 4 },
				{ 5, 7, 8, 12 },
				{ 9, 6, 11, 15 },
				{ 13, 10, 14, 0 }
			};

			int expectedMoves = 1;
			char moveMade = 'w';

			testMove((int *)sourceTable, (int *)expectedTable, rows, cols, expectedMoves, "Abhijith", moveMade);

		};

		[TestMethod, Timeout(1000)]
		void C15Puzzle_TestMoveDownValid()
		{
			int rows = 4;
			int cols = 4;

			int sourceTable[][4] = {
				{ 1, 2, 3, 4 },
				{ 5, 7, 8, 12 },
				{ 9, 6, 11, 15 },
				{ 13, 10, 14, 0 }
			};

			int expectedTable[][4] = {
				{ 1, 2, 3, 4 },
				{ 5, 7, 8, 12 },
				{ 9, 6, 11, 0 },
				{ 13, 10, 14, 15 }
			};

			int expectedMoves = 1;
			char moveMade = 's';

			testMove((int *)sourceTable, (int *)expectedTable, rows, cols, expectedMoves, "Abhijith", moveMade);

		};

		[TestMethod, Timeout(1000)]
		void C15Puzzle_TestMoveDownInValid()
		{
			int rows = 4;
			int cols = 4;

			int sourceTable[][4] = {
				{ 1, 2, 3, 0 },
				{ 5, 7, 8, 4 },
				{ 9, 6, 11, 12 },
				{ 13, 10, 14, 15 }
			};

			int expectedTable[][4] = {
				{ 1, 2, 3, 0 },
				{ 5, 7, 8, 4 },
				{ 9, 6, 11, 12 },
				{ 13, 10, 14, 15 }
			};

			int expectedMoves = 0;
			char moveMade = 's';

			testMove((int *)sourceTable, (int *)expectedTable, rows, cols, expectedMoves, "Abhijith", moveMade);

		};

		[TestMethod, Timeout(1000)]
		void C15Puzzle_TestMoveSequence1()
		{
			int rows = 4;
			int cols = 4;

			int sourceTable[][4] = {
				{ 1, 2, 3, 4 },
				{ 0, 5, 7, 8 },
				{ 10, 6, 11, 12 },
				{ 9, 13, 14, 15 }
			};

			int expectedTable[][4] = {
				{ 1, 2, 4, 0 },
				{ 5, 7, 3, 8 },
				{ 10, 6, 11, 12 },
				{ 9, 13, 14, 15 }
			};
			int expectedMoves = 14;
			char movesMade[100] = "DDDSWWSAASSSSAwsdadaaaaa";
			testMoves((int *)sourceTable, (int *)expectedTable, rows, cols, expectedMoves, "Abhijith", movesMade);

		};

		[TestMethod, Timeout(1000)]
		void C15Puzzle_TestMoveSequence2()
		{
			int rows = 4;
			int cols = 4;

			int sourceTable[][4] = {
				{ 1, 2, 3, 4 },
				{ 0, 5, 7, 8 },
				{ 10, 6, 11, 12 },
				{ 9, 13, 14, 15 }
			};

			int expectedTable[][4] = {
				{ 1, 2, 3, 4 },
				{ 10, 5, 7, 8 },
				{ 9, 11, 14, 0 },
				{ 13, 6, 15, 12 }
			};

			int expectedMoves = 10;
			char movesMade[100] = "wdwddaswsawasaaaa";
			testMoves((int *)sourceTable, (int *)expectedTable, rows, cols, expectedMoves, "Abhijith", movesMade);

		};

		[TestMethod, Timeout(1000)]
		void C15Puzzle_TestMoveSequenceHard1()
		{
			int rows = 4;
			int cols = 4;

			int sourceTable[][4] = {
				{ 1, 2, 3, 4 },
				{ 5, 6, 7, 8 },
				{ 9, 10, 11, 12 },
				{ 13, 14, 15, 0 }
			};


			int expectedMoves = 26;
			char movesMade[100] = "dDdSASasADWddaasaDWDWDwaaa";

			testMoves((int *)sourceTable, (int *)sourceTable, rows, cols, expectedMoves, "Abhijith", movesMade);

		};

		[TestMethod, Timeout(1000)]
		void C15Puzzle_TestMoveSequenceHard2()
		{
			int rows = 4;
			int cols = 4;

			int sourceTable[][4] = {
				{ 1, 2, 3, 4 },
				{ 5, 6, 7, 8 },
				{ 9, 10, 11, 12 },
				{ 13, 14, 15, 0 }
			};


			int expectedMoves = 52;
			char movesMade[100] = "dDdSASasADWddaasaDWDWDwaaadDdSASasADWddaasaDWDWDwaaa";


			testMoves((int *)sourceTable, (int *)sourceTable, rows, cols, expectedMoves, "Abhijith", movesMade);

		};

		//Test Win Condition
		[TestMethod, Timeout(1000)]
		void C15Puzzle_TestMoveSequenceLeadingToWin()
		{
			int rows = 4;
			int cols = 4;

			int sourceTable[][4] = {
				{ 1, 2, 3, 4 },
				{ 0, 5, 7, 8 },
				{ 10, 6, 11, 12 },
				{ 9, 13, 14, 15 }
			};

			int expectedTable[][4] = {
				{ 1, 2, 3, 4 },
				{ 5, 6, 7, 8 },
				{ 9, 10, 11, 12 },
				{ 13, 14, 15, 0 }
			};

			int expectedMoves = 13;
			char movesMade[100] = "aaSADWdWDwdwaaa";

			Board *board = createBoardSpec((int *)sourceTable, rows, cols);
			Board *expectedBoard = createBoardSpec((int *)expectedTable, rows, cols);

			User *user = createUser("Abhijith");
			User *expectedUser = createUser("Abhijith");
			expectedUser->movesCount = expectedMoves;

			int index = 0;
			while (movesMade[index] != '\0'){
				char moveMade = movesMade[index];
				playMove(board, user, moveMade);
				index++;
			}

			compareBoardAndUsers(expectedBoard, board, expectedUser, user);

			int check = checkBoard(board);

			Assert::AreEqual(1, check, "Win Conditon not satisfied ,check CheckBoard", 1, 2);
		};


	};

}
