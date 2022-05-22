//
// Created by Екатерина on 03.04.2022.
//

#include "LibraryRepository.h"
#include "../DBBook/BookRepository.h"
#include "../DBBook/BookSpecifications/GetBooks.h"

std::vector<std::shared_ptr<Library>> LibraryRepository::query(std::shared_ptr<Session> session, std::shared_ptr<LibarySpecification> specification)
{
    std::vector<DBLibrary> dblib = specification->exec(session);
    std::vector<std::shared_ptr<Library>> vec;
    LibraryConverter converter;
    for (auto &i : dblib)
        vec.push_back(converter.convert(i));
    return vec;
}
int LibraryRepository::addLibrary(std::shared_ptr<Session> session, const std::shared_ptr<Library> &library)
{
    LibraryConverter converter;
    DBLibrary dbLibrary = converter.convert(library);
    std::vector<std::shared_ptr<LibraryFilter>> filters = {
            std::shared_ptr<LibraryFilter>(new ByAddressFilter(dbLibrary.address)),
            std::shared_ptr<LibraryFilter>(new ByLibraryNameFilter(dbLibrary.name))
    };
    std::vector<std::shared_ptr<Library>> libs = query(session, std::shared_ptr<LibarySpecification>(new GetLibrary(filters)));

    if (libs.empty()) {
        int id;
        session->exec_using("insert into public.Library "
                   "values(default, :name, :address);",
                   dbLibrary);
        session->exec_into("select max(id) "
                   "from public.Library;", id);
        library->setID(id);
    }
    else
        library->setID(libs[0]->getID());
    return library->getID();
}
void LibraryRepository::updateLibrary(std::shared_ptr<Session> session, std::shared_ptr<Library> library)
{
    LibraryConverter converter;
    DBLibrary dblib = converter.convert(library);
    std::string q = "update Library set name = :name, address = :address "
                    "where id = " + std::to_string(library->getID());
    session->exec_using(q,
                        dblib);
}
void LibraryRepository::removeLibrary(std::shared_ptr<Session> session, int id)
{
    std::string q = "delete from Library "
                    "where id = " + std::to_string(id);
    session->exec(q);
}