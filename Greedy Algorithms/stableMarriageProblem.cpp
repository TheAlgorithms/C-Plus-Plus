#include <iostream> 
#include <string.h> 
#include <stdio.h> 
using namespace std; 

// Number of Men or Women 
#define N 4 

// This function returns true if woman 'w' prefers man 'm1' over man 'm' 
bool wPrefersM1OverM(int prefer[2*N][N], int w, int m, int m1) 
{ 
	// Check if w prefers m over her current engagment m1 
	for (int i = 0; i < N; i++) 
	{ 
		// If m1 comes before m in list of w, then w prefers her 
		// current engagement, don't do anything 
		if (prefer[w][i] == m1) 
			return true; 

		// If m comes before m1 in w's list, then free her current 
		// engagement and engage her with m 
		if (prefer[w][i] == m) 
		return false; 
	} 
} 

// Prints stable matching for N boys and N girls. Boys are numbered as 0 to 
// N-1. Girls are numbereed as N to 2N-1. 
void stableMarriage(int prefer[2*N][N]) 
{ 
	// Stores partner of women. This is our output array that 
	// stores pairing information. The value of wPartner[i] 
	// indicates the partner assigned to woman N+i. Note that 
	// the woman numbers between N and 2*N-1. The value -1 
	// indicates that (N+i)'th woman is free 
	int wPartner[N]; 

	// An array to store availability of men. If mFree[i] is 
	// false, then man 'i' is free, otherwise engaged. 
	bool mFree[N]; 

	// Initialize all men and women as free 
	memset(wPartner, -1, sizeof(wPartner));  //Google "memset() function in C++" to get the idea about how this works 
	memset(mFree, false, sizeof(mFree)); 
	int freeCount = N; 

	// While there are free men 
	while (freeCount > 0) 
	{ 
		// Pick the first free man (we could pick any) 
		int m; 
		for (m = 0; m < N; m++) 
			if (mFree[m] == false) 
				break; 

		// One by one go to all women according to m's preferences. 
		// Here m is the picked free man 
		for (int i = 0; i < N && mFree[m] == false; i++) 
		{ 
			int w = prefer[m][i]; 

			// The woman of preference is free, w and m become 
			// partners (Note that the partnership maybe changed 
			// later). So we can say they are engaged not married 
			if (wPartner[w-N] == -1) 
			{ 
				wPartner[w-N] = m; 
				mFree[m] = true; 
				freeCount--;
				cout<<"Woman- "<<w<<"engaged with man- "<<m<<endl;  //Prints the new pair formed in the ongoing iteration. Note that
																	// this is not the final pair as all iterations may have been completed yet
			} 

			else // If w is not free 
			{ 
				// Find current engagement of w 
				int m1 = wPartner[w-N]; 

				// If w prefers m over her current engagement m1, 
				// then break the engagement between w and m1 and 
				// engage m with w. 
				if (wPrefersM1OverM(prefer, w, m, m1) == false) 
				{ 
					wPartner[w-N] = m; 
					mFree[m] = true; 
					mFree[m1] = false; 
					cout<<"Woman- "<<w<<"engaged with man- "<<m<<endl; //Prints the new pair formed in the ongoing iteration. Note that
																		// this is not the final pair as all iterations may have been completed yet
				} 
			} // End of Else 
		} // End of the for loop that goes to all women in m's list 
	} // End of main while loop 


	// Print the solution 
	cout<<endl<<"Final pairs:- "<<endl;
	cout << "Woman Man" << endl; 
	for (int i = 0; i < N; i++) 
	cout << " " << i+N << "\t" << wPartner[i] << endl; 
} 

int main() 
{ 
	//0, 1, 2, and 3 are men; 4, 5, 6, and 7 are women
	int prefer[2*N][N] = { {7, 5, 6, 4}, //from here
		{5, 4, 6, 7}, 
		{4, 5, 6, 7}, 
		{4, 5, 6, 7}, //till here is the preferences of men (first 4 rows) 
		{3, 2, 1, 0}, //from here
		{3, 2, 1, 0}, 
		{3, 2, 1, 0}, 
		{3, 2, 1, 0}, //till here are the preferences of women (next 4 rows)
	};
	
	//function call 
	stableMarriage(prefer); 

	return 0; 
} 

