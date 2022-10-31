#ifndef REGISTRATIONLIBRARIANCONTROLLER_H
#define REGISTRATIONLIBRARIANCONTROLLER_H

#include <QMainWindow>
#include "../../../Model/Model.h"

namespace Ui {
class RegistrationLibrarianController;
}

class RegistrationLibrarianController : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrationLibrarianController(const std::shared_ptr<Model> &model, QWidget *parent = nullptr);
    ~RegistrationLibrarianController();
    void showEvent(QShowEvent* event);
signals:
    void back();
    void finish();
private slots:
    void on_backButton_clicked();

    void on_finishButton_clicked();

private:
    void loadLibrariesTable();
    Ui::RegistrationLibrarianController *ui;
    std::shared_ptr<Model> model;
    std::vector<std::shared_ptr<Library>> cur_libs;
};

#endif // REGISTRATIONLIBRARIANCONTROLLER_H
