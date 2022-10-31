#ifndef ADMINMAINPRESENTER_H
#define ADMINMAINPRESENTER_H

#include <QMainWindow>
#include "../../../Model/Model.h"

namespace Ui {
class AdminMainPresenter;
}

class AdminMainPresenter : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminMainPresenter(const std::string &login, const std::string &pass,const std::shared_ptr<Model> &model, QWidget *parent = nullptr);
    ~AdminMainPresenter();
    void showEvent(QShowEvent *event);
signals:
    void back();
private slots:
    void on_back_clicked();

private slots:
    void on_AddBookButton_clicked();

    void on_UpdateBookButton_clicked();

    void on_DeleteBookButton_clicked();

    void on_AddLibraryButton_clicked();

    void on_UpdateLibraryButton_clicked();

    void on_DeleteLibraryButton_clicked();

private:
    void updateTableLibraries();
    void updateTableBooks();
    Ui::AdminMainPresenter *ui;
    std::shared_ptr<Model> model;
    std::string login, pass;
};

#endif // ADMINMAINPRESENTER_H
