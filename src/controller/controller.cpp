#include "controller.h"

namespace s21 {
std::pair<std::string, double> Controller::calculation() {
  std::string error = "";
  double res = 0.0;
  try {
    Model model(mInputString);
    res = model.Calc();
  } catch (const std::exception& e) {
    error = e.what();
  }
  
  std::pair<std::string, double> result = {error, res};
  return result;
}

std::vector<double> Controller::CrCalc(double loanAmount, int term,
                                       double interestRate,
                                       bool paymentType) {
  Model model(mInputString);
  return model.CreditCalc(loanAmount, term, interestRate, paymentType);
}

}  // namespace s21
