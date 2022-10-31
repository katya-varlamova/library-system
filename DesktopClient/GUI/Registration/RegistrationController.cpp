#include "RegistrationController.h"
#include "ui_RegistrationView.h"

RegistrationController::RegistrationController(const std::shared_ptr<Model> &model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegistrationController)
{
    this->model = model;
    ui->setupUi(this);
    regAdminController = new RegistrationAdminController(model);
    connect(regAdminController, &RegistrationAdminController::back, this, &RegistrationController::show);
    connect(regAdminController, &RegistrationAdminController::finish, this, &RegistrationController::back);

    regReaderController = new RegistrationReaderController(model);
    connect(regReaderController, &RegistrationReaderController::back, this, &RegistrationController::show);
    connect(regReaderController, &RegistrationReaderController::finish, this, &RegistrationController::back);

    regLibrarianController = new RegistrationLibrarianController(model);
    connect(regLibrarianController, &RegistrationLibrarianController::back, this, &RegistrationController::show);
    connect(regLibrarianController, &RegistrationLibrarianController::finish, this, &RegistrationController::back);
}

RegistrationController::~RegistrationController()
{
    delete ui;
}

void RegistrationController::on_backButton_clicked()
{
    this->close();
    emit back();
}

void RegistrationController::on_nexButton_clicked()
{
    if (ui->RoleBox->currentText() == "Administrator")
    {
        regAdminController->show();
        this->close();
    }
    if (ui->RoleBox->currentText() == "Reader")
    {
        regReaderController->show();
        this->close();
    }
    if (ui->RoleBox->currentText() == "Librarian")
    {
        regLibrarianController->show();
        this->close();
    }
}
