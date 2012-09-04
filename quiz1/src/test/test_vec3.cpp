#include "vec3.h"
#include <cmath>
#include "gtest/gtest.h"

/*
  Note that even without proper implementations, this test will
  pass. Why is that? You should make the test pass because the code is
  correct, not because of trivial correctness conditions.
 */
TEST(Vec3Test, VectorAdditionCommutativity) {
  simphys::vec3 v1(1.0f, 2.0f, 3.0f);
  simphys::vec3 v2(4.0f, 5.0f, 6.0f);

  simphys::vec3 v3 = v1 + v2;
  simphys::vec3 v4 = v2 + v1;
  
  // EXPECT_FLOAT_EQ tests two floating-point numbers for equality and
  // is aware of numerical precision.
  EXPECT_FLOAT_EQ(v3.getX(), v4.getX());
  EXPECT_FLOAT_EQ(v3.getY(), v4.getY());
  EXPECT_FLOAT_EQ(v3.getZ(), v4.getZ());
}

/*
  TODO - put your tests here.
*/
TEST(Vec3Test, DotProdTest)
{
  simphys::vec3 v1(1.0f, 2.0f, 3.0f);
  simphys::vec3 v2(4.0f, 5.0f, 6.0f);

  float dot = v1.dotProduct(v2);
  float dot2 = v2.dotProduct(v1);
  
  // EXPECT_FLOAT_EQ tests two floating-point numbers for equality and
  // is aware of numerical precision.
  EXPECT_FLOAT_EQ(dot, dot2);

  simphys::vec3 v3(0.0f,0.0f,1.0f);
  simphys::vec3 v4(1.0f,0.0f,0.0f);
  float dot3 = v3.dotProduct(v4);
  //
  EXPECT_FLOAT_EQ(0.0f, dot3);
}

TEST(Vec3Test, CrossProdTest)
{
  simphys::vec3 v1(1.0f, 2.0f, 3.0f);
  simphys::vec3 v2(4.0f, 5.0f, 6.0f);

  simphys::vec3 v3 = v1.crossProduct(v2);
  simphys::vec3 v4 = v2.crossProduct(v1);
  
  // EXPECT_FLOAT_EQ tests two floating-point numbers for equality and
  // is aware of numerical precision.
  EXPECT_FLOAT_EQ(-v3.getX(), v4.getX());
  EXPECT_FLOAT_EQ(-v3.getY(), v4.getY());
  EXPECT_FLOAT_EQ(-v3.getZ(), v4.getZ());

  simphys::vec3 v5(0.0f,0.0f,1.0f);
  simphys::vec3 v6(1.0f,0.0f,0.0f);
  simphys::vec3 v7 = v5.crossProduct(v6);
  
  EXPECT_FLOAT_EQ(0.0f, v7.getX());
  EXPECT_FLOAT_EQ(1.0f, v7.getY());
  EXPECT_FLOAT_EQ(0.0f, v7.getZ());
}
TEST(Vec3Test, VectorScalarComm)
{
  simphys::vec3 v1(4.0f, 5.0f, 6.0f);

  simphys::vec3 v2 = 2*v1;
  simphys::vec3 v3 = v1*2;
  
  // EXPECT_FLOAT_EQ tests two floating-point numbers for equality and
  // is aware of numerical precision.
  EXPECT_FLOAT_EQ(v2.getX(), v3.getX());
  EXPECT_FLOAT_EQ(v2.getY(), v3.getY());
  EXPECT_FLOAT_EQ(v2.getZ(), v3.getZ());
}
TEST(Vec3Test, NormTest)
{
  simphys::vec3 v1(1.0f, 2.0f, 3.0f);
  simphys::vec3 v2(4.0f, 5.0f, 6.0f);
  simphys::vec3 v3(4.0f, 5.0f, 6.0f);

  // testing norm functions
  EXPECT_FLOAT_EQ(sqrt(14),v1.norm());
  EXPECT_EQ(14,v1.norm_sq());

  //testing normalized and normalize
  simphys::vec3 test = v3.normalized();
  v2.normalize();
  EXPECT_FLOAT_EQ(test.getX(), v2.getX());
  EXPECT_FLOAT_EQ(test.getY(), v2.getY());
  EXPECT_FLOAT_EQ(test.getZ(), v2.getZ());

}

TEST(Vec3Test, SetVecTest)
{
   simphys::vec3 v1(1.0f, 2.0f, 3.0f);
   v1.setX(2.1f);
   v1.setY(3.2f);
   v1.setZ(4.5f);
   EXPECT_FLOAT_EQ(2.1f, v1.getX());
   EXPECT_FLOAT_EQ(3.2f, v1.getY());
   EXPECT_FLOAT_EQ(4.5f, v1.getZ());
}
