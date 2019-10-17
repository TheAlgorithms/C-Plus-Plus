#include <cstdio>
using namespace std;

int useC[8], A[8], ht, useS[20], useG[20], N;
bool found = false;

bool proveri(){
	for (int i=0; i<N; i++) if (useC[i] > 1) return false;
	for (int i=0; i<2*N; i++) if (useS[i] > 1) return false;
	for (int i=0; i<2*N; i++) if (useG[i] > 1) return false;
	return true;
}

void zavrsi(){
	if (found) printf("\n");
	found = true;
	for (int i=0; i<N; i++){
		for (int j=0; j<N; j++){
			printf("%s%s", j==A[i] ? "Q" : "-", j==N-1 ? "\n" : "\t");
		}
	}
}

void rek(){
	if (!proveri()) return;
	if (ht == N){
		zavrsi();
		return;
	}
	ht++;
	int i = ht-1;
	for (int j=0; j<N; j++){
		A[i] = j;
		useC[j]++;
		useS[i+j]++;
		useG[i-j+N]++;
		rek();
		useC[j]--;
		useS[i+j]--;
		useG[i-j+N]--;
	}
	ht--;
}

int main(){
	scanf("%d", &N);
	rek();
	if (!found){
		printf("Not Possible\n");
	}
	return 0;
}
