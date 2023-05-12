#include "model.h"

namespace s21 {

Model::Model(std::string initString) {
// Описание конструктора класса Model с одним параметром типа std::string
  if (initString.length() > 255) {
    // проверка длины переданной строки на превышение максимально допустимой длины (255 символов)
    throw std::overflow_error(
        "AHTUNG: An Expressionession of more than 255 characters has been entered");
    // создание исключения типа "std::overflow_error" в случае превышения максимальной длины входной строки
  } else {
    p_stream_string = initString;
    // инициализация входной строки класса переменной "p_stream_string"
    p_stream = nullptr;
    // инициализация указателя на поток ввода "p_stream"
    current = NUMBER;
    // инициализация переменной "current" значением "NUMBER"
    m_number_value = '0';
    // инициализация переменной "m_number_value" символом '0'
  }
}

Model::~Model() {
  // реализация деструктора класса Model
  delete p_stream;
  // удаляет объект, на который указывает указатель `p_stream`
  p_stream = nullptr;
  // устанавливает указатель `p_stream` в значение nullptr,
  // чтобы предотвратить повторное удаление объекта
}

void Model::GetSymbol() {
  char ch;
  // объявление переменной типа char для хранения текущего символа выражения
  if (!p_stream->get(ch)) {
    current = END;
  } // если символ закончился в потоке ввода, устанавливается текущий символ END
  if (ch == 0) {
    current = END; // если `ch` - ноль, устанавливается текущий символ END
  } else if (ch == MULT || ch == DIV || ch == PLUS || ch == MINUS ||
             ch == MOD || ch == POW || ch == SIN || ch == COS || ch == TAN ||
             ch == ATAN || ch == ASIN || ch == ATAN || ch == ACOS ||
             ch == SQRT || ch == LOG || ch == LN || ch == ROUNDBRACKET_L ||
             ch == ROUNDBRACKET_R) { 
    current = type_t(ch);
    // если `ch` является знаком операции, то устанавливается соответствующий 
    // символьный тип для текущего символа с помощью перечисления `type_t`
  } else if (isdigit(ch) || ch == '.') {
    // если `ch` является цифрой или точкой, то символ помещается обратно в 
    // поток ввода и считывается последовательность символов, которая преобразуется 
    // в число и устанавливается как текущее число
    p_stream->putback(ch); // помещает символ `ch` обратно в входной поток
    *p_stream >> m_number_value;
    // считывает последовательность символов и преобразовывает её в число, которое сохраняется в переменной `m_number_value`
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
  for (size_t i = 0; i < p_stream_string.size(); i++) {
    // начало цикла перебора всех символов строки p_stream_string, начиная с индекса 0 и заканчивая последним индексом строки
    char c = p_stream_string[i]; // создание переменной c типом char и присвоение её значения символа, 
    // соответствующего текущему индексу i в строке p_stream_string
    switch (c) { // начало конструкции switch-case для проверки текущего символа.
      case 'm': // если текущий символ - 'm', то выполняется следующий код
        if (p_stream_string.substr(i, 3) == "mod") { // проверяем, совпадает ли следующая подстрока в `p_stream_string` со строкой "mod"
          newStr += "mod"; // если подстрока равна "mod", добавляем эту строку в переменную `newStr`
          i += 2;
          // увеличиваем значение `i` на 2, так как мы добавили в `newStr` три символа: "m", "o" и "d", а в следующей итерации цикла `i` увеличится еще на 1
        } else {
          check = true;
          // если подстрока не равна "mod", устанавливаем переменную `check` в значение `true`
        }
        break;
      case 's':
        if (p_stream_string.substr(i, 3) == "sin") {
          newStr += "sin";
          i += 2;
        } else if (p_stream_string.substr(i, 4) == "sqrt") {
          newStr += "sqrt";
          i += 3;
        } else {
          check = true;
        }
        break;
      case 'c':
        if (p_stream_string.substr(i, 3) == "cos") {
          newStr += "cos";
          i += 2;
        } else {
          check = true;
        }
        break;
      case 't':
        if (p_stream_string.substr(i, 3) == "tan") {
          newStr += "tan";
          i += 2;
        } else {
          check = true;
        }
        break;
      case 'a':
        if (p_stream_string.substr(i, 4) == "atan") {
          newStr += "atan";
          i += 3;
        } else if (p_stream_string.substr(i, 4) == "asin") {
          newStr += "asin";
          i += 3;
        } else if (p_stream_string.substr(i, 4) == "acos") {
          newStr += "acos";
          i += 3;
        } else {
          check = true;
        }
        break;
      case 'l':
        if (p_stream_string.substr(i, 2) == "ln") {
          newStr += "ln";
          i += 1;
        } else if (p_stream_string.substr(i, 3) == "log") {
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
    // проверяем, если значение переменной `check` равно `true`, выбрасываем исключение
  }
  return newStr;
}

double Model::Arithmetic(bool get) {
  // начало определения функции `Arithmetic` с параметром `get`, который определяет, нужно ли получить следующий символ из входной строки
  if (get) {
    GetSymbol();
  }
  // если параметр `get` равен `true`, вызываем метод `GetSymbol` для получения следующего символа из входной строки
  double result = 0.0;
  // инициализируем переменную `result` значениями 0.0
  if (current == NUMBER) { //проверяем, равен ли текущий символ числу
    result = m_number_value;
    // если текущий символ является числом, присваиваем переменной `result` значение атрибута `m_number_value`
    GetSymbol();
    // получаем следующий символ из входной строки
  } else if (current == MINUS) { // проверяем, является ли текущий символ знаком минус
    result = -Arithmetic(true);
    // сли текущий символ является знаком минус, вызываем рекурсивно функцию `Arithmetic` с 
    // параметром `true` для получения следующего числа и меняем знак на противоположный.
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
    // вызываем рекурсивно метод `Expression` с параметром `true`, чтобы вычислить выражение в скобках
    GetSymbol(); // получаем следующий символ из входной строки
    result = expr; // результатом является результат выражения в скобках
  } else {
    throw std::logic_error("AHTUNG: undefined");
    // если текущий символ не является числом, знаком минус или левой круглой скобкой, выбрасываем исключение
  }
  return result;
}

}  // namespace s21


