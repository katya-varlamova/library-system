#ifndef LOGINVIEWCONTROLLER_H
#define LOGINVIEWCONTROLLER_H

#include <QMainWindow>
#include "../Registration/RegistrationController.h"
#include "../Main/Reader/ReaderMainPresenter.h"
#include "../Main/Admin/AdminMainPresenter.h"
#include "../Main/Librarain/LibrarianMainPresenter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginViewController; }
QT_END_NAMESPACE

class LoginViewController : public QMainWindow
{
    Q_OBJECT

public:
    LoginViewController(const std::shared_ptr<Model> &model, QWidget *parent = nullptr);
    ~LoginViewController();

private slots:
    void on_LoginButton_clicked();

    void on_RegistrationButton_clicked();

private:
    Ui::LoginViewController *ui;
    RegistrationController *regController;
    ReaderMainPresenter *readerMainPresenter;
    AdminMainPresenter *adminMainPresenter;
    LibrarianMainPresenter *librarianMainPresenter;
    std::shared_ptr<Model> model;
};
#endif // LOGINVIEWCONTROLLER_H
