#include "credit.h"

#include <QMessageBox>

#include "ui_credit.h"

credit::credit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::credit)
{
    ui->setupUi(this);
    ui->lineEdit_monthly_payment->setReadOnly(true);
    ui->lineEdit_total_payment->setReadOnly(true);
    ui->lineEdit_overpayment->setReadOnly(true);
}

credit::~credit()
{
    delete ui;
}


void credit::on_pushButton_credit_clicked()
{
    double total_credit_amount = ui->lineEdit_total_credit_amount->text().toDouble();
    double interes_rate = ui->lineEdit_interes_rate->text().toDouble();
    double term = ui->lineEdit_term->text().toDouble();

    bool check = false;
    if (ui->radioButton_Annuity->isChecked()) {
        check = true;
    }
    if (ui->radioButton_Differentiated->isChecked()) {
        check = false;
    }
    if (ui->lineEdit_total_credit_amount->text() != "" && ui->lineEdit_interes_rate->text() != "" && ui->lineEdit_term->text() != "") {

        s21::Controller cn;
        std::vector<double> rez = cn.CrCalc(total_credit_amount, term, interes_rate, check);
        if (check) {
            ui->lineEdit_monthly_payment->setText(QString::number(rez[1]));
        } else {
            ui->lineEdit_monthly_payment->setText(QString::number(rez[0]) + "..." + QString::number(rez[1]));
        }
        ui->lineEdit_total_payment->setText(QString::number(rez[2]));
        ui->lineEdit_overpayment->setText(QString::number(rez[3]));
    }

}
