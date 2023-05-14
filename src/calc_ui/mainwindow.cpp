#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "credit.h"
#include "deposit.h"

double num_first;
int flag = 0;
int dot = 0;
int count = 0;
int min_flag = 0;
int pl_falg = 0;
int is_digit = 1;
int is_r_bracket = 1;
int is_sign = 0;
int is_x = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
    connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(ariph_numbers()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(ariph_numbers()));
    connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(ariph_numbers()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(ariph_numbers()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers() {
    QPushButton *button = (QPushButton *) sender();
    QString all_numbers;
    if (ui->result->text() == '0') {
        ui->result->setText("");
    }
        all_numbers = (ui->result->text() + button->text());
        ui->result->setText(all_numbers);

    flag = 0;
    min_flag = 0;
    pl_falg = 0;
    is_digit = 0;
    is_r_bracket = 1;
    is_sign = 1;
    is_x = 1;
}

void MainWindow::ariph_numbers() {
    QPushButton *button = (QPushButton *) sender();
    if (ui->result->text() == '0') flag = 1;
    if (flag == 0) {
        ui->result->setText(ui->result->text() + button->text());
        flag = 1;
        dot = 0;
        is_digit = 1;
        is_r_bracket = 1;
        is_sign = 0;
        is_x = 1;
    }
}

void MainWindow::trigon_numbers() {
    QPushButton *button = (QPushButton *) sender();
    int loc_falg = 1;
    if (dot == 0) {
        if (ui->result->text() == '0') {
            ui->result->setText("");
            loc_falg = 0;
        }
        if ((is_digit == 0 || is_r_bracket == 0) && loc_falg == 1) {
            ui->result->setText(ui->result->text() + "*" + button->text()  + "(");
        } else {
            ui->result->setText(ui->result->text() + button->text()  + "(");
        }
        flag = 1;
        dot = 0;
        count += 1;
        min_flag = 0;
        pl_falg = 0;
        is_digit = 1;
        is_r_bracket = 1;
        is_sign = 0;
        is_x = 1;
   }
}

void MainWindow::on_pushButton_dot_clicked()
{
    if (flag == 0 && dot == 0) {
        ui->result->setText(ui->result->text() + ".");
        flag = 1;
        dot = 1;
        is_digit = 1;
        is_r_bracket = 1;
        is_sign = 1;
        is_x = 1;
    }
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_mul->setChecked(false);
    ui->pushButton_div->setChecked(false);
    ui->result->setText("0");
    flag = 0;
    dot = 0;
    count = 0;
    min_flag = 0;
    pl_falg = 0;
    is_digit = 1;
    is_r_bracket = 1;
    is_sign = 0;
    is_x = 1;
}


void MainWindow::on_pushButton_equals_clicked()
{
//    double x = 0;
    QPushButton *button = (QPushButton *)sender();
    button->setChecked(true);
    QString send = ui->result->text();
//    QByteArray ba = send.toLocal8Bit();
//    char* buf = ba.data();

//    if (ui->x_value->text() != "") {
//        x = (ui->x_value->text().toDouble());
//    }
    s21::Controller cont(send.toStdString());
//    QString toStr = QString::number(s21_parser(buf, x), 'g', 15);
    std::pair res = cont.calculation();
    ui->result->setText(QString::number(res.second));
    is_x = 1;
}

void MainWindow::on_pushButton_round_bracket_L_clicked()
{
    QString all_numbers;
    if (ui->result->text() == '0') {
        ui->result->setText("");
        is_sign = 0;
    }
    if (is_sign == 0) {
        all_numbers = (ui->result->text() + "(");
        ui->result->setText(all_numbers);
        count += 1;
    }
    is_x = 1;
}

void MainWindow::on_pushButton_round_bracket_R_clicked()
{
    QString all_numbers;
    if (count > 0 && flag == 0) {
        all_numbers = (ui->result->text() + ")");
        ui->result->setText(all_numbers);
        flag = 0;
        count -= 1;
        min_flag = 0;
        pl_falg = 0;
        is_digit = 1;
        is_r_bracket = 0;
        is_sign = 1;
        is_x = 1;
    }
}

void MainWindow::on_pushButton_minus_clicked()
{
    if (min_flag == 0) {
        if (ui->result->text() == '0') ui->result->setText("");
        ui->result->setText(ui->result->text() + "-");
        flag = 1;
        dot = 0;
        min_flag = 1;
        pl_falg = 1;
        is_digit = 1;
        is_r_bracket = 1;
        is_sign = 0;
        is_x = 1;
    }
}

void MainWindow::on_pushButton_plus_clicked()
{
    if (pl_falg == 0) {
        if (ui->result->text() == '0') ui->result->setText("");
        ui->result->setText(ui->result->text() + "+");
        flag = 1;
        dot = 0;
        min_flag = 1;
        pl_falg = 1;
        is_digit = 1;
        is_r_bracket = 1;
        is_sign = 0;
        is_x = 1;
    }
}

void MainWindow::on_pushButton_graph_clicked()
{
    QString send = ui->result->text();
      ui->widget->clearGraphs();
      if (send != "") {
        QByteArray ba = send.toLocal8Bit();
        if (ui->x2->text().toDouble() >= ui->x1->text().toDouble() ||
            ui->y2->text().toDouble() >= ui->y1->text().toDouble()) {
          QMessageBox::warning(this, "AHTUNG", "Неверный интервал x/y",
                               QMessageBox::Ok);
        } else {
          ui->widget->xAxis->setRange(ui->x2->text().toDouble(),
                                      ui->x1->text().toDouble());
          ui->widget->yAxis->setRange(ui->y2->text().toDouble(),
                                      ui->y1->text().toDouble());
          ui->widget->addGraph();
          QList<double> x;
          QList<double> y;
          for (double i = ui->x2->text().toDouble();
               i < ui->x1->text().toDouble();) {
            x.push_back(i);
            QString buf = ui->result->text();
            QString str_expr =
                buf.replace(QString("x"), QString::number(i, 'f', 3));
            std::string strBuf = str_expr.toLocal8Bit().data();
            s21::Controller ctrl(strBuf);
            std::pair<std::string, double> result = ctrl.calculation();
            y.push_back(result.second);
            i += 0.10;
          }
          ui->widget->graph(0)->addData(x, y);
          ui->widget->setInteraction(QCP::iRangeZoom, true);
          ui->widget->setInteraction(QCP::iRangeDrag, true);
          ui->widget->graph(0)->addData(x, y);
          ui->widget->replot();
        }
      } else {
        QMessageBox::warning(this, "AHTUNG", "Нет данных для построения графика");
      }
}

void MainWindow::on_pushButton_x_clicked()
{
    int loc_falg = 1;
        if (ui->result->text() == '0') {
            ui->result->setText("");
            loc_falg = 0;
        }
        if ((is_digit == 0 || is_r_bracket == 0 || is_x == 0) && loc_falg == 1) {
            ui->result->setText(ui->result->text() + "*x");
        } else {
           ui->result->setText(ui->result->text() + "x");
        }
        flag = 0;
        min_flag = 0;
        pl_falg = 0;
        is_digit = 0;
        is_r_bracket = 1;
        is_sign = 1;
        is_x = 0;
}


void MainWindow::on_pushButton_10_clicked()
{
    deposit window;
    window.setModal(true);
    window.exec();
}



void MainWindow::on_on_pushButton_credit_clicked()
{
    credit window;
    window.setModal(true);
    window.exec();
}

