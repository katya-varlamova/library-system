//
// Created by Екатерина on 03.04.2022.
//

#include "LibraryRepository.h"
#include "../DBBook/BookSpecifications/GetBooks.h"

std::vector<std::shared_ptr<Library>> LibraryRepository::query(std::shared_ptr<Session<>> session, std::shared_ptr<LibarySpecification> specification)
{
    std::vector<DBLibrary> dblib = specification->exec(session);
    std::vector<std::shared_ptr<Library>> vec;
    LibraryConverter converter;
    for (auto &i : dblib)
        vec.push_back(converter.convert(i));
    return vec;
}
int LibraryRepository::addLibrary(std::shared_ptr<Session<>> session, const std::shared_ptr<Library> &library)
{
    LibraryConverter converter;
    DBLibrary dbLibrary = converter.convert(library);
    int id;
    session->exec("insert into Library (name, address) "
                            "values('" + dbLibrary.name + "', '" + dbLibrary.address + "');");
    session->exec_into("select max(id) "
                   "from Library;", id);
    library->setID(id);

    return library->getID();
}
void LibraryRepository::updateLibrary(std::shared_ptr<Session<>> session, std::shared_ptr<Library> library)
{
    LibraryConverter converter;
    DBLibrary dblib = converter.convert(library);

    std::string q = "update Library set name = '" + dblib.name + "', address = '" + dblib.address + "' "
                    "where id = " + std::to_string(library->getID());
    session->exec(q);
}
void LibraryRepository::removeLibrary(std::shared_ptr<Session<>> session, int id)
{
    std::string q = "delete from Library "
                    "where id = " + std::to_string(id);
    session->exec(q);
}