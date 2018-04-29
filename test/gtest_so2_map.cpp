#include <gtest/gtest.h>

#include "manif/SO2.h"

using namespace manif;

TEST(TEST_SO2, TEST_SO2_MAP)
{
  double data[2] = {1,0};

  Eigen::Map<SO2d> so2(data);

  EXPECT_DOUBLE_EQ(0, so2.angle());
}

TEST(TEST_SO2, TEST_SO2_MAP_CONST)
{
  double data[2] = {1,0};

  Eigen::Map<const SO2d> so2(data);

  EXPECT_DOUBLE_EQ(0, so2.angle());
}

TEST(TEST_SO2, TEST_SO2_MAP_DATA)
{
  /// @todo without specifying const
  /// it calls non-const data()

  double data[2] = {1,0};

  const Eigen::Map</*const*/ SO2d> so2(data);

  EXPECT_NE(nullptr, so2.data());
  EXPECT_EQ(data, so2.data()->data());

  EXPECT_DOUBLE_EQ(1, (*so2.data())(0));
  EXPECT_DOUBLE_EQ(0, (*so2.data())(1));
}

TEST(TEST_SO2, TEST_SO2_MAP_ASSIGN_OP)
{
  double dataa[2] = {1,0};
  Eigen::Map<SO2d> so2a(dataa);

  double datab[2] = {0,1};
  const Eigen::Map<const SO2d> so2b(datab);

  so2a = so2b;

  EXPECT_DOUBLE_EQ(0, so2a.real());
  EXPECT_DOUBLE_EQ(1, so2a.imag());

  so2a = SO2d(0.5,0.5);

  EXPECT_DOUBLE_EQ(0.5, so2a.real());
  EXPECT_DOUBLE_EQ(0.5, so2a.imag());
}

TEST(TEST_SO2, TEST_SO2_MAP_IDENTITY)
{
  double data[2] = {0,0};
  Eigen::Map<SO2d> so2(data);

  so2.identity();

  EXPECT_DOUBLE_EQ(0, so2.angle());
  EXPECT_DOUBLE_EQ(1, so2.real());
  EXPECT_DOUBLE_EQ(0, so2.imag());
}

TEST(TEST_SO2, TEST_SO2_MAP_IDENTITY2)
{
  double data[2] = {0,0};
  Eigen::Map<SO2d> so2(data);
  so2 = SO2d::Identity();

  EXPECT_DOUBLE_EQ(0, so2.angle());
  EXPECT_DOUBLE_EQ(1, so2.real());
  EXPECT_DOUBLE_EQ(0, so2.imag());
}

TEST(TEST_SO2, TEST_SO2_MAP_RANDOM)
{
  double data[2] = {0,0};
  Eigen::Map<SO2d> so2(data);

  so2.random();

  const auto& so2_ref = so2;

  EXPECT_DOUBLE_EQ(1, so2_ref.data()->norm());
}

TEST(TEST_SO2, TEST_SO2_MAP_RANDOM2)
{
  double data[2] = {0,0};
  Eigen::Map<SO2d> so2(data);
  so2 = SO2d::Random();

  const auto& so2_ref = so2;

  EXPECT_DOUBLE_EQ(1, so2_ref.data()->norm());
}

TEST(TEST_SO2, TEST_SO2_MAP_MATRIX)
{
  double data[2] = {1,0};
  Eigen::Map<SO2d> so2(data);

  SO2d::Transformation t = so2.transform();

  EXPECT_EQ(3, t.rows());
  EXPECT_EQ(3, t.cols());

  /// @todo Eigen matrix comparison
}


TEST(TEST_SO2, TEST_SO2_MAP_ROTATION)
{
  double data[2] = {1,0};
  Eigen::Map<SO2d> so2(data);

  SO2d::Rotation r = so2.rotation();

  EXPECT_EQ(2, r.rows());
  EXPECT_EQ(2, r.cols());

  /// @todo Eigen matrix comparison
}

TEST(TEST_SO2, TEST_SO2_MAP_INVERSE)
{
  double data[2] = {1,0};
  Eigen::Map<SO2d> so2(data);

  auto so2_inv = so2.inverse();

  EXPECT_DOUBLE_EQ(so2.angle(), so2_inv.angle());
  EXPECT_DOUBLE_EQ(1, so2_inv.real());
  EXPECT_DOUBLE_EQ(0, so2_inv.imag());

  so2.angle(M_PI);
  so2_inv = so2.inverse();

  EXPECT_DOUBLE_EQ(-M_PI, so2_inv.angle());

  double data_inv[2] = {1,0};
  Eigen::Map<SO2d> so2_inv_map(data_inv);

  so2.identity();
  so2_inv_map = so2.inverse();

  EXPECT_DOUBLE_EQ(so2.angle(), so2_inv_map.angle());
  EXPECT_DOUBLE_EQ(1, so2_inv_map.real());
  EXPECT_DOUBLE_EQ(0, so2_inv_map.imag());

  so2.angle(M_PI);
  so2_inv_map = so2.inverse();

  EXPECT_DOUBLE_EQ(-M_PI, so2_inv_map.angle());
}

TEST(TEST_SO2, TEST_SO2_MAP_RPLUS)
{
  double dataa[2] = {1,0};
  Eigen::Map<SO2d> so2a(dataa);
  so2a = SO2d(M_PI_2);

  SO2Tangentd so2b(M_PI_2);

  double datac[2] = {1,0};
  Eigen::Map<SO2d> so2c(datac);
  so2c = so2a.rplus(so2b);

  EXPECT_DOUBLE_EQ(M_PI, so2c.angle());
}

TEST(TEST_SO2, TEST_SO2_MAP_LPLUS)
{
  double dataa[2] = {1,0};
  Eigen::Map<SO2d> so2a(dataa);
  so2a = SO2d(M_PI_2);

  SO2Tangentd so2b(M_PI_2);

  double datac[2] = {1,0};
  Eigen::Map<SO2d> so2c(datac);

  so2c = so2a.lplus(so2b);

  EXPECT_DOUBLE_EQ(M_PI, so2c.angle());
}

TEST(TEST_SO2, TEST_SO2_MAP_PLUS)
{
  double dataa[2] = {1,0};
  Eigen::Map<SO2d> so2a(dataa);
  so2a = SO2d(M_PI_2);

  SO2Tangentd so2b(M_PI_2);

  auto so2c = so2a.plus(so2b);

  EXPECT_DOUBLE_EQ(M_PI, so2c.angle());
}

TEST(TEST_SO2, TEST_SO2_MAP_OP_PLUS)
{
  double dataa[2] = {1,0};
  Eigen::Map<SO2d> so2a(dataa);
  so2a = SO2d(M_PI_2);

  SO2Tangentd so2b(M_PI_2);

  auto so2c = so2a + so2b;

  EXPECT_DOUBLE_EQ(M_PI, so2c.angle());
}

TEST(TEST_SO2, TEST_SO2_MAP_OP_PLUS_EQ)
{
  double dataa[2] = {1,0};
  Eigen::Map<SO2d> so2a(dataa);
  so2a = SO2d(M_PI_2);

  SO2Tangentd so2b(M_PI_2);

  so2a += so2b;

  EXPECT_DOUBLE_EQ(M_PI, so2a.angle());
}

TEST(TEST_SO2, TEST_SO2_MAP_RMINUS)
{
  double dataa[2] = {1,0};
  Eigen::Map<SO2d> so2a(dataa);
  so2a = SO2d(M_PI);

  double datab[2] = {1,0};
  Eigen::Map<SO2d> so2b(datab);
  so2b = SO2d(M_PI_2);

  auto so2c = so2a.rminus(so2b);

  EXPECT_DOUBLE_EQ(M_PI_2, so2c.angle());
}

TEST(TEST_SO2, TEST_SO2_MAP_LMINUS)
{
  double dataa[2] = {1,0};
  Eigen::Map<SO2d> so2a(dataa);
  so2a = SO2d(M_PI);

  double datab[2] = {1,0};
  Eigen::Map<SO2d> so2b(datab);
  so2b = SO2d(M_PI_2);

  auto so2c = so2a.lminus(so2b);

  EXPECT_DOUBLE_EQ(-M_PI_2, so2c.angle());
}

TEST(TEST_SO2, TEST_SO2_MAP_MINUS)
{
  double dataa[2] = {1,0};
  Eigen::Map<SO2d> so2a(dataa);
  so2a = SO2d(M_PI);

  double datab[2] = {1,0};
  Eigen::Map<SO2d> so2b(datab);
  so2b = SO2d(M_PI_2);

  auto so2c = so2a.minus(so2b);

  EXPECT_DOUBLE_EQ(M_PI_2, so2c.angle());
}

TEST(TEST_SO2, TEST_SO2_MAP_LIFT)
{
  double data[2] = {1,0};
  Eigen::Map<SO2d> so2(data);
  so2 = SO2d(M_PI);

  auto so2_lift = so2.lift();

  static_assert(std::is_same<SO2d::Tangent, decltype(so2_lift)>::value, "");

  EXPECT_DOUBLE_EQ(M_PI, so2_lift.angle());
}

TEST(TEST_SO2, TEST_SO2_MAP_COMPOSE)
{
  double dataa[2] = {1,0};
  Eigen::Map<SO2d> so2a(dataa);
  so2a = SO2d(M_PI_2);

  double datab[2] = {1,0};
  Eigen::Map<SO2d> so2b(datab);
  so2b = SO2d(M_PI_2);

  double datac[2] = {1,0};
  Eigen::Map<SO2d> so2c(datac);

  so2c = so2a.compose(so2b);

  EXPECT_DOUBLE_EQ(M_PI, so2c.angle());

  SO2d so2d(M_PI_2);

  auto so2e = so2a.compose(so2d);

  EXPECT_DOUBLE_EQ(M_PI, so2e.angle());

  SO2d so2f(M_PI_2);

  auto so2g = so2f.compose(so2a);

  EXPECT_DOUBLE_EQ(M_PI, so2g.angle());
}

TEST(TEST_SO2, TEST_SO2_MAP_OP_COMPOSE)
{
  double dataa[2] = {1,0};
  Eigen::Map<SO2d> so2a(dataa);
  so2a = SO2d(M_PI_2);

  double datab[2] = {1,0};
  Eigen::Map<SO2d> so2b(datab);
  so2b = SO2d(M_PI_2);

  double datac[2] = {1,0};
  Eigen::Map<SO2d> so2c(datac);

  so2c = so2a * so2b;

  EXPECT_DOUBLE_EQ(M_PI, so2c.angle());

  SO2d so2d(M_PI_2);

  auto so2e = so2a * so2d;

  EXPECT_DOUBLE_EQ(M_PI, so2e.angle());

  SO2d so2f(M_PI_2);

  auto so2g = so2f * so2a;

  EXPECT_DOUBLE_EQ(M_PI, so2g.angle());
}

TEST(TEST_SO2, TEST_SO2_MAP_OP_COMPOSE_EQ)
{
  double dataa[2] = {1,0};
  Eigen::Map<SO2d> so2a(dataa);
  so2a = SO2d(M_PI_2);

  double datab[2] = {1,0};
  Eigen::Map<SO2d> so2b(datab);
  so2b = SO2d(M_PI_2);

  so2a *= so2b;

  EXPECT_DOUBLE_EQ(M_PI, so2a.angle());

  SO2d so2d(M_PI_2);

  so2a *= so2d;

  EXPECT_DOUBLE_EQ(-M_PI_2, so2a.angle());

  SO2d so2f(M_PI_2);

  so2f *= so2a;

  /// Expected : 0 Actual : -2.4492935982947064e-16
//  EXPECT_DOUBLE_EQ(0., so2f.angle());
  EXPECT_NEAR(0., so2f.angle(), 1e-15);
}

TEST(TEST_SO2, TEST_SO2_MAP_BETWEEN)
{
  double dataa[2] = {1,0};
  Eigen::Map<SO2d> so2a(dataa);
  so2a = SO2d(M_PI);

  double datab[2] = {1,0};
  Eigen::Map<SO2d> so2b(datab);
  so2b = SO2d(M_PI_2);

  auto so2c = so2a.between(so2b);

  EXPECT_DOUBLE_EQ(-M_PI_2, so2c.angle());

  SO2d so2d(M_PI_2);

  auto so2e = so2a.between(so2d);

  EXPECT_DOUBLE_EQ(-M_PI_2, so2e.angle());

  SO2d so2f(M_PI_2);

  auto so2g = so2f.between(so2a);

  EXPECT_DOUBLE_EQ(M_PI_2, so2g.angle());
}

/// with Jacs
/*
TEST(TEST_SO2, TEST_SO2_MAP_INVERSE_JAC)
{
  SO2d so2 = SO2d::Identity();

  SO2d so2_inv;
  SO2d::Jacobian J_inv;
  so2.inverse(so2_inv, J_inv);

  EXPECT_DOUBLE_EQ(so2.angle(), so2_inv.angle());
  EXPECT_DOUBLE_EQ(1, so2_inv.real());
  EXPECT_DOUBLE_EQ(0, so2_inv.imag());

  EXPECT_EQ(1, J_inv.rows());
  EXPECT_EQ(1, J_inv.cols());
  EXPECT_DOUBLE_EQ(-1, J_inv(0));

  so2.angle(M_PI);
  so2.inverse(so2_inv, J_inv);

  EXPECT_DOUBLE_EQ(-M_PI, so2_inv.angle());

  EXPECT_EQ(1, J_inv.rows());
  EXPECT_EQ(1, J_inv.cols());
  EXPECT_DOUBLE_EQ(-1, J_inv(0));
}

TEST(TEST_SO2, TEST_SO2_MAP_LIFT_JAC)
{
  SO2d so2(M_PI);

  SO2d::Tangent so2_lift;
  SO2d::Tangent::Jacobian J_lift;

  so2.lift(so2_lift, J_lift);

  EXPECT_DOUBLE_EQ(M_PI, so2_lift.angle());

  /// @todo check this J
  EXPECT_EQ(1, J_lift.rows());
  EXPECT_EQ(1, J_lift.cols());
  EXPECT_DOUBLE_EQ(1, J_lift(0));
}

TEST(TEST_SO2, TEST_SO2_MAP_COMPOSE_JAC)
{
  SO2d so2a(M_PI_2);
  SO2d so2b(M_PI_2);

  SO2d so2c;
  SO2d::Jacobian J_c_a, J_c_b;

  so2a.compose(so2b, so2c, J_c_a, J_c_b);

  EXPECT_DOUBLE_EQ(M_PI, so2c.angle());

  EXPECT_EQ(1, J_c_a.rows());
  EXPECT_EQ(1, J_c_a.cols());
  EXPECT_DOUBLE_EQ(1, J_c_a(0));

  EXPECT_EQ(1, J_c_b.rows());
  EXPECT_EQ(1, J_c_b.cols());
  EXPECT_DOUBLE_EQ(1, J_c_b(0));
}

TEST(TEST_SO2, TEST_SO2_MAP_RPLUS_JAC)
{
  SO2d so2a(M_PI_2);
  SO2Tangentd so2b(M_PI_2);

  SO2d so2c;
  SO2d::Jacobian J_rplus_m;
  SO2d::Jacobian J_rplus_t;

  so2a.rplus(so2b, so2c, J_rplus_m, J_rplus_t);

  EXPECT_DOUBLE_EQ(M_PI, so2c.angle());

  EXPECT_EQ(1, J_rplus_m.rows());
  EXPECT_EQ(1, J_rplus_m.cols());
  EXPECT_DOUBLE_EQ(1, J_rplus_m(0));

  EXPECT_EQ(1, J_rplus_t.rows());
  EXPECT_EQ(1, J_rplus_t.cols());
  EXPECT_DOUBLE_EQ(1, J_rplus_t(0));
}

TEST(TEST_SO2, TEST_SO2_MAP_LPLUS_JAC)
{
  SO2d so2a(M_PI_2);
  SO2Tangentd so2b(M_PI_2);

  SO2d so2c;
  SO2d::Jacobian J_lplus_t;
  SO2d::Jacobian J_lplus_m;

  so2a.lplus(so2b, so2c, J_lplus_t, J_lplus_m);

  EXPECT_DOUBLE_EQ(M_PI, so2c.angle());

  EXPECT_EQ(1, J_lplus_t.rows());
  EXPECT_EQ(1, J_lplus_t.cols());
  EXPECT_DOUBLE_EQ(1, J_lplus_t(0));

  EXPECT_EQ(1, J_lplus_m.rows());
  EXPECT_EQ(1, J_lplus_m.cols());
  EXPECT_DOUBLE_EQ(1, J_lplus_m(0));
}

TEST(TEST_SO2, TEST_SO2_MAP_PLUS_JAC)
{
  SO2d so2a(M_PI_2);
  SO2Tangentd so2b(M_PI_2);

  SO2d so2c;
  SO2d::Jacobian J_plus_m;
  SO2d::Jacobian J_plus_t;

  so2a.plus(so2b, so2c, J_plus_m, J_plus_t);

  EXPECT_DOUBLE_EQ(M_PI, so2c.angle());

  EXPECT_EQ(1, J_plus_m.rows());
  EXPECT_EQ(1, J_plus_m.cols());
  EXPECT_DOUBLE_EQ(1, J_plus_m(0));

  EXPECT_EQ(1, J_plus_t.rows());
  EXPECT_EQ(1, J_plus_t.cols());
  EXPECT_DOUBLE_EQ(1, J_plus_t(0));
}

TEST(TEST_SO2, TEST_SO2_MAP_RMINUS_JAC)
{
  SO2d so2a(M_PI);
  SO2d so2b(M_PI_2);

  SO2Tangentd so2c;

  SO2d::Jacobian J_rminus_a, J_rminus_b;

  so2a.rminus(so2b, so2c, J_rminus_a, J_rminus_b);

  EXPECT_DOUBLE_EQ(M_PI_2, so2c.angle());

  EXPECT_EQ(1, J_rminus_a.rows());
  EXPECT_EQ(1, J_rminus_a.cols());
  EXPECT_DOUBLE_EQ(1, J_rminus_a(0));

  EXPECT_EQ(1, J_rminus_b.rows());
  EXPECT_EQ(1, J_rminus_b.cols());
  EXPECT_DOUBLE_EQ(-1, J_rminus_b(0));
}

TEST(TEST_SO2, TEST_SO2_MAP_LMINUS_JAC)
{
  SO2d so2a(M_PI);
  SO2d so2b(M_PI_2);

  SO2Tangentd so2c;

  SO2d::Jacobian J_lminus_a, J_lminus_b;

  so2a.lminus(so2b, so2c, J_lminus_a, J_lminus_b);

  EXPECT_DOUBLE_EQ(-M_PI_2, so2c.angle());

  EXPECT_EQ(1, J_lminus_a.rows());
  EXPECT_EQ(1, J_lminus_a.cols());
  EXPECT_DOUBLE_EQ(-1, J_lminus_a(0));

  EXPECT_EQ(1, J_lminus_b.rows());
  EXPECT_EQ(1, J_lminus_b.cols());
  EXPECT_DOUBLE_EQ(1, J_lminus_b(0));
}

TEST(TEST_SO2, TEST_SO2_MAP_MINUS_JAC)
{
  SO2d so2a(M_PI);
  SO2d so2b(M_PI_2);

  SO2Tangentd so2c;

  SO2d::Jacobian J_minus_a, J_minus_b;

  so2a.minus(so2b, so2c, J_minus_a, J_minus_b);

  EXPECT_DOUBLE_EQ(M_PI_2, so2c.angle());

  EXPECT_EQ(1, J_minus_a.rows());
  EXPECT_EQ(1, J_minus_a.cols());
  EXPECT_DOUBLE_EQ(1, J_minus_a(0));

  EXPECT_EQ(1, J_minus_b.rows());
  EXPECT_EQ(1, J_minus_b.cols());
  EXPECT_DOUBLE_EQ(-1, J_minus_b(0));
}
*/
int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
