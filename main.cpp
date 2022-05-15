//#include <iostream>
//#include <libpq-fe.h>
//#include <soci/soci.h>
#include "Database/DataAccessFacade/PostgresDataAccessFacade.h"
#include "Database/DataAccessFacade/Commands/RegisterCommand/RegisterAdminCommand.h"
#include "Logic/DataAccessManager/DataAccessManager.h"
#include "Database/DataAccessFacade/Commands/AddBooksCommand/AddBooksCommand.h"
//
//
//void add_new_book(std::vector<std::shared_ptr<Book>> &books, std::string name, std::string author,
//                  std::string lname, std::string address)
//{
//    std::shared_ptr<Library> library = std::shared_ptr<Library>(new Library(lname, address));
//    std::shared_ptr<Book> book = std::shared_ptr<Book>(new Book(name, author, library));
//    books.push_back(book);
//}
//int main()
//{
//    DataAccessManager manager;
//    manager.connect();
//    //manager.create();
////    manager.registration(std::shared_ptr<Account>(new Account("admin",
////                                                              "admin",
////                                                              "admin",
////                                                              "admin")));
////    manager.registration(std::shared_ptr<Account>(new Account("katya_varlamova",
////                                                                          "12345",
////                                                                          "reader",
////                                                                          "Ekaterina")));
//
//
//    std::vector<std::shared_ptr<Book>> books;
////    add_new_book(books, "alie parusa", "grin", "library", "ivana franko");
////    add_new_book(books, "revisor", "gogol", "library", "ivana franko");
////    add_new_book(books, "mertvie dushi", "gogol", "library", "ivana franko");
////    manager.exec(std::shared_ptr<Command>(new AddBooksCommand(books)), "admin", "admin");
//
//    books.clear();
//    manager.exec(std::shared_ptr<Command>(new GetFreeBooksByNameCommand(books, "mertvie dushi")), "katya_varlamova","12345" );
//    for (auto &book : books)
//        std::cout << book->getName() << book->getAuthor() << book->getLibrary()->getAddress() << std::endl;
//
//    manager.disconnect();
//
//}

#include "./Logic/Server/Controller/ServerController.h"
#include "./Logic/Server/ServerSettings/ServerSettings.h"

#include "oatpp/network/Server.hpp"

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

    server.run();

}

/**
 *  main
 */
//manager->create();
std::shared_ptr<DataAccessManager> ServerController::manager = std::shared_ptr<DataAccessManager>(new DataAccessManager);
int main(int argc, const char * argv[]) {

    oatpp::base::Environment::init();
    //std::shared_ptr<DataAccessManager> manager = std::shared_ptr<DataAccessManager>(new DataAccessManager());
    ServerController::manager->connect();
    ServerController::manager->del();
    ServerController::manager->create();
//    ServerController::manager->registration(std::shared_ptr<AdminAccount>(new AdminAccount(std::shared_ptr<Account>(new Account("admin",
//                                                              "admin",
//                                                              "admin",
//                                                              "admin")))));
//    ServerController::manager->registration(std::shared_ptr<ReaderAccount>(new ReaderAccount(std::shared_ptr<Account>(new Account("katya_varlamova",
//                                                                          "12345",
//                                                                          "reader",
//                                                                          "Ekaterina")), "89961008307")));
    run();
    ServerController::manager->disconnect();

    /* Print how much objects were created during app running, and what have left-probably leaked */
    /* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
    std::cout << "\nEnvironment:\n";
    std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
    std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";

    oatpp::base::Environment::destroy();

    return 0;
}