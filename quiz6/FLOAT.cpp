#include "FLOAT.h"
#include <cmath>
FLOAT::FLOAT()
{
   e = 0;
   q = 7;
   p = 8;
   b = 10;
   d = 0;
   for(int i = 0; i < 8; i++)
   {
      number[i] = 0;
   }
}

FLOAT::FLOAT(int d1, int d2, int d3, int d4, int d5, int d6, int d7, int d8, int expo, int decimal, int sigh)
{
  number[0] = d1;
  number[1] = d2;
  number[2] = d3;
  number[3] = d4;
  number[4] = d5;
  number[5] = d6;
  number[6] = d7;
  number[7] = d8;
  e = expo;
  q = 7;
  if (expo < -1)
  {
     e = -1;
  }
  else if ( expo > 16 )
  {
     e = 15;
  }
  p = 8;
  b = 10;
  d = decimal;
  sign = sigh;
}

FLOAT ONE{1,0,0,0,0,0,0,0,7,1,1};
FLOAT ZERO{0,0,0,0,0,0,0,0,-1,0,1};
FLOAT POINTONE{1,0,0,0,0,0,0,0,7,0,1};

int FLOAT::getE() const
{
   return e;
}

void FLOAT::setE(int val)
{
   e = val;
}

int FLOAT::getQ() const
{
   return q;
}

int FLOAT::getB() const
{
   return b;
}
int FLOAT::getP() const
{
   return p;
}

int FLOAT::getD() const
{
   return d;
}

void FLOAT::setD(int val)
{
   d = val;
}

int FLOAT::getDigit(int i) const
{
   return number[i];
}

void FLOAT::setDigit(int at, int val)
{
   number[at] = val;
}
FLOAT normalize(FLOAT a)
{
   bool normed = false;
   int temp;
   while(!normed)
   {
      std::cout << "norm iteration: " << a << std::endl;
      if(equal(ONE,a) || compare(a,ONE))
      {
         a = shift(true,a);
         a.setE(a.getE()+1);
         std::cout << a;
         normed = true;
         break;
      }
      else if(equal(ZERO,a))
      {
         normed = true;
         continue;
      }
      if(equal (POINTONE,a)||compare(a,POINTONE))
      { 
         //std::cin >> temp;
         //std::cout << "here" << std::endl;
         int high = a.findlastnonzero(a.getD());
         // step 5
         if (high != 0 && high != -1 && a.getDigit(high) >= 5 )
         {
            a.setDigit(high-1,a.getDigit(high-1)+1);
            a.zeroout(high);
            //std::cout << high-1 << "laksldljfl";
         }
         else if (high != 0 && high != -1 && a.getDigit(high) < 5 )
         {
            //a.setDigit(high-1,a.getDigit(high-1)+1);
            a.zeroout(high);
         }
         if(equal(ONE,a) || compare(a,ONE))
         {
            a = shift(true,a);
            a.setE(a.getE()+1);
            //std::cout << "here99100";
         }
         normed = true;
         continue;
      }
      //std::cout << "shifting" << std::endl;
      a = shift(false,a);
      //std::cout << a;
      //std::cin >> temp;
      a.setE(a.getE()-1);
      if (a.getE() > 15)
      {
         std::cout << a << " overflow error!";
         return a;
      }
      else if (a.getE() < -1)
      {
         std::cout << a << " underflow error!";
         return a;
      }
   }
   return a;
}

// if true then a greater than b, false is a less than b
bool compare (FLOAT a, FLOAT b)
{
   int temp = a.getD();
   int temp2 = b.getD();
   bool greater = false;
   bool found = false;
   //checking greatness through left
   //if (temp != 0 && temp2 != 0 )
   for ( int i = temp-1, j = temp2 - 1; i > 0 && j > 0; i--, j--)
   {
      //for (int j = temp2-1; j > 0; j--)
      //{
            std::cout << a.getDigit(i) << " " << b.getDigit(j) << std::endl;
            if(a.getDigit(i) > b.getDigit(j))
            {
               found = true;
               greater = true;
            }
            else if (b.getDigit(j)>a.getDigit(i))
            {
               greater = false;
               found = true;
            }
      //}
   }
   if (!found)
   {
      // if not found, then check if one is obviously greater than the other
      if(temp == 0 && temp2 != 0)
      {
         int index = b.findnonzero(0);
         if( index != -1 && index <= temp2)
         {
            return false;
         }
      }
      else if (temp2 == 0 && temp != 0)
      {
         int index = a.findnonzero(0);
         //std::cout << index;
         if( index != -1 && index < temp)
         {
            return true;
         }
      }
      
   }
   // check right
   for ( int i = temp, j = temp2; i < 8 && j < 8; i++, j++)
   {
      //for (int j = temp2-1; j > 0; j--)
      //{
            //std::cout << a.getDigit(i) << " " << b.getDigit(j) << std::endl;
            if(a.getDigit(i) > b.getDigit(j))
            {
               return true;
            }
            else if (b.getDigit(j)>a.getDigit(i))
            { 
               return false;
            }
      //}
   }
   return greater;
}

bool equal(FLOAT a, FLOAT b)
{
   int temp = a.getD();
   int temp2 = b.getD();
   //bool greater = false;
   //bool found = false;
   //checking greatness through left
   //if (temp != 0 && temp2 != 0 )
   std::cout << "here\t\t\t\n\n\n\n" << std::endl;
   for ( int i = temp-1, j = temp2 - 1; i > 0 && j > 0; i--, j--)
   {
      std::cout << a.getDigit(i) << " " << b.getDigit(j) << std::endl;
      if(a.getDigit(i) != b.getDigit(j))
      {
         return false;
      }
   }
   std::cout << "here\t\t\t\n\n\n\n" << std::endl;
   // check right
   for ( int i = temp, j = temp2; i < 8 && j < 8; i++, j++)
   {
      //std::cout << a.getDigit(i) << " " << b.getDigit(j) << std::endl;
      if(a.getDigit(i) != b.getDigit(j))
      {
         return false;
      }
   }
   std::cout << "here\t\t\t\n\n\n\n" << std::endl;
   return true;
   /*if(a.getD() == b.getD() && a.getE() == a.getE())
   {
      for (int i = 0; i < 8; i++)
      {
         if (a.getDigit(i) != b.getDigit(i))
            return false;
      }
      return true;
   }
   return false;*/
}

std::ostream& operator<<(std::ostream& os,const FLOAT& number)
{
   if (number.getS
() < 0 )
   {
      os << "- ";
   }
   else
   {
      os << "+ ";   
   }
   for(int i = 0; i < 8; i++)
   {
      if ( number.getD() != i )
      {
         os << number.getDigit(i);
      }
      else
      {
         os << '.' << number.getDigit(i);
      }
   }
   os << " x 10^" << number.getE() - number.getQ() << std::endl;
}

int FLOAT::getS() const
{
   return sign;
}

FLOAT shift(bool lorr, FLOAT A)
{
   int shiftstarter = 0;
   int temp;
   // if true shift right
   if( lorr)
   {
      for (int i = 0; i < 8; i++ )
      {
         
         temp = A.getDigit(i);
         A.setDigit(i,shiftstarter);
         shiftstarter = temp;
      }

   }
   //else shift left
   else
   {
      for (int i = 7; i >= 0; i-- )
      {
         temp = A.getDigit(i);
         A.setDigit(i,shiftstarter);
         shiftstarter = temp;
      }
   }
   //std::cout << std::endl << A << std::endl;
   return A;   
}

FLOAT operator+ (FLOAT a, FLOAT b)
{
   std::cout << "Original: " << a << " " << b << std::endl;
   a=normalize(a);
   b=normalize(b);
   FLOAT* highest = &a;
   FLOAT* lowest = &b;
   FLOAT c;
   if (a.getE() < b.getE())
   {
      FLOAT* temp = lowest;
     lowest = highest;
     highest = temp;
   }
   c.setE(highest->getE());
   if(highest->getE() - lowest->getE() >= 8+2)
   {  
      //std::cout << "spaghetti" << std::endl;
      assign(c,(*highest));
      return normalize(c);
   }
   //FLOAT temp;
   if (highest->getE() - lowest->getE() != 0)
   for(int i = 0; i < highest->getE() - lowest->getE(); i++)
   {
      auto temp = ((shift(true,(*lowest))));
      lowest = &temp;
   }
   //lowest = &temp;

   return normalize(assign(c,addFs((*highest),(*lowest))));
}

FLOAT addFs(FLOAT a, FLOAT b)
{
   FLOAT c;
   int nextsum = 0;
   if(a.getS() == -1 && compare(a,b))
   {
      c.setSign(-1);
   }
   else if ( b.getS() == -1 && compare(b,a))
   {
      c.setSign(-1);
   }
   else
      c.setSign(1);
   // add to right of decimal point
   for ( int i = 7, j = 7; a.getD() <= i || b.getD() <= j; i--, j--)
   {
      std::cout << a.getS() << " " << a.getDigit(i) << " " << b.getS() << " " << b.getDigit(i) << std::endl;
      int sum = (a.getS()*a.getDigit(i)+b.getS()*b.getDigit(i)+nextsum);
      nextsum = 0;
      // carry operation -- check other rows
      if ( abs(a.getDigit(i)) < abs(b.getDigit(i)))
      { 
         for (int k = i+1;0<k;k--)
         {
           if( a.getDigit(k)> 0)
           {
              //nextsum = 1*b.getS();
              a.setDigit(k,a.getDigit(k)-1);
           }
         }
         sum = sum + 10 *a.getS();
      }
      /*if ((a.getS() < 0 && b.getS() > 0)||(a.getS()>0 && b.getS() <0))
      {
      }*/
      else if (a.getS()==b.getS())
      {
         if(abs(sum) > 9)
         {
           nextsum = 1*a.getS();
           sum = sum % 10;
         }
      }

      c.setDigit(i,sum);
      if(c.getDigit(i) < 0)
      { 
         c.setDigit(i,c.getDigit(i)*-1);
      }
   }
   // add to left of decimal point
   return c;
   for(int i = 7; i >= 0; i--)
   {
      std::cout << a.getS() << " " << a.getDigit(i) << " " << b.getS() << " " << b.getDigit(i) << std::endl;
      int sum = (a.getS()*a.getDigit(i)+b.getS()*b.getDigit(i)+nextsum);
      nextsum = 0;
      // carry operation
      if ((a.getS() < 0 && b.getS() > 0)||(a.getS()>0 && b.getS() <0))
      {
         if ( abs(a.getDigit(i)) < abs(b.getDigit(i)))
         {
            nextsum = 1*b.getS();
            sum = sum + 10 *a.getS();
         }
      }
      else if (a.getS()==b.getS())
      {
         if(abs(sum) > 9)
         {
           nextsum = 1*a.getS();
           sum = sum % 10;
         }
      }

      c.setDigit(i,sum);
      if(c.getDigit(i) < 0)
      { 
         c.setDigit(i,c.getDigit(i)*-1);
      }
   }
   return c;
}

// assign b's f to a's f
FLOAT assign(FLOAT a, FLOAT b)
{
  a.setSign(b.getS());
  for (int i = 0; i < 8; i++)
  {
     a.setDigit(i,b.getDigit(i));
  }
  return a;
}

void FLOAT::setSign(int val)
{
   sign = val;
}
