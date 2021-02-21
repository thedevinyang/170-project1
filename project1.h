// Devin Yang
// SID: 862021705

#ifndef _PROJECT1_H_
#define _PROJECT1_H_

#include <stdio.h>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <ctime>


using namespace std;

const int puzzleSize = 9; // Change for larger puzzles

class puzzleFunctions {
	public:
		puzzleFunctions();
		int parent[puzzleSize];
		int heuristic;
		int depth;
		
		void copyPuzzle(int inputPuzzle[puzzleSize], int outputPuzzle[puzzleSize]); // Creates a copy of the current board state
		void outputBoard(); // Outputs the current puzzle state
		int findBlank(); // Checks if the current puzzle has a space in it
		bool goalChecker(); // Checks if the array is in ascending value
		void expand(puzzleFunctions node); // Expands tree with all possible moves
		void puzzleUp(puzzleFunctions node, int blankPosition); // Attempts to move the blank up one square
		void puzzleDown(puzzleFunctions node, int blankPosition); // Attempts to move the blank down one square
		void puzzleLeft(puzzleFunctions node, int blankPosition); // Attempts to move the blank left one square
		void puzzleRight(puzzleFunctions node, int blankPosition); // Attempts to move the blank right one square
		
		void uniformSearch(puzzleFunctions node);
		void misplacedTileSearch(puzzleFunctions node);
		void manhattanDistanceSearch(puzzleFunctions node);
		int misplacedHeuristic(puzzleFunctions node); // Calculates heuristic for any misplaced tiles in the puzzle
		int manhattanHeuristic(puzzleFunctions node); // Calculates heuristic for manhattan distances in the puzzle
};

class comparisonOverload { // Reverses order of nodes in the priority queue
	public:
		bool operator()(const puzzleFunctions nodeA, const puzzleFunctions nodeB) {
			if ((nodeA.depth + nodeA.heuristic) > (nodeB.depth + nodeB.heuristic)){
				return true;
			} else {
				return false;
			}
		}
};	

#endif
