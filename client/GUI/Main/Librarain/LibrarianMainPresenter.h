#ifndef LIBRARIANMAINPRESENTER_H
#define LIBRARIANMAINPRESENTER_H

#include <QMainWindow>
#include "../../../Model/Model.h"

namespace Ui {
class LibrarianMainPresenter;
}

class LibrarianMainPresenter : public QMainWindow
{
    Q_OBJECT

public:
    explicit LibrarianMainPresenter(const std::string &login, const std::string &pass, const std::shared_ptr<Model> &model, QWidget *parent = nullptr);
    ~LibrarianMainPresenter();
    void showEvent(QShowEvent *event);
    void updateTableBooks();
signals:
    void back();
private slots:
    void on_back_clicked();

private slots:
    void on_AcceptButton_clicked();

private slots:
    void on_GiveButton_clicked();

private:
    Ui::LibrarianMainPresenter *ui;
    std::shared_ptr<Model> model;
    std::string login, pass;
    std::shared_ptr<LibrarianAccount> lacc;
};

#endif // LIBRARIANMAINPRESENTER_H
