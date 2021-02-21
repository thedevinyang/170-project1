// Devin Yang
// SID: 862021705

#include <stdio.h>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <ctime>
#include "project1.h"

using namespace std;

vector<puzzleFunctions> nodeQueue;
priority_queue<puzzleFunctions, vector<puzzleFunctions>, comparisonOverload> minHeap; // min-heap priority queue

int searchChoice;
int totalNodesStandard = 0; 
int totalNodesPriority = 0;
int nodeCount = 0; // Total number of nodes expanded to reach goal
int gn = 0;
bool isCorrect = false;


puzzleFunctions::puzzleFunctions() { // Creates an inital array filled with zeroes
	for (int i = 0; i < puzzleSize; i++){
		parent[i] = 0;
	}
}


void puzzleFunctions::copyPuzzle(int inputPuzzle[puzzleSize], int outputPuzzle[puzzleSize]){ // Creates a copy of the current board state
	for (int i = 0; i < puzzleSize; i++){
		outputPuzzle[i] = inputPuzzle[i];
	}
}


void puzzleFunctions::outputBoard(){ // Outputs the current puzzle state
	cout << this->parent[0] << " " << this->parent[1] << " " << this->parent[2] << endl;
	cout << this->parent[3] << " " << this->parent[4] << " " << this->parent[5] << endl;
	cout << this->parent[6] << " " << this->parent[7] << " " << this->parent[8] << endl;
}


int puzzleFunctions::findBlank(){ // Checks if the current puzzle has a space in it
	int blankLocation = -1;
	for (int i = 0; i < puzzleSize; i++){
		if (this->parent[i] == 0){
			blankLocation = i;
		}
	}
	if (blankLocation == -1){
		cout << "There is no blank in this puzzle." << endl;
	} else { 
		cout << "The blank is located on square " << blankLocation << "." << endl;
	}
	return blankLocation;
}


bool puzzleFunctions::goalChecker(){ // Checks if the array is in ascending value
	bool goalMet = false;
	if (this->parent[0] == 1 && this->parent[1] == 2 &&
		this->parent[2] == 3 && this->parent[3] == 4 &&
		this->parent[4] == 5 && this->parent[5] == 6 &&
		this->parent[6] == 7 && this->parent[7] == 8 &&
		this->parent[8] == 0){
		goalMet = true;
	}
	return goalMet;
}


void puzzleFunctions::expand(puzzleFunctions node){ // Expands tree with all possible moves
	node.goalChecker();
	int blankPosition = node.findBlank();
	gn++;
	nodeCount++;
	puzzleUp(node, blankPosition);
	puzzleDown(node, blankPosition);
	puzzleLeft(node, blankPosition);
	puzzleRight(node, blankPosition);
}
	

void puzzleFunctions::puzzleUp(puzzleFunctions node, int blankPosition){ // Attempts to move the blank up one square
	if (isCorrect == false){
		if (blankPosition - 3 >= 0){
			// Cant move up on squares 0, 1, and 2
			// 0* 1* 2*
			// 3  4  5
			// 6  7  8
			puzzleFunctions child;
			copyPuzzle(node.parent, child.parent);
			swap(child.parent[blankPosition - 3], child.parent[blankPosition]); // Indexes need to be changed for larger puzzles
			if (searchChoice == 1){ // Uniform Cost
				child.heuristic = 0;
			}
			if (searchChoice == 2){ // A* Misplaced
				child.heuristic = child.misplacedHeuristic(child);
			}
			if (searchChoice == 3){ // A* Manhattan
				child.heuristic = child.manhattanHeuristic(child);
			}
			if (child.goalChecker() == false){
				child.depth = gn;
				if (searchChoice == 1){ 
					nodeQueue.push_back(child);
				}
				if (searchChoice == 2){ 
					minHeap.push(child);
				}
				if (searchChoice == 3){ 
					minHeap.push(child);
				}
				cout << "g(n) = " << gn << " and h(n) = " << child.heuristic << endl;
				child.outputBoard();
				cout << "Expanding this node..." << endl;
			} 
			if (child.goalChecker() == true){
				cout << "g(n) = " << gn << " and h(n) = " << child.heuristic << endl;
				child.outputBoard();
				cout << "To solve the problem the search algorithm expanded a total of " << nodeCount << " nodes." << endl;
				if (searchChoice == 1) {
					cout << "The maximum number of nodes in the queue at any one time was " << totalNodesStandard << "." << endl;
				} else {
					cout << "The maximum number of nodes in the queue at any one time was " << totalNodesPriority << "." << endl;
				}
				isCorrect = true;
			}
		}
		int temp;
		temp = nodeQueue.size();
		if (temp > totalNodesStandard){
			totalNodesStandard = nodeQueue.size();
		}
		temp = minHeap.size();
		if (temp > totalNodesPriority){
			totalNodesPriority = minHeap.size();
		}
	}
}


void puzzleFunctions::puzzleDown(puzzleFunctions node, int blankPosition){ // Attempts to move the blank down one square
	if (isCorrect == false){
		if (blankPosition + 3 < 9){
			// Cant move down on squares 6, 7, and 8
			// 0  1  2 
			// 3  4  5
			// 6* 7* 8*
			puzzleFunctions child;
			copyPuzzle(node.parent, child.parent);
			swap(child.parent[blankPosition + 3], child.parent[blankPosition]); // Indexes need to be changed for larger puzzles
			if (searchChoice == 1){ // Uniform Cost
				child.heuristic = 0;
			}
			if (searchChoice == 2){ // A* Misplaced
				child.heuristic = child.misplacedHeuristic(child);
			}
			if (searchChoice == 3){ // A* Manhattan
				child.heuristic = child.manhattanHeuristic(child);
			}
			if (child.goalChecker() == false){
				child.depth = gn;
				if (searchChoice == 1){ 
					nodeQueue.push_back(child);
				}
				if (searchChoice == 2){ 
					minHeap.push(child);
				}
				if (searchChoice == 3){ 
					minHeap.push(child);
				}
				cout << "g(n) = " << gn << " and h(n) = " << child.heuristic << endl;
				child.outputBoard();
				cout << "Expanding this node..." << endl;
			} 
			if (child.goalChecker() == true){
				cout << "g(n) = " << gn << " and h(n) = " << child.heuristic << endl;
				child.outputBoard();
				cout << "To solve the problem the search algorithm expanded a total of " << nodeCount << " nodes." << endl;
				if (searchChoice == 1) {
					cout << "The maximum number of nodes in the queue at any one time was " << totalNodesStandard << "." << endl;
				} else {
					cout << "The maximum number of nodes in the queue at any one time was " << totalNodesPriority << "." << endl;
				}
				isCorrect = true;
			}
		}
		int temp;
		temp = nodeQueue.size();
		if (temp > totalNodesStandard){
			totalNodesStandard = nodeQueue.size();
		}
		temp = minHeap.size();
		if (temp > totalNodesPriority){
			totalNodesPriority = minHeap.size();
		}
	}
}


void puzzleFunctions::puzzleLeft(puzzleFunctions node, int blankPosition){ // Attempts to move the blank left one square
	if (isCorrect == false){
		if (blankPosition % 3 > 0){
			// Cant move left on squares 0, 3, and 6
			// 0* 1  2
			// 3* 4  5
			// 6* 7  8
			puzzleFunctions child;
			copyPuzzle(node.parent, child.parent);
			swap(child.parent[blankPosition - 1], child.parent[blankPosition]); // Indexes need to be changed for larger puzzles
			if (searchChoice == 1){ // Uniform Cost
				child.heuristic = 0;
			}
			if (searchChoice == 2){ // A* Misplaced
				child.heuristic = child.misplacedHeuristic(child);
			}
			if (searchChoice == 3){ // A* Manhattan
				child.heuristic = child.manhattanHeuristic(child);
			}
			if (child.goalChecker() == false){
				child.depth = gn;
				if (searchChoice == 1){ 
					nodeQueue.push_back(child);
				}
				if (searchChoice == 2){ 
					minHeap.push(child);
				}
				if (searchChoice == 3){ 
					minHeap.push(child);
				}
				cout << "g(n) = " << gn << " and h(n) = " << child.heuristic << endl;
				child.outputBoard();
				cout << "Expanding this node..." << endl;
			} 
			if (child.goalChecker() == true){
				cout << "g(n) = " << gn << " and h(n) = " << child.heuristic << endl;
				child.outputBoard();
				cout << "To solve the problem the search algorithm expanded a total of " << nodeCount << " nodes." << endl;
				if (searchChoice == 1) {
					cout << "The maximum number of nodes in the queue at any one time was " << totalNodesStandard << "." << endl;
				} else {
					cout << "The maximum number of nodes in the queue at any one time was " << totalNodesPriority << "." << endl;
				}
				isCorrect = true;
			}
		}
		int temp;
		temp = nodeQueue.size();
		if (temp > totalNodesStandard){
			totalNodesStandard = nodeQueue.size();
		}
		temp = minHeap.size();
		if (temp > totalNodesPriority){
			totalNodesPriority = minHeap.size();
		}
	}
}


void puzzleFunctions::puzzleRight(puzzleFunctions node, int blankPosition){ // Attempts to move the blank right one square
	if (isCorrect == false){
		if (blankPosition % 3 < 2){
			// Cant move right on squares 2, 5, and 8
			// 0  1  2*
			// 3  4  5*
			// 6  7  8*
			puzzleFunctions child;
			copyPuzzle(node.parent, child.parent);
			swap(child.parent[blankPosition + 1], child.parent[blankPosition]); // Indexes need to be changed for larger puzzles
			if (searchChoice == 1){ // Uniform Cost
				child.heuristic = 0;
			}
			if (searchChoice == 2){ // A* Misplaced
				child.heuristic = child.misplacedHeuristic(child);
			}
			if (searchChoice == 3){ // A* Manhattan
				child.heuristic = child.manhattanHeuristic(child);
			}
			if (child.goalChecker() == false){
				child.depth = gn;
				if (searchChoice == 1){ 
					nodeQueue.push_back(child);
				}
				if (searchChoice == 2){ 
					minHeap.push(child);
				}
				if (searchChoice == 3){ 
					minHeap.push(child);
				}
				cout << "g(n) = " << gn << " and h(n) = " << child.heuristic << endl;
				child.outputBoard();
				cout << "Expanding this node..." << endl;
			} 
			if (child.goalChecker() == true){
				cout << "g(n) = " << gn << " and h(n) = " << child.heuristic << endl;
				child.outputBoard();
				cout << "To solve the problem the search algorithm expanded a total of " << nodeCount << " nodes." << endl;
				if (searchChoice == 1) {
					cout << "The maximum number of nodes in the queue at any one time was " << totalNodesStandard << "." << endl;
				} else {
					cout << "The maximum number of nodes in the queue at any one time was " << totalNodesPriority << "." << endl;
				}
				isCorrect = true;
			}
		}
		int temp;
		temp = nodeQueue.size();
		if (temp > totalNodesStandard){
			totalNodesStandard = nodeQueue.size();
		}
		temp = minHeap.size();
		if (temp > totalNodesPriority){
			totalNodesPriority = minHeap.size();
		}
	}
}

void puzzleFunctions::uniformSearch(puzzleFunctions node){ // general-search(problem, queueing-function)
	cout << "Expanding state : " << endl;
	node.outputBoard();
	nodeQueue.push_back(node); // Makes the queue with the inital state as the problem
	int temp = nodeQueue.size();
	if (temp > totalNodesStandard){
		totalNodesStandard = nodeQueue.size();
	}
	while (nodeQueue.size() > 0 && isCorrect == false) {
		if (nodeQueue.size() == 0){ // If empty, return failure
			cout << "Failure." << endl;
			return;
		}
		puzzleFunctions curr = nodeQueue.front();
		if (curr.goalChecker() == true){ 
			isCorrect = true;
			curr.heuristic = 0; // h(n) = 0 for Uniform Cost
			cout << "Reached solution." << endl;
		} else {
			nodeQueue.erase(nodeQueue.begin());
			expand(curr);
		}
	}
}

void puzzleFunctions::misplacedTileSearch(puzzleFunctions node){
	cout << "Expanding state : " << endl;
	node.outputBoard();
	node.depth = 0;
	node.heuristic = misplacedHeuristic(node); // Calculates h(n)
	minHeap.push(node); // Makes the queue with the inital state as the problem
	
	while (minHeap.size() > 0 && isCorrect == false) {
		if (minHeap.size() == 0){ // If empty, return failure
			cout << "Failure." << endl;
			return;
		}
		puzzleFunctions curr = minHeap.top();
		int temp;
		temp = minHeap.size();
		if (temp > totalNodesPriority){
			totalNodesPriority = minHeap.size();
		}
		if (curr.goalChecker() == true){ 
			isCorrect = true;
			cout << "Reached solution." << endl;
		} else {
			minHeap.pop();
			expand(curr);
		}
	}
}


void puzzleFunctions::manhattanDistanceSearch(puzzleFunctions node){
	cout << "Expanding state : " << endl;
	node.outputBoard();
	node.depth = 0;
	node.heuristic = manhattanHeuristic(node); // Calculates h(n)
	minHeap.push(node); // Makes the queue with the inital state as the problem
	
	while (minHeap.size() > 0 && isCorrect == false) {
		if (minHeap.size() == 0){ // If empty, return failure
			cout << "Failure." << endl;
			return;
		}
		puzzleFunctions curr = minHeap.top();
		int temp;
		temp = minHeap.size();
		if (temp > totalNodesPriority){
			totalNodesPriority = minHeap.size();
		}
		if (curr.goalChecker() == true){ 
			isCorrect = true;
			cout << "Reached solution." << endl;
		} else {
			minHeap.pop();
			expand(curr);
		}
	}
}


int puzzleFunctions::misplacedHeuristic(puzzleFunctions node){ // Calculates heuristic for any misplaced tiles in the puzzle
	int hn = 0;
	if (node.parent[0] != 1){ // If any nodes are not in their expected position, h(n) increments
		hn++;
	}
	if (node.parent[1] != 2){
		hn++;
	}
	if (node.parent[2] != 3){
		hn++;
	}
	if (node.parent[3] != 4){
		hn++;
	}
	if (node.parent[4] != 5){
		hn++;
	}
	if (node.parent[5] != 6){
		hn++;
	}
	if (node.parent[6] != 7){
		hn++;
	}
	if (node.parent[7] != 8){
		hn++;
	}
	return hn;
}


int puzzleFunctions::manhattanHeuristic(puzzleFunctions node){ // Calculates manhattan heuristic
	int dx;
	int dy;
	int nodeX;
	int nodeY;
	int goalX;
	int goalY;
	int hn = 0;
	for (int i = 0; i < puzzleSize; i++){ // Naive method of setting coordinates to points on the matrix
		if (node.parent[i] != 0){ // Function needs to be greatly edited for puzzles of larger sizes
			if (i == 0){   // Sets the coordinates for the current index
				nodeX = 1; 
				nodeY = 1; 
			}
			if (i == 1){  
				nodeX = 2;
				nodeY = 1;
			}
			if (i == 2){   
				nodeX = 3; 
				nodeY = 1; 
			}
			if (i == 3){   
				nodeX = 1;
				nodeY = 2;
			}
			if (i == 4){
				nodeX = 2;
				nodeY = 2;
			}
			if (i == 5){
				nodeX = 3;
				nodeY = 2;
			}
			if (i == 6){
				nodeX = 1;
				nodeY = 3;
			}
			if (i == 7){
				nodeX = 2;
				nodeY = 3;
			}
			if (i == 8){
				nodeX = 3;
				nodeY = 3;
			}
			if(node.parent[i] == 1){ // Sets the coordinates of where that index is supposed to be
				goalX = 1;
				goalY = 1;
			}
			if(node.parent[i] == 2){
				goalX = 2;
				goalY = 1;
			}
			if(node.parent[i] == 3){
				goalX = 3;
				goalY = 1;
			}
			if(node.parent[i] == 4){
				goalX = 1;
				goalY = 2;
			}
			if(node.parent[i] == 5){
				goalX = 2;
				goalY = 2;
			}
			if(node.parent[i] == 6){
				goalX = 3;
				goalY = 2;
			}
			if(node.parent[i] == 7){
				goalX = 1;
				goalY = 3;
			}
			if(node.parent[i] == 8){
				goalX = 2;
				goalY = 3;
			}
			dx = abs(nodeX - goalX);
			dy = abs(nodeY - goalY);
			hn += dx + dy;
		}
	}
	return hn;
}


int main(){
    int eightpuzzle[puzzleSize];
    int input;
    
	cout << "Welcome to Devin Yang's 8-puzzle solver." << endl;
	cout << "Type 1 to use a default puzzle, or type 2 to create a custom puzzle." << endl;
	cin >> input;
	if (input == 1){ 
		// Initializes a default puzzle of Depth 8:
		// 1 3 6
		// 5 0 2
		// 4 7 8
		eightpuzzle[0] = 1;
		eightpuzzle[1] = 3;
		eightpuzzle[2] = 6;
		eightpuzzle[3] = 5;
		eightpuzzle[4] = 0;
		eightpuzzle[5] = 2;
		eightpuzzle[6] = 4;
		eightpuzzle[7] = 7;
		eightpuzzle[8] = 8;
		//cout << "Default puzzle: " << endl;
		//outputBoard(eightpuzzle);
	} if (input == 2){
		int a, b, c;
		cout << "Enter your puzzle, using 0 to determine the location of the blank and digits from 1 through 8." << endl;
		cout << "Enter the first row, using spaces in between each digit." << endl;
		cin >> a >> b >> c;
		eightpuzzle[0] = a;
		eightpuzzle[1] = b;
		eightpuzzle[2] = c;
		cout << "Enter the second row, using spaces in between each digit." << endl;
		cin >> a >> b >> c;
		eightpuzzle[3] = a;
		eightpuzzle[4] = b;
		eightpuzzle[5] = c;
		cout << "Enter the third row, using spaces in between each digit." << endl;
		cin >> a >> b >> c;
		eightpuzzle[6] = a;
		eightpuzzle[7] = b;
		eightpuzzle[8] = c;
	}
	
	
	puzzleFunctions faker;
	faker.copyPuzzle(eightpuzzle, faker.parent);
	cout << "Your current puzzle is: " << endl;
	faker.outputBoard();
	
	// Check if the board is valid
	faker.findBlank();
	
	cout << "Enter your choice of algorithm: " << endl;
	cout << "1. Uniform Cost Search " << endl;
	cout << "2. A* with the Misplaced Tile heuristic" << endl;
	cout << "3. A* with the Manhattan Distance heuristic" << endl;
	
	cin >> searchChoice;
	clock_t begin;
	clock_t end;
	if (searchChoice == 1){
		begin = clock();
		faker.uniformSearch(faker);
		end = clock();
	}
	if (searchChoice == 2){
		begin = clock();
		faker.misplacedTileSearch(faker);
		end = clock();
	}
	if (searchChoice == 3){
		begin = clock();
		faker.manhattanDistanceSearch(faker);
		end = clock();
	}
	double elaspedSeconds = double(end - begin)/CLOCKS_PER_SEC;
	cout << "Time elasped in seconds: " << elaspedSeconds << endl;
	return 0;
}
