#include "LoginViewController.h"
#include "../../ui_LoginView.h"

LoginViewController::LoginViewController(const std::shared_ptr<Model> &model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginViewController)
{
    ui->setupUi(this);
    this->model = model;
    regController = new RegistrationController(model);
    connect(regController, &RegistrationController::back, this, &LoginViewController::show);
}

LoginViewController::~LoginViewController()
{
    delete ui;
}

void LoginViewController::on_LoginButton_clicked()
{
    std::string login = ui->LoginText->text().toStdString();
    std::string pass = ui->PasswordText->text().toStdString();
    std::shared_ptr<Account> acc = model->login(login, pass);
    if (acc) {
        if (acc->getRole() == "reader") {
            readerMainPresenter = new ReaderMainPresenter(login, pass, model);
            connect(readerMainPresenter, &ReaderMainPresenter::back, this, &LoginViewController::show);
            readerMainPresenter->show();
            this->close();
        }
        if (acc->getRole() == "admin") {
            adminMainPresenter = new AdminMainPresenter(login, pass, model);
            connect(adminMainPresenter, &AdminMainPresenter::back, this, &LoginViewController::show);
            adminMainPresenter->show();
            this->close();
        }
        if (acc->getRole() == "librarian") {
            librarianMainPresenter = new LibrarianMainPresenter(login, pass, model);
            connect(librarianMainPresenter, &LibrarianMainPresenter::back, this, &LoginViewController::show);
            librarianMainPresenter->show();
            this->close();
        }
    }
}

void LoginViewController::on_RegistrationButton_clicked()
{
    regController->show();
    this->close();
}
