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

}  // namespace s21


