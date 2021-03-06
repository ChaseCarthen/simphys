#include "gtest/gtest.h"
#include "mat22.h"
#include "mat33.h"
#include "mat44.h"
#include <iostream>
using namespace simphys;

class matTest2 : public ::testing::Test {
protected:
  mat22 a2;
  mat22 b2;
  vec2 v2;
  matTest2()
    : a2{1,2,3,4}
    , b2{1,2,3,4}, v2{1,1} { }
};

class matTest3 : public ::testing::Test {
protected:
  mat33 a3;
  mat33 b3;
  vec3 v3;
  matTest3()
    : a3{1,2,3,4,5,6,7,8,9}
    , b3{1,2,3,4,5,6,7,8,9}, v3{1,1,1} { }
};

class matTest4 : public ::testing::Test {
protected:
  mat44 a4;
  mat44 b4;
  vec4 v4;
  matTest4()
    : a4{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}
    , b4{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}, v4{1,1,1,1} { }
};
TEST_F(matTest2,elementtest) {
  a2(0,0)=1;
  EXPECT_EQ(1,a2(0,0));
  EXPECT_EQ(2,a2(0,1));
  EXPECT_EQ(3,a2(1,0));
  EXPECT_EQ(4,a2(1,1));
}
TEST_F(matTest2,transposetest) {
   a2.transpose();
   EXPECT_EQ(1,a2(0,0));
   EXPECT_EQ(3,a2(0,1));
   EXPECT_EQ(2,a2(1,0));
   EXPECT_EQ(4,a2(1,1));
}
TEST_F(matTest2,vectortest) {
  auto v = a2 * v2;
  EXPECT_EQ(3,v.getX());
  EXPECT_EQ(7,v.getY());
}

TEST_F (matTest2, determinanttest)
{
  EXPECT_EQ ( 1*4 - 2*3, a2.determinant());
}

TEST_F (matTest3, determinanttest)
{
  EXPECT_EQ(1*(5*9 - 6*8)-2*(4*9-6*7)+3*(4*8-5*7),a3.determinant());
}
TEST_F(matTest3,elementtest) {

  EXPECT_EQ(1,a3(0,0));
  EXPECT_EQ(2,a3(0,1));
  EXPECT_EQ(3,a3(0,2));
  EXPECT_EQ(4,a3(1,0));
  EXPECT_EQ(5,a3(1,1));
  EXPECT_EQ(6,a3(1,2));
  EXPECT_EQ(7,a3(2,0));
  EXPECT_EQ(8,a3(2,1));
  EXPECT_EQ(9,a3(2,2));
}
TEST_F(matTest3,transposetest) {
  a3.transpose();
  EXPECT_EQ(1,a3(0,0));
  EXPECT_EQ(4,a3(0,1));
  EXPECT_EQ(7,a3(0,2));
  EXPECT_EQ(2,a3(1,0));
  EXPECT_EQ(5,a3(1,1));
  EXPECT_EQ(8,a3(1,2));
  EXPECT_EQ(3,a3(2,0));
  EXPECT_EQ(6,a3(2,1));
  EXPECT_EQ(9,a3(2,2));
}
TEST_F(matTest3,vectortest) {
  auto v = a3 * v3;
  EXPECT_EQ(1*1+2*1+3*1,v.getX());
  EXPECT_EQ(4*1+5*1+6*1,v.getY());
  EXPECT_EQ(7*1+8*1+9*1,v.getZ());
}
TEST_F(matTest4,elementtest) 
{
  EXPECT_EQ(1,a4(0,0));
  EXPECT_EQ(2,a4(0,1));
  EXPECT_EQ(3,a4(0,2));
  EXPECT_EQ(4,a4(0,3));
  EXPECT_EQ(5,a4(1,0));
  EXPECT_EQ(6,a4(1,1));
  EXPECT_EQ(7,a4(1,2));
  EXPECT_EQ(8,a4(1,3));
  EXPECT_EQ(9,a4(2,0));
  EXPECT_EQ(10,a4(2,1));
  EXPECT_EQ(11,a4(2,2));
  EXPECT_EQ(12,a4(2,3));
  EXPECT_EQ(13,a4(3,0));
  EXPECT_EQ(14,a4(3,1));
  EXPECT_EQ(15,a4(3,2));
  EXPECT_EQ(16,a4(3,3));
}
TEST_F(matTest4,transposetest) {
  a4.transpose();
  EXPECT_EQ(1,a4(0,0));
  EXPECT_EQ(5,a4(0,1));
  EXPECT_EQ(9,a4(0,2));
  EXPECT_EQ(13,a4(0,3));
  EXPECT_EQ(2,a4(1,0));
  EXPECT_EQ(6,a4(1,1));
  EXPECT_EQ(10,a4(1,2));
  EXPECT_EQ(14,a4(1,3));
  EXPECT_EQ(3,a4(2,0));
  EXPECT_EQ(7,a4(2,1));
  EXPECT_EQ(11,a4(2,2));
  EXPECT_EQ(15,a4(2,3));
  EXPECT_EQ(4,a4(3,0));
  EXPECT_EQ(8,a4(3,1));
  EXPECT_EQ(12,a4(3,2));
  EXPECT_EQ(16,a4(3,3));
}
TEST_F(matTest4,vectortest) {
  auto v = a4 * v4;
  EXPECT_EQ(1*1+2*1+3*1+4*1,v.getX());
  EXPECT_EQ(5*1+6*1+7*1+8*1,v.getY());
  EXPECT_EQ(9*1+10*1+11*1+12*1,v.getZ());
  EXPECT_EQ(13*1+14*1+15*1+16*1,v.getW());
}
