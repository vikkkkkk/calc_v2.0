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
// Объявление класса

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
// Перечисление type_t, которое определяет возможные типы символов для выражения

/*

NUMBER - числовой символ
END - конец выражения
PLUS - операция сложения
MINUS - операция вычитания
MULT - операция умножения
DIV - операция деления
MOD - операция взятия остатка
POW - операция возведения в степень
SIN - операция синуса
COS - операция косинуса
TAN - операция тангенса
ATAN - операция арктангенса
ASIN - операция арксинуса
ACOS - операция арккосинуса
SQRT - операция извлечения корня
LOG - операция логарифма по заданному основанию
LN - операция натурального логарифма
ROUNDBRACKET_L - открывающаяся скобка
ROUNDBRACKET_R - закрывающаяся скобка

*/

 public:
  Model() : p_stream(nullptr), p_stream_string("") {}
  explicit Model(std::string initString);
  ~Model();
  double Calculate();
// Объявление конструкторов, деструктора и метода для выполнения расчёта выражения

 private:
  std::istream* p_stream;
  std::string p_stream_string;
  type_t current;
  double m_number_value;
  void GetSymbol();
  double Arithmetic(bool get);
  double Operation(bool get);
  double Pow(bool get);
  double Expression(bool get);
  std::string Parser();
  void Check(std::string str);
  void ReplaceSubstrings(std::string& str);
// Определение приватных переменных и методов.

/*

p_stream - указатель на поток ввода
p_stream_string - строка со входным выражением
current - текущий символ выражения
m_number_value - текущее числовое значение

GetSymbol() - получение следующего символа выражения
Arithmetic() - выполнение операций сложения и вычитания
Operation() - выполнение операций умножения, деления и взятия остатка
Pow() - выполнение операций возведения в степень
Expression() - вычисление выражения
Parser() - парсинг выражения
Check() - проверка корректности входного выражения
ReplaceSubstrings() - замена подстрок во входной строке

*/

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
// Определение методов для расчёта кредитов и депозитов

}  // namespace s21

#endif  // SRC_MODEL_MODEL_H
