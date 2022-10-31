//
// Created by Екатерина on 22.05.2022.
//

#ifndef INTERFACE_CONSOLEVIEW_H
#define INTERFACE_CONSOLEVIEW_H

#include <string>

class ConsoleView {
public:
    void inputString(const char * intro, std::string &s);
    void outputString(std::string s);
    void inputNum(const char * intro, int &n);
};


#endif //INTERFACE_CONSOLEVIEW_H
