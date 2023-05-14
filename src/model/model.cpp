#include "model.h"

namespace s21 {

Model::Model(std::string initLine) {
  if (initLine.length() > 255) {
    throw std::overflow_error("AHTUNG: An Expressionession of more than 255 "
                              "characters has been entered");
  } else {
    pStreamLine = initLine;
    pStream = nullptr;
    current = NUMBER;
    mNumberValue = '0';
  }
}

Model::~Model() {
  delete pStream;
  pStream = nullptr;
}

void Model::GetSymbol() {
  char ch;
  if (!pStream->get(ch)) {
    current = END;
  }
  if (ch == 0) {
    current = END;
  } else if (ch == MULT || ch == DIV || ch == PLUS || ch == MINUS ||
             ch == MOD || ch == POW || ch == SIN || ch == COS || ch == TAN ||
             ch == ATAN || ch == ASIN || ch == ATAN || ch == ACOS ||
             ch == SQRT || ch == LOG || ch == LN || ch == ROUNDBRACKET_L ||
             ch == ROUNDBRACKET_R) {
    current = type_t(ch);
  } else if (isdigit(ch) || ch == '.') {
    pStream->putback(ch);
    *pStream >> mNumberValue;
    current = NUMBER;
  } else {
    current = END;
  }
}

std::string Model::Parser() {
  std::string newStr;
  bool check = false;
  for (size_t i = 0; i < pStreamLine.size(); i++) {
    char c = pStreamLine[i];
    switch (c) {
    case 'm':
      if (pStreamLine.substr(i, 3) == "mod") {
        newStr += "mod";
        i += 2;
      } else {
        check = true;
      }
      break;
    case 's':
      if (pStreamLine.substr(i, 3) == "sin") {
        newStr += "sin";
        i += 2;
      } else if (pStreamLine.substr(i, 4) == "sqrt") {
        newStr += "sqrt";
        i += 3;
      } else {
        check = true;
      }
      break;
    case 'c':
      if (pStreamLine.substr(i, 3) == "cos") {
        newStr += "cos";
        i += 2;
      } else {
        check = true;
      }
      break;
    case 't':
      if (pStreamLine.substr(i, 3) == "tan") {
        newStr += "tan";
        i += 2;
      } else {
        check = true;
      }
      break;
    case 'a':
      if (pStreamLine.substr(i, 4) == "atan") {
        newStr += "atan";
        i += 3;
      } else if (pStreamLine.substr(i, 4) == "asin") {
        newStr += "asin";
        i += 3;
      } else if (pStreamLine.substr(i, 4) == "acos") {
        newStr += "acos";
        i += 3;
      } else {
        check = true;
      }
      break;
    case 'l':
      if (pStreamLine.substr(i, 2) == "ln") {
        newStr += "ln";
        i += 1;
      } else if (pStreamLine.substr(i, 3) == "log") {
        newStr += "log";
        i += 2;
      } else {
        check = true;
      }
      break;
    default:
      newStr += c;
      break;
    }
  }
  if (check) {
    throw std::invalid_argument("AHTUNG: invalid symbol");
  }
  return newStr;
}

double Model::Arithmetic(bool get) {
  if (get) {
    GetSymbol();
  }
  double result = 0.0;
  if (current == NUMBER) {
    result = mNumberValue;
    GetSymbol();
  } else if (current == MINUS) {
    result = -Arithmetic(true);
  } else if (current == PLUS) {
    result = Arithmetic(true);
  } else if (current == SIN) {
    result = sin(Arithmetic(true));
  } else if (current == COS) {
    result = cos(Arithmetic(true));
  } else if (current == TAN) {
    result = tan(Arithmetic(true));
  } else if (current == ATAN) {
    result = atan(Arithmetic(true));
  } else if (current == ASIN) {
    result = asin(Arithmetic(true));
  } else if (current == ACOS) {
    result = acos(Arithmetic(true));
  } else if (current == SQRT) {
    result = sqrt(Arithmetic(true));
  } else if (current == LOG) {
    result = log10(Arithmetic(true));
  } else if (current == LN) {
    result = log(Arithmetic(true));
  } else if (current == ROUNDBRACKET_L) {
    double expr = Expression(true);
    GetSymbol();
    result = expr;
  } else {
    throw std::logic_error("AHTUNG: undefined");
  }
  return result;
}

double Model::Pow(bool get) {
  double left = Arithmetic(get);

  while (true) {
    if (current == POW) {
      left = pow(left, Arithmetic(true));
    } else {
      return left;
    }
  }
}

double Model::Operation(bool get) {
  double left = Pow(get);

  while (true) {
    switch (current) {
    case MULT:
      left *= Pow(true);
      break;
    case DIV:
      if (double divisor = Pow(true)) {
        left /= divisor;
        break;
      }
      throw std::logic_error("AHTUNG: divide by 0");
    case MOD:
      if (double divisor = Pow(true)) {
        left = std::fmod(left, divisor);
        break;
      }
      throw std::logic_error("AHTUNG: mode by 0");
    default:
      return left;
    }
  }
}

double Model::Expression(bool get) {
  double left = Operation(get);

  for (;;) {
    switch (current) {
    case PLUS:
      left += Operation(true);
      break;
    case MINUS:
      left -= Operation(true);
      break;
    default:
      return left;
    }
  }
}

void Model::ReplaceSubscriptLines(std::string &str) {
  std::unordered_map<std::string, std::string> replacements = {
      {"mod", "m"},  {"log", "g"}, {"ln", "l"},  {"acos", "o"}, {"asin", "i"},
      {"atan", "n"}, {"tan", "t"}, {"cos", "c"}, {"sin", "s"},  {"sqrt", "q"},
  };
  for (auto &replacement : replacements) {
    size_t pos = 0;
    while ((pos = str.find(replacement.first, pos)) != std::string::npos) {
      if ((pos == 0 || !std::isalpha(str[pos - 1])) &&
          (pos + replacement.first.length() == str.length() ||
           !std::isalpha(str[pos + replacement.first.length()]))) {
        str.replace(pos, replacement.first.length(), replacement.second);
        pos += replacement.second.length();
      } else {
        pos += replacement.first.length();
      }
    }
  }
}

double Model::Calc() {
  std::string str = Parser();
  ReplaceSubscriptLines(str);
  pStream = new std::istringstream(str);
  double tmp = 0.0;
  while (pStream) {
    GetSymbol();
    if (current == END) {
      break;
    }
    tmp = Expression(false);
  }
  if (pStream != nullptr) {
    delete pStream;
    pStream = nullptr;
  }
  return tmp;
}

std::vector<double> Model::CreditCalc(double sum_credit, double time_credit,
                                      double per, bool check) {
  std::vector<double> rez;
  if (check) {
    double month_pay = 0.0, over_pay = 0.0, all_pay = 0.0;
    double per_m = (per / 12.0) / 100;
    month_pay = per_m * pow(1 + per_m, time_credit) /
                (pow(1 + per_m, time_credit) - 1) * sum_credit;
    over_pay = month_pay * time_credit - sum_credit;
    all_pay = over_pay + sum_credit;
    rez = {0, month_pay, all_pay, over_pay};
  } else {
    double overpayment = 0, first_month_payment = 0, last_month_payment = 0,
           total_payment = 0;
    double rest = sum_credit;
    double monthly = 0;
    double monthly_interes_rate = per / (100 * 12);
    for (int i = 0; i < time_credit; i++) {
      if (i == 0) {
        first_month_payment =
            rest * monthly_interes_rate + sum_credit / time_credit;
        total_payment += first_month_payment;
        rest -= first_month_payment;
      } else if (i == (time_credit - 1)) {
        last_month_payment =
            rest * monthly_interes_rate + sum_credit / time_credit;
        total_payment += last_month_payment;
        rest -= last_month_payment;
      } else {
        monthly = rest * monthly_interes_rate + sum_credit / time_credit;
        total_payment += monthly;
        rest -= monthly;
      }
    }
    overpayment = total_payment - sum_credit;
    rez = {last_month_payment, first_month_payment, total_payment, overpayment};
  }
  return rez;
}

std::vector<double> Model::DepositCalc(bool check, double deposit_term,
                                       double deposit_amount,
                                       double interest_rate, double tax_rate,
                                       double replenishments_month,
                                       double replenishments_sum,
                                       double partial_withdrawals_month,
                                       double partial_withdrawals_sum) {
  double accrued_interest = 0, tax_amount = 0, deposit_end = 0;
  if (check) {
    double accrued_month_interest = 0;
    double month_tax_amount = 0;
    for (int i = 0; i < deposit_term; i++) {
      accrued_month_interest = (((deposit_amount / 100) * interest_rate) / 12);
      month_tax_amount = accrued_month_interest * (tax_rate / 100);
      accrued_month_interest = accrued_month_interest - month_tax_amount;
      deposit_amount += accrued_month_interest;
      accrued_interest += accrued_month_interest;
      tax_amount += month_tax_amount;
      if (i == replenishments_month && replenishments_sum > 0) {
        deposit_amount += replenishments_sum;
      }
      if (i == partial_withdrawals_month && partial_withdrawals_sum > 0) {
        deposit_amount -= partial_withdrawals_sum;
      }
    }
  } else if (partial_withdrawals_month != 0 || replenishments_month != 0) {
    double accrued_month_interest = 0;
    for (int i = 0; i < deposit_term; i++) {
      accrued_month_interest = (((deposit_amount / 100) * interest_rate) / 12);
      accrued_interest += accrued_month_interest;
      if (i == replenishments_month && replenishments_sum > 0) {
        deposit_amount += replenishments_sum;
      }
      if (i == partial_withdrawals_month && partial_withdrawals_sum > 0) {
        deposit_amount -= partial_withdrawals_sum;
      }
    }
    tax_amount = accrued_interest * (tax_rate / 100);
    accrued_interest = accrued_interest - tax_amount;
  } else {
    accrued_interest =
        (((deposit_amount / 100) * interest_rate) / 12) * deposit_term;
    tax_amount = accrued_interest * (tax_rate / 100);
    accrued_interest = accrued_interest - tax_amount;
  }
  deposit_end = accrued_interest + deposit_amount;
  std::vector<double> rez = {accrued_interest, deposit_end, tax_amount};
  return rez;
}

} // namespace s21
