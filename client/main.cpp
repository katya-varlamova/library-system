#include "GUI/Login/LoginViewController.h"

#include <QApplication>

#include "Model/Client.hpp"
#include "Model/Client.hpp"
#include "oatpp-curl/RequestExecutor.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"
#include "oatpp/network/tcp/client/ConnectionProvider.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include <iostream>
#include "ConsoleUI/ConsolePresenter.h"

int main(int argc, char *argv[])
{
    std::shared_ptr<Model> model = std::shared_ptr<Model>(new Model());
//    ConsolePresenter c(model);
//    c.run();
    QApplication a(argc, argv);
    LoginViewController w(model);
    w.show();
    return a.exec();
}
