#include "controller.h"

namespace s21 {
std::pair<std::string, double> Controller::calculation() {
  // Объявляем переменную error, в которую будем записывать сообщение об ошибке при обработке входных данных
  std::string error = "";
  // Объявляем переменную res, которая будет хранить результат вычислений
  double res = 0.0;
  try {
    // Создаем объект класса Model, передавая в качестве аргумента строку с входными данными
    Model model(mInputString);
    // Вызываем метод Calc() объекта model для произведения вычислений
    res = model.Calc();
  } catch (const std::exception& e) {
    // Если возникла ошибка при обработке входных данных, записываем в переменную error сообщение об ошибке
    error = e.what();
  }
  // Создаем объект типа std::pair, в котором в первом элементе хранится сообщение об ошибке, а во втором результат вычислений
  std::pair<std::string, double> result = {error, res};
  // Возвращаем объект result
  return result;
}

std::vector<double> Controller::CrCalc(double loanAmount, int term,
                                               double interestRate,
                                               bool paymentType) {
  // Создаем объект класса Model, передавая в качестве аргумента строку с входными данными
  Model model(mInputString);
  // Вызываем метод CreditCalc() объекта model для вычисления графика платежей
  return model.CreditCalc(loanAmount, term, interestRate, paymentType);
}

/* 

Этот код относится к классу Controller, который является частью архитектуры MVC (Model-View-Controller) 
и используется для управления взаимодействием между моделью (Model) и представлением (View). 

В методе calculation() класса Controller происходит вызов метода Calc() у объекта класса Model, который 
выполняет вычисления на основе входных данных, хранящихся в объекте mInputString класса Controller. Если при 
обработке данных возникает ошибка, она записывается в переменную error типа std::string. Результат вычислений и 
сообщение об ошибке затем сохраняются в объект std::pair<std::string, double> и возвращаются как результат 
выполнения метода.

Метод CrCalc() класса Controller также использует объект класса Model для выполнения вычислений с передачей 
параметров в метод CreditCalc(). Этот метод возвращает вектор типа double, который содержит график платежей 
для заданных параметров.

*/


}  // namespace s21
