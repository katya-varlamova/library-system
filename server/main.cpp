#include "Logic/Server/ServerSettings/IocRepositories.h"
#include "Database/DataAccessFacade/DataAccessFacade.h"
#include "Database/DataAccessFacade/Commands/RegisterCommand/RegisterAdminCommand.h"
#include "Logic/DataAccessManager/DataAccessManager.h"
#include "Database/DataAccessFacade/Commands/AddBooksCommand/AddBooksCommand.h"
#include "./Logic/Server/Controller/ServerController.h"
#include "./Logic/Server/ServerSettings/ServerSettings.h"
#include "oatpp/network/Server.hpp"
#include "Configuration/FileConfiguration.h"
#include "Logger/Logger.h"
#include <iostream>

/**
 *  run() method.
 *  1) set Environment components.
 *  2) add ApiController's endpoints to router
 *  3) run server
 */
void run() {

    ServerSettings components; // Create scope Environment components
    /* create ApiControllers and add endpoints to router */
    auto router = components.httpRouter.getObject();


    router->addController(ServerController::createShared());


    /* create server */
    oatpp::network::Server server(components.serverConnectionProvider.getObject(),
                                  components.serverConnectionHandler.getObject());

    OATPP_LOGD("Server", "Running on port %s...", components.serverConnectionProvider.getObject()->getProperty("port").toString()->c_str());
    Logger::getInstance()->log(0, __FILE__, __LINE__, __TIME__,"Server started!");
    server.run();


}

/**
 *  main
 */
//manager->create();
std::shared_ptr<Configuration> configuration = std::shared_ptr<Configuration>(new FileConfiguration("config.json"));
std::shared_ptr<IIocRepository> ServerController::ioc = std::shared_ptr<IIocRepository>(new PGIocRepositories(configuration));
std::shared_ptr<DataAccessManager> ServerController::manager = std::shared_ptr<DataAccessManager>(new DataAccessManager(ioc));
int main(int argc, const char * argv[]) {
    oatpp::base::Environment::init();
    ServerController::manager->connect();
    ServerController::manager->registration(std::shared_ptr<AdminAccount>(new AdminAccount(std::shared_ptr<Account>(new Account("admin",
                                                              "admin",
                                                              "admin",
                                                              "admin")))));

    run();
    ServerController::manager->disconnect();
    std::cout << "\nEnvironment:\n";
    std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
    std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";

    oatpp::base::Environment::destroy();

    return 0;
}