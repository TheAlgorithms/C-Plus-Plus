//---------------------------------------------------------------------------------------
//                             Nuclear Explosion Simulation
//                             ----------------------------
//
// General : The program should simulate a nuclear explosion and sum the energy product 
//			 from the process
//
// Input   : Atoms number and locations come from a .txt file formated like so
//			 N,X1,Y1,X2,Y2,X3,Y3...Xn,Yn
// 
// Process : First we read the data and enter it to a char array to visualize the process
//			 then we blow the first atom picked randomly while reading the file and after that
//			 starts the process of handling every blown neutron movement
// 
// Output  : Every iteration prints the current state of the board and energy output
// 
// 
//---------------------------------------------------------------------------------------

#include <iostream>
#include <string.h>
#include <fstream>
#include <ctime>
using namespace std;

//  variables declaration
constexpr auto null = 0;
const char FILE_PATH[] = "E:\\tmp\\atoms.tnXt";
const int NUMBER_OF_ATOMS = 10;
const int NUMBER_OF_ROWS = 6;
const int NUMBER_OF_COLS = 5;
static int nEunits = 0;

//  Structs
struct point {
	int nX;
	int nY;
};
struct neutron {
	int nX;
	int nY;
	char cDirection;
};
struct neutronNode {
	neutron neutcurrNeutron;
	neutronNode* pneutnNext;
};
struct neutronQueue {
	neutronNode* pneutnfront;
	neutronNode* pneutnrear;
	int nsize;
};

//  Functions prototypes
void visualiseArr(char carratomsArr[NUMBER_OF_ROWS][NUMBER_OF_COLS]);
void push(neutronQueue* q, int nX, int nY, char cDirection);
neutronNode* pop(neutronQueue* q);
bool bis_Empty(neutronQueue* q);
void blowAtom(char carratomsArr[NUMBER_OF_ROWS][NUMBER_OF_COLS], int nrow, int ncol);
void printneutron(char carratomsArr[NUMBER_OF_ROWS][NUMBER_OF_COLS], neutronNode* node);
void push(neutronQueue* q, neutronNode* ptmpNode);
void deleteCollidingneutrons(neutronQueue* q, int nrow, int ncol);
bool bnoHalfwayBlownAtoms(char carratomsArr[NUMBER_OF_ROWS][NUMBER_OF_COLS]);
void visualizeQueue(neutronQueue* q);
bool bnotAtStartOfRow(int nrow);
bool bnotAtStartOfCol(int ncol);
bool bnotAtEndOfRow(int nrow);
bool bnotAtEndOfCol(int ncol);

//---------------------------------------------------------------------------------------
//                                        Main
//                                        ----
// General      : Handles the course of action for the program, that includes the file
//				  retrieval, the turns loop that covers the atom blowing and the movement  
//				  of the neutrons, and finally the tally for the total energy product 
//				  from the simulation
//
// Parameters   : none
//
//
//
// Return Value : 0 \ none
//
//---------------------------------------------------------------------------------------
int main()
{
	neutronQueue q = {null,null,0};

	//  use current time as seed for random generator
	std::srand((unsigned int)std::time(nullptr)); 

	// first we generate the coordinates and their location and write them to a file.

	fstream file;
	file.open(FILE_PATH, ios::out);

	if (!file.is_open()) {
		cout << "problem opening file" << endl;
	}
	else { //  N,nX1,y1,nX2,y2...nXN,yN
		file << NUMBER_OF_ATOMS << ",";
		for (int i = 0; i < NUMBER_OF_ATOMS; i++) {
			int nX = std::rand() % NUMBER_OF_COLS;
			int nY = std::rand() % NUMBER_OF_ROWS;
			if (i != NUMBER_OF_ATOMS-1)
				file << nX << "," << nY << ",";
			else
				file << nX << "," << nY;
		}
	}
	file.close();


	// then we read from file the number of coordinates and their location.
	char carratomsArr[NUMBER_OF_ROWS][NUMBER_OF_COLS];
	for (int i = 0; i < NUMBER_OF_ROWS; i++){
		for (int j = 0; j < NUMBER_OF_COLS; j++) {
			carratomsArr[i][j] = '.';// symbolizes empty cell
		}
	}
	char comma = ',';
	int nX, nY, N=10, firstAtomtoBlow, row=0, col=0;
	file.open(FILE_PATH, ios::in);
	if (!file.is_open()) {
		cout << "problem opening file" << endl;
		return 0;
	}
	else {
		file >> N;
		file >> comma;
		firstAtomtoBlow = std::rand() % N;
		for (int i = 0; i < NUMBER_OF_ATOMS; i++) {
			file >> nX;
			file >> comma;
			file >> nY;
			file >> comma;

			if (i == firstAtomtoBlow)
			{
				row = nY;
				col = nX;
			}
			
			//  symbolizes a cell filled with an atom
			carratomsArr[nY][nX] = 'A';
		}
	}
	///carratomsArr[0][0] = 'A';
	///carratomsArr[0][3] = 'A';
	///carratomsArr[3][0] = 'A';
	///carratomsArr[3][1] = 'A';
	///carratomsArr[3][2] = 'A';
	///carratomsArr[2][3] = 'A';
	///carratomsArr[4][2] = 'A';
	///carratomsArr[5][2] = 'A';
	visualiseArr(carratomsArr);
	
	// each neutron will be represented by an arrow head in the direction its going
	// we'll create a queue which every neutron would enter once out of atom, then as long as it didn't reach the border or hit another atom it cycles through the queue 

	nEunits = 0;
	// we blowup an atom
	int natomsCount = N;
	blowAtom(carratomsArr,row,col);

	// show action
	visualiseArr(carratomsArr);
	// as long as there are neutrons that can do stuff and atoms to blow, keep going
	while (!bnoHalfwayBlownAtoms(carratomsArr) || !bis_Empty(&q) && nEunits < N) {

		int ntargetCount = 0;
		char carrneutronsTargets[NUMBER_OF_ROWS][NUMBER_OF_COLS];

		for(int i=0;i<NUMBER_OF_ROWS;i++)
			for(int j=0;j<NUMBER_OF_COLS;j++)
				carrneutronsTargets[i][j] = '?';

		///visualiseArr(carratomsArr);
		
		// go over array and finalize first stage blown atoms
		for(int i=0;i<NUMBER_OF_ROWS;i++)
			for (int j = 0; j < NUMBER_OF_COLS; j++)
			{

				// if 'first stage blown atom' found create its neutrons and assign 
				// targets to each one
				if (carratomsArr[i][j] == '*')
				{
					//  Reset cell
					carratomsArr[i][j] = '.';

					// create 4 neutrons

					// UP
					// check if above location is in boundaries and if its an empty target
					// to move to 
					if (i!=0 && carrneutronsTargets[i - 1][j]!='T') {
						carrneutronsTargets[i-1][j] = 'T';
						push(&q, j, i, '^');
						///visualizeQueue(&q);

					}// target not empty but doesn't contain atom
					else if (carrneutronsTargets[i - 1][j] == 'T' && 
						carratomsArr[i - 1][j] != 'A') 
						 {

						carrneutronsTargets[i - 1][j] = 'N';
						deleteCollidingneutrons(&q,i-1,j);
						///visualizeQueue(&q);
						 }

					// DOWN
					// check if below location is in boundaries and if its an empty target
					// to move to 
					if (i != NUMBER_OF_ROWS-1 && carrneutronsTargets[i + 1][j] != 'T') {
						carrneutronsTargets[i + 1][j] = 'T';
						push(&q, j, i, 'v');
						///visualizeQueue(&q);

					}// target not empty but doesn't contain atom
					else if (carrneutronsTargets[i + 1][j] == 'T' && carratomsArr[i + 1][j] != 'A') {
						carrneutronsTargets[i + 1][j] = 'N';
						deleteCollidingneutrons(&q, i + 1, j);
						///visualizeQueue(&q);
					}

					// LEFT
					// check if location to the left is in boundaries and if its an empty target
					// to move to 
					if (j != 0 && carrneutronsTargets[i][j - 1] != 'T') {
						carrneutronsTargets[i][j - 1] = 'T';
						push(&q, j, i, '<');
						///visualizeQueue(&q);

					}// target not empty but doesn't contain atom
					else if (carrneutronsTargets[i][j- 1] == 'T' && carratomsArr[i][j - 1] != 'A') {
						carrneutronsTargets[i][j - 1] = 'N';
						deleteCollidingneutrons(&q, i, j - 1);
						///visualizeQueue(&q);
					}

					// check if location to the right is in boundaries and if its an empty target
					// to move to 
					// RIGHT
					if (j != NUMBER_OF_COLS-1 && carrneutronsTargets[i][j+1] != 'T') {
						carrneutronsTargets[i][j+1] = 'T';
						push(&q, j, i, '>');
						///visualizeQueue(&q);

					}// target not empty but doesn't contain atom
					else if (carrneutronsTargets[i][j+1] == 'T' && carratomsArr[i][j+1] != 'A') {
						carrneutronsTargets[i][j+1] = 'N';
						deleteCollidingneutrons(&q, i, j+1);
						///visualizeQueue(&q);
					}
				}
			}

		
		///visualiseArr(carratomsArr);

		//  get queue initial size
		int nsize = q.nsize;

		// handle every neutron
		for(int i = 0; i < nsize; i++) {
			///visualiseArr(carratomsArr);

			// gather and shorten data
			neutronNode* tmpNode = pop(&q);
			int *pncurrRow = &tmpNode->neutcurrNeutron.nY;
			int *pncurrCol = &tmpNode->neutcurrNeutron.nX;
			// check if there is a problem with the future target like 
			// another neutron already declared this point as its target and if so delete the latter 
			switch (tmpNode->neutcurrNeutron.cDirection) {
			case '^':

				// if target in boundaries and doesn't collide with another neutron
				if (bnotAtStartOfRow(*pncurrRow) && carrneutronsTargets[(*pncurrRow)-1][(*pncurrCol)] != 'N' &&
					!(((*pncurrRow) > 1 && carratomsArr[(*pncurrRow) - 2][(*pncurrCol)] == 'v') ||
					(bnotAtEndOfCol((*pncurrCol)) && bnotAtStartOfRow(*pncurrRow) && carratomsArr[(*pncurrRow)-1][(*pncurrCol) + 1] == '<') ||
					(bnotAtStartOfCol((*pncurrCol)) && bnotAtStartOfRow(*pncurrRow) && carratomsArr[(*pncurrRow)-1][(*pncurrCol) - 1] == '>')))
				{
					// reset previous cell
					carratomsArr[(*pncurrRow)][(*pncurrCol)] = '.';

					// change current neutron location values
					(*pncurrRow)--;

					// if there is an atom ahead blow it otherwise move neutron
					if (carratomsArr[(*pncurrRow)][(*pncurrCol)] == 'A') {
						blowAtom(carratomsArr, (*pncurrRow), (*pncurrCol));
					}
					else {// neutron moving
						
						printneutron(carratomsArr, tmpNode);
						push(&q, tmpNode);
					}
				}
				else {
					//reset target cell
					carratomsArr[(*pncurrRow)][(*pncurrCol)] = '.';

					// if in boundaries declare target overpopulated
					if (bnotAtStartOfRow((*pncurrRow)))
						carrneutronsTargets[(*pncurrRow) - 1][(*pncurrCol)] = 'N';

					// free current neutron allocation
					free(tmpNode);
				}
				break;
			case 'v':
				if (bnotAtEndOfRow((*pncurrRow)) && carrneutronsTargets[(*pncurrRow) + 1][(*pncurrCol)] != 'N' &&
					!(((*pncurrRow) < NUMBER_OF_ROWS - 2 && carratomsArr[(*pncurrRow) + 2][(*pncurrCol)] == '^') ||
						(bnotAtEndOfCol((*pncurrCol)) && bnotAtEndOfRow((*pncurrRow)) && carratomsArr[(*pncurrRow)+1][(*pncurrCol) + 1] == '<') ||
						(bnotAtEndOfRow((*pncurrRow)) && bnotAtStartOfCol((*pncurrCol)) && carratomsArr[(*pncurrRow) + 1][(*pncurrCol) - 1] == '>')))
				{

					// reset previous cell
					carratomsArr[(*pncurrRow)][(*pncurrCol)] = '.';

					// change current neutron location values
					(*pncurrRow)++;

					// if there is an atom ahead blow it otherwise move neutron
					if (carratomsArr[(*pncurrRow)][(*pncurrCol)] == 'A') {
						blowAtom(carratomsArr, (*pncurrRow), (*pncurrCol));
					}
					else {//  neutron moving

						printneutron(carratomsArr, tmpNode);
						push(&q, tmpNode);
					}
				}
				else {
					//reset target cell
					carratomsArr[(*pncurrRow)][(*pncurrCol)] = '.';

					// if in boundaries declare target overpopulated
					if (bnotAtEndOfRow((*pncurrRow)))
						carrneutronsTargets[(*pncurrRow) + 1][(*pncurrCol)] = 'N';

					// free current neutron allocation
					free(tmpNode);
				}
				break;
			case '<':
				if (bnotAtStartOfCol((*pncurrCol)) && carrneutronsTargets[(*pncurrRow)][(*pncurrCol) - 1] != 'N' &&
					!((bnotAtEndOfRow((*pncurrRow)) && bnotAtStartOfCol((*pncurrCol)) && carratomsArr[(*pncurrRow) + 1][(*pncurrCol) - 1] == '^') ||
					(bnotAtEndOfRow((*pncurrRow)) && bnotAtStartOfCol((*pncurrCol)) && carratomsArr[(*pncurrRow) - 1][(*pncurrCol) - 1] == 'v') ||
					((*pncurrCol) > 1 && carratomsArr[(*pncurrRow)][(*pncurrCol) - 2] == '>')))
				{

					// reset previous cell
					carratomsArr[(*pncurrRow)][(*pncurrCol)] = '.';

					// change current neutron location values
					(*pncurrCol)--;

					// if there is an atom ahead blow it otherwise move neutron
					if (carratomsArr[(*pncurrRow)][(*pncurrCol)] == 'A') {
						blowAtom(carratomsArr, (*pncurrRow), (*pncurrCol));
					}
					else {// neutron moving

						printneutron(carratomsArr, tmpNode);
						push(&q, tmpNode);
					}
				}
				else
				{
					//reset target cell
					carratomsArr[(*pncurrRow)][(*pncurrCol)] = '.';

					// if in boundaries declare target overpopulated
					if (bnotAtStartOfCol((*pncurrCol)))
						carrneutronsTargets[(*pncurrRow)][(*pncurrCol) - 1] = 'N';

					// free current neutron allocation
					free(tmpNode);
				}
				break;
			case '>':
				if (bnotAtEndOfCol((*pncurrCol)) && carrneutronsTargets[(*pncurrRow)][(*pncurrCol) + 1] != 'N' &&
					!((bnotAtEndOfRow((*pncurrRow)) && carratomsArr[(*pncurrRow) + 1][(*pncurrCol) + 1] == '^') ||
					(bnotAtStartOfRow((*pncurrRow)) && carratomsArr[(*pncurrRow) - 1][(*pncurrCol) + 1] == 'v') ||
						((*pncurrCol) < NUMBER_OF_COLS - 2 && carratomsArr[(*pncurrRow)][(*pncurrCol) + 2] == '<')))
				{

					// reset previous cell
					carratomsArr[(*pncurrRow)][(*pncurrCol)] = '.';

					// change current neutron location values
					(*pncurrCol)++;

					// if there is an atom ahead blow it otherwise move neutron
					if (carratomsArr[(*pncurrRow)][(*pncurrCol)] == 'A') {
						blowAtom(carratomsArr, (*pncurrRow), (*pncurrCol));
					}
					else {// neutron moving

						printneutron(carratomsArr, tmpNode);
						push(&q, tmpNode);
					}
				}
				else
				{
					//reset target cell
					carratomsArr[(*pncurrRow)][(*pncurrCol)] = '.';

					// if in boundaries declare target overpopulated
					if(bnotAtEndOfCol((*pncurrCol)))
						carrneutronsTargets[(*pncurrRow)][(*pncurrCol) + 1] = 'N';

					// free current neutron allocation
					free(tmpNode);
				}
				break;
			}
			///visualiseArr(carratomsArr);
		}
		visualiseArr(carratomsArr);
		 
	}

	
	cout << "energy units: " << nEunits << endl;
	return 0;
}

//---------------------------------------------------------------------------------------
//                                        not At Start Of Row
//                                        -------------------
// General      : checks that row isn't equal to zero
//
// Parameters   : int nrow - row index (In)
//
//
//
// Return Value : boolean value indicating the check result
//
//---------------------------------------------------------------------------------------

bool bnotAtStartOfRow(int nrow) {
	if (nrow != 0)
		return true;
	return false;
}

//---------------------------------------------------------------------------------------
//                                        not At Start Of Col
//                                        -------------------
// General      : checks that col isn't equal to zero
//
// Parameters   : int ncol - col index (In)
//
//
//
// Return Value : boolean value indicating the check result
//
//---------------------------------------------------------------------------------------

bool bnotAtStartOfCol(int ncol) {
	if (ncol != 0)
		return true;
	return false;

}

//---------------------------------------------------------------------------------------
//                                        not At End Of Row
//                                        -------------------
// General      : checks that row isn't equal to last index in dimension
//
// Parameters   : int nrow - row index (In)
//
//
//
// Return Value : boolean value indicating the check result
//
//---------------------------------------------------------------------------------------

bool bnotAtEndOfRow(int nrow) {
	if (nrow != NUMBER_OF_ROWS-1)
		return true;
	return false;

}

//---------------------------------------------------------------------------------------
//                                        not At End Of Col
//                                        -------------------
// General      : checks that col isn't equal to last index in dimension
//
// Parameters   : int ncol - col index (In)
//
//
//
// Return Value : boolean value indicating the check result
//
//---------------------------------------------------------------------------------------

bool bnotAtEndOfCol(int ncol) {
	if (ncol != NUMBER_OF_COLS-1)
		return true;
	return false;

}

//---------------------------------------------------------------------------------------
//                                        delete Colliding neutrons
//                                        ------------------------
// General      : deletes all neutrons with target specified with row, col
//
// Parameters   : neutronQueue* q - neutron Queue (In \ Out)
//				  int nrow - target row index (In)
//				  int ncol - target col index (In)
//
// Return Value : none
//
//---------------------------------------------------------------------------------------

void deleteCollidingneutrons(neutronQueue* q, int nrow, int ncol) {// 
	for (int i = 0; i < q->nsize; i++)
	{
		neutronNode* tmp = pop(q);
		bool freed = false;
		switch (tmp->neutcurrNeutron.cDirection) {
		case'^':
			if (tmp->neutcurrNeutron.nY - 1 == nrow && tmp->neutcurrNeutron.nX == ncol) {
				free(tmp);
				freed = true;
			}
			break;
		case'v':
			if (tmp->neutcurrNeutron.nY + 1 == nrow && tmp->neutcurrNeutron.nX == ncol) {
				free(tmp);
				freed = true;
			}
			break;
		case'<':
			if (tmp->neutcurrNeutron.nY == nrow && tmp->neutcurrNeutron.nX-1 == ncol) {
				free(tmp);
				freed = true;
			}
			break;
		case'>':
			if (tmp->neutcurrNeutron.nY == nrow && tmp->neutcurrNeutron.nX+1 == ncol) {
				free(tmp);
				freed = true;
			}
			break;

		}
		if (!freed)
			push(q, tmp);
	}
}

//---------------------------------------------------------------------------------------
//                                        Print Neutron
//                                        -------------
// General      : prints given node direction in its location on the array\ board
//
// Parameters   : char carratomsArr[NUMBER_OF_ROWS][NUMBER_OF_COLS] - simulation board (In \ Out)
//				  neutronNode* node - node to be printed (In)
//
// Return Value : none
//
//---------------------------------------------------------------------------------------

void printneutron(char carratomsArr[NUMBER_OF_ROWS][NUMBER_OF_COLS],neutronNode* node) {
	carratomsArr[node->neutcurrNeutron.nY][node->neutcurrNeutron.nX] = node->neutcurrNeutron.cDirection;
}

//---------------------------------------------------------------------------------------
//                                        no Half way Blown Atoms
//                                        -----------------------
// General      : prints given node direction in its location on the array\ board
//
// Parameters   : char carratomsArr[NUMBER_OF_ROWS][NUMBER_OF_COLS] - simulation board (In)
//
// Return Value : whether aren't there any first stage blown atoms 
//
//---------------------------------------------------------------------------------------

bool bnoHalfwayBlownAtoms(char carratomsArr[NUMBER_OF_ROWS][NUMBER_OF_COLS]) {
	for (int i = 0; i < NUMBER_OF_ROWS; i++)
		for (int j = 0; j < NUMBER_OF_COLS; j++)
			if (carratomsArr[i][j] == '*')
				return false;
	return true;
}

//---------------------------------------------------------------------------------------
//                                        visualise Arr
//                                        -------------
// General      : prints the simulation board in its current status and the current tally for energy units
//
// Parameters   : char carratomsArr[NUMBER_OF_ROWS][NUMBER_OF_COLS] - simulation board (In)
//
// Return Value : none
//
//---------------------------------------------------------------------------------------

void visualiseArr(char carratomsArr[NUMBER_OF_ROWS][NUMBER_OF_COLS]) {
	for (int i = 0; i < NUMBER_OF_ROWS; i++) { //  visualize the array
		for (int j = 0; j < NUMBER_OF_COLS; j++) {
			if (j != 0)
				cout << " ";
			cout << carratomsArr[i][j];
			if (j != NUMBER_OF_COLS-1)
				cout << " ";
		}
		cout << endl;
	}
	cout << "Energy units" << nEunits << endl;
	cout << endl;
}

//---------------------------------------------------------------------------------------
//                                        visualize Queue
//                                        ---------------
// General      : prints a representation of the current neutron queue status
//
// Parameters   : neutronQueue* q - neutrons queue (In)
//
// Return Value : none
//
//---------------------------------------------------------------------------------------

void visualizeQueue(neutronQueue* q) {
	int times = q->nsize;
	for (int i = 0; i < times; i++)
	{
		neutronNode* tmp = pop(q);
		cout << "x=" << tmp->neutcurrNeutron.nX << " y=" << tmp->neutcurrNeutron.nY << " " << tmp->neutcurrNeutron.cDirection << " <-- ";
		push(q, tmp);
	}
	cout << endl;
	cout << "..................................." << endl;
}

//---------------------------------------------------------------------------------------
//                                        blow Atom
//                                        ---------
// General      : prints a first stage blown atom in specified location by row, col and deletes any neighboring neutrons
//
// Parameters   : char carratomsArr[NUMBER_OF_ROWS][NUMBER_OF_COLS] - simulation board (In\out)
//				  int nrow - current atom row (In)
//				  int ncol - current atom col (In)
//
// Return Value : none
//
//---------------------------------------------------------------------------------------

void blowAtom(char carratomsArr[NUMBER_OF_ROWS][NUMBER_OF_COLS],int nrow, int ncol) {

	// show sign of halfway blown atom
	carratomsArr[nrow][ncol] = '*';

	// add +1 to total score 
	nEunits++;

	// reset surrounding values to delete close neutrons
	if(nrow != 0)
		if(carratomsArr[nrow - 1][ncol] == 'v')
			carratomsArr[nrow - 1][ncol] = '.';
	if (nrow != NUMBER_OF_ROWS-1)
		if (carratomsArr[nrow + 1][ncol] == '^')
			carratomsArr[nrow + 1][ncol] = '.';
	if (ncol != 0)
		if (carratomsArr[nrow][ncol - 1] == '>')
			carratomsArr[nrow][ncol - 1] = '.';
	if (ncol != NUMBER_OF_COLS)
		if (carratomsArr[nrow][ncol + 1] == '<')
			carratomsArr[nrow][ncol + 1] = '.';
}

//---------------------------------------------------------------------------------------
//                                        push
//                                        ----
// General      : inserts a given neutron by its values to the rear of the neutrons queue
//
// Parameters   : neutronQueue* q - neutrons queue (In\out)
//				  int nX - current neutron col (In)
//				  int nY - current neutron row (In)
//				  char cDirection - current neutron direction (In)
//
// Return Value : none
//
//---------------------------------------------------------------------------------------
//  rear 1->2->3->4->5->6->7 front 
void push(neutronQueue* q, int nX, int nY, char cDirection) {
		if (cDirection == '>' || cDirection == '<' || cDirection == '^' || cDirection == 'v') {
			if (bis_Empty(q)) {// no elements in queue its empty
				neutronNode* tmpNode = new neutronNode;
				tmpNode->neutcurrNeutron.nX = nX;
				tmpNode->neutcurrNeutron.nY = nY;
				tmpNode->neutcurrNeutron.cDirection = cDirection;
				q->pneutnrear = null;
				q->pneutnfront = tmpNode;
				q->nsize++;
			}
			else if (q->nsize == 1) {
				neutronNode* tmpNode = new neutronNode;
				tmpNode->neutcurrNeutron.nX = nX;
				tmpNode->neutcurrNeutron.nY = nY;
				tmpNode->neutcurrNeutron.cDirection = cDirection;
				q->pneutnrear = tmpNode;
				q->pneutnrear->pneutnNext = q->pneutnfront;
				q->nsize++;
			}
			else {
				neutronNode* tmpNode = new neutronNode;
				tmpNode->neutcurrNeutron.nX = nX;
				tmpNode->neutcurrNeutron.nY = nY;
				tmpNode->neutcurrNeutron.cDirection = cDirection;
				tmpNode->pneutnNext = q->pneutnrear;
				q->pneutnrear = tmpNode;
				q->nsize++;
			}
		}
}

//---------------------------------------------------------------------------------------
//                                        push
//                                        ----
// General      : inserts a given neutron by its pointer to the rear of the neutrons queue
//
// Parameters   : neutronQueue* q - neutrons queue (In\out)
//				  neutronNode* tmpNode - node to insert(In)
//
// Return Value : none
//
//---------------------------------------------------------------------------------------

void push(neutronQueue* q, neutronNode* ptmpNode) {
		if (bis_Empty(q)) {// no elements in queue its empty
			q->pneutnrear = null;
			q->pneutnfront = ptmpNode;
			q->nsize++;
		}
		else if(q->nsize==1){
			ptmpNode->pneutnNext = q->pneutnfront;
			q->pneutnrear = ptmpNode;
			q->nsize++;
		}
		else {
			ptmpNode->pneutnNext = q->pneutnrear;
			q->pneutnrear = ptmpNode;
			q->nsize++;
		}
}

//---------------------------------------------------------------------------------------
//                                        pop
//                                        ---
// General      : get out the neutron at front and returns it
//
// Parameters   : neutronQueue* q - neutrons queue (In\out)
//
// Return Value : removed neutron
//
//---------------------------------------------------------------------------------------

neutronNode* pop(neutronQueue* q) {
	if (bis_Empty(q)) {
		cout << "queue empty" << endl;
		return null;
	}
	else if (q->pneutnrear==null) {
		neutronNode* tmp = q->pneutnfront;
		q->pneutnfront = null;
		q->pneutnrear = null;
		q->nsize--;
		return tmp;
	}
	else if(q->nsize==2){
		neutronNode* tmp = q->pneutnfront;
		q->pneutnrear->pneutnNext = null;
		q->pneutnfront = q->pneutnrear;
		q->pneutnrear = null;
		q->nsize--;
		return tmp;
	}
	else {
		neutronNode* currNode = q->pneutnrear;
		while (currNode->pneutnNext != q->pneutnfront) {
			currNode = currNode->pneutnNext;
		}
		neutronNode* tmp = q->pneutnfront;
		q->pneutnfront = currNode;
		q->pneutnfront->pneutnNext = null;
		q->nsize--;
		return tmp;
	}
}

//---------------------------------------------------------------------------------------
//                                        is Empty
//                                        --------
// General      : checks whether the queue has no elements in it
//
// Parameters   : neutronQueue* q - neutrons queue (In\out)
//
// Return Value : boolean value are there any more neutrons left in the queue
//
//---------------------------------------------------------------------------------------

bool bis_Empty(neutronQueue* q)
{
	if (q->nsize==0)
	{
		return true;
	}
	return false;
}
