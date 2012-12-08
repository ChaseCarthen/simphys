#include <iostream>
#include <iomanip>
#include <cmath>
#include "FLOAT.h"
using namespace std;

int main()
{
   FLOAT A {1,1,1,1,1,1,1,3,7,7,1};
   FLOAT B {1,1,1,1,1,1,1,1,7,7,-1};
   FLOAT C {7,5,1,1,1,1,1,1,7,0,1};
   FLOAT a{0,0,0,1,0,0,0,0,7,4,-1};
   FLOAT b{0,0,0,0,0,0,0,0,15,0,1};
   cout << A << " " << B << " " << C << endl << a << endl;
   a = normalize(a);
   //A = shift(false,A);  
   //auto ARESULT = normalize(A);
   //FLOAT B {2,3,4,5,6,7,8,1,3,0,1};
   //cout << (A+B)+C << std::endl << std::endl;
   cout << (a) << 10123123.0f << setprecision(16);
   return 0;
}
