#include<fstream>
#include<string>

using namespace std;

void array_push(int * a){
	int i,j,tmp=0, flag=0;
	for(i = 99; i > -1; --i){
		tmp = a[i] / 10;
		a[i] = a[i] % 10;
		if(i>0)
			a[i-1] += tmp;
		tmp = 0;
		if(a[i-1] == 0)
			break;
	}
	flag = i;
	for(i=flag;i<flag+10;++i){
		printf("%d", a[i]);
	}
	printf("\n");
}
int main(){
	fstream file("./13.txt", fstream::in);
	int v[100][50];
	string line;
	int i,j,c=0;
	int ans[100];
	for(i=0;i<100;++i){
		ans[i] = 0;
	}
	i = 0;
	if(file.is_open()){
		while(getline(file, line)){
			for(j=0;j<50;j++){
				v[i][j] = line[j] - '0';
			}
			++i;
		}
		file.close();
		for(j = 49; j>=0 ; --j){
			for(i=0; i<100; ++i){
				if(c<100){
					ans[99-c] += v[i][j];
				}
			}
			++c;
		}
		array_push(ans);
	}
	return 0;
}

