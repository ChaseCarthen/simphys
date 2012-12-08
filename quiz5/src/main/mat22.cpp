#include "mat22.h"

simphys::mat22::mat22(float val1, float val2, float val3, float val4)
{
   std::vector<float> temp {val1,val2};
   matrix.push_back(temp);
   std::vector<float> temp2 {val3,val4};
   matrix.push_back(temp2);
}

float const& simphys::mat22::operator() (int i, int j) const
{
   return matrix[i][j];
}

float& simphys::mat22::operator() (int i, int j)
{
   return matrix[i][j];
}


void simphys::mat22::transpose()
{
   std::vector<std::vector<float>> temp { {},{} };
   for(int i= 0; i < 2; i++ )
   {
      //temp[i][0].push_back(matrix[i][0]);
      for (int j = 0; j < 2; j++)
      {
         temp[j].push_back(matrix[i][j]);
      }
   }
   matrix.swap(temp);
}

simphys::mat22 simphys::operator* (const simphys::mat22& here, const simphys::mat22& other)
{
   simphys::mat22 temp {0.0f,0.0f,0.0f,0.0f};
   for(int i = 0; i <2; i++)
   {
      for(int j = 0; j<2; j++)
      {
         for(int k = 0; k < 2; k++)
         {
            //float temp1 = here(i,j);
            //float temp2 = other(k,j);
            temp(i,j) += here(i,k)*other(k,j);
         }
      }
  }
  //simphys::mat22 temp2{temp[0][0],temp[0][1],temp[1][0],temp[1][1]}
  return temp;
}

simphys::vec2 simphys::operator*(const simphys::mat22& m, const simphys::vec2& v )
{
   simphys::vec2 temp;
   float val = 0.0f;
   for(int i = 0; i <2; i++)
   {
         val += m(i,0)*v.getX();
         val += m(i,1)*v.getY();
         if(i == 0)
            temp.setX(val);
         else
            temp.setY(val);
         val = 0.0f;
   }
   return temp;

}

simphys::vec2 simphys::operator*(const simphys::vec2& v, const simphys::mat22& m )
{
   simphys::vec2 temp;
   float val = 0.0f;
   for(int i = 0; i <2; i++)
   {
         val += m(i,0)*v.getX();
         val += m(i,1)*v.getY();
         if(i == 0)
            temp.setX(val);
         else
            temp.setY(val);
         val = 0.0f;
   }
   return temp;

}
float simphys::mat22::determinant()
{
   return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
}
