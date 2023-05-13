#ifndef SRC_CONTROLLER_CONTROLLER_H
#define SRC_CONTROLLER_CONTROLLER_H

#include <exception>

#include "../model/model.h"

namespace s21 {
// объявление пространства имён
class Controller {
// объявление класса Controller
private:
std::string mInputString;
// приватная переменная типа std::string для хранения входной строки
public:
Controller(std::string const &str = "") : mInputString(str) {}
// конструктор класса с одним параметром - входной строкой. По умолчанию - пустая строка.

std::pair<std::string, double> calculation();
// метод для выполнения математических операций над входной строкой. Возвращает пару значений - строку с выражением и результат операций.

std::vector<double> CrCalc(double loanAmount, int term, 
                                   double interestRate,  bool paymentType);
// метод для расчёта кредита. Принимает на вход сумму кредита, срок кредита, процентную ставку и тип выплат. Возвращает вектор с результатами расчёта.

std::vector<double> DepCalc(bool check, double deposit_term, 
                                    double deposit_amount, double interest_rate, 
                                    double tax_rate, double replenishments_month, 
                                    double replenishments_sum, 
                                    double partial_withdrawals_month, 
                                    double partial_withdrawals_sum); 
// метод для расчёта депозита. Принимает на вход параметры депозита и возвращает вектор с результатами расчёта.
};
// завершение объявления класса и пространства имён.

}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H

