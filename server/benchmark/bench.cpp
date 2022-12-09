//
// Created by Екатерина on 04.12.2022.
//
#include <stdlib.h>
#include <stdio.h>
#include <DataAccessFacade/Commands/BookCommands/GetBooksByLoginCommand.h>
#include "../Database/SqlIoc/IocRepository.h"
#include "../Logic/Configuration/Configuration.h"
#include "../Logic/Configuration/FileConfiguration.h"
#include "../Database/SqlIoc/SqlIoc.h"
#include "../Database/DataAccessFacade/DataAccessFacade.h"
#include "../Database/DataAccessFacade/Commands/LibraryCommands/GetlibrariesCommand.h"

std::shared_ptr<IIocRepository> preapre(const char *fn)
{
    std::shared_ptr<Configuration> configuration = std::shared_ptr<Configuration>(new FileConfiguration(fn));
    configuration->read();
    std::shared_ptr<IIocRepository> ioc = std::shared_ptr<IIocRepository>(new SqlIocRepositories(configuration));
    return ioc;
}
int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;
    auto ioc = preapre(argv[1]);
    std::vector<std::shared_ptr<Library>> libs;

    std::vector<std::shared_ptr<LibraryFilter>> filters;
    printf("name,count,num,value\n");
    filters = {std::shared_ptr<LibraryFilter>(new ByLibraryNameFilter("ln1"))};
    GetlibrariesCommand getByName1Command = GetlibrariesCommand(ioc->getLibraryRepository(),libs, filters);

    filters = {std::shared_ptr<LibraryFilter>(new ByLibraryNameFilter("ln10"))};
    GetlibrariesCommand getByName10Command = GetlibrariesCommand(ioc->getLibraryRepository(),libs, filters);

    filters = {std::shared_ptr<LibraryFilter>(new ByLibraryNameFilter("ln100"))};
    GetlibrariesCommand getByName100Command = GetlibrariesCommand(ioc->getLibraryRepository(),libs, filters);

    filters = {std::shared_ptr<LibraryFilter>(new ByLibraryNameFilter("ln500"))};
    GetlibrariesCommand getByName500Command = GetlibrariesCommand(ioc->getLibraryRepository(),libs, filters);

    filters = {std::shared_ptr<LibraryFilter>(new ByLibraryNameFilter("ln1000"))};
    GetlibrariesCommand getByName1000Command = GetlibrariesCommand(ioc->getLibraryRepository(),libs, filters);

    std::vector<std::shared_ptr<Book>> books;
    std::vector<std::shared_ptr<Filter>> bfilters;

    bfilters = {std::shared_ptr<Filter>(new ByLibraryNameFilter("ln1"))};
    GetBooksByLoginCommand getBooksByLibName1Command = GetBooksByLoginCommand(ioc->getBookRepository(), books, bfilters);

    bfilters = {std::shared_ptr<Filter>(new ByLibraryNameFilter("ln10"))};
    GetBooksByLoginCommand getBooksByLibName10Command = GetBooksByLoginCommand(ioc->getBookRepository(), books, bfilters);

    bfilters = {std::shared_ptr<Filter>(new ByLibraryNameFilter("ln100"))};
    GetBooksByLoginCommand getBooksByLibName100Command = GetBooksByLoginCommand(ioc->getBookRepository(), books, bfilters);

    bfilters = {std::shared_ptr<Filter>(new ByLibraryNameFilter("ln500"))};
    GetBooksByLoginCommand getBooksByLibName500Command = GetBooksByLoginCommand(ioc->getBookRepository(), books, bfilters);

    bfilters = {std::shared_ptr<Filter>(new ByLibraryNameFilter("ln1000"))};
    GetBooksByLoginCommand getBooksByLibName1000Command = GetBooksByLoginCommand(ioc->getBookRepository(), books, bfilters);

    DataAccessFacade facade = DataAccessFacade(ioc->getConnectionPool());


    facade.connectDB();
    for (int i = 0; i < 100; i++) {
        printf("nojoin,1,%d,", i);
        facade.execute(getByName1Command, "reader");
        printf("\n");

        printf("nojoin,10,%d,", i);
        facade.execute(getByName10Command, "reader");
        printf("\n");

        printf("nojoin,100,%d,", i);
        facade.execute(getByName100Command, "reader");
        printf("\n");

        printf("nojoin,500,%d,", i);
        facade.execute(getByName500Command, "reader");
        printf("\n");

        printf("nojoin,1000,%d,", i);
        facade.execute(getByName1000Command, "reader");
        printf("\n");
    }

    for (int i = 100; i < 200; i++) {
        printf("join,1,%d,", i);
        facade.execute(getBooksByLibName1Command, "reader");
        printf("\n");

        printf("join,10,%d,", i);
        facade.execute(getBooksByLibName10Command, "reader");
        printf("\n");

        printf("join,100,%d,", i);
        facade.execute(getBooksByLibName100Command, "reader");
        printf("\n");

        printf("join,500,%d,", i);
        facade.execute(getBooksByLibName500Command, "reader");
        printf("\n");

        printf("join,1000,%d,", i);
        facade.execute(getBooksByLibName1000Command, "reader");
        printf("\n");
    }
    facade.disconnectDB();

}