#ifndef REGISTRATIONCONTROLLER_H
#define REGISTRATIONCONTROLLER_H

#include <QMainWindow>
#include "Admin/RegistrationAdminController.h"
#include "Reader/RegistrationReaderController.h"
#include "Librarian/RegistrationLibrarianController.h"
#include "../../Model/Model.h"
namespace Ui {
class RegistrationController;
}

class RegistrationController : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrationController(const std::shared_ptr<Model> &model, QWidget *parent = nullptr);
    ~RegistrationController();
signals:
    void back();
private slots:
    void on_backButton_clicked();

    void on_nexButton_clicked();

private:
    RegistrationAdminController *regAdminController;
    RegistrationReaderController *regReaderController;
    RegistrationLibrarianController *regLibrarianController;
    Ui::RegistrationController *ui;
    std::shared_ptr<Model> model;
};

#endif // REGISTRATIONCONTROLLER_H
