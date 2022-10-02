#include "RegistrationAdminController.h"
#include "ui_RegistrationAdminView.h"

RegistrationAdminController::RegistrationAdminController(const std::shared_ptr<Model> &model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegistrationAdminController)
{
    this->model = model;
    ui->setupUi(this);
}

RegistrationAdminController::~RegistrationAdminController()
{
    delete ui;
}

void RegistrationAdminController::on_finishButton_clicked()
{
    std::string login = ui->LoginText->text().toStdString();
    std::string pass = ui->PasswordText->text().toStdString();
    std::string name = ui->NameText->text().toStdString();
    std::string role = "admin";
    std::shared_ptr<Account> account = std::shared_ptr<Account>(new Account(login , pass, role, name));
    std::shared_ptr<AdminAccount> adminAccount = std::shared_ptr<AdminAccount>(new AdminAccount(account));
    model->registration(adminAccount);
    this->close();
    emit finish();
}

void RegistrationAdminController::on_backButton_clicked()
{
    this->close();
    emit back();
}
