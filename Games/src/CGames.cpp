#define _CRT_SECURE_NO_WARNINGS

//Helper Utils
#include "C15BoardUtils.h"
#include "C15UserUtils.h"
#include "C15MovesUtils.h"

#include "C15Puzzle.cpp"

#include "ReversiBoardUtils.h"
#include "ReversiMovesUtils.h"

#include "CReversi.cpp"

int main(){

	/*
		Read The Description in C15Puzzle.h
	*/

	//c15Puzzle_main();

	/*
		Read The Description in Reversi.h
	*/

	Reversi_main();

	system("pause");
	return 0;
}