#include <errno.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>

#include "model/model.h"

// Arithmetic - ar

TEST(Calc, ArTest1) {
  std::string str = "14+10.3";
  s21::Model model(str);
  double rez = model.Calc();
  double calc = 14 + 10.3;
  ASSERT_EQ(rez, calc);
}

TEST(Calc, ArTest2) {
  std::string str = "100.0-50+10.3";
  s21::Model model(str);
  double rez = model.Calc();
  double calc = 100.0 - 50 + 10.3;
  ASSERT_EQ(std::round(rez * 10000000), std::round(calc * 10000000));
}

TEST(Calc, ArTest3) {
  std::string str = "100/90*5";
  s21::Model model(str);
  double rez = model.Calc();
  double calc = 5.55555555556;
  ASSERT_EQ(std::round(rez * 10000000), std::round(calc * 10000000));
}

TEST(Calc, ArTest4) {
  std::string str = "10*(2+3)";
  s21::Model model(str);
  double rez = model.Calc();
  double calc = 50;
  ASSERT_EQ(rez, calc);
}

TEST(Calc, ArTest5) {
  std::string str = "28+3*15-47/15*8+10.6";
  s21::Model model(str);
  double rez = model.Calc();
  double calc = 58.5333333333;
  ASSERT_EQ(std::round(rez * 10000000), std::round(calc * 10000000));
}

TEST(Calc, ModTest6) {
  std::string str = "8mod4";
  s21::Model model(str);
  double rez = model.Calc();
  double calc = 8 % 4;
  ASSERT_EQ(std::round(rez * 10000000), std::round(calc * 10000000));
}

TEST(Calc, ModTest7) {
  std::string str = "18mod14";
  s21::Model model(str);
  double rez = model.Calc();
  double calc = 18 % 14;
  ASSERT_EQ(std::round(rez * 10000000), std::round(calc * 10000000));
}

TEST(Calc, NumTest8) {
  std::string str = "10.12345";
  s21::Model model(str);
  double rez = model.Calc();
  double check = 10.12345;
  ASSERT_EQ(std::round(rez * 10000000), std::round(check * 10000000));
}

TEST(Calc, CosTest9) {
  std::string str = "cos1";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((cos(1)) * 10000000));
}

TEST(Calc, CosTest10) {
  std::string str = "cos0";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((cos(0)) * 10000000));
}

TEST(Calc, CosTest11) {
  std::string str = "cos(-1)";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((cos(-1)) * 10000000));
}

TEST(Calc, SinTest12) {
  std::string str = "sin1";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((sin(1)) * 10000000));
}

TEST(Calc, SinTest13) {
  std::string str = "sin0";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((sin(0)) * 10000000));
}

TEST(Calc, SinTest14) {
  std::string str = "sin(-1)";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((sin(-1)) * 10000000));
}

TEST(Calc, SinTest15) {
  std::string str = "sin50";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((sin(50)) * 10000000));
}

TEST(Calc, TanTest16) {
  std::string str = "tan1";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((tan(1)) * 10000000));
}

TEST(Calc, TanTest17) {
  std::string str = "tan0";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((tan(0)) * 10000000));
}

TEST(Calc, TanTest18) {
  std::string str = "tan(-1)";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((tan(-1)) * 10000000));
}

TEST(Calc, TanTest19) {
  std::string str = "tan(-45)";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((tan(-45)) * 10000000));
}

TEST(Calc, AtanTest20) {
  std::string str = "atan(0)";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((atan(0)) * 10000000));
}

TEST(Calc, AtanTest21) {
  std::string str = "atan(-45)";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((atan(-45)) * 10000000));
}

TEST(Calc, AtanTest22) {
  std::string str = "atan(1)";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((atan(1)) * 10000000));
}

TEST(Calc, AsinTest23) {
  std::string str = "asin(0)";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((asin(0)) * 10000000));
}

TEST(Calc, AsinTest24) {
  std::string str = "asin(1)";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((asin(1)) * 10000000));
}

TEST(Calc, AsinTest25) {
  std::string str = "asin(-1)";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(rez, (asin(-1)));
}

TEST(Calc, AsinTest26) {
  std::string str = "asin(-15)";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_TRUE(std::isnan(rez));
}

TEST(Calc, AcosTest27) {
  std::string str = "acos(-1)";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((acos(-1)) * 10000000));
}

TEST(Calc, AcosTest28) {
  std::string str = "acos(0)";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((acos(0)) * 10000000));
}

TEST(Calc, AcosTest29) {
  std::string str = "acos(1)";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((acos(1)) * 10000000));
}

TEST(Calc, AcosTest30) {
  std::string str = "acos(100)";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_TRUE(std::isnan(rez));
}

TEST(Calc, SqrtTest31) {
  std::string str = "sqrt4";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((sqrt(4)) * 10000000));
}

TEST(Calc, SqrtTest32) {
  std::string str = "sqrt0";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((sqrt(0)) * 10000000));
}

TEST(Calc, SqrtTest33) {
  std::string str = "sqrt(-1)";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_TRUE(std::isnan(rez));
}

TEST(Calc, LogTest34) {
  std::string str = "log4";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((log10(4)) * 10000000));
}

TEST(Calc, LogTest35) {
  std::string str = "log0";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((log10(0)) * 10000000));
}

TEST(Calc, LogTest36) {
  std::string str = "log0+log1";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000),
            std::round((log10(0) + log10(1)) * 10000000));
}

TEST(Calc, LnTest37) {
  std::string str = "ln4";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((log(4)) * 10000000));
}

TEST(Calc, LnTest38) {
  std::string str = "ln0";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round((log(0)) * 10000000));
}

TEST(Calc, PowTest39) {
  std::string str = "4^2";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(std::round(rez * 10000000), std::round(pow(4, 2)) * 10000000);
}

TEST(Calc, PowTest40) {
  std::string str = "9^0.2";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(rez, pow(9, 0.2));
}

TEST(Calc, Test41) {
  std::string str = "9^0.2*cos(1)";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(rez, pow(9, 0.2) * cos(1));
}

TEST(Calc, Test42) {
  std::string str = "ln(0)^(0.2*cos(1))";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(rez, pow((log(0)), 0.2 * cos(1)));
}

TEST(Calc, Test43) {
  std::string str = "acos(1)^(1.2*sin(11))*10";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(rez, pow((acos(1)), 1.2 * sin(11)) * 10);
}

TEST(Calc, Test44) {
  std::string str = "cos(10)+(1.2*sin(11))";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(rez, (cos(10)) + (1.2 * sin(11)));
}

TEST(Calc, Test45) {
  std::string str = "sin(10)+(1.2*cos(11))+acos(1)^(1.2*sin(11))";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(rez, (sin(10)) + (1.2 * cos(11)) + pow((acos(1)), 1.2 * sin(11)));
}

TEST(Calc, Test46) {
  std::string str = "tan(3)*(3.2*atan(1))^(1.2*sin(11))";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(rez, (tan(3)) * pow((3.2 * atan(1)), 1.2 * sin(11)));
}

TEST(Calc, Test47) {
  std::string str = "tan(3)/(3*atan(1))^(12*sin(1))";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(rez, (tan(3)) / pow((3 * atan(1)), 12 * sin(1)));
}

TEST(Calc, Test48) {
  std::string str = "log((3*atan(1))^(12*sin(1)/12))";
  s21::Model model(str);
  double rez = model.Calc();
  ASSERT_EQ(rez, log10(pow((3 * atan(1)), 12 * sin(1) / 12)));
}

// throw
TEST(Calc, Test49) {
  std::string longString(256, 'x');
  EXPECT_THROW(s21::Model model(longString), std::overflow_error);
}

TEST(Calc, Test50) {
  std::string str = "lo";
  s21::Model model(str);
  ASSERT_THROW(model.Calc(), std::invalid_argument);
}

TEST(Calc, Test51) {
  std::string str = "at";
  s21::Model model(str);
  ASSERT_THROW(model.Calc(), std::invalid_argument);
}

TEST(Calc, Test52) {
  std::string str = "si";
  s21::Model model(str);
  ASSERT_THROW(model.Calc(), std::invalid_argument);
}

TEST(Calc, Test53) {
  std::string str = "cs";
  s21::Model model(str);
  ASSERT_THROW(model.Calc(), std::invalid_argument);
}

TEST(Calc, Test54) {
  std::string str = "mo";
  s21::Model model(str);
  ASSERT_THROW(model.Calc(), std::invalid_argument);
}

TEST(Calc, Test55) {
  std::string str = "6/0";
  s21::Model model(str);
  ASSERT_THROW(model.Calc(), std::logic_error);
}

TEST(Calc, Test56) {
  std::string str = "6mod0";
  s21::Model model(str);
  ASSERT_THROW(model.Calc(), std::logic_error);
}

TEST(Calc, Test57) {
  std::string str = "cos7arc6";
  s21::Model model(str);
  ASSERT_THROW(model.Calc(), std::invalid_argument);
}

TEST(Calc, Test58) {
  std::string str = "a+b";
  std::istringstream iss(str);
  s21::Model model(iss.str());
  ASSERT_THROW(model.Calc(), std::invalid_argument);
}

// bonus

TEST(ModelTest, Test59) {
  s21::Model model;
  std::vector<double> expected = {831.20, 1000, 10958.9, 958.879};
  std::vector<double> result = model.CreditCalc(10000, 12, 20, false);
  ASSERT_NEAR(expected[0], result[0], 1);
  ASSERT_NEAR(expected[1], result[1], 1);
  ASSERT_NEAR(expected[2], result[2], 1);
}

TEST(DepositCalcTest, Test60) {
  s21::Model model_;
  std::vector<double> result =
      model_.DepositCalc(true, 12, 10000, 10, 20, 0, 0, 0, 0);
  ASSERT_NEAR(829.995, result[0], 1);
  ASSERT_NEAR(11659.990, result[1], 1);
  ASSERT_NEAR(207.498, result[2], 1);
}

TEST(DepositCalcTest, Test61) {
  s21::Model model_;
  std::vector<double> result =
      model_.DepositCalc(false, 12, 10000, 10, 20, 0, 0, 0, 0);
  ASSERT_NEAR(800, result[0], 1);
  ASSERT_NEAR(10800, result[1], 1);
  ASSERT_NEAR(200, result[2], 1);
}

TEST(DepositCalcTest, Test62) {
  s21::Model model_;
  std::vector<double> result =
      model_.DepositCalc(true, 12, 10000, 10, 20, 5, 500, 0, 0);
  ASSERT_NEAR(850.33, result[0], 1);
  ASSERT_NEAR(12200.66, result[1], 1);
  ASSERT_NEAR(212.58, result[2], 1);
}

TEST(DepositCalcTest, Test63) {
  s21::Model model_;
  std::vector<double> result =
      model_.DepositCalc(true, 12, 10000, 10, 20, 0, 0, 5, 500);
  ASSERT_NEAR(809.65, result[0], 1);
  ASSERT_NEAR(11119.31, result[1], 1);
  ASSERT_NEAR(202.41, result[2], 1);
}

TEST(DepositCalcTest, Test64) {
  s21::Model model_;
  std::vector<double> result =
      model_.DepositCalc(true, 12, 10000, 10, 20, 5, 500, 5, 500);
  ASSERT_NEAR(829.99, result[0], 1);
  ASSERT_NEAR(11659.99, result[1], 1);
  ASSERT_NEAR(207.49, result[2], 1);
}

TEST(DepositCalcTest, Test65) {
  s21::Model model_;
  std::vector<double> result =
      model_.DepositCalc(false, 12, 10000, 10, 20, 5, 500, 5, 500);
  ASSERT_NEAR(800.00, result[0], 1);
  ASSERT_NEAR(10800, result[1], 1);
  ASSERT_NEAR(200.00, result[2], 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
