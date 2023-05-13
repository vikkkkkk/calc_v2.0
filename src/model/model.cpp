#include "model.h"

namespace s21 {

Model::Model(std::string initLine) {
// Описание конструктора класса Model с одним параметром типа std::string
  if (initLine.length() > 255) {
    // проверка длины переданной строки на превышение максимально допустимой длины (255 символов)
    throw std::overflow_error(
        "AHTUNG: An Expressionession of more than 255 characters has been entered");
    // создание исключения типа "std::overflow_error" в случае превышения максимальной длины входной строки
  } else {
    pStreamLine = initLine;
    // инициализация входной строки класса переменной "pStreamLine"
    pStream = nullptr;
    // инициализация указателя на поток ввода "pStream"
    current = NUMBER;
    // инициализация переменной "current" значением "NUMBER"
    mNumberValue = '0';
    // инициализация переменной "mNumberValue" символом '0'
  }
}

Model::~Model() {
  // реализация деструктора класса Model
  delete pStream;
  // удаляет объект, на который указывает указатель pStream
  pStream = nullptr;
  // устанавливает указатель pStream в значение nullptr,
  // чтобы предотвратить повторное удаление объекта
}

void Model::GetSymbol() {
  char ch;
  // объявление переменной типа char для хранения текущего символа выражения
  if (!pStream->get(ch)) {
    current = END;
  } // если символ закончился в потоке ввода, устанавливается текущий символ END
  if (ch == 0) {
    current = END; // если ch - ноль, устанавливается текущий символ END
  } else if (ch == MULT || ch == DIV || ch == PLUS || ch == MINUS ||
             ch == MOD || ch == POW || ch == SIN || ch == COS || ch == TAN ||
             ch == ATAN || ch == ASIN || ch == ATAN || ch == ACOS ||
             ch == SQRT || ch == LOG || ch == LN || ch == ROUNDBRACKET_L ||
             ch == ROUNDBRACKET_R) { 
    current = type_t(ch);
    // если ch является знаком операции, то устанавливается соответствующий 
    // символьный тип для текущего символа с помощью перечисления type_t
  } else if (isdigit(ch) || ch == '.') {
    // если ch является цифрой или точкой, то символ помещается обратно в 
    // поток ввода и считывается последовательность символов, которая преобразуется 
    // в число и устанавливается как текущее число
    pStream->putback(ch); // помещает символ ch обратно в входной поток
    *pStream >> mNumberValue;
    // считывает последовательность символов и преобразовывает её в число, которое сохраняется в переменной mNumberValue
    current = NUMBER;
    // устанавливает тип текущего символа NUMBER
  } else {
    current = END;
    // устанавливает тип текущего символа END
  }
}

std::string Model::Parser() {
  std::string newStr; // создание пустой строки newStr
  bool check = false; // создание переменной check типом bool со значением false
  for (size_t i = 0; i < pStreamLine.size(); i++) {
    // начало цикла перебора всех символов строки pStreamLine, начиная с индекса 0 и заканчивая последним индексом строки
    char c = pStreamLine[i]; // создание переменной c типом char и присвоение её значения символа, 
    // соответствующего текущему индексу i в строке pStreamLine
    switch (c) { // начало конструкции switch-case для проверки текущего символа.
      case 'm': // если текущий символ - 'm', то выполняется следующий код
        if (pStreamLine.substr(i, 3) == "mod") { // проверяем, совпадает ли следующая подстрока в pStreamLine со строкой "mod"
          newStr += "mod"; // если подстрока равна "mod", добавляем эту строку в переменную newStr
          i += 2;
          // увеличиваем значение i на 2, так как мы добавили в newStr три символа: "m", "o" и "d", а в следующей итерации цикла i увеличится еще на 1
        } else {
          check = true;
          // если подстрока не равна "mod", устанавливаем переменную check в значение true
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
    // проверяем, если значение переменной check равно true, выбрасываем исключение
  }
  return newStr;
}

double Model::Arithmetic(bool get) {
  // начало определения функции Arithmetic с параметром get, который определяет, нужно ли получить следующий символ из входной строки
  if (get) {
    GetSymbol();
  }
  // если параметр get равен true, вызываем метод GetSymbol для получения следующего символа из входной строки
  double result = 0.0;
  // инициализируем переменную result значениями 0.0
  if (current == NUMBER) { //проверяем, равен ли текущий символ числу
    result = mNumberValue;
    // если текущий символ является числом, присваиваем переменной result значение атрибута mNumberValue
    GetSymbol();
    // получаем следующий символ из входной строки
  } else if (current == MINUS) { // проверяем, является ли текущий символ знаком минус
    result = -Arithmetic(true);
    // сли текущий символ является знаком минус, вызываем рекурсивно функцию Arithmetic с 
    // параметром true для получения следующего числа и меняем знак на противоположный.
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
    // если текущий символ является левой круглой скобкой, 
    // вызываем рекурсивно метод Expression с параметром true, чтобы вычислить выражение в скобках
    GetSymbol(); // получаем следующий символ из входной строки
    result = expr; // результатом является результат выражения в скобках
  } else {
    throw std::logic_error("AHTUNG: undefined");
    // если текущий символ не является числом, знаком минус или левой круглой скобкой, выбрасываем исключение
  }
  return result;
}

double Model::Pow(bool get) {
  double left = Arithmetic(get); // инициализация переменной left значением, возвращенным функцией Arithmetic, вызванной с параметром get

  while (true) {
    if (current == POW) { // проверяем, является ли текущий символ знаком возведения в степень
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
      case MULT: // проверка, равен ли символ current знаку умножения
        left *= Pow(true);
        // если символ current равен знаку умножения, вызываем рекурсивно функцию Pow 
        // с параметром true, чтобы получить следующее число, и перемножаем его с переменной left, 
        // присваивая результат переменной left
        break;
      case DIV: // проверка, равен ли символ current знаку деления
        if (double divisor = Pow(true)) {
          left /= divisor;
          // если символ current равен знаку деления, вызываем 
          // рекурсивно функцию Pow с параметром true, чтобы получить 
          // следующее число, и сохраняем его значение в переменной divisor
          break;
        }
        throw std::logic_error("AHTUNG: divide by 0");
      case MOD: // проверка, равен ли символ current знаку взятия остатка
        if (double divisor = Pow(true)) {
          // если символ current равен знаку взятия остатка, вызываем рекурсивно 
          // функцию Pow с параметром true, чтобы получить следующее число, и сохраняем 
          // его значение в переменной divisor
          left = std::fmod(left, divisor);
          // если значение divisor не равно 0, выполняем операцию взятия остатка операндов 
          // left и divisor, присваивая результат переменной left
          break;
        }
        throw std::logic_error("AHTUNG: mode by 0");
      default:
        return left;
        //  если текущий символ не соответствует никакому из знаков арифметических операций, 
        // выходим из цикла и возвращаем значение переменной left
    }
  }
}

double Model::Expression(bool get) {
  double left = Operation(get);

  for (;;) { // начало бесконечного цикла, решила выпендриться))) while (true) == for (;;) 
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

void Model::ReplaceSubscriptLines(std::string& str) {
  std::unordered_map<std::string, std::string> replacements = { // хранит пары значений типа string (ключ и значение)
      {"mod", "m"},  {"log", "g"}, {"ln", "l"},  {"acos", "o"}, {"asin", "i"},
      {"atan", "n"}, {"tan", "t"}, {"cos", "c"}, {"sin", "s"},  {"sqrt", "q"},
  }; // инициализация переменной replacements парами значений, которые нужно заменить в строке
  for (auto& replacement : replacements) { // перебирает все пары значений в переменной replacements
    size_t pos = 0; // будет содержать позицию, с которой начинается следующий поиск подстроки
    while ((pos = str.find(replacement.first, pos)) != std::string::npos) { // находит все вхождения подстроки replacement.first в строке str
      if ((pos == 0 || !std::isalpha(str[pos - 1])) &&
          (pos + replacement.first.length() == str.length() ||
           !std::isalpha(str[pos + replacement.first.length()]))) { 
             // проверка, что найденная подстрока отделена от других символов буквами, цифрами и знаками подчеркивания
        str.replace(pos, replacement.first.length(), replacement.second); 
        // заменяем найденную подстроку на ее новое значение replacement.second
        pos += replacement.second.length(); 
        // увеличиваем значение pos на длину замененной подстроки, чтобы продолжить поиск подстроки сразу 
        // после замененной подстроки
      } else {
        pos += replacement.first.length();
        // если найденная подстрока не отделена от других символов, увеличиваем значение pos на длину 
        // заменяемой подстроки, чтобы продолжить поиск сразу после найденной подстроки
      }
    }
  }
}

double Model::Calc() {
  std::string str = Parser();
  // Вызов функции Parser и сохранение результата в переменную str
  ReplaceSubscriptLines(str);
  pStream = new std::istringstream(str);
  double tmp = 0.0;
  while (pStream) {
    GetSymbol();
    if (current == END) {
      break;
    }
    // Если текущий символ - конец строки, то выход из цикла
    tmp = Expression(false);
  }
  if (pStream != nullptr) {
    delete pStream;
    pStream = nullptr;
  }
  // Если объект потока ввода pStream не равен nullptr, то освобождение памяти, выделенной под этот объект
  return tmp;
}

std::vector<double> Model::CreditCalc(double sum_credit,
                                              double time_credit, double per,
                                              bool check) {
  std::vector<double> rez;
  if (check) {
    double month_pay = 0.0, over_pay = 0.0, all_pay = 0.0;
    double per_m = (per / 12.0) / 100;
    month_pay = per_m * pow(1 + per_m, time_credit) /
                (pow(1 + per_m, time_credit) - 1) * sum_credit;
    over_pay = month_pay * time_credit - sum_credit;
    all_pay = over_pay + sum_credit;
    rez = {all_pay, over_pay, month_pay};
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

std::vector<double> Model::DepositCalc(
    bool check, double deposit_term, double deposit_amount,
    double interest_rate, double tax_rate, double replenishments_month,
    double replenishments_sum, double partial_withdrawals_month,
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

}  // namespace s21


