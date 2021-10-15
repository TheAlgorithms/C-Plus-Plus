//---------------------------------------------------------------------------------------
//                                           Reversi
//                                           -------
//
// General : The program should simulate a reversi game
//
// Input   : if its a new game then all inputs are from the players, but if an old game
//			 loaded in then we read the current state of the board from a binary file
// 
// Process : First we read the data and enter it to a char array to visualize the process
//			 then we blow the first atom picked randomly while reading the file and after that
//			 starts the process of handling every blown neutron movement
// 
// Output  : Every iteration prints the current state of the board and energy output
// 
// 
//---------------------------------------------------------------------------------------
#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> 
#include<math.h>
using namespace std;
struct Point {
	int nrow;
	int ncol;
};
struct Bridge {
	Point A;//start
	Point B;//finish
};
struct matrix {
	char carrmatGameBoard[8][8];
};
struct Game {
	char carrmatGameBoard[8][8];
	char ccurrPlayerTurn;
};
void visualizeBoard(char carrboard[8][8]);
void startGame(Game* ggame);
void searchBridges(Game* ggame, Bridge* pbridges);
char oppositeColor(char c);
Point findBridgeEnd(Game ggame, int nrow, int ncol,int nrowAdder, int ncolAdder);
bool bboardIsntFull(Game ggame);
void exitGame(Game* ggame);
bool bisInputValid(int nrow, int ncol);
void paintBridge(Bridge brdgbridge, Game* ggame);
int ncountPieces(char copponet, Game ggame);
bool bsaveGame(const char* cppath, Game ggame);
bool bisNewBridge(Point A, Point B, Bridge* pbridges);
bool barePointsEqual(Point A, Point B);
static int nBridges = 0;
//---------------------------------------------------------------------------------------
//                                        Main
//                                        ----
// General      : initializes the game and board and presents the starting options to the player
//				  
// Parameters   : none
//
// Return Value : 0 \ none
//
//---------------------------------------------------------------------------------------
int main()
{
	// get move\choice (=move\save&Exit\exit) from player
		// go over every cell in the 8x8 matrix

		// for each cell start a recursion that gets the start color, direction and returns
		// the end point (x,y) of a bridge if there is one and if not return something
		// like (-1,-1) to know the recursion stopped cause it hit an empty cell 
		// or the matrix edge

		// paint the bridges found by painting everything between the two points 
		// in the direction specified for them.

	ifstream file;
	char carrArrstartGameBoard[8][8];
	int nchoise;
	Game ggame;
	string flocation;

	// initialize array
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			carrArrstartGameBoard[i][j] = '?';
	carrArrstartGameBoard[3][4] = 'B';
	carrArrstartGameBoard[4][3] = 'B';
	carrArrstartGameBoard[3][3] = 'W';
	carrArrstartGameBoard[4][4] = 'W';

	///visualizeBoard(ArrgameBoard);

	// print options
	cout << "LETS PLAY!!!" << endl;
	cout << "Type 1 to Start a New Game" << endl;
	cout << "Type 2 to Load a Game" << endl;
	cout << "Type 3 to Exit" << endl;
	

	//receive it
	cin >> nchoise;
	
	
	switch (nchoise) {
		case 1:
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
					ggame.carrmatGameBoard[i][j] = carrArrstartGameBoard[i][j];
			ggame.ccurrPlayerTurn = 'W';
			startGame(&ggame);
			break;
		case 2:
			cout << "enter game file path" << endl;
			cin >> flocation;
			file.open(flocation, ios::in | ios::binary);
			if (file.is_open()) {
				// place file pointer at beginning
				file.seekg(0, ios::beg);
				// read from file game sized block
				file.read((char*)&ggame, sizeof(Game));
				file.close();

			}
			else {
				cout << "Problem opening file" << endl;
				exit(0);
			}
			
			startGame(&ggame);
			break;
		case 3:
			return 0;
			break;

	}
	return 0;
}

//---------------------------------------------------------------------------------------
//                                        start Game
//                                        ----------
// General      :  keeps tabs on the game board, checks for bridges and paints them 
//				  if needed, changes turns and finally shows the winner with its score
//
// Parameters   : Game* game - game pointer the loaded or new game (In \ Out)
//
// Return Value : none
//
//---------------------------------------------------------------------------------------

void startGame(Game* game) {
	int row, col;
	Bridge* pbridgesToPaint = new Bridge;
	visualizeBoard(game->carrmatGameBoard);
	do {

		// keep requesting for the move until 
		// getting in boundaries move for an empty cell i.e. valid inputs
		do {

			// instruct the appropriate player to move
			cout << "enter row and column to move " << game->ccurrPlayerTurn 
				<< " player" << endl;

			// get player wishes
			cin >> row;
			cout << endl;

			// check row input if player wants to exit
			if (row == -1)
				exitGame(game);

			// get player wishes
			cin >> col;
			cout << endl;

			// check row input if player wants to exit
			if (col == -1)
				exitGame(game);

		} while ((game->carrmatGameBoard[row][col] == game->ccurrPlayerTurn || 
			game->carrmatGameBoard[row][col] == oppositeColor(game->ccurrPlayerTurn)) || 
			!bisInputValid(row, col));//if cell is occupied or input isn't valid keep asking for new input
		
		cout << flush;

		// print user requested location
		game->carrmatGameBoard[row][col] = game->ccurrPlayerTurn;

		//search Bridges and assign them to bridgesToPaint pointer
		searchBridges(game, pbridgesToPaint);

		// paint bridges
		for (int i = 0; i < nBridges; i++) {
			paintBridge(*(pbridgesToPaint+i),game);
		}

		// show results
		visualizeBoard(game->carrmatGameBoard);

		// change current players turn
		game->ccurrPlayerTurn = oppositeColor(game->ccurrPlayerTurn);

		// while inputs are valid and board isn't full keep going
	} while (bisInputValid(row, col) && bboardIsntFull(*game));

	// check if the game was other regularly and count tally between players
	if (!bboardIsntFull(*game)) {
		int nwhite = ncountPieces('W', *game);
		int nblack = ncountPieces('B', *game);
		if (nwhite > nblack)
			cout << "White Won with " << nwhite << " Pieces!!!" << endl;
		else if(nwhite == nblack)
			cout << "ohhh its a draw" << endl;
		else
			cout << "Black Won with "<< nblack << " Pieces!!!"<< endl;
	}
	
}

//---------------------------------------------------------------------------------------
//                                        count Pieces
//                                        ------------
// General      :  counts the pieces for the specified opponent and returns the sum
//				  
//
// Parameters   : Game game - contains the game board (In)
//				  char opponent - opponent color character (In)
//
// Return Value : none
//
//---------------------------------------------------------------------------------------

int ncountPieces(char copponent, Game ggame) {
	int count = 0;
	for (int row = 0; row < 8; row++)
		for (int col = 0; col < 8; col++)
			if (ggame.carrmatGameBoard[row][col] == copponent)
				count++;
	return count;
}

//---------------------------------------------------------------------------------------
//                                        exit Game
//                                        ---------
// General      :  player wants to exit asks if to save and saves if does
//				  
//
// Parameters   : Game* game - game pointer to save the game (Out)
//
// Return Value : none
//
//---------------------------------------------------------------------------------------

void exitGame(Game* ggame) {
	
	char canswer;
	string szpath;

	//ask if to save
	cout << "would you like to save the game? y/n" << endl;

	// accept answer
	cin >> canswer;

	//if so then save
	if (canswer == 'y')
	{
		cout << "pls write the complete file path to save to with name and " << 
			".dat extension and \\ between each directory" << endl;
		cin >> szpath;
		// print game save final status
		try {
			if (!bsaveGame(szpath.c_str(), *ggame)) {
				cout << "Problem Writing to file" << endl;
				exit(0);
			}
			else 
			{
					cout << "game saved successfully" << endl;
					exit(0);
			}
		}
		catch (exception) { cout << "Bad saving path! exiting" << endl; exit(0); }
	}
	else {//otherwise return
		exit(0);
	}
	 
	
}

//---------------------------------------------------------------------------------------
//                                        save Game
//                                        ---------
// General      :  tries to save game and returns succession
//				  
//
// Parameters   : Game* game - game pointer to save the game (Out)
//				  const char* cppath - file path to save in (In)
//
// Return Value : returns save succession
//
//---------------------------------------------------------------------------------------

bool bsaveGame(const char* cppath, Game ggame) {
		ofstream file;
		file.open(cppath, ios::out | ios::binary);
		if (file.is_open()) {
			file.seekp(0, ios::beg);
			file.write((char*)& ggame, sizeof(Game));
			file.close();
			return true;
		}
		else {
			return false;
		}
}

//---------------------------------------------------------------------------------------
//                                        board Isnt Full
//                                        ---------------
// General      :  tests the board to check whether its full
//				  
//
// Parameters   : Game game - to access the game board (In)
//				  
//
// Return Value : returns if board is not full with pieces
//
//---------------------------------------------------------------------------------------

bool bboardIsntFull(Game ggame) {
	for (int nrow = 0; nrow < 8; nrow++)
		for (int ncol = 0; ncol < 8; ncol++)// if at least one cell isn't equal to 'W' or 'B'
			if (ggame.carrmatGameBoard[nrow][ncol] != ggame.ccurrPlayerTurn && 
				ggame.carrmatGameBoard[nrow][ncol] != oppositeColor(ggame.ccurrPlayerTurn))
				return true;
	return false;
}

//---------------------------------------------------------------------------------------
//                                        is Input Valid
//                                        --------------
// General      :  checks if inputed row and col make sense and are valid
//				  
//
// Parameters   : int nrow - row index (In)
//				  int ncol - col index (In)
//				  
//
// Return Value : returns if input is in boundaries
//
//---------------------------------------------------------------------------------------

bool bisInputValid(int nrow, int ncol) {
	if (nrow > 0 && nrow < 8 && ncol > 0 && ncol < 8)
		return true;
	return false;
}

//---------------------------------------------------------------------------------------
//                                        paint Bridge
//                                        ------------
// General      :  given a game and a bridge it paints the appropriate locations the bridge crosses 
//				  
//
// Parameters   : Bridge bridge - start and end points of bridge to paint (In)
//				  Game* game - board to apply changes to (In\Out)
//				  
//
// Return Value : none
//
//---------------------------------------------------------------------------------------

void paintBridge(Bridge bridge,Game* game) {
	
	if (bridge.A.nrow == bridge.B.nrow) {//same row
		int times = abs(bridge.B.ncol - bridge.A.ncol);//distance
		int row = bridge.A.nrow;
		int col = (bridge.B.ncol > bridge.A.ncol) ? bridge.A.ncol : bridge.B.ncol;
		for (int i = 0; i < times; i++) {
			game->carrmatGameBoard[row][col + i] = game->ccurrPlayerTurn;
		}
	}
	else if(bridge.A.ncol ==bridge.B.ncol){//same column
		int times = abs(bridge.B.nrow - bridge.A.nrow);//distance
		int col = bridge.A.ncol;
		int row = (bridge.B.nrow > bridge.A.nrow) ? bridge.A.nrow : bridge.B.nrow;
		for (int i = 0; i < times; i++) {
			game->carrmatGameBoard[row + i][col] = game->ccurrPlayerTurn;
		}
	}
	else {//diagonally
		//right
		if (bridge.B.ncol > bridge.A.ncol) {
			
			//up right
			if (bridge.B.nrow < bridge.A.nrow) {
				int times = abs(bridge.B.nrow - bridge.A.nrow);//distance
				int row = bridge.A.nrow;
				int col = bridge.A.ncol;
				for (int i = times; i > 1; i--)
					game->carrmatGameBoard[row - i][col + i] = game->ccurrPlayerTurn;
			}
			//down right
			else {
				int times = abs(bridge.B.nrow - bridge.A.nrow);//distance
				int row = bridge.A.nrow;
				int col = bridge.A.ncol;
				for (int i = 1; i < times; i++)
					game->carrmatGameBoard[row + i][col + i] = game->ccurrPlayerTurn;
			}
		}
		else {//left
			  
			//up left
			if (bridge.B.nrow < bridge.A.nrow) {
				int times = abs(bridge.B.nrow - bridge.A.nrow); //distance
				int row = bridge.A.nrow;
				int col = bridge.A.ncol;
				for (int i = times-1; i > 0; i--)
					game->carrmatGameBoard[row -i][col -i] = game->ccurrPlayerTurn;
			}
			//down left
			else {
				int times = abs(bridge.B.nrow - bridge.A.nrow);//distance
				int row = bridge.A.nrow;
				int col = bridge.A.ncol;
				for (int i = 1; i < times; i++)
					game->carrmatGameBoard[row + i][col - i] = game->ccurrPlayerTurn;
			}
		}
	}
}

//----------------------------------------------------------------------------------------
//                                        searchBridges
//                                        ------------
// General      :  given a game and a bridge it paints the appropriate locations the bridge crosses 
//				  
//
// Parameters   : Bridge* pbridges - pointer to set result bridges to (Out)
//				  Game* game - to access current players turn and current board status (In)
//				  
//
// Return Value : none
//
//---------------------------------------------------------------------------------------

void searchBridges(Game* game, Bridge* pbridges)
{

	// we assume there could be a maximum of 8 bridges logically\theoretically 
	// with a normal max of 2

	// we count the number of bridges each time
	nBridges = 0;
	char colorToSearch = game->ccurrPlayerTurn;
	for (int row = 0; row < 8; row++)
		for (int col = 0; col < 8; col++)
			if (game->carrmatGameBoard[row][col] == colorToSearch)
			{
				Point a = {row,col};
				Point b[8]; 
				
				b[0] = findBridgeEnd(*game, row - 1, col, -1, 0);// up
				b[1] = findBridgeEnd(*game, row + 1, col, +1, 0);// down
				b[2] = findBridgeEnd(*game, row, col - 1, 0, -1);// left
				b[3] = findBridgeEnd(*game, row, col + 1, 0, +1);// right
				b[4] = findBridgeEnd(*game, row - 1, col - 1, -1, -1);// up left
				b[5] = findBridgeEnd(*game, row - 1, col + 1, -1, +1);// up right
				b[6] = findBridgeEnd(*game, row + 1, col - 1, +1, -1);// down left
				b[7] = findBridgeEnd(*game, row + 1, col + 1, +1, +1);// down right
				Bridge bridges[8];
				bridges[0] = { a, b[0] };
				bridges[1] = { a, b[1] };
				bridges[2] = { a, b[2] };
				bridges[3] = { a, b[3] };
				bridges[4] = { a, b[4] };
				bridges[5] = { a, b[5] };
				bridges[6] = { a, b[6] };
				bridges[7] = { a, b[7] };
				for (int i = 0; i < 8; i++)
				{
					//calculate distance to exit if bridge is too short i.e. nothing in between
					int distance = (int)sqrt(pow(bridges[i].A.ncol - bridges[i].B.ncol, 2) + pow(bridges[i].A.nrow - bridges[i].B.nrow, 2));
					
					if (distance > 1 && 
						bisNewBridge((pbridges + i)->A, bridges[i].A, pbridges) && 
						bridges[i].B.ncol != -1) {//if bridge is new and real then assign it
						*(pbridges + nBridges) = bridges[i];
						nBridges++;
					}
				}
			}
}

//----------------------------------------------------------------------------------------
//                                        is New Bridge
//                                        -------------
// General      :  given a game and a bridge it paints the appropriate locations the bridge crosses 
//				  
//
// Parameters   : Bridge* pbridges - pointer to access present bridges (Out)
//				  Point A - possible point of an existing bridge (In)
//				  Point B - second possible point of an existing bridge (In)
//				  
//
// Return Value : boolean value of is there a bridge with specified points A and B
//
//---------------------------------------------------------------------------------------

bool bisNewBridge(Point A, Point B, Bridge* pbridges) {
	for (int i = 0; i < nBridges; i++)
		if (barePointsEqual((pbridges + i)->A, A) && barePointsEqual((pbridges + i)->B, B) || 
			barePointsEqual((pbridges + i)->B, A) && barePointsEqual((pbridges + i)->B, A))
			return false;
	return true;
}

//----------------------------------------------------------------------------------------
//                                        are Points Equal
//                                        ----------------
// General      :  checks if points are equal
//				  
//
// Parameters   : Point A - point (In)
//				  Point B - point (In)
//				  
//				  
//
// Return Value : boolean value of are the points the same one
//
//---------------------------------------------------------------------------------------

bool barePointsEqual(Point A,Point B) {
	if (A.ncol == B.ncol && A.nrow == B.nrow)
		return true;
	return false;
}

//----------------------------------------------------------------------------------------
//                                        find Bridge End
//                                        ---------------
// General      :  a recursive function to find bridge end
//				  
//
// Parameters   : Game game - to access the game board (In)
//				  int nrow - row index (In)
//				  int ncol - col index (In)
//				  int nrowAdder - row index addition (In)
//				  int ncolAdder - col index addition (In)
//
// Return Value : possible bridge end Point
//
//---------------------------------------------------------------------------------------

//get next location checking spot in requested direction by row adder and col adder
Point findBridgeEnd(Game game, int nrow, int ncol, int nrowAdder, int ncolAdder) {
	Point b;
	if (nrow != 0) {
		if (game.carrmatGameBoard[nrow][ncol] == game.ccurrPlayerTurn || 
			game.carrmatGameBoard[nrow][ncol] == '?') {
			//end of bridge
			if (game.carrmatGameBoard[nrow][ncol] == game.ccurrPlayerTurn)
				b = { nrow,ncol };
			else {
				b = { -1,-1 };
			}
			return b;
		}
		else if (game.carrmatGameBoard[nrow][ncol] == oppositeColor(game.ccurrPlayerTurn))
		{
			return findBridgeEnd(game, nrow + nrowAdder, ncol + ncolAdder, nrowAdder, ncolAdder);
		}
	}
	//bridge out of boundaries i.e. scrap it
	b = { -1, -1 };
	return b;
}

//----------------------------------------------------------------------------------------
//                                        opposite Color
//                                        --------------
// General      : returns 'B' if input is 'W' and the opposite
//				  
//
// Parameters   : char c - current player (In)
//
// Return Value : opposite player character
//
//---------------------------------------------------------------------------------------

char oppositeColor(char c) {
	if (c == 'W')
		return 'B';
	else
		return 'W';
}

//----------------------------------------------------------------------------------------
//                                        visualize Board
//                                        ---------------
// General      : prints the game board
//				  
//
// Parameters   : char carrboard[8][8] - game board to show (In)
//
// Return Value : none
//
//---------------------------------------------------------------------------------------

void visualizeBoard(char carrboard[8][8]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
			cout << carrboard[i][j] << " ";
		cout << endl;
	}
}
