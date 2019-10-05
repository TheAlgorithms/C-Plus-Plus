/* contributed by manav014*/

/*project_euler problem 26
Reciprocal cycles
Question
A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:

1/2	= 	0.5
1/3	= 	0.(3)
1/4	= 	0.25
1/5	= 	0.2
1/6	= 	0.1(6)
1/7	= 	0.(142857)
1/8	= 	0.125
1/9	= 	0.(1)
1/10	= 	0.1
Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.

Find the init of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.*/

/*Explaination of the solution
Just applied the simple brute force algorithm of the solution 
for example if i take the example of 1/7
1/7	= 0.(142857)

1/7=0
10/7=1 and 10%7=3
(3*10)/7=4 and 30%7=2
(2*10)/7=2 and 20%7=6
(6*10)/7=8 and 60%7=4
(4*10)/7=5 and 40%7=5
(5*10)/7=7 and 50%7=1
(1*10)/7=1 and 10%7=3
as the cycle starts repeating itself we will stop here

*/
#include <iostream>
using namespace std;
void solve()
{
	unsigned long long int i,init,high,counter,higher,x;
  high=0;
  for (i=3;i<=1000;i++){
    counter=0;
    init = 10%i;
    x=1001;
    while (x>0 && init != 1){
      init *=10;
      init %=i;
      counter++;
      x--;
    }
    if (counter>high && x>1){
      high=counter;
      higher=i;
    }
  }
	cout<<higher<<endl;
}

int main(){
  solve();
return 0;
}
