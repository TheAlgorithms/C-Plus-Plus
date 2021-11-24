/**
 * @file
 * @author [jang-jaehyuk](https://github.com/jang-jaehyuk)
 * @brief Implementation of [minimization of
 * Boolean functions](https://en.wikipedia.org/wiki/Quine-McCluskey_algorithm).
 */

#include <iostream> /// for io operations
#include <vector> /// for store the implicant
#include <algorithm> /// for sorting implicant

using namespace std;

/**
 * @brief This structure is for organizing the bits.
 */
typedef struct BitNode {
	vector<int> v; /// combined numbers or selected number
	int a = 0;	/// first bit value 
	int b = 0;	/// second bit value 
	int c = 0;	/// third bit value 
	int d = 0;	/// fourth bit value 
	int howmany1 = 0;	/// number of 1
}BitNode;

/**
 * @brief This class is the overall form
 * @for implementing an algorithm.
 */
class McCluskey {
	int select[16];	/// The selected number is initialized to 1 in this array.
public:
	/**
	* @brief Initialize the member variable as a constructor.
	*/
	McCluskey() {
		memset(select, 0, sizeof(int) * 16);
	}
	/**
	 * @brief This is a function that receives a number from 0 to 15, creates a node, and adds it to the vector.
	 * @return a vector of nodes for the selected numbers
	 */
	vector<BitNode> selectNum() {
		BitNode selectN;
		vector<BitNode> v;
		int n;	///variable to be input
		do {
			selectN.a = 0;
			selectN.b = 0;
			selectN.c = 0;
			selectN.d = 0;
			selectN.howmany1 = 0;
			selectN.v.clear();

			cin >> n;

			select[n] = 1;
			// Convert selected number to 8421 bit
			if ((n % 2) == 1) {
				selectN.d = 1;
			}
			if ((n % 4) > 1) {
				selectN.c = 1;
			}
			if ((n % 8) > 3) {
				selectN.b = 1;
			}
			if (n > 7) {
				selectN.a = 1;
			}
			selectN.howmany1 = count1(selectN.a, selectN.b, selectN.c, selectN.d);
			selectN.v.push_back(n);
			v.push_back(selectN);
		} while (getc(stdin) == ' ');	///until you press enter
		return v;
	}
	/**
	* @brief This function checks how many bits of two nodes are different.
	* @return a number of different bits
	*/
	int comparebit(BitNode node1, BitNode node2) {
		int i = 0;
		if (node1.a != node2.a) i++;
		if (node1.b != node2.b) i++;
		if (node1.c != node2.c) i++;
		if (node1.d != node2.d) i++;
		return i;
	}
	/**
	* @brief If there is only one bit difference among the two nodes, a function to know the bit position
	* @return 0~4
	*/
	int bitposition(BitNode node1, BitNode node2) {
		if (node1.a != node2.a) return 4;
		if (node1.b != node2.b) return 3;
		if (node1.c != node2.c) return 2;
		if (node1.d != node2.d) return 1;
		return 0;
	}
	/**
	* @brief function that counts the number of 1
	* @return 0~4
	*/
	int count1(int a, int b, int c, int d) {
		int cnt1 = 0;
		if (a == 1) cnt1++;
		if (b == 1) cnt1++;
		if (c == 1) cnt1++;
		if (d == 1) cnt1++;
		return cnt1;
	}
	/**
	* @brief function that combines two nodes
	* @param column vector
	* @return vector<BitNode> combined nodes
	*/
	vector<BitNode> mergingBit(vector<BitNode>& columnlist) {
		BitNode selectN;
		vector<BitNode> v;
		for (unsigned int i = 0; i < columnlist.size() - 1; i++) {
			for (unsigned int j = i + 1; j < columnlist.size(); j++) {
				if (comparebit(columnlist[j], columnlist[i]) == 1) { // merge when the condition is met while traversing
					selectN.v.clear();
					for (unsigned int k = 0; k < columnlist[i].v.size(); k++) {	//insert combined numbers
						selectN.v.push_back(columnlist[i].v[k]);
						selectN.v.push_back(columnlist[j].v[k]);
					}
					selectN.a = columnlist[i].a;
					selectN.b = columnlist[i].b;
					selectN.c = columnlist[i].c;
					selectN.d = columnlist[i].d;
					switch (bitposition(columnlist[i], columnlist[j])) {	//'-' representing a combined number is denoted as 2.
					case 1:
						selectN.d = 2;
						break;
					case 2:
						selectN.c = 2;
						break;
					case 3:
						selectN.b = 2;
						break;
					case 4:
						selectN.a = 2;
						break;
					default:
						printf("error");
					}
					selectN.howmany1 = count1(selectN.a, selectN.b, selectN.c, selectN.d);
					bool duplicateImplicant = false;
					for (unsigned int k = 0; k < v.size(); k++) {	// If there are duplicate terms before push_back, push_back is not performed.
						if ((v[k].a == selectN.a) && (v[k].b == selectN.b) && (v[k].c == selectN.c) && (v[k].d == selectN.d)) {
							duplicateImplicant = true;
						}
					}
					if (!duplicateImplicant) {
						v.push_back(selectN);
					}
				}
			}
		}
		return v;
	}

	/**
	* @brief Function to delete if term is not pi
	* @details for example, if 0 and 1 are merged
	* column 1 contains 0(0000) and 1(0001)
	* column 2 has 0,1 (0002)
	* 0 and 1 in column 1 exist in column 2, so delete them.
	* @param1 exam) column merged once
	* @param2 exam) column merged twice
	* @return void
	*/
	void delNotPi(vector<BitNode>& columnlist1, vector<BitNode>& columnlist2) {
		for (int i = columnlist1.size() - 1; i >= 0; i--) {
			for (unsigned int j = 0; j < columnlist2.size(); j++) {
				if (selectPi(columnlist1[i], columnlist2[j])) {
					columnlist1.erase(columnlist1.begin() + i);
					break;
				}
			}
		}
	}
	/**
	* @brief function that checks whether the selected number belongs to the next column
	* @details for example, if 0 and 1 are merged
	* node1 contains 0(0000)
	* node2 has 0,1 (0002)
	* 0 in node1 exist in node2, so return true.
	* @param1 exam) nodes in a column once merged
	* @param2 exam) nodes in a column twice merged
	*/
	bool selectPi(BitNode node1, BitNode node2) {
		int commonCnt = 0;	//count on equal numbers
		for (unsigned int i = 0; i < node1.v.size(); i++) {
			for (unsigned int j = 0; j < node2.v.size(); j++) {
				if (node1.v[i] == node2.v[j]) {
					commonCnt++;
				}
			}
		}
		if (commonCnt == node1.v.size()) return true;
		else return false;
	}

	bool equalArrays(vector<int>& v1, vector<int>& v2, int n) { // function to check if two vectors are equal
		for (int i = 0; i < n; ++i) {
			if (v1[i] != v2[i])
				return false;
		}
		return true;
	}
	bool belongsToArr(vector<int>& v1, vector<int>& v2, int n1, int n2) {	// function to check if a vector belongs to another vector
		int count = 0;
		for (int i = 0; i < n1; ++i) {
			for (int j = 0; j < n2; ++j) {
				if (v1[i] == v2[j]) count++;
			}
		}
		if (count == n2) return true;
		else return false;
	}

	/**
	* @brief function that finds and returns epi
	* @details for example)
	*				 4   8   10   11  12  15
	* m(4,12)*		 X			       X
	* m(8,10,11)	     X    X    X
	* m(8,10,12)	     X    X	       X
	* m(10,11,15)* 			  X    X	   X
	* in the first column, with minterm 4, there is only one "X".
	* This means that m(4,12) is essential. So we place a star next to it. 
	* Minterm 15 also has only one "X", so m(10,11,14,15) is also essential. 
	* Now all columns with one "X" are covered.
	* @param exam) vector in which pi exists
	* @return vector<BitNode>& epi
	*/
	vector<BitNode> findEpi(vector<BitNode>& pi) {
		vector<BitNode> epi;
		vector<int> epirow;
		int picollect[16];
		memset(picollect, 0, sizeof(int) * 16);
		for (unsigned int i = 0; i < pi.size(); i++) {				// Counts the number that became pi
			for (unsigned int j = 0; j < pi[i].v.size(); j++) {		// (since we only have to have one numeric value in the column to find the epi).
				picollect[pi[i].v[j]]++;
			}
		}

		for (unsigned int i = 0; i < pi.size(); i++) {			// Find pi with only one number in the column and push_back it to the epi vector.
			for (unsigned int j = 0; j < pi[i].v.size(); j++) {
				for (int k = 0; k < 16; k++) {
					bool duplicateImplicant = false;
					if ((picollect[k] == 1) && (pi[i].v[j] == k)) {
						for (unsigned int l = 0; l < epi.size(); l++) {		//If there are duplicate terms before push_back, push_back is not performed.
							if ((epi[l].a == pi[i].a) && (epi[l].b == pi[i].b) && (epi[l].c == pi[i].c) && (epi[l].d == pi[i].d)) {
								duplicateImplicant = true;
							}
						}
						if (!duplicateImplicant) {
							epi.push_back(pi[i]);
						}
					}
				}
			}
		}
		for (unsigned int i = 0; i < epi.size(); i++) {					// Since there is only one column number, the row numbers belonging to epi are separately stored in a vector.
			for (unsigned int j = 0; j < epi[i].v.size(); j++) {		// the row numbers belonging to epi are separately stored in a vector.
				select[epi[i].v[j]] = 0;
			}
		}
		for (int i = 0; i < 16; i++) {
			if (select[i] == 1) {
				epirow.push_back(i);
			}
		}

		bool areUEpi = false;
		bool pushOk = true;
		int duplicateN = 0;
		BitNode additionEpi;
		vector<vector<BitNode>> addEpi;	//additional epi
		int count = 0;
		for (unsigned int i = 0; i < pi.size(); i++) {
			for (unsigned int j = 0; j < pi[i].v.size(); j++) {
				for (unsigned int k = 0; k < epirow.size(); k++) {
					if (epirow[k] == pi[i].v[j]) {
						areUEpi = true;
						additionEpi.v.push_back(pi[i].v[j]);
					}
				}
			}
			if (areUEpi) {
				additionEpi.a = pi[i].a;
				additionEpi.b = pi[i].b;
				additionEpi.c = pi[i].c;
				additionEpi.d = pi[i].d;
				additionEpi.howmany1 = pi[i].howmany1;
				sort(additionEpi.v.begin(), additionEpi.v.end());	// Sort to compare two vectors

				/**
				* @brief If the additional epi belongs to the existing epi, push_back is not performed.
				* @details If 0 and 1 are included to be epi
				* (0,2) cannot be pushed_back if (0,1) already exists in epi
				*/
				for (unsigned int l = 0; l < epi.size(); l++) {
					if (epi[l].v.size() > additionEpi.v.size()) {
						if (belongsToArr(epi[l].v, additionEpi.v, epi[l].v.size(), additionEpi.v.size())) {
							pushOk = false;
						}
						else pushOk = true;
					}
					else if (epi[l].v.size() < additionEpi.v.size()) {
						if (belongsToArr(additionEpi.v, epi[l].v, additionEpi.v.size(), epi[l].v.size())) {
							epi.erase(epi.begin() + l);
						}
						pushOk = true;
					}
				}
				if (pushOk) {
					epi.push_back(additionEpi);
				}
			}
			areUEpi = false;
			pushOk = true;
			additionEpi.v.clear();
		}
		return epi;
	}

	/**
	* @brief function for print
	* @param epi vector
	* @return void
	*/
	void prettyprint(vector<BitNode>& epi) {
		for (unsigned int i = 0; i < epi.size(); i++) {
			if ((epi[i].a == 2) && (epi[i].b == 2) && (epi[i].c == 2) && (epi[i].d == 2)) {
				printf("1");
			}
			if (epi[i].a == 1) {
				printf("A");
			}
			else if (epi[i].a == 0) {
				printf("A'");
			}
			if (epi[i].b == 1) {
				printf("B");
			}
			else if (epi[i].b == 0) {
				printf("B'");
			}
			if (epi[i].c == 1) {
				printf("C");
			}
			else if (epi[i].c == 0) {
				printf("C'");
			}
			if (epi[i].d == 1) {
				printf("D");
			}
			else if (epi[i].d == 0) {
				printf("D'");
			}
			if ((i < epi.size() - 1) && (!equalArrays(epi[i].v, epi[i + 1].v, min(epi[i].v.size(), epi[i + 1].v.size())))) {
				printf(" + ");
			}
			else if ((i < epi.size() - 1) && (equalArrays(epi[i].v, epi[i + 1].v, min(epi[i].v.size(), epi[i + 1].v.size())))) {
				printf(" or ");
			}
		}
	}
};
int main() {
	McCluskey quine;
	vector<BitNode> columnlist[6];
	vector<BitNode> pi;
	vector<BitNode> epi;
	columnlist[0] = quine.selectNum();
	/**
	* @sample input 
	* 0 1 2 5 6 7 8 9 10 14
	**/

	int count = 0;
	while (columnlist[count].size() != 0) {	// until no merge
		columnlist[count + 1] = quine.mergingBit(columnlist[count]);
		quine.delNotPi(columnlist[count], columnlist[count + 1]);
		for (unsigned int i = 0; i < columnlist[count].size(); i++) {
			pi.push_back(columnlist[count][i]);
		}
		columnlist[count].clear();
		count++;
	}

	epi = quine.findEpi(pi);

	quine.prettyprint(epi);
	/**
	* @sample output
	* B'C' + CD' + A'BD
	**/
	return 0;
}
