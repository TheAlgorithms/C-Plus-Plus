/*Gas Station- Greedy

Problem Statement: 
There are N gas stations along a circular route, where the amount of gas at station i is gas[i].
You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i 
to its next station (i+1). You begin the journey with an empty tank at one of the gas stations.

Task: 
Return the starting gas station's index if you can travel around the circuit once in the clockwise 
direction, otherwise return -1.

Solution: 
The main observation here is this: If start from i, stop before station x it implies no station 
k from i + 1 to x - 1 can reach x. Because if so, i can reach k and k can reach x, then i reaches x. Contradiction.
From station 0 we will stop at if we cannot move further and then skip all the station in between 
using the above theory. If we reach a station again then this is our answer, we check this by keeping 
a unordered map.
*/


#include <iostream>
#include <vector> 
#include <cassert>
#include <unordered_map>

int gasStation(std::vector<int> gas, std::vector<int> cost) 
{
    int i, start, tank, n = gas.size();
    std::unordered_map<int,int>mark;
	
    start = 0;
        
    do
    {
        i = start;
        tank = 0;
            
        while(tank + gas[i] >= cost[i])
        {
            tank += gas[i] - cost[i];
            i = (i + 1)%n;
                
            if(i == start)
                return start;
        }
            
        mark[start] = 1;
        start = (i + 1)%n;
            
        }while(mark[start] == 0);
        
        return -1;
    }

/**
 * @brief Function to test above algorithm
 * @returns void
 */
 
static void test()
{
  // Test 1
  {
   std::vector<int> gas =  {2, 3, 4};
   std::vector<int> cost = {3, 4, 3};

   int output = gasStation(gas, cost);
   assert(output == -1);
   std::cout << "Input:" << std::endl;
   std::cout << "Gas array: ";
   for(auto i: gas)
   {
     std::cout << i << " ";
   }
   std::cout << std::endl;
   std::cout << "Cost array: ";
   for(auto i: cost)
   {
     std::cout << i << " ";
   }
   std::cout << "Output: -1" << std::endl;
  }
  
  // Test 2
  {
   std::vector<int> gas =  {1, 2, 3, 4, 5};
   std::vector<int> cost = {3, 4, 5, 1, 2};

   int output = gasStation(gas, cost);
   assert(output == 3);
   std::cout << "Input:" << std::endl;
   std::cout << "Gas array: ";
   for(auto i: gas)
   {
     std::cout << i << " ";
   }
   std::cout << std::endl;
   std::cout << "Cost array: ";
   for(auto i: cost)
   {
     std::cout << i << " ";
   }
   std::cout << "Output: 3" << std::endl;
  }
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
 
int main() 
{
	test();
    return 0;
}
