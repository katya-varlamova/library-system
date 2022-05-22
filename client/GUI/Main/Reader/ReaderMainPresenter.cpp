#include "ReaderMainPresenter.h"
#include "ui_ReaderMainView.h"

ReaderMainPresenter::ReaderMainPresenter(const std::string &login, const std::string &pass, const std::shared_ptr<Model> &model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReaderMainPresenter)
{
    ui->setupUi(this);
    this->model = model;
    this->login = login;
    this->pass = pass;
    bn = ln = la = ba = false;
    free = true;
}
void ReaderMainPresenter::updateTableBooks(const std::string &name,
                                           const std::string &author,
                                           const std::string &lib_name,
                                           const std::string &address,
                                           bool l)
{
    std::vector<std::shared_ptr<Book>> books = model->getBooks(login, pass, name, author, l, true);
    ui->BooksTable->clear();
    ui->BooksTable->setColumnCount(4);
    ui->BooksTable->setHorizontalHeaderItem(0, new QTableWidgetItem("name"));
    ui->BooksTable->setHorizontalHeaderItem(1, new QTableWidgetItem("author"));
    ui->BooksTable->setHorizontalHeaderItem(2, new QTableWidgetItem("library name"));
    ui->BooksTable->setHorizontalHeaderItem(3, new QTableWidgetItem("library author"));

    int i = 0;
    for (auto &book : books)
    {
        auto libs = model->getLibraries(login, pass, book->getLibraryID(), lib_name, address);
        if (!libs.empty()) {
            ui->BooksTable->insertRow(i);
            ui->BooksTable->setItem(i, 0, new QTableWidgetItem(QString(book->getName().c_str())));
            ui->BooksTable->setItem(i, 1, new QTableWidgetItem(QString(book->getAuthor().c_str())));
            ui->BooksTable->setItem(i, 2, new QTableWidgetItem(QString(libs[0]->getName().c_str())));
            ui->BooksTable->setItem(i, 3, new QTableWidgetItem(QString(libs[0]->getAddress().c_str())));
            i++;
        }

    }
}
ReaderMainPresenter::~ReaderMainPresenter()
{
    delete ui;
}
void ReaderMainPresenter::showEvent(QShowEvent *event)
{
    bn = ln = la = ba = false;
    free = true;
    updateTableBooks("", "", "", "", false);
}
void ReaderMainPresenter::on_ByNameBookButton_stateChanged(int arg1)
{
    bn = !bn;
}

void ReaderMainPresenter::on_ByNameLibraryButton_stateChanged(int arg1)
{
    ln = !ln;
}

void ReaderMainPresenter::on_ByAuthorButton_stateChanged(int arg1)
{
    ba = !ba;
}

void ReaderMainPresenter::on_ByAddressButton_stateChanged(int arg1)
{
    la = !la;
}

void ReaderMainPresenter::on_FreeBooksButton_clicked()
{
    free = true;
}

void ReaderMainPresenter::on_MyBooksButton_clicked()
{
    free = false;
}

void ReaderMainPresenter::on_FindButton_clicked()
{
    std::string name, lib_name, address, author;
    if (ln)
        lib_name = ui->LibraryNameText->text().toStdString();
    if (la)
        address = ui->AddressText->text().toStdString();
    if (bn)
        name = ui->BookNameText->text().toStdString();
    if (ba)
        author = ui->AuthorText->text().toStdString();
    if (free)
        updateTableBooks(name, author, lib_name, address, false);
    else
        updateTableBooks(name, author, lib_name, address, true);
}

void ReaderMainPresenter::on_back_clicked()
{
    emit back();
    close();
}
