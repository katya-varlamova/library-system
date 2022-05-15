//
// Created by Екатерина on 08.05.2022.
//

#ifndef SRC_BYLIBRARYIDFILTER_H
#define SRC_BYLIBRARYIDFILTER_H
class ByLibraryIDFilter : public LibraryFilter{
public:
    ByLibraryIDFilter(int id)
    {
        this->id = id;
    }
    std::string getEqualClause() override
    {
        return "id = " + std::to_string(id);
    }
private:
    int id;
};
#endif //SRC_BYLIBRARYIDFILTER_H
