//this algorithm only works with positive, whole numbers.
//O(2n) time complexity where n is the summation of the whole list to be sorted. 
//O(3n) space complexity.
 
#include <iostream>
#include <vector>
 
using std::cout;
using std::vector;
 
void distribute(int dist, vector<int> &List) {
	//*beads* go down into different buckets using gravity (addition).
    if (dist > List.size() )
        List.resize(dist); //resize if too big for current vector
 
    for (int i=0; i < dist; i++)
        List[i]++;
}
 
vector<int> beadSort(int *myints, int n) {
    vector<int> list, list2, fifth (myints, myints + n);
 
    cout << "#1 Beads falling down: ";
    for (int i=0; i < fifth.size(); i++)
        distribute (fifth[i], list);
    cout << '\n';
 
    cout << "\nBeads on their sides: ";
    for (int i=0; i < list.size(); i++)
        cout << " " << list[i];
    cout << '\n';
 
    //second part
 
    cout << "#2 Beads right side up: ";
    for (int i=0; i < list.size(); i++)
        distribute (list[i], list2);
    cout << '\n';
 
    return list2;
}
 
int main() {
    int myints[] = {734,3,1,24,324,324,32,432,42,3,4,1,1};
	vector<int> sorted = beadSort(myints, sizeof(myints)/sizeof(int));
	cout << "Sorted list/array: ";
	for(unsigned int i=0; i<sorted.size(); i++)
		cout << sorted[i] << ' ';
}