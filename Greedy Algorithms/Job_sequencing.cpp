//Samrat Mukherjee
//Program for Job-Scheduling using Greedy methodology

#include<iostream>
using namespace std;
int main()
{
	//n describes the number of jobs 
	int n;
	cout<<"Enter the number of jobs \t";
	cin>>n;
	
	//arrays to strore the details of each job
	int job_id[n] , profit[n] , deadline[n];
	
	for(int i = 0 ; i< n ; i++){
		cout << "Job ID: \t";
		cin>> job_id[i];
		cout<< "\nProfit: \t";
		cin>> profit[i];
		cout<< "\nDeadline: \t";
		cin>> deadline[i];
		cout << "\n";
	}
	
	//sort the array of profit while changing deadline and job_id array accordingly
	//sorting technique used :  Bubble sort  though any other sorting algo can also be applied
	
	for(int i = 0 ; i < n - 1 ; i++){
		for(int j = 0 ; j < n - i - 1 ; j++){
			if(profit[j] < profit[j+1]){
				int temp;
				//swap profit
				temp = profit[j];
				profit[j] = profit[j + 1];
				profit[j+1] = temp;
				
				//swap deadline
				temp = deadline[j];
				deadline[j] = deadline[j+1];
				deadline[j+1] = temp;
				
				//swap job_id
				temp = job_id[j];
				job_id[j] = job_id[j+1];
				job_id[j+1] = temp;
				
			}
		}
	}
	
	//max deadline
	int max = -1;
	for(int i=0;i<n;i++){
		if(max < deadline[i]){
			max = deadline[i];
		}
	}
	
	//selecting the number of job slots possible
	int len = max;
	if (max > n){
		len = n;
	}
	
	int job_seq[len];
	//initializing with -1 to show that the slot is empty
	for(int i = 0 ; i< len ; i++){
		job_seq[i] = -1;	
	}
	
	//cnt counts the number of slots filled
	int cnt = 0;
	int net_profit = 0;
	
	//looping over the total number of jobs
	for(int i=0;i<n;i++){
		if(cnt < len){
			if(deadline[i] > len){
				deadline[i] = len;
			}
			//finding the slot for the job
			for(int j = deadline[i] - 1 ; j >=0 ; j--){
				//if the slot is free
				if(job_seq[j] == -1){
					job_seq[j] = job_id[i];
					net_profit += profit[i];
					cnt++;
					break;
				}
			}
		}
		else{
			break;
		}
	}
	
	cout<<"Job ordering yielding maximum profit\n";

	for(int i=0 ; i < len ; i++){
		cout<<"T" << i + 1 <<"->"<<job_seq[i] << "\n";
	}
	
	cout<<"\nNet profit\n";
	cout<<net_profit;
}
