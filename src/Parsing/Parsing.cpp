/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Parsing
*/

#include <iostream>

#include "Parsing.hpp"


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


Parsing::Parsing(char **argv, int argc)
{
    if (argc < 4) {
        throw ParsingError("not enough arguments provided");
    }
    for (int i = 0; argv[i] != nullptr; i++) {
        _arguments.push_back(argv[i]);
    }
    if (std::atof(_arguments[1].c_str()) <= 0
        || !isOnlyInt(_arguments[1])
        || _arguments[2].find('.') != std::string::npos
        || !isOnlyInt(_arguments[2])
        || std::atoi(_arguments[2].c_str()) <= 0
        || _arguments[3].find('.') != std::string::npos
        || !isOnlyInt(_arguments[3])
        || std::atoi(_arguments[3].c_str()) <= 0) {
        throw ParsingError("invalid arguments provided");
    }
    
    _cookTime = static_cast<int>(std::atof(_arguments[1].c_str()) * 1000);
    _nbCookNumber = std::atoi(_arguments[2].c_str());
    _regenerateTime = std::atoi(_arguments[3].c_str());
}

Parsing::~Parsing()
{
}


/************************************************************
**               >>>>   MEMBER FUNCTIONS   <<<<            **
************************************************************/

Parsing::ParsingError::ParsingError(const std::string &message)
    : std::exception(), _message(message)
{
}

const char *Parsing::ParsingError::what() const noexcept
{
    return _message.c_str();
}

bool Parsing::isOnlyInt(std::string str) const
{
    for (std::size_t i = 0; i < str.length(); i++) {
        if (!isdigit(str[i]) && str[i] != '.') {
            return false;
        }
    }
    return true;
}

void Parsing::help()
{
    std::cout << "Usage: ./plazza [cook time] [number of cooks] [regenerate time]" << std::endl;
    std::cout << "Example: ./plazza 0.5 5 10000" << std::endl;
    std::cout << "  cook time: multiplicator for a cook to prepare a pizza" << std::endl;
    std::cout << "  number of cooks: number of cooks available in each kitchen" << std::endl;
    std::cout << "  regenerate time: time in milliseconds to regenerate the stock" << std::endl;
}

int Parsing::getCookTime() const
{
    return _cookTime;
}

int Parsing::getNbCookNumber() const
{
    return _nbCookNumber;
}

int Parsing::getRegenerateTime() const
{
    return _regenerateTime;
}