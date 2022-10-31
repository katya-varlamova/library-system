#include "AdminMainPresenter.h"
#include "ui_AdminMainView.h"

AdminMainPresenter::AdminMainPresenter(const std::string &login, const std::string &pass, const std::shared_ptr<Model> &model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminMainPresenter)
{
    ui->setupUi(this);
    this->model = model;
    this->login = login;
    this->pass = pass;
    updateTableLibraries();
    updateTableBooks();
}
void AdminMainPresenter::showEvent(QShowEvent *event)
{
    updateTableLibraries();
    updateTableBooks();
}
void AdminMainPresenter::updateTableLibraries()
{
    std::vector<std::shared_ptr<Library>> libs = model->getLibraries(login, pass);
    ui->LibraryTable->clear();
    ui->LibraryTable->setColumnCount(3);
    ui->LibraryTable->setHorizontalHeaderItem(0, new QTableWidgetItem("id"));
    ui->LibraryTable->setHorizontalHeaderItem(1, new QTableWidgetItem("library name"));
    ui->LibraryTable->setHorizontalHeaderItem(2, new QTableWidgetItem("library address"));

    int i = 0;
    for (auto &lib : libs)
    {
        ui->LibraryTable->insertRow(i);
        ui->LibraryTable->setItem(i, 0, new QTableWidgetItem(QString(std::to_string(lib->getID()).c_str())));
        ui->LibraryTable->setItem(i, 1, new QTableWidgetItem(QString(lib->getName().c_str())));
        ui->LibraryTable->setItem(i, 2, new QTableWidgetItem(QString(lib->getAddress().c_str())));
        i++;
    }
}
void AdminMainPresenter::updateTableBooks()
{
    std::vector<std::shared_ptr<Book>> books = model->getBooks(login, pass);
    ui->BooksTable->clear();
    ui->BooksTable->setColumnCount(5);
    ui->BooksTable->setHorizontalHeaderItem(0, new QTableWidgetItem("id"));
    ui->BooksTable->setHorizontalHeaderItem(1, new QTableWidgetItem("name"));
    ui->BooksTable->setHorizontalHeaderItem(2, new QTableWidgetItem("author"));
    ui->BooksTable->setHorizontalHeaderItem(3, new QTableWidgetItem("library id"));
    ui->BooksTable->setHorizontalHeaderItem(4, new QTableWidgetItem("login"));
    int i = 0;
    for (auto &book : books)
    {
        ui->BooksTable->insertRow(i);
        ui->BooksTable->setItem(i, 0, new QTableWidgetItem(QString(std::to_string(book->getID()).c_str())));
        ui->BooksTable->setItem(i, 1, new QTableWidgetItem(QString(book->getName().c_str())));
        ui->BooksTable->setItem(i, 2, new QTableWidgetItem(QString(book->getAuthor().c_str())));
        ui->BooksTable->setItem(i, 3, new QTableWidgetItem(QString(std::to_string(book->getLibraryID()).c_str())));
        ui->BooksTable->setItem(i, 4, new QTableWidgetItem(QString(book->getLogin().c_str())));
        i++;
    }
}
AdminMainPresenter::~AdminMainPresenter()
{
    delete ui;
}

void AdminMainPresenter::on_DeleteLibraryButton_clicked()
{
    int id = ui->LibraryIDText->text().toInt();
    model->deleteLibrary(login, pass, id);
    updateTableLibraries();
}

void AdminMainPresenter::on_UpdateLibraryButton_clicked()
{
    std::string name, address;
    name = ui->LibraryNameText_2->text().toStdString();
    address = ui->AddressText_2->text().toStdString();
    int id = ui->LibraryIDText->text().toInt();
    std::shared_ptr<Library> library = std::shared_ptr<Library>(new Library(name, address));
    library->setID(id);
    model->updateLibrary(login, pass, library);
    updateTableLibraries();
}

void AdminMainPresenter::on_AddLibraryButton_clicked()
{
    std::string name, address;
    name = ui->LibraryNameText_2->text().toStdString();
    address = ui->AddressText_2->text().toStdString();
    std::shared_ptr<Library> library = std::shared_ptr<Library>(new Library(name, address));
    model->addLibrary(login, pass, library);
    updateTableLibraries();
}

void AdminMainPresenter::on_DeleteBookButton_clicked()
{
    int id = ui->BookIDText->text().toInt();
    model->deleteBook(login, pass, id);
    updateTableBooks();
}

void AdminMainPresenter::on_UpdateBookButton_clicked()
{
    std::string name, author;
    name = ui->BookNameText_2->text().toStdString();
    author = ui->AuthorText_2->text().toStdString();
    int id = ui->BookIDText->text().toInt();
    int lib_id = ui->LibraryIDText->text().toInt();
    std::shared_ptr<Book> book = std::shared_ptr<Book>(new Book(name, author, lib_id));
    book->setID(id);
    model->updateBook(login, pass, book);
    updateTableBooks();
}

void AdminMainPresenter::on_AddBookButton_clicked()
{
    std::string name, author;
    name = ui->BookNameText_2->text().toStdString();
    author = ui->AuthorText_2->text().toStdString();
    int lib_id = ui->LibraryIDText->text().toInt();
    std::shared_ptr<Book> book = std::shared_ptr<Book>(new Book(name, author, lib_id));
    model->addBook(login, pass, book);
    updateTableBooks();
}

void AdminMainPresenter::on_back_clicked()
{
    emit back();
    close();
}
