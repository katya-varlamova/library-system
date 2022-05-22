#include "LibrarianMainPresenter.h"
#include "ui_LibrarianMainView.h"

LibrarianMainPresenter::LibrarianMainPresenter(const std::string &login, const std::string &pass, const std::shared_ptr<Model> &model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LibrarianMainPresenter)
{
    ui->setupUi(this);
    this->model = model;
    this->login = login;
    this->pass = pass;
    this->lacc = model->getLibrarianAccount(login, pass);
}
void LibrarianMainPresenter::showEvent(QShowEvent *event)
{
    updateTableBooks();
}
LibrarianMainPresenter::~LibrarianMainPresenter()
{
    delete ui;
}
void LibrarianMainPresenter::updateTableBooks()
{
    std::vector<std::shared_ptr<Book>> books = model->getBooks(login, pass);
    ui->BooksTable->clear();
    ui->BooksTable->setColumnCount(4);
    ui->BooksTable->setHorizontalHeaderItem(0, new QTableWidgetItem("id"));
    ui->BooksTable->setHorizontalHeaderItem(1, new QTableWidgetItem("name"));
    ui->BooksTable->setHorizontalHeaderItem(2, new QTableWidgetItem("author"));
    ui->BooksTable->setHorizontalHeaderItem(3, new QTableWidgetItem("login"));
    int i = 0;
    for (auto &book : books)
    {
        if (book->getLibraryID() == lacc->getLibraryID()) {
            ui->BooksTable->insertRow(i);
            ui->BooksTable->setItem(i, 0, new QTableWidgetItem(QString(std::to_string(book->getID()).c_str())));
            ui->BooksTable->setItem(i, 1, new QTableWidgetItem(QString(book->getName().c_str())));
            ui->BooksTable->setItem(i, 2, new QTableWidgetItem(QString(book->getAuthor().c_str())));
            ui->BooksTable->setItem(i, 3, new QTableWidgetItem(QString(book->getLogin().c_str())));
            i++;
        }

    }
}
void LibrarianMainPresenter::on_GiveButton_clicked()
{
    std::string login_user;
    int book_id;
    login_user = ui->ReaderLoginText->text().toStdString();
    book_id = std::atoi(ui->BookIDText->text().toStdString().c_str());
    model->giveBook(login, pass, login_user, book_id);
    updateTableBooks();
}

void LibrarianMainPresenter::on_AcceptButton_clicked()
{
    std::string login_user;
    int book_id;
    login_user = ui->ReaderLoginText->text().toStdString();
    book_id = std::atoi(ui->BookIDText->text().toStdString().c_str());
    model->returnBook(login, pass, login_user, book_id);
    updateTableBooks();
}

void LibrarianMainPresenter::on_back_clicked()
{
    emit back();
    close();
}
