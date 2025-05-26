/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Logger
*/

#ifndef LOGGER_HPP_
    #define LOGGER_HPP_
    
    #include <fstream>
    #include <iostream>
    #include <string>
    #include <ctime>
    #include <iomanip>
    #include <sstream>
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