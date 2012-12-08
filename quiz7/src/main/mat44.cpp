#include "mat44.h"

simphys::mat44::mat44(float val1, float val2, float val3, float val4, float val5, float val6, float val7, float val8, float val9, float val10, float val11, float val12, float val13, float val14, float val15, float val16)
{
   std::vector<float> temp {val1,val2,val3,val4};
   matrix.push_back(temp);
   std::vector<float> temp2 {val5,val6,val7,val8};
   matrix.push_back(temp2);
   std::vector<float> temp3 {val9,val10,val11,val12};
   matrix.push_back(temp3);
   std::vector<float> temp4 {val13,val14,val15,val16};
   matrix.push_back(temp4);
}

float const& simphys::mat44::operator() (int i, int j) const
{
   return matrix[i][j];
}

float& simphys::mat44::operator() (int i, int j)
{
   return matrix[i][j];
}


void simphys::mat44::transpose()
{
   std::vector<std::vector<float>> temp { {},{},{}, {}};
   for(int i= 0; i < 4; i++ )
   {
      //temp[i][0].push_back(matrix[i][0]);
      for (int j = 0; j < 4; j++)
      {
         temp[j].push_back(matrix[i][j]);
      }
   }
   matrix.swap(temp);
}

simphys::mat44 simphys::operator* (const simphys::mat44& here, const simphys::mat44& other)
{
   simphys::mat44 temp {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
   for(int i = 0; i <4; i++)
   {
      for(int j = 0; j<4; j++)
      {
         for(int k = 0; k < 4; k++)
         {
            //float temp1 = here(i,j);
            //float temp2 = other(k,j);
            temp(i,j) += here(i,k)*other(k,j);
         }
      }
  }
  //simphys::mat44 temp2{temp[0][0],temp[0][1],temp[1][0],temp[1][1]}
  return temp;
}

simphys::vec4 simphys::operator*(const simphys::mat44& m, const simphys::vec4& v )
{
   simphys::vec4 temp;
   float val = 0.0f;
   for(int i = 0; i <4; i++)
   {
         val += m(i,0)*v.getX();
         val += m(i,1)*v.getY();
         val += m(i,2) *v.getZ();
         val += m(i,3) * v.getW();
         if(i == 0)
            temp.setX(val);
         else if (i==1)
            temp.setY(val);
         else if (i==2)
            temp.setZ(val);
         else
            temp.setW(val);
         val = 0.0f;
   }
   return temp;

}

simphys::vec4 simphys::operator*(const simphys::vec4& v, const simphys::mat44& m )
{
   simphys::vec4 temp;
   float val = 0.0f;
   for(int i = 0; i <4; i++)
   {
         val += m(i,0)*v.getX();
         val += m(i,1)*v.getY();
         val += m(i,2) *v.getZ();
         val += m(i,3) * v.getW();
         if(i == 0)
            temp.setX(val);
         else if (i==1)
            temp.setY(val);
         else if (i==2)
            temp.setZ(val);
         else
            temp.setW(val);
         val = 0.0f;
   }
   return temp;

}
