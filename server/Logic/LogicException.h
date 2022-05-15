//
// Created by Екатерина on 04.04.2022.
//

#ifndef SRC_LOGICEXCEPTION_H
#define SRC_LOGICEXCEPTION_H
#include <exception>
#include <string>
#include <string.h>
class LogicException : public std::exception //base_matrix nam
{
public:
    LogicException(const char* file, int line, const char* time, const char* msg)
    {
        this->err_str = new char [strlen(file) + strlen(time) + strlen(msg) + 40];
        sprintf(this->err_str, "file: %s, line: %-3d, time: %s, error: %s", file, line, time, msg);
    }

    virtual const char * what() const noexcept override
    {
        return this->err_str;
    }

protected:
    char * err_str;
};



#endif //SRC_LOGICEXCEPTION_H
