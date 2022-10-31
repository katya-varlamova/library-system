#ifndef REGISTRATIONREADERCONTROLLER_H
#define REGISTRATIONREADERCONTROLLER_H

#include <QMainWindow>
#include "../../../Model/Model.h"

namespace Ui {
class RegistrationReaderController;
}

class RegistrationReaderController : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrationReaderController(const std::shared_ptr<Model> &model, QWidget *parent = nullptr);
    ~RegistrationReaderController();
signals:
    void back();
    void finish();
private slots:
    void on_backButton_clicked();

    void on_finishButton_clicked();

private:
    Ui::RegistrationReaderController *ui;
    std::shared_ptr<Model> model;
};

#endif // REGISTRATIONREADERCONTROLLER_H
