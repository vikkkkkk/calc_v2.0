#include "deposit.h"

#include <QMessageBox>

#include "ui_deposit.h"

deposit::deposit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deposit)
{
    ui->setupUi(this);
    ui->lineEdit_accured_interest->setReadOnly(true);
    ui->lineEdit_tax_ammount->setReadOnly(true);
    ui->lineEdit_deposit_end->setReadOnly(true);
}

deposit::~deposit()
{
    delete ui;
}

void deposit::on_pushButton_credit_clicked()
{
    double deposit_amount = ui->lineEdit_deposit_amount->text().toDouble();
    double deposit_term = ui->lineEdit_deposit_term->text().toDouble();
    double interest_rate = ui->lineEdit_interes_rate->text().toDouble();
    double tax_rate = ui->lineEdit_tax_rate->text().toDouble();
//    double periodicity_of_payments = ui->lineEdit_periodicity_of_payments->text().toDouble();
    double replenishments_sum = ui->lineEdit_replenishments_sum->text().toDouble();
    double replenishments_month = ui->lineEdit_partial_replanishment_month->text().toDouble();
    double partial_withdrawals_sum = ui->lineEdit_withdraw_sum->text().toDouble();
    double partial_withdrawals_month = ui->lineEdit_partial_withdraw_month->text().toDouble();

    bool check = false;
    if (ui->checkBox->isChecked()) {
        check = true;
    }
    s21::Controller cn;
    std::vector<double> rez = cn.DepCalc(check, deposit_term, deposit_amount, interest_rate, tax_rate,
                                         replenishments_month, replenishments_sum,
                                         partial_withdrawals_month, partial_withdrawals_sum);

    ui->lineEdit_accured_interest->setText(QString::number(rez[0]));
    ui->lineEdit_deposit_end->setText(QString::number(rez[1]));
    ui->lineEdit_tax_ammount->setText(QString::number(rez[2]));
}
