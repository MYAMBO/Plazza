/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** main
*/

#include "Core.hpp"
#include "Logger.hpp"
#include "Parsing.hpp"

#include <iostream>

int main(int argc, char **argv)
{
    try {
        Parsing parsing(argv, argc);
        Core restaurante(parsing.getNbCookNumber(), parsing.getRegenerateTime(), parsing.getCookTime());
    
        Debug::ClearLogFile();
        restaurante.parse();
    } catch (const Parsing::ParsingError &ex) {
        ex.what();
        std::cout << std::endl;
        Parsing::help();
        return 84;
    }
    return 0;
}
