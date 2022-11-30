//
// Created by Екатерина on 22.05.2022.
//

#ifndef SRC_FILECONFIGURATION_H
#define SRC_FILECONFIGURATION_H

#include "Configuration.h"
#ifdef __APPLE__
#include <json/value.h>
#include <json/json.h>
#else
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#endif
#include <fstream>
#include <string>
class FileConfiguration : public Configuration{
public:
    explicit FileConfiguration(const std::string &filename)
    {
        this->filename = filename;
    }
    void read() override;

protected:
    std::string filename;

};


#endif //SRC_FILECONFIGURATION_H
