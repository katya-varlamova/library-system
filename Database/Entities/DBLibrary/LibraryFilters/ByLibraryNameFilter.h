//
// Created by Екатерина on 08.05.2022.
//

#ifndef SRC_BYLIBRARYNAMEFILTER_H
#define SRC_BYLIBRARYNAMEFILTER_H
class ByLibraryNameFilter : public LibraryFilter{
public:
    ByLibraryNameFilter(const std::string &name)
    {
        this->name = name;
    }
    std::string getEqualClause() override
    {
        return "Library.name = '" + name + "'";
    }
private:
    std::string name;
};
#endif //SRC_BYLIBRARYNAMEFILTER_H
