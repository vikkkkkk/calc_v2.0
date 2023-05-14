#include "controller.h"

namespace s21 {
std::pair<std::string, double> Controller::calculation() {
  std::string error = "";
  double res = 0.0;
  try {
    Model model(mInputString);
    res = model.Calc();
  } catch (const std::exception &e) {
    error = e.what();
  }

  std::pair<std::string, double> result = {error, res};
  return result;
}

std::vector<double> Controller::CrCalc(double loanAmount, int term,
                                       double interestRate, bool paymentType) {
  Model model(mInputString);
  return model.CreditCalc(loanAmount, term, interestRate, paymentType);
}

std::vector<double> Controller::DepCalc(bool check, double deposit_term,
                                        double deposit_amount,
                                        double interest_rate, double tax_rate,
                                        double replenishments_month,
                                        double replenishments_sum,
                                        double partial_withdrawals_month,
                                        double partial_withdrawals_sum) {
  Model model(mInputString);
  return model.DepositCalc(check, deposit_term, deposit_amount, interest_rate,
                           tax_rate, replenishments_month, replenishments_sum,
                           partial_withdrawals_month, partial_withdrawals_sum);
}

} // namespace s21
