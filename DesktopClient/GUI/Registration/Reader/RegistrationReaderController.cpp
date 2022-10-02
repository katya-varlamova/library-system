#include "RegistrationReaderController.h"
#include "ui_RegistrationReaderView.h"
#include "../../../Model/Entities/Account/ReaderAccount.h"

RegistrationReaderController::RegistrationReaderController(const std::shared_ptr<Model> &model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegistrationReaderController)
{
    this->model = model;
    ui->setupUi(this);
}

RegistrationReaderController::~RegistrationReaderController()
{
    delete ui;
}

void RegistrationReaderController::on_finishButton_clicked()
{
    std::string login = ui->LoginText->text().toStdString();
    std::string pass = ui->PasswordText->text().toStdString();
    std::string name = ui->NameText->text().toStdString();
    std::string role = "reader";
    std::string phone = ui->PhoneText->text().toStdString();
    std::shared_ptr<Account> account = std::shared_ptr<Account>(new Account(login , pass, role, name));
    std::shared_ptr<ReaderAccount> readerAccount = std::shared_ptr<ReaderAccount>(new ReaderAccount(account, phone));
    model->registration(readerAccount);
    this->close();
    emit finish();
}

void RegistrationReaderController::on_backButton_clicked()
{
    this->close();
    emit back();
}
