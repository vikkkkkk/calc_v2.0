#ifndef SRC_CONTROLLER_CONTROLLER_H
#define SRC_CONTROLLER_CONTROLLER_H

#include <exception>

#include "../model/model.h"

namespace s21 {
class Controller {
private:
  std::string mInputString;

public:
  Controller(std::string const &str = "") : mInputString(str) {}

  std::pair<std::string, double> calculation();

  std::vector<double> CrCalc(double loanAmount, int term, double interestRate,
                             bool paymentType);

  std::vector<double> DepCalc(bool check, double deposit_term,
                              double deposit_amount, double interest_rate,
                              double tax_rate, double replenishments_month,
                              double replenishments_sum,
                              double partial_withdrawals_month,
                              double partial_withdrawals_sum);
};
} // namespace s21

#endif // SRC_CONTROLLER_CONTROLLER_H
