#ifndef READERMAINPRESENTER_H
#define READERMAINPRESENTER_H

#include <QMainWindow>
#include "../../../Model/Model.h"

namespace Ui {
class ReaderMainPresenter;
}

class ReaderMainPresenter : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReaderMainPresenter(const std::string &login, const std::string &pass, const std::shared_ptr<Model> &model, QWidget *parent = nullptr);
    ~ReaderMainPresenter();
    void showEvent(QShowEvent *event);
    void updateTableBooks(const std::string &name, const std::string &author, const std::string &lib_name, const std::string &address, bool l);
signals:
    void back();
private slots:
    void on_back_clicked();
    void on_FindButton_clicked();
    void on_MyBooksButton_clicked();
    void on_FreeBooksButton_clicked();
    void on_ByAddressButton_stateChanged(int arg1);
    void on_ByAuthorButton_stateChanged(int arg1);
    void on_ByNameLibraryButton_stateChanged(int arg1);
    void on_ByNameBookButton_stateChanged(int arg1);

private:
    Ui::ReaderMainPresenter *ui;
    std::shared_ptr<Model> model;
    std::string login, pass;
    bool bn, ln, ba, la, free;
};

#endif // READERMAINPRESENTER_H
