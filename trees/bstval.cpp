 #include <bits/stdc++.h>

using namespace std;
  void count_plus (int x,int y ,int &b)
{
  if(!x)
      b=-1;
  //return -1;
  if(x==y)
      return;
    //  return b;
      int c=x/10;
      int d=x%10;
   count_plus(c,y,d);  
}
int minimum_pluses(string A){
vector<string> tokens;
     stringstream check1(A);
    string intermediate;
    while(getline (check1,intermediate,'='))
    {
         tokens.push_back(intermediate);
    }
    int X=stoi( tokens[0]);
    int Y=stoi(tokens[1]);
    int b=0;
   // cout<<X<<" "<<Y;
    //return b;
   count_plus(X,Y,b);
    return b;