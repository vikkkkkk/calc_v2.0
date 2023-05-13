#ifndef SRC_MODEL_MODEL_H
#define SRC_MODEL_MODEL_H

#include <cctype>
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace s21 {
class Model {

 private:
  enum type_t : char {
    NUMBER,
    END,
    PLUS = '+',
    MINUS = '-',
    MULT = '*',
    DIV = '/',
    MOD = 'm',
    POW = '^',
    SIN = 's',
    COS = 'c',
    TAN = 't',
    ATAN = 'n',
    ASIN = 'i',
    ACOS = 'o',
    SQRT = 'q',
    LOG = 'g',
    LN = 'l',
    ROUNDBRACKET_L = '(',
    ROUNDBRACKET_R = ')'
  };

 public:
  Model() : pStream(nullptr), pStreamLine("") {}
  explicit Model(std::string initLine);
  ~Model();
  double Calc();

 private:
  std::istream* pStream;
  std::string pStreamLine;
  type_t current;
  double mNumberValue;
  void GetSymbol();
  double Arithmetic(bool get);
  double Operation(bool get);
  double Pow(bool get);
  double Expression(bool get);
  std::string Parser();
  void Check(std::string str);
  void ReplaceSubscriptLines(std::string& str);

 public:
  std::vector<double> CreditCalc(double sum_credit, double time_credit,
                                 double per, bool check);
  std::vector<double> DepositCalc(bool check, double deposit_term,
                                  double deposit_amount,
                                  double interest_rate, double tax_rate,
                                  double replenishments_month,
                                  double replenishments_sum,
                                  double partial_withdrawals_month,
                                  double partial_withdrawals_sum);
};

}  // namespace s21

#endif  // SRC_MODEL_MODEL_H
