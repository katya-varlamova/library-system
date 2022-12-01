//#include "Logic/Server/ServerSettings/IocRepositories.h"
#include "DataAccessFacade/DataAccessFacade.h"
#include "DataAccessFacade/Commands/AccountCommands/RegisterCommand/RegisterAdminCommand.h"
#include "../Logic/DataAccessManager/DataAccessManagerRest.h"
#include "DataAccessFacade/Commands/BookCommands/AddBooksCommand.h"
#include "../Logic/Server/Controller/ServerControllerRestApi.h"
#include "../Logic/Server/ServerSettings/ServerSettings.h"
#include "oatpp/network/Server.hpp"
#include "SqlIoc/SqlIoc.h"
#include "../Logic/Configuration/FileConfiguration.h"
#include "../Logger/Logger.h"
#include <iostream>
#include "oatpp-swagger/AsyncController.hpp"
#include <soci/postgresql/soci-postgresql.h>
#include "oatpp-libressl/Callbacks.hpp"
#include <csignal>
/**
 *  run() method.
 *  1) set Environment components.
 *  2) add ApiController's endpoints to router
 *  3) run server
 */
void run() {
    /* set lockingCallback for libressl */
    oatpp::libressl::Callbacks::setDefaultCallbacks();

    /* ignore SIGPIPE */
#if !(defined(WIN32) || defined(_WIN32))
    std::signal(SIGPIPE, SIG_IGN);
#endif

    ServerSettings components; // Create scope Environment components
    /* create ApiControllers and add endpoints to router */
    auto router = components.httpRouter.getObject();

    router->addController(oatpp::swagger::AsyncController::createShared(ServerControllerRestApi::createShared()->getEndpoints()));
    router->addController(ServerControllerRestApi::createShared());



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
std::shared_ptr<IIocRepository> ServerControllerRestApi::ioc = std::shared_ptr<IIocRepository>(new SqlIocRepositories(configuration));
std::shared_ptr<DataAccessManagerRest> ServerControllerRestApi::manager = std::shared_ptr<DataAccessManagerRest>(new DataAccessManagerRest(ioc));
int main(int argc, const char * argv[]) {
    oatpp::base::Environment::init();
    ServerControllerRestApi::manager->connect();
//    ServerController::manager->registration(std::shared_ptr<AdminAccount>(new AdminAccount(std::shared_ptr<Account>(new Account("admin",
//                                                              "admin",
//                                                              "admin",
//                                                              "admin")))));

    run();
    ServerControllerRestApi::manager->disconnect();
    std::cout << "\nEnvironment:\n";
    std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
    std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";

    oatpp::base::Environment::destroy();

    return 0;
}