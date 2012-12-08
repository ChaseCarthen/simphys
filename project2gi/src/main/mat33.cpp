#include "simphys/mat33.h"

simphys::mat33::mat33(float val1, float val2, float val3, float val4, float val5, float val6, float val7, float val8, float val9)
{
   std::vector<float> temp {val1,val2,val3};
   matrix.push_back(temp);
   std::vector<float> temp2 {val4,val5,val6};
   matrix.push_back(temp2);
   std::vector<float> temp3 {val7,val8,val9};
   matrix.push_back(temp3);
}

float const& simphys::mat33::operator() (int i, int j) const
{
   return matrix[i][j];
}

float& simphys::mat33::operator() (int i, int j)
{
   return matrix[i][j];
}


void simphys::mat33::transpose()
{
   std::vector<std::vector<float>> temp { {},{},{}};
   for(int i= 0; i < 3; i++ )
   {
      //temp[i][0].push_back(matrix[i][0]);
      for (int j = 0; j < 3; j++)
      {
         temp[j].push_back(matrix[i][j]);
      }
   }
   matrix.swap(temp);
}

simphys::mat33 simphys::operator* (const simphys::mat33& here, const simphys::mat33& other)
{
   simphys::mat33 temp {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
   for(int i = 0; i <3; i++)
   {
      for(int j = 0; j<3; j++)
      {
         for(int k = 0; k < 3; k++)
         {
            //float temp1 = here(i,j);
            //float temp2 = other(k,j);
            temp(i,j) += here(i,k)*other(k,j);
         }
      }
  }
  //simphys::mat33 temp2{temp[0][0],temp[0][1],temp[1][0],temp[1][1]}
  return temp;
}

simphys::vec3 simphys::operator*(const simphys::mat33& m, const simphys::vec3& v )
{
   simphys::vec3 temp;
   float val = 0.0f;
   for(int i = 0; i <3; i++)
   {
         val += m(i,0)*v.getX();
         val += m(i,1)*v.getY();
         val += m(i,2) *v.getZ();
         if(i == 0)
            temp.setX(val);
         else if (i==1)
            temp.setY(val);
         else
            temp.setZ(val);
         val = 0.0f;
   }
   return temp;

}

simphys::vec3 simphys::operator*(const simphys::vec3& v, const simphys::mat33& m )
{
   simphys::vec3 temp;
   float val = 0.0f;
   for(int i = 0; i <3; i++)
   {
         val += m(i,0)*v.getX();
         val += m(i,1)*v.getY();
         val += m(i,2)*v.getZ();
         if(i == 0)
            temp.setX(val);
         else
            temp.setY(val);
         val = 0.0f;
   }
   return temp;

}
float simphys::mat33::determinant()
{
   return matrix[0][0]*(matrix[1][1]*matrix[2][2] - matrix[1][2] * matrix[2][1])-matrix[0][1]*(matrix[1][0]*matrix[2][2] - matrix[1][2] * matrix[2][0])+matrix[0][2]*(matrix[1][0]*matrix[2][1] - matrix[1][1] * matrix[2][0]);
}
