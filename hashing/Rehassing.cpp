#include "iostream"
#include "string.h"

using namespace std;
class HashTable
{
private:
	string* table; 
	int size; 
	int curSize; 
public:
	HashTable(int size) {
		this->size = size;
		table = new string[size];
		this->curSize = 0;
		for (int i = 0; i < size; i++) {
			table[i] = "empty";
		}
	} 
	
	~HashTable() {
		delete[] table;
	}
	
	bool isEmpty() {
		if (curSize == 0) {
			return true;
		}
		return false;
	}

	bool isFull() {
		if (curSize == size) {
			return true;
		}
		return false;
	}
	double loadFactor() {
		return (curSize / size);
	}

	int hash(string name) {
		return value(name) % size;
	}

	int value(string name) {
		int temp = 0;
		for (int i = 0; i < name.length(); i++) {
			temp = temp + name[i];
		}
		return temp;
	}

	bool insert(string name) {
		if (curSize != size) {
			int h = hash(name);
			for (int i = 0; i < size; i++) {
				if (table[h] == "empty") {
					table[h] = name;
					curSize++;
					return true;
				}
				else
				{
					h = (h + 1) % size;
				}
			}
			cout << "can not insert" << endl;
		}
		else
		{
			cout << "arrays Full" << endl;
			return false;
		}
	}

	void display() {
		if(curSize != 0){
			for (int i = 0; i < size; i++) {
				cout << i << " : " << table[i] << endl;
			}
		}else{
			cout << "Litsa ia empty" << endl;
		}
	}


	bool search(string name) {
		if (curSize != 0) {
			int h = hash(name);
			for (int i = 0; i < size; i++) {
				if (table[h] == name) {
					cout << "Name is there" << endl;
					return true;
				}
				else
				{
					h = (h + 1) % size;
				}
			}
			cout << "Nmae not found" << endl;
			return false;
		}
		cout << "Empty" << endl;
		return false;
	}

	bool remove(string name)
	{
		if (!isEmpty())
		{
			int h = hash(name);
			for (int i = 0; i < size; i++)
			{
				if (table[h] == name)
				{
					cout << "Name Found in Search, Removing Item" << endl;
					curSize--;
					table[h] = "empty";
					return true;
				}
				else
				{
					h = (h + 1) % size;
				}
			}
			cout << "Name NOT Found in Search, Not Removed" << endl;
			return false;
		}
		else
		{
			cout << "Table Empty, Cannot remove" << endl;
			return false;
		}
	}

};


int main() {
	HashTable obj(3);
	cout << obj.insert("AHMAD") << endl;
	cout << obj.insert("ahmad") << endl;
	cout << obj.insert(".") << endl;
	/*string A[1] = { "ALI" };
	string B = "ALI";
	cout << A->length() << endl;
	cout << B[0] << endl;
	cout << B[0]+1 << endl;
	*/
	obj.search(".");
	obj.display();
	obj.remove(".");
	obj.display();
	return 0;
}