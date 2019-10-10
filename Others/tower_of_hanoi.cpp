void tower_of_hanoi(int N, char source='A', char helper='B', char destination='C')
{
	if(N==0)
		return;
	tower_of_hanoi(N-1, source, destination, helper);
	cout<<"From "<<source<<" to "<<destination<<endl;
	tower_of_hanoi(N-1, helper, source, destination);
}
