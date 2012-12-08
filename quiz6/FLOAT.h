#include <iostream>

/*
Constraint: numbers in array must be between 0 and 9
Additions NEEDED:  operations work with respect to decimal point
*/
class FLOAT
{
   public:
      FLOAT();
      FLOAT(int d1, int d2, int d3, int d4, int d5, int d6, int d7, int d8, int expo, int decimal, int sigh);
      int getE() const;
      void setE(int val);
      int getQ() const;
      int getB() const;
      int getP() const;
      int getD() const;
      void setD(int val);
      int getS() const;
      void setSign(int val);
      int findnonzero(int start)
      {
         for(int i = start; i < 8; i++)
         {
            if(number[i] > 0)
               return i;
         }
         return -1;
      }
      // function for finding the rightmost nonzero digit
      int findlastnonzero(int start)
      {
         int temp = -1;
         for(int i = start; i < 8; i++)
         {
            if(number[i] > 0)
               temp = i;
         }
         return temp;
      }
      void zeroout(int at)
      {
         for (int i = at; i < 8; i++)
         {
            number[i] = 0;
         }
      }
      int getDigit(int i) const;
      void setDigit(int at, int val);
   private:
      int e, q, p, b, d, sign;
      int number[8];      
};
FLOAT shift(bool lorr, FLOAT A);
FLOAT operator+ (FLOAT a, FLOAT b);
FLOAT normalize(FLOAT a);
bool compare (FLOAT a, FLOAT b);
bool equal(FLOAT a, FLOAT b);
FLOAT addFs(FLOAT a, FLOAT b);
FLOAT assign(FLOAT a, FLOAT b);
std::ostream& operator<<(std::ostream& os,const FLOAT& number); 
