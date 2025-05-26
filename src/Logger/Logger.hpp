/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Logger
*/

#ifndef LOGGER_HPP_
    #define LOGGER_HPP_
    
    #include <ctime>
    #include <string>
    #include <fstream>
    #include <iomanip>
    #include <sstream>
    #include <iostream>
    #include <filesystem>
    
class Logger {
    public:
        Logger();
        ~Logger();
        
        void setLogFile(const std::string& filePath);

        std::string getLogFile() const;

        bool createLogFile();
        bool logFileExists() const;
        void logCurrentTime() const;
        bool logFileIsWritable() const;
        bool log(const std::string& message);
        
    private:
        std::string _logFilePath;
};

#endif