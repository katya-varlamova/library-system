//
// Created by Екатерина on 03.04.2022.
//

#include "LibraryRepository.h"
std::vector<std::shared_ptr<Library>> LibraryRepository::query(soci::session & session, std::shared_ptr<LibarySpecification> specification)
{
    std::vector<DBLibrary> dblib = specification->exec(session);
    std::vector<std::shared_ptr<Library>> vec;
    LibraryConverter converter;
    for (auto &i : dblib)
        vec.push_back(converter.convert(i));
    return vec;
}
void LibraryRepository::addLibrary(soci::session &session, const std::shared_ptr<Library> &library)
{
    LibraryConverter converter;
    DBLibrary dbLibrary = converter.convert(library);
    bool exist;
    query(session, std::shared_ptr<CheckExistanceLibrary>(new CheckExistanceLibrary(dbLibrary, exist)));
    if (!exist) {
        int id;
        session << "insert into public.Library "
                   "values(default, :name, :address);",
                soci::use(dbLibrary);
        session << "select max(id) "
                   "from public.Library;", soci::into(id);
        library->setID(id);
    }
    else
        library->setID(dbLibrary.id);
}