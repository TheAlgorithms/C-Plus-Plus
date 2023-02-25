#include <iostream>
#include <cmath>
#include <cstdint>

# define G_CONSTANT 6.6743e-11
# define EARTH_MASS 5.98e24
# define EARTH_RADIUS 6.39e+6
using namespace std;

inline void compute()
{
   // the mass of the second body attracting the earth
   uint64_t  mass;
   //Gravitational force
   long double fg;
   cout << "Enter the mass of the second body: :";
   cin >> mass;
   // applying Newton's gravitional law
   fg = (G_CONSTANT*EARTH_MASS*mass)/pow(EARTH_RADIUS , 2);
   cout << "Fg = " << fg << endl;
}
int main()
{
   compute();
   return 0;
}
