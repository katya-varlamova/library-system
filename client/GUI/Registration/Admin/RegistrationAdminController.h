#ifndef REGISTRATIONADMINCONTROLLER_H
#define REGISTRATIONADMINCONTROLLER_H

#include <QMainWindow>
#include "../../../Model/Model.h"

namespace Ui {
class RegistrationAdminController;
}

class RegistrationAdminController : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrationAdminController(const std::shared_ptr<Model> &model, QWidget *parent = nullptr);
    ~RegistrationAdminController();
signals:
    void back();
    void finish();
private slots:
    void on_finishButton_clicked();

    void on_backButton_clicked();

private:
    Ui::RegistrationAdminController *ui;
    std::shared_ptr<Model> model;
};

#endif // REGISTRATIONADMINCONTROLLER_H
