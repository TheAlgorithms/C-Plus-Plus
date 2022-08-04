#include <iostream>
#include <cassert>
#include <random>
#include "rbtree.h"

using namespace std;

void TestSimpleConstructor(){
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	//cout << "empty r-b-tree: " << rbt.ToInfixString() << endl;
	assert(rbt.ToInfixString() == "");
	
	cout << "PASSED!"<< endl << endl;
}

void TestInsertFirstNode(){
	cout << "Testing Insert One Node..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	//cout << "rbt: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B30 ");

	cout << "PASSED!" << endl << endl;
}

void TestInsertSecondNode(){
	cout << "Testing Insert Second Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30); // leak here
	rbt->Insert(15);
	//cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  R15 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	//cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  R45 ");	
	delete rbt;

	cout << "PASSED!" << endl << endl;
}

void TestInsertThirdNode(){
	cout << "Testing Insert Third Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10); // Left Left
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	
	// ROTATE RIGHT ONCE
	assert(rbt->ToPrefixString() == " B15  R10  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(25); // Left right
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;

	// ROTATE ONCE RIGHT ON PARENT THEN ONCE LEFT ON GRANDPARENT
	assert(rbt->ToPrefixString() == " B25  R15  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45); // Easy case

	// NODES ON EITHER SIDE AND PARENT IS BLACK, SO NO ROTATION OR RECOLOR
	assert(rbt->ToPrefixString() == " B30  R15  R45 ");
	delete rbt;
	
	// more tests go here
	// consider some symmetry!

	rbt = new RedBlackTree();
	rbt->Insert(75);
	rbt->Insert(215);
	rbt->Insert(130); // Right left

	assert(rbt->ToPrefixString() == " B130  R75  R215 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(648);
	rbt->Insert(735);
	rbt->Insert(9442); // Right right

	assert(rbt->ToPrefixString() == " B735  R648  R9442 ");
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestInsertFourthNode(){
	cout << "Testing Insert Fourth Node..." << endl;

	RedBlackTree rbt = RedBlackTree();

	rbt.Insert(13);
	rbt.Insert(7);
	rbt.Insert(3);
	rbt.Insert(9);

	assert(rbt.ToPrefixString() == " B7  B3  B13  R9 ");

	RedBlackTree rbt2 = RedBlackTree();

	rbt2.Insert(34);
	rbt2.Insert(76);
	rbt2.Insert(21984);
	rbt2.Insert(2);

	//cout << "rbt2: " << rbt2.ToPrefixString() << endl;
	assert(rbt2.ToPrefixString() == " B76  B34  R2  B21984 ");

	cout << "PASSED!" << endl << endl;
}

void TestInsertFifthNode(){
	cout << "Testing Insert Fifth Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	rbt->Insert(25);
	//cout << "result: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  B15  R10  R25  B45 ");
	delete rbt;

	RedBlackTree rbt2 = RedBlackTree();
	rbt2.Insert(783);
	rbt2.Insert(91);
	rbt2.Insert(31);
	rbt2.Insert(11);
	rbt2.Insert(-87);
	//cout << "rbt2: " << rbt2.ToPrefixString() << endl;
	assert(rbt2.ToPrefixString() == " B91  B11  R-87  R31  B783 ");
	
	cout << "PASSED!" << endl << endl;
}


void TestToStrings(){
	cout << "Testing ToString Methods..." << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(12);
	rbt.Insert(11);
	rbt.Insert(15);
	rbt.Insert(5);
	rbt.Insert(13);
	rbt.Insert(7);
	
	assert(rbt.ToPrefixString() == " B12  B7  R5  R11  B15  R13 ");
	assert(rbt.ToInfixString() == " R5  B7  R11  B12  R13  B15 ");
	assert(rbt.ToPostfixString() == " R5  R11  B7  R13  B15  B12 ");

	cout << "PASSED!" << endl << endl;
}

void TestInsertRandomTests(){
	cout << "Testing Random Insert Stuff..." << endl;
	cout << "\t This test passes if it doesn't crash and valgrind reports no issues" << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(13);
	rbt->Insert(20);
	rbt->Insert(12);
	cout << endl;
	//cout << "tree: " << rbt->ToInfixString() << endl;
	delete rbt;
	
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(11);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(15);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(5);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(13);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(7);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(10);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(8);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestCopyConstructor(){
	cout << "Testing Copy Constructor..." << endl;

	RedBlackTree rbt1 = RedBlackTree();
	rbt1.Insert(11);
	rbt1.Insert(23);
	rbt1.Insert(9);
	rbt1.Insert(52);
	rbt1.Insert(31);
	rbt1.Insert(4);

	assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

	RedBlackTree rbt2 = RedBlackTree(rbt1);

	assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());

	rbt1.Insert(200);
	assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());

	cout << "PASSED!" << endl << endl;
}


void TestContains(){
	cout << "Testing Contains..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(31);
	rbt->Insert(55);
	rbt->Insert(12);
	rbt->Insert(17);
	rbt->Insert(29);
	rbt->Insert(34);
	//cout << "rbt: " << rbt->ToInfixString() << endl;
	
	assert(rbt->Contains(34));
	delete rbt;

	RedBlackTree rbt2 = RedBlackTree();
	rbt2.Insert(1);
	rbt2.Insert(27);
	rbt2.Insert(99);
	rbt2.Insert(19);

	assert(rbt2.Contains(1) && rbt2.Contains(99));

	cout << "PASSED!" << endl << endl;
}


void TestGetMinimumMaximum(){
	cout << "Testing Get Minimum and Get Maximum..." << endl;

	RedBlackTree rbt = RedBlackTree();

	rbt.Insert(34);
	rbt.Insert(76);
	rbt.Insert(21984);
	rbt.Insert(2);

	//cout << "rbt: " << rbt.ToPrefixString() << endl;
	assert(rbt.GetMax() == 21984 && rbt.GetMin() == 2);

	cout << "PASSED!" << endl << endl;
}

void TestCopyConstructor2(){
	cout << "Testing Copy Constructor..." << endl;

	RedBlackTree rbt1 = RedBlackTree();
	rbt1.Insert(11);
	rbt1.Insert(23);
	rbt1.Insert(9);
	rbt1.Insert(52);
	rbt1.Insert(31);
	rbt1.Insert(4);

    //cout << "rbt: " << rbt1.ToPrefixString() << endl;
	assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

	RedBlackTree rbt2 = RedBlackTree(rbt1);

	assert(rbt1.Size() == rbt2.Size());
	assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());

	rbt1.Insert(200);
	assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());

	RedBlackTree rbt3 = RedBlackTree();
    cout << rbt3.ToPrefixString() << endl;
	rbt3.Insert(12);
	rbt3.Insert(10);
	rbt3.Insert(0);
	rbt3.Insert(11);
	rbt3.Insert(3);
	rbt3.Insert(9);
	rbt3.Insert(2);
	rbt3.Insert(7);
	rbt3.Insert(1);
	rbt3.Insert(4);
	rbt3.Insert(6);
	rbt3.Insert(8);
	rbt3.Insert(37);
	rbt3.Insert(5);
	rbt3.Insert(72);
	rbt3.Insert(55);
	rbt3.Insert(90);
	rbt3.Insert(92);
	rbt3.Insert(20);
	rbt3.Insert(13);
	rbt3.Insert(57); // (good here for whole tree) should have B7 root, B3 root left, R12 root right here
	rbt3.Insert(30);
	rbt3.Insert(64);
	rbt3.Insert(69); // **where left rotate on root occurs, but good here (root = B12, root left = R7, root right = R55)
	rbt3.Insert(50);
	rbt3.Insert(67);
	rbt3.Insert(99);
	rbt3.Insert(89);
	rbt3.Insert(33);
    //cout << "rbt: " << rbt3.ToPrefixString() << endl;

	assert(rbt3.ToPrefixString() == " B12  R7  B3  B1  R0  R2  B5  R4  R6  B10  B9  R8  B11  R55  B20  B13  R37  B30  R33  B50  B69  R64  B57  B67  R90  B72  R89  B92  R99 ");

	RedBlackTree rbt4 = RedBlackTree(rbt3);

	string s3 = rbt3.ToPrefixString();
	//cout << "s3: " << s3 << endl;
	string s4 = rbt4.ToPrefixString();
	//cout << "s4: " << s4 << endl;
	assert(rbt3.Size() == rbt4.Size());
	assert(s3 == s4);


	rbt3.Insert(200);
	assert(rbt3.ToPrefixString() != rbt4.ToPrefixString());

	cout << "PASSED!" << endl << endl;
}


void TestInsertWithRecursiveFixUp(){
	cout << "Testing Recursive FixUp..." << endl;
	
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(400);
	rbt->Insert(800);
	rbt->Insert(200);
	rbt->Insert(600);
	rbt->Insert(150);
	rbt->Insert(900);
	rbt->Insert(300);
	rbt->Insert(100); // visualization and prefix looks good up to here for my code
	rbt->Insert(175); // also looks good here
	rbt->Insert(160); // does some weird stuff!
    //cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B200  R150  B100  B175  R160  R400  B300  B800  R600  R900 ");
	rbt->Insert(185);
	rbt->Insert(180); // does a recursive fix-up
	assert(rbt->ToPrefixString() == " B200  B150  B100  R175  B160  B185  R180  B400  B300  B800  R600  R900 ");
	//cout << "rbt: " << rbt->ToPrefixString() << endl;
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void PrintTestLine(string desc, RedBlackTree*& rbt, string exp_ans) {
	cout << desc << ": " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == exp_ans);
}

void RemoveTest1() {
	cout << "Testing removing root (with one child)..." << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(10);
	rbt.Insert(459);

	cout << "Size: " << rbt.Size() << endl;
	assert(rbt.Size() == 2);

	cout << "rbt: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B10  R459 ");

	// remove root with one right child
	rbt.Remove(10);

	cout << "rbt: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B459 ");

	// remove root with no children (empties tree)
	rbt.Remove(459);

	cout << "rbt: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == "");
	assert(rbt.Size() == 0);

	cout << "PASSED!" << endl << endl;
}

void RemoveTest2() {
	cout << "Testing removing leaf..." << endl;

 	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(10);
	rbt.Insert(459);

	cout << "rbt: " << rbt.ToPrefixString() << endl;

	// Removing leaf
	rbt.Remove(459);

	cout << "rbt: " << rbt.ToPrefixString() << endl;

	// Removing last node/root (empties tree again)
	rbt.Remove(10);

	cout << "rbt: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == "");

	cout << "PASSED!" << endl << endl;
}

void RemoveTest3() {
	cout << "Testing removing node with two children..." << endl;

	RedBlackTree* rbt = new RedBlackTree();
	rbt->Insert(14);
	rbt->Insert(10);
	rbt->Insert(459); // B14 R10 R459 -- node 14 with two children 10 and 459

	PrintTestLine("tree", rbt, " B14  R10  R459 ");

	// Remove 14 (has two children)
	rbt->Remove(14);
	PrintTestLine("removing 14", rbt, " B459  R10 ");

	rbt->Remove(459);
	PrintTestLine("removing 459", rbt, " B10 ");

	rbt->Remove(10);
	PrintTestLine("removing 10", rbt, "");

	delete rbt;
	cout << "PASSED!" << endl << endl;
}

void RemoveTest4() {
	cout << "Removing from larger tree (recursive call with IOS or IOP test)..." << endl;

	RedBlackTree *rbt = new RedBlackTree();

	rbt->Insert(94);
	rbt->Insert(18);
	rbt->Insert(3);
	rbt->Insert(22);
	rbt->Insert(0);
	rbt->Insert(537);
	rbt->Insert(308);
	rbt->Insert(23);
	rbt->Insert(24);
	rbt->Insert(21);
	rbt->Insert(25);

	PrintTestLine("tree", rbt, " B23  R18  B3  R0  B22  R21  R94  B24  R25  B537  R308 ");

	rbt->Remove(23);

	PrintTestLine("removing 23", rbt, " B24  R18  B3  R0  B22  R21  R94  B25  B537  R308 ");

	delete rbt;
	cout << "PASSED!" << endl << endl;
}

void RemoveTestRotateCase() {
	cout << "Testing removing that requires double-black fix..." << endl;

	RedBlackTree *rbt = new RedBlackTree();

	rbt->Insert(9);
	rbt->Insert(11);
	rbt->Insert(5);
	rbt->Insert(14);
	rbt->Insert(4);
	rbt->Insert(6);
	rbt->Insert(7);

	PrintTestLine("tree", rbt, " B9  R5  B4  B6  R7  B11  R14 ");

	// RIGHT RIGHT CASE -- rotate left on black sibling
	rbt->Remove(4);

	PrintTestLine("right right remove", rbt, " B9  R6  B5  B7  B11  R14 ");
	
	RedBlackTree rbt2 = RedBlackTree();

	rbt2.Insert(9);
	rbt2.Insert(11);
	rbt2.Insert(5);
	rbt2.Insert(14);
	rbt2.Insert(4);
	rbt2.Insert(7);
	rbt2.Insert(6);

	cout << "tree2: " << rbt2.ToPrefixString() << endl;
	assert(rbt2.ToPrefixString() == " B9  R5  B4  B7  R6  B11  R14 ");

	// RIGHT LEFT CASE (black sibling 7 is right child with one left red child)
	rbt2.Remove(4);

	cout << "right left remove: " << rbt2.ToPrefixString() << endl;
	assert(rbt2.ToPrefixString() == " B9  R6  B5  B7  B11  R14 ");

	rbt2.Insert(4); // makes left left case when removing 7
	assert(rbt2.ToPrefixString() == " B9  R6  B5  R4  B7  B11  R14 ");

	// LEFT LEFT CASE (black sibling 5 is left child with one left red child)
	rbt2.Remove(7);
	assert(rbt2.ToPrefixString() == " B9  R5  B4  B6  B11  R14 ");

	// deconstruct red black tree and construct a new, empty tree again from same variable
	delete rbt;
	rbt = new RedBlackTree();

	// inserting nodes into tree from an array
	int fill_tree_vec[12] = { 9, 11, 5, 14, 4, 6, 7, 3, 2, 17, 1, 8 };
	for (int val : fill_tree_vec) {
		rbt->Insert(val);
	}
	cout << "tree3: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B5  R3  B2  R1  B4  R9  B7  R6  R8  B14  R11  R17 ");

	rbt->Remove(1); // simple remove on red leaf
	//cout << "removing 1: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B5  R3  B2  B4  R9  B7  R6  R8  B14  R11  R17 ");

	rbt->Insert(0);
	//cout << "inserting 0: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B5  R3  B2  R0  B4  R9  B7  R6  R8  B14  R11  R17 ");

	rbt->Insert(1);
	//cout << "inserting 1: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B5  R3  B1  R0  R2  B4  R9  B7  R6  R8  B14  R11  R17 ");

	rbt->Remove(0); // another simple red leaf remove
	//cout << "removing 0: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B5  R3  B1  R2  B4  R9  B7  R6  R8  B14  R11  R17 ");

	// LEFT RIGHT CASE (black sibling 1 is a left child with one right red child)
	rbt->Remove(4);
	cout << "left right remove: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B5  R2  B1  B3  R9  B7  R6  R8  B14  R11  R17 ");

	// removing 3 (recursive fix double black case) (*TRY LATER) -- PASSING NOW!! :)
	rbt->Remove(3);
	PrintTestLine("recursive double-black fix (removing 3)", rbt, " B5  B2  R1  R9  B7  R6  R8  B14  R11  R17 ");

	delete rbt;
	cout << "PASSED!" << endl << endl;
}

void RemoveTestRedSiblingCase() {
	cout << "Testing remove that requires double-black fix with red sibling case..." << endl;

	RedBlackTree rbt = RedBlackTree();

	int fill_tree_vec[6] = {11, 9, 7, 5, 8, 6};
	for (int val : fill_tree_vec) {
		rbt.Insert(val);
	}
	cout << "tree: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B9  R7  B5  R6  B8  B11 ");

	rbt.Remove(11); // 11 is black leaf with red sibling 7
	cout << "removing 11: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B7  B5  R6  B9  R8 ");

	cout << "PASSED!" << endl << endl;
}

void LargeRandomRemoveMemoryTest() {
	cout << "Giant Remove Test..." << endl;

	RedBlackTree* giant_rbt = new RedBlackTree();

	vector<int> random_numbers; // to store inserted numbers

	while (giant_rbt->Size() != 711){
		int random_num = rand();
		if (!giant_rbt->Contains(random_num)) {
			random_numbers.push_back(random_num);
			giant_rbt->Insert(random_num);
		}
	}
	int idx = random_numbers.size() - 1; // getting numbers to remove, starting from end of vector

	// then removing the numbers until tree is empty (checking for memory issues/exceptions)
	while (giant_rbt->Size() != 0) {
		giant_rbt->Remove(random_numbers[idx--]);
	}

	delete giant_rbt;
	cout << "PASSED!" << endl << endl;
}

void LargerComprehensiveRemoveTest() {
	cout << "Testing many removes from larger tree..." << endl;

	RedBlackTree *rbt = new RedBlackTree();

	int fill_tree_vec[19] = { 40, 97, 12, 43, 33, 87, 99, 439, 8762, 3, 7, 1, 2, 9999, 8888, 2345, 111, 687, 0 };

	for (int val : fill_tree_vec) {
		rbt->Insert(val);
	}

	cout << "tree: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B87  B12  R3  B1  R0  R2  B7  R40  B33  B43  B439  R99  B97  B111  R8762  B2345  R687  B9999  R8888 ");

	rbt->Remove(87); // removing root
	cout << "removing 87: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B97  B12  R3  B1  R0  R2  B7  R40  B33  B43  B439  B99  R111  R8762  B2345  R687  B9999  R8888 ");

	delete rbt;
	cout << "PASSED!" << endl << endl;
}


int main(){
	
	TestSimpleConstructor();

	TestInsertFirstNode();

	TestInsertSecondNode();
	TestInsertThirdNode();
	TestInsertFourthNode();
	TestInsertFifthNode();

	TestToStrings();
	TestInsertRandomTests();
	TestCopyConstructor();

	TestContains();
	TestGetMinimumMaximum();

	TestCopyConstructor2();
	TestInsertWithRecursiveFixUp();

	RemoveTest1();
	RemoveTest2();
	RemoveTest3();
	RemoveTest4();
	RemoveTestRotateCase();
	RemoveTestRedSiblingCase();
	LargeRandomRemoveMemoryTest();
	LargerComprehensiveRemoveTest();
	
	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}