#include <iostream>
#include <cmath>

#include "vec3.h"
#include "gtest/gtest.h"

using std::fabs;

/*
  A test fixture class. A fixture creates data that is reused across
  tests.

*/
class Vec3Test : public ::testing::Test {
protected:

  Vec3Test() 
    : origin{0.0f, 0.0f, 0.0f},
    i_vec{1.0f, 0.0f, 0.0f},
    j_vec{0.0f, 1.0f, 0.0f},
    k_vec{0.0f, 0.0f, 1.0f},
    u{14.57, 23.11, 63.6345},
    v{1043.5, 1300.0, 657.4}

  { }

  simphys::vec3 origin;
  simphys::vec3 i_vec;
  simphys::vec3 j_vec;
  simphys::vec3 k_vec;

  simphys::vec3 u;
  simphys::vec3 v;

  //simphys::vec3 small;
  //simphys::vec3 large;

};

/*
  Tests for vec3::norm
*/
// |av| = |a| * |v| for vector v and scalar a.
TEST_F(Vec3Test, NormIsPositiveHomogeneous) {
  auto a = 1.6f;
  auto b = 35.6f;
  auto c = -1.1f;
  auto d = -50.1f;
  
  auto av = a * v;
  auto bv = b * v;
  auto cv = c * v;
  auto dv = d * v;

  EXPECT_FLOAT_EQ(fabs(av.norm()), (fabs(a) * v.norm()));
  EXPECT_FLOAT_EQ(fabs(bv.norm()), (fabs(b) * v.norm()));
  EXPECT_FLOAT_EQ(fabs(cv.norm()), (fabs(c) * v.norm()));
  EXPECT_FLOAT_EQ(fabs(dv.norm()), (fabs(d) * v.norm()));
  
}

//|u + v| <= |u| + |v|
TEST_F(Vec3Test, NormIsSubadditive) {
  auto norm_u = u.norm();
  auto norm_v = v.norm();
  auto w = u + v;
  auto norm_w = w.norm();
  
  EXPECT_TRUE(norm_w <= norm_u + norm_v);

}

// |0| = 0
TEST_F(Vec3Test, ZeroHasNormZero) {
  EXPECT_FLOAT_EQ(0.0f, origin.norm());
}

// |v| > 0 if v != 0
TEST_F(Vec3Test, NonZeroHasPositiveNorm) {
  EXPECT_TRUE(v.norm() > 0.0f);
  EXPECT_TRUE(u.norm() > 0.0f);
}

/*
  Tests for vec3::norm_sq
*/
TEST_F(Vec3Test, NormSq) {
  EXPECT_FLOAT_EQ(1.0f, i_vec.norm_sq());
  EXPECT_FLOAT_EQ(1.0f, j_vec.norm_sq());
  EXPECT_FLOAT_EQ(1.0f, j_vec.norm_sq());

  float normsq = 14.57 * 14.57 + 
    23.11 * 23.11 + 63.6345 * 63.6345;
  EXPECT_FLOAT_EQ(normsq, u.norm_sq());

}

/*
  Tests for vec3::normalized
*/
TEST_F(Vec3Test, NormalizedGeneralValues) {
  auto unormed = u.normalized();
  auto vnormed = v.normalized();  
  
  EXPECT_FLOAT_EQ(1.0f, unormed.norm());
  EXPECT_FLOAT_EQ(1.0f, vnormed.norm());
}

TEST_F(Vec3Test, NormalizedIJKValues) {
  auto inormed = i_vec.normalized();
  auto jnormed = j_vec.normalized();
  auto knormed = k_vec.normalized();

  EXPECT_FLOAT_EQ(1.0f, inormed.norm());
  EXPECT_FLOAT_EQ(1.0f, jnormed.norm());
  EXPECT_FLOAT_EQ(1.0f, knormed.norm());
}

TEST_F(Vec3Test, NormalizedIJKUnchanged) {
  auto inormed = i_vec.normalized();
  auto jnormed = j_vec.normalized();
  auto knormed = k_vec.normalized();

  EXPECT_FLOAT_EQ(inormed.getX(), i_vec.getX());
  EXPECT_FLOAT_EQ(inormed.getY(), i_vec.getY());
  EXPECT_FLOAT_EQ(inormed.getZ(), i_vec.getZ());

  EXPECT_FLOAT_EQ(jnormed.getX(), j_vec.getX());
  EXPECT_FLOAT_EQ(jnormed.getY(), j_vec.getY());
  EXPECT_FLOAT_EQ(jnormed.getZ(), j_vec.getZ());

  EXPECT_FLOAT_EQ(knormed.getX(), k_vec.getX());
  EXPECT_FLOAT_EQ(knormed.getY(), k_vec.getY());
  EXPECT_FLOAT_EQ(knormed.getZ(), k_vec.getZ());
}

/*
  Tests for vec3::normalize
*/
TEST_F(Vec3Test, NormalizeModifiesStateCorrectly) {
  u.normalize();
  EXPECT_FLOAT_EQ(1.0f, u.norm());

  v.normalize();
  EXPECT_FLOAT_EQ(1.0f, v.norm());
}

TEST_F(Vec3Test, NormalizeIdempotent) {
  u.normalize();
  EXPECT_FLOAT_EQ(1.0f, u.norm());

  auto u_normalized = u;

  u.normalize();

  EXPECT_FLOAT_EQ(u_normalized.getX(), u.getX());
  EXPECT_FLOAT_EQ(u_normalized.getY(), u.getY());
  EXPECT_FLOAT_EQ(u_normalized.getZ(), u.getZ());
}

TEST_F(Vec3Test, NormalizePreservesDirection) {
  auto unorm = u.norm();
  auto old_u = u;

  u.normalize();

  EXPECT_FLOAT_EQ( (u*unorm).getX(), old_u.getX());
  EXPECT_FLOAT_EQ( (u*unorm).getY(), old_u.getY());
  EXPECT_FLOAT_EQ( (u*unorm).getZ(), old_u.getZ());
}

/*
  Tests for vec3::dotProduct
*/
TEST_F(Vec3Test, DotProductCommutative) {
  auto ij_dot = i_vec.dotProduct(j_vec);
  auto ji_dot = j_vec.dotProduct(i_vec);
  EXPECT_FLOAT_EQ(ij_dot, ji_dot);

  auto uv_dot = u.dotProduct(v);
  auto vu_dot = v.dotProduct(u);
  EXPECT_FLOAT_EQ(uv_dot, vu_dot); 
}

TEST_F(Vec3Test, DotProductDistributivity) {
  auto vec_sum = u + v;
  auto sum_dot = u.dotProduct(vec_sum);
  auto distributed = u.dotProduct(u) + u.dotProduct(v);
  EXPECT_FLOAT_EQ(sum_dot, distributed);
}

TEST_F(Vec3Test, SelfDotProductMatchesNormSq) {
  auto iidot = i_vec.dotProduct(i_vec);
  auto jjdot = j_vec.dotProduct(j_vec);
  auto kkdot = k_vec.dotProduct(k_vec);

  auto uudot = u.dotProduct(u);
  auto vvdot = v.dotProduct(v);

  EXPECT_FLOAT_EQ(i_vec.norm_sq(), iidot);
  EXPECT_FLOAT_EQ(j_vec.norm_sq(), jjdot);
  EXPECT_FLOAT_EQ(k_vec.norm_sq(), kkdot);

  EXPECT_FLOAT_EQ(u.norm_sq(), uudot);
  EXPECT_FLOAT_EQ(v.norm_sq(), vvdot);
}

/*
  Tests for vec3::crossProduct
*/
TEST_F(Vec3Test, CrossProductBases) {
  auto ij = i_vec.crossProduct(j_vec);
  EXPECT_FLOAT_EQ(ij.getX(), k_vec.getX());
  EXPECT_FLOAT_EQ(ij.getY(), k_vec.getY());
  EXPECT_FLOAT_EQ(ij.getZ(), k_vec.getZ());

  auto jk = j_vec.crossProduct(k_vec);
  EXPECT_FLOAT_EQ(jk.getX(), i_vec.getX());
  EXPECT_FLOAT_EQ(jk.getY(), i_vec.getY());
  EXPECT_FLOAT_EQ(jk.getZ(), i_vec.getZ());

  auto ki = k_vec.crossProduct(i_vec);
  EXPECT_FLOAT_EQ(ki.getX(), j_vec.getX());
  EXPECT_FLOAT_EQ(ki.getY(), j_vec.getY());
  EXPECT_FLOAT_EQ(ki.getZ(), j_vec.getZ());
}

TEST_F(Vec3Test, CrossProductZeroes) {
  auto zeroed = u.crossProduct(u);
  EXPECT_FLOAT_EQ(0.0f, zeroed.getX());
  EXPECT_FLOAT_EQ(0.0f, zeroed.getY());
  EXPECT_FLOAT_EQ(0.0f, zeroed.getZ());
}

TEST_F(Vec3Test, CrossProductAntiCommutative) {
  auto uv = u.crossProduct(v);
  auto vu = v.crossProduct(u);
  
  EXPECT_FLOAT_EQ(uv.getX(), -1.0 * vu.getX());
  EXPECT_FLOAT_EQ(uv.getY(), -1.0 * vu.getY());
  EXPECT_FLOAT_EQ(uv.getZ(), -1.0 * vu.getZ());
}

/*
  Tests for operator+
*/
TEST_F(Vec3Test, TestOperatorPlus) {
  auto ijk = i_vec + j_vec + k_vec;
  
  EXPECT_FLOAT_EQ(1.0f, ijk.getX());
  EXPECT_FLOAT_EQ(1.0f, ijk.getY());
  EXPECT_FLOAT_EQ(1.0f, ijk.getZ());
}

/*
  Tests for operator-
*/
TEST_F(Vec3Test, TestOperatorMinus) {
  auto ij = i_vec - j_vec;
  auto ji = j_vec - i_vec;
  
  EXPECT_FLOAT_EQ(1.0f, ij.getX());
  EXPECT_FLOAT_EQ(-1.0f, ij.getY());
  EXPECT_FLOAT_EQ(0.0f, ij.getZ());

  EXPECT_FLOAT_EQ(-1.0f, ji.getX());
  EXPECT_FLOAT_EQ(1.0f, ji.getY());
  EXPECT_FLOAT_EQ(0.0f, ji.getZ());
}

/*
  Tests for scalar mult
*/
TEST_F(Vec3Test, TestScalarMultCommutative) {
  auto u_five = u * 5.0f;
  auto five_u = 5.0f * u;
  EXPECT_FLOAT_EQ(u_five.getX(), five_u.getX());
  EXPECT_FLOAT_EQ(u_five.getY(), five_u.getY());
  EXPECT_FLOAT_EQ(u_five.getZ(), five_u.getZ());
}
