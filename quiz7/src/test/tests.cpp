#include "gtest/gtest.h"
#include "mat22.h"
#include "quaternion.h"
#include <iostream>
using namespace simphys;

class quat1 : public ::testing::Test {
protected:
   Quaternion a, b, c, d, rotate, zero;
   quat1() : a{1.0f,2.0f,3.0f,4.0f}, b{1.0f,2.0f,3.0f,4.0f}, c{12,45,65,44}, d{55,33,22,33}, rotate{1.0f, 1.0f,1.0f,1.0f}, zero{0,0,0,0}
   {

   }
   
};

TEST_F(quat1,addMultiplyTest) {
  auto ab = a * b;
  EXPECT_FLOAT_EQ(-28, ab.getW());
  EXPECT_FLOAT_EQ(4,ab.getX());
  EXPECT_FLOAT_EQ(6,ab.getY());
  EXPECT_FLOAT_EQ(8,ab.getZ());
 
  auto ab2 = a + b;
  
  EXPECT_FLOAT_EQ(2, ab2.getW());
  EXPECT_FLOAT_EQ(4,ab2.getX());
  EXPECT_FLOAT_EQ(6,ab2.getY());
  EXPECT_FLOAT_EQ(8,ab2.getZ());
  
  auto a2 = 2*a;
  EXPECT_FLOAT_EQ(2,a2.getW());
  EXPECT_FLOAT_EQ(4,a2.getX());
  EXPECT_FLOAT_EQ(6,a2.getY());
  EXPECT_FLOAT_EQ(8,a2.getZ());
  
  auto cd = c*d;
  EXPECT_FLOAT_EQ(-3707, cd.getW());
  EXPECT_FLOAT_EQ(4048,cd.getX());
  EXPECT_FLOAT_EQ(3806,cd.getY());
  EXPECT_FLOAT_EQ(1661,cd.getZ());
}

TEST_F(quat1, rotationtest)
{
   auto gotten = rotate.getMatrix();
   EXPECT_FLOAT_EQ( 0, gotten(0,0));
   EXPECT_FLOAT_EQ( 0, gotten(0,1));
   EXPECT_FLOAT_EQ( 1, gotten(0,2));
   EXPECT_FLOAT_EQ( 1, gotten(1,0));
   EXPECT_FLOAT_EQ( 0, gotten(1,1));
   EXPECT_FLOAT_EQ( 0, gotten(1,2));
   EXPECT_FLOAT_EQ( 0, gotten(2,0));
   EXPECT_FLOAT_EQ( 1, gotten(2,1));
   EXPECT_FLOAT_EQ( 0, gotten(2,2)); 
}

TEST_F(quat1, excepttest)
{
   zero.normalize();
   EXPECT_FLOAT_EQ(0,zero.getW());
   EXPECT_FLOAT_EQ(0,zero.getX());
   EXPECT_FLOAT_EQ(0,zero.getY());
   EXPECT_FLOAT_EQ(0,zero.getZ());
   rotate.getMatrix();
   EXPECT_FLOAT_EQ(1.0f,rotate.getW());
   EXPECT_FLOAT_EQ(1.0f,rotate.getX());
   EXPECT_FLOAT_EQ(1.0f,rotate.getY());
   EXPECT_FLOAT_EQ(1.0f,rotate.getZ());
}
