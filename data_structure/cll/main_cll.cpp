#include "cll.h"
using namespace std;

int main()
{
	/* Test CLL */
	cout << "----------- Test construct -----------" << endl;
	cll list1;
	list1.display();
	cout << "----------- Test insert front -----------" << endl;
	list1.insert_front(5);
	cout << "After insert 5 at front: "<<endl;
    list1.display();
	cout << "After insert 10 3 7 at front: "<<endl;
	list1.insert_front(10);
	list1.insert_front(3);
	list1.insert_front(7);
	list1.display();
	cout << "----------- Test insert tail -----------" << endl;
	cout << "After insert 18 19 20 at tail: "<<endl;
	list1.insert_tail(18);
	list1.insert_tail(19);
	list1.insert_tail(20);
	list1.display();
	cout << "----------- Test find item -----------" << endl;
	if (list1.find_item(10))
		cout << "PASS" << endl;
	else
		cout << "FAIL" << endl;
	if (!list1.find_item(30))
		cout << "PASS" << endl;
	else
		cout << "FAIL" << endl;
	cout << "----------- Test * operator -----------" << endl;
	int value = *list1;
	cout << "Value at *list1: " << value <<endl;
	cout << "----------- Test ++ operator -----------" << endl;
	list1.display();
	++list1;
	cout << "After ++list1: " <<endl;
	list1.display();

	return 0;
}
