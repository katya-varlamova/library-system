#include "RegistrationLibrarianController.h"
#include "ui_RegistrationLibrarianView.h"

RegistrationLibrarianController::RegistrationLibrarianController(const std::shared_ptr<Model> &model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegistrationLibrarianController)
{
    this->model = model;
    ui->setupUi(this);
}
void RegistrationLibrarianController::showEvent(QShowEvent *event)
{
    loadLibrariesTable();
}
RegistrationLibrarianController::~RegistrationLibrarianController()
{
    delete ui;
}
void RegistrationLibrarianController::loadLibrariesTable()
{
    ui->LibraryBox->clear();
    cur_libs = model->getLibraries("admin", "admin");
    int i = 0;
    for (auto &lib : cur_libs)
    {
        QString s = QString((lib->getName() + " address: " + lib->getAddress()).c_str());
        ui->LibraryBox->insertItem(i, s);
        i++;
    }
}
void RegistrationLibrarianController::on_finishButton_clicked()
{
    std::string login = ui->LoginText->text().toStdString();
    std::string pass = ui->PasswordText->text().toStdString();
    std::string name = ui->NameText->text().toStdString();
    std::string role = "librarian";
    std::shared_ptr<Library> lib = cur_libs[ui->LibraryBox->currentIndex()];
    std::shared_ptr<Account> account = std::shared_ptr<Account>(new Account(login , pass, role, name));
    std::shared_ptr<LibrarianAccount> librarianAccount = std::shared_ptr<LibrarianAccount>(new LibrarianAccount(account, lib->getID()));
    model->registration(librarianAccount);
    this->close();
    emit finish();
}

void RegistrationLibrarianController::on_backButton_clicked()
{
    this->close();
    emit back();
}
