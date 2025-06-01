/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Core
*/

#include <ostream>
#include <iostream>
#include <algorithm>

#include "Core.hpp"
#include "Utils.hpp"
#include "Regina/ReginaPizza.hpp"
#include "Fantasia/FantasiaPizza.hpp"
#include "Margarita/MargaritaPizza.hpp"
#include "Americana/AmericanaPizza.hpp"

Core::Core(size_t cookNumber, int regenerateTime, int cookTime)
    : _cookNumber(cookNumber), _regenerateTime(regenerateTime), _cookTime(cookTime), _isRunning(true), _kitchenIndex(0)
{
    _pizzaNameList["regina"] = [](std::string size) { return std::make_shared<ReginaPizza>(size); };
    _pizzaNameList["fantasia"] = [](std::string size) { return std::make_shared<FantasiaPizza>(size); };
    _pizzaNameList["margarita"] = [](std::string size) { return std::make_shared<MargaritaPizza>(size); };
    _pizzaNameList["americana"] = [](std::string size) { return std::make_shared<AmericanaPizza>(size); };

    _pizzaSizeList.emplace("S", PizzaSize::S);
    _pizzaSizeList.emplace("M", PizzaSize::M);
    _pizzaSizeList.emplace("L", PizzaSize::L);
    _pizzaSizeList.emplace("XL", PizzaSize::XL);
    _pizzaSizeList.emplace("XXL", PizzaSize::XXL);
}

void Core::spawnKitchen(int index)
{
    std::string fifoPathToKitchen = "/tmp/kitchen_tokitchen_" + std::to_string(index);
    std::string fifoPathToReception = "/tmp/kitchen_toreception_" + std::to_string(index);
    mkfifo(fifoPathToKitchen.c_str(), 0666);
    mkfifo(fifoPathToReception.c_str(), 0666);

    pid_t pid = fork();
    if (pid == 0) {
        KitchenPipe pipeToKitchen(fifoPathToKitchen, false);
        KitchenPipe pipeToReception(fifoPathToReception, true);
        Kitchen kitchen(_cookNumber, _regenerateTime, _cookTime, _isRunning, pipeToKitchen, pipeToReception);
        std::cout << "Here" << std::endl;
        std::exit(0);
    }
    else if (pid > 0) {
        KitchenHandle handle;
        handle.pid = pid;
        handle.fifoPath = fifoPathToKitchen;
        handle.toKitchenPipe = std::make_unique<KitchenPipe>(fifoPathToKitchen, true);
        handle.toReceptionPipe = std::make_unique<KitchenPipe>(fifoPathToReception, false);
        _kitchens.push_back(std::move(handle));
    }
    else
    {
        std::perror("fork error");
    }
}


void Core::handlePizza(std::string type, std::string size, int nb)
{
    for (auto &elt : _kitchens)
    {
        if (elt.isClosed)
            continue;
        elt.toKitchenPipe->operator<<("getAvailable");
        std::string availableCookNumber;
        elt.toReceptionPipe->operator>>(availableCookNumber);
        int availableCookNumberInt = std::stoi(availableCookNumber);
        if (availableCookNumberInt >= nb)
        {
            elt.toKitchenPipe->operator<<("add " + type + " " + size + " " + std::to_string(nb) + "\n");
            nb = 0;
        }
        else
        {
            elt.toKitchenPipe->operator<<("add " + type + " " + size + " " + std::to_string(availableCookNumberInt) + "\n");
            nb = nb - availableCookNumberInt;
        }
    }
    while (nb != 0)
    {
        this->spawnKitchen(_kitchenIndex++);
        this->_kitchens.back().toKitchenPipe->operator<<("getAvailable");
        std::string availableCookNumber;
        this->_kitchens.back().toReceptionPipe->operator>>(availableCookNumber);
        int availableCookNumberInt = std::stoi(availableCookNumber);
        if (availableCookNumberInt >= nb)
        {
            this->_kitchens.back().toKitchenPipe->operator<<("add " + type + " " + size + " " + std::to_string(nb) + "\n");
            nb = 0;
        }
        else
        {
            this->_kitchens.back().toKitchenPipe->operator<<("add " + type + " " + size + " " + std::to_string(availableCookNumberInt) + "\n");
            nb = nb - availableCookNumberInt;
        }
    }

}

void Core::handleCommand(std::vector<std::string> wordArray)
{
    if (wordArray.size() != 3) {
        std::cout << "command must be : \"[pizza type] [pizza size] [xn]\" when n is the number of pizza" << std::endl;
        return;
    }
    std::transform(wordArray[0].begin(), wordArray[0].end(), wordArray[0].begin(), ::tolower);
    if (this->_pizzaNameList.find(wordArray[0]) == this->_pizzaNameList.end()) {
        std::cout << "\"" << wordArray[0] << "\" : this pizza does not exist" << std::endl;
        return;
    }
    if (this->_pizzaSizeList.find(wordArray[1]) == this->_pizzaSizeList.end()) {
        std::cout << "\"" << wordArray[1] << "\" : this size does not exist" << std::endl;
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
    handlePizza(wordArray[0], wordArray[1], nb);
}

void Core::parse()
{
    std::string line;
    std::vector<std::string> wordArray;
    std::vector<std::string> commandList;

    std::cout << "> ";
    while (std::getline(std::cin, line)) {
        for (auto &elt : _kitchens)
        {
            if (elt.isClosed)
                continue;
            elt.toKitchenPipe->operator<<("time");
            std::string time;
            elt.toReceptionPipe->operator>>(time);
            if (stoi(time) >= 5)
            {
                elt.isClosed = true;
                elt.toKitchenPipe->operator<<("close");
            }
        }
        if (line == "exit")
            break;
        if (line == "ingredients") {
            for (auto &elt : _kitchens)
            {
                if (elt.isClosed)
                    continue;
                elt.toKitchenPipe->operator<<("ingredients");
                std::string tmp;
                elt.toReceptionPipe->operator>>(tmp);
                std::cout << "Kitchen " << elt.fifoPath.substr(elt.fifoPath.find_last_of('_')) << std::endl << tmp;
            }
            std::cout << "> ";
            continue;
        }
        commandList = Utils::strToWordArray(line, ";");
        for (auto elt : commandList) {
            wordArray = Utils::strToWordArray(elt, " \t");
            handleCommand(wordArray);
        }
        std::cout << "> ";
    }
    for (auto &elt : _kitchens)
    {
        if (elt.isClosed)
            continue;
        elt.toKitchenPipe->operator<<("close");
    }
    _isRunning = false;
    std::cout << "exit" << std::endl;
}
