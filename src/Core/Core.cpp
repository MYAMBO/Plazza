/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Core
*/

#include "Core.hpp"
#include "Utils.hpp"

Core::Core()
{
    this->_pizzaNameList.emplace("regina");
    this->_pizzaNameList.emplace("fantasia");
    this->_pizzaNameList.emplace("margarita");
    this->_pizzaNameList.emplace("americana");

    this->_pizzaSizeList.emplace("S");
    this->_pizzaSizeList.emplace("M");
    this->_pizzaSizeList.emplace("L");
    this->_pizzaSizeList.emplace("XL");
    this->_pizzaSizeList.emplace("XXL");
}

Core::~Core()
{

}

void Core::handleCommand(std::vector<std::string> wordArray)
{
    if (wordArray.size() != 3) {
        std::cout << "command must be : \"[pizza type] [pizza size] [xn]\" when n is the number of pizza" << std::endl;
        return;
    }
    if (this->_pizzaNameList.find(wordArray[0]) == this->_pizzaNameList.end()) {
        std::cout << "this pizza does not exist" << std::endl;
        return;
    }
    if (this->_pizzaSizeList.find(wordArray[1]) == this->_pizzaSizeList.end()) {
        std::cout << "this size does not exist" << std::endl;
        return;
    }
    std::string strNbWithoutX = wordArray[2].substr(1, wordArray[2].size() - 1);
    if (wordArray[2][0] != 'x' || !Utils::strIsDigit(strNbWithoutX)) {
        std::cout << "number of pizza must be \"xn\" when n is the number of pizza" << std::endl;
        return;
    }
    int nb = std::atoi(strNbWithoutX.c_str());
    if (nb <= 0 || nb >= 100) {
        std::cout << "number of pizza must be a number between 1 and 99" << std::endl;
        return;
    }
    std::cout << "type: " << wordArray[0] << std::endl;
    std::cout << "taille: " << wordArray[1] << std::endl;
    std::cout << "nombre: " << nb << std::endl;
    // handle pizza
}

void Core::parse()
{
    std::string line;
    std::vector<std::string> wordArray;

    std::cout << "> ";
    while (std::getline(std::cin, line)) {
        if (line == "exit")
            break;
        wordArray = Utils::strToWordArray(line, " \t");
        handleCommand(wordArray);
        std::cout << "> ";
    }
    std::cout << "exit" << std::endl;
}
