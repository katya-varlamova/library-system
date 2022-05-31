//
// Created by Екатерина on 22.05.2022.
//

#ifndef SRC_LOGGER_H
#define SRC_LOGGER_H
#include <string>
#include "../Logic/Configuration/FileConfiguration.h"

class Logger {
public:
    static std::shared_ptr<Logger> getInstance()
    {
        static std::shared_ptr<Logger> instance = std::shared_ptr<Logger>(new Logger);
        return instance;
    }
    void log(int level, const char* file, int line, const char* time, const char* msg)
    {
        char *err_str = (char *)malloc(strlen(file) + strlen(time) + strlen(msg) + 40);
        sprintf(err_str, "file: %s, line: %-3d, time: %s, msg: %s\n", file, line, time, msg);
        FILE *f = fopen(filename.c_str(), "a");
        if (level < need_level)
            fprintf(f, "%s", err_str);
        fclose(f);
        free(err_str);
    }
    friend void FileConfiguration::read();
private:
    Logger() = default;

    void init(int need_level, const std::string &filename)
    {
        this->need_level = need_level;
        this->filename = filename;
    }

    int need_level;
    std::string filename;
};


#endif //SRC_LOGGER_H
