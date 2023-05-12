#include "controller.h"

namespace s21 {
std::pair<std::string, double> Controller::calculations() {
  // Объявляем переменную error, в которую будем записывать сообщение об ошибке при обработке входных данных
  std::string error = "";
  // Объявляем переменную rez, которая будет хранить результат вычислений
  double rez = 0.0;
  try {
    // Создаем объект класса Model, передавая в качестве аргумента строку с входными данными
    Model model(m_inputString);
    // Вызываем метод Calculate() объекта model для произведения вычислений
    rez = model.Calculate();
  } catch (const std::exception& e) {
    // Если возникла ошибка при обработке входных данных, записываем в переменную error сообщение об ошибке
    error = e.what();
  }
  // Создаем объект типа std::pair, в котором в первом элементе хранится сообщение об ошибке, а во втором результат вычислений
  std::pair<std::string, double> result = {error, rez};
  // Возвращаем объект result
  return result;
}

std::vector<double> Controller::CrCalculations(double loanAmount, int term,
                                               double interestRate,
                                               bool paymentType) {
  // Создаем объект класса Model, передавая в качестве аргумента строку с входными данными
  Model model(m_inputString);
  // Вызываем метод CreditCalculations() объекта model для вычисления графика платежей
  return model.CreditCalc(loanAmount, term, interestRate, paymentType);
}

/* 

Этот код относится к классу Controller, который является частью архитектуры MVC (Model-View-Controller) 
и используется для управления взаимодействием между моделью (Model) и представлением (View). 

В методе calculations() класса Controller происходит вызов метода Calculate() у объекта класса Model, который 
выполняет вычисления на основе входных данных, хранящихся в объекте m_inputString класса Controller. Если при 
обработке данных возникает ошибка, она записывается в переменную error типа std::string. Результат вычислений и 
сообщение об ошибке затем сохраняются в объект std::pair<std::string, double> и возвращаются как результат 
выполнения метода.

Метод CrCalculations() класса Controller также использует объект класса Model для выполнения вычислений с передачей 
параметров в метод CreditCalculations(). Этот метод возвращает вектор типа double, который содержит график платежей 
для заданных параметров.

*/


}  // namespace s21
