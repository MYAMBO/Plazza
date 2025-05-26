/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Logger
*/

#include "Logger.hpp"


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


Logger::Logger()
    : _logFilePath("log.txt")
{
    createLogFile();
}

Logger::~Logger()
{
}


/************************************************************
**               >>>>   MEMBER FUNCTIONS   <<<<            **
************************************************************/

void Logger::logCurrentTime() const
{
    std::ofstream os(_logFilePath, std::ios::app);

    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    os << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << std::endl;
}

bool Logger::log(const std::string& message)
{
    if (message.empty()) {
        std::cerr << "Erreur : Message vide fourni au logger" << std::endl;
        return false;
    }

    bool fileExists = logFileExists();
    if (!fileExists && !createLogFile()) {
        std::cerr << "Erreur : Impossible de créer le fichier log : " << _logFilePath << std::endl;
        return false;
    }
    if (!logFileIsWritable()) {
        std::cerr << "Erreur : Le fichier " << _logFilePath << " n'est pas accessible en écriture" << std::endl;
        return false;
    }

    std::ofstream logFile(_logFilePath, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier log : " << _logFilePath << std::endl;
        return false;
    }

    logFile << message;

    logFile.flush();
    logFile.close();

    if (logFile.fail())
        std::cerr << "Error : Problème lors de la fermeture du fichier log" << std::endl;
    return true;
}

bool Logger::logFileExists() const
{
    return std::filesystem::exists(_logFilePath);
}


bool Logger::logFileIsWritable() const
{
    std::error_code ec;
    auto perms = std::filesystem::status(_logFilePath, ec).permissions();

    if (ec) {
        std::cerr << "Erreur : Impossible de vérifier les permissions du fichier : " << ec.message() << std::endl;
        return false;
    }
    return (perms & std::filesystem::perms::owner_write) != std::filesystem::perms::none
        || (perms & std::filesystem::perms::group_write) != std::filesystem::perms::none
        || (perms & std::filesystem::perms::others_write) != std::filesystem::perms::none;
}

bool Logger::createLogFile()
{
    if (logFileExists())
        return true;

    std::ofstream logFile(_logFilePath);

    if (!logFile.is_open()) {
        std::cerr << "Erreur : Impossible de créer le fichier log : " << _logFilePath << std::endl;
        return false;
    }
    logFile.close();
    return true;
}

/************************************************************
**                  >>>>    SETTERS   <<<<                 **
************************************************************/


void Logger::setLogFile(const std::string& filePath)
{
    _logFilePath = filePath;
}


/************************************************************
**               >>>>   GETTERS   <<<<                     **
************************************************************/


std::string Logger::getLogFile() const
{
    return _logFilePath;
}