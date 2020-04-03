#include<iostream>
#include<fstream>
#include<stdint.h>


using namespace std;

void _13adjacent(int64_t array[], int num)
{
    int i;
    int64_t max=0,temp;
    for(i=0;i<num;++i)
    {
        if(array[i] == 0 || array[i+1] == 0 || array[i+2] == 0 || array[i+3] == 0 || array[i+4] == 0 || array[i+5] == 0 || array[i+6] == 0 || array[i+7] == 0 || array[i+8] == 0 || array[i+9] == 0 || array[i+10] == 0 || array[i+11] == 0 || array[i+12] == 0)
        {   
            i+=12;
        } 
        else
            temp = array[i]*array[i+1]*array[i+2]*array[i+3]*array[i+4]*array[i+5]*array[i+6]*array[i+7]*array[i+8]*array[i+9]*array[i+10]*array[i+11]*array[i+12];
        if(temp > max)
            max = temp;
    }
    cout<<max;
}


int main()
{

    int64_t arr[1000];
    char ch;
    int i=0;
    fstream file;
    file.open ("problem-8.txt", ios::in);
    file.seekg(0, file.beg);
    while(!file.eof())
    {
        file.get(ch);        
        if(ch != '\n')
        {
            arr[i] = (int) ch - '0';
            i++;
        }
    }
    file.close();
    _13adjacent(arr,1000);
    return 0;
}
