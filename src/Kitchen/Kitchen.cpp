/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Kitchen
*/

#include <ctime>
#include <iostream>
#include <ostream>

#include "Logger.hpp"
#include "Kitchen.hpp"

#include "Utils.hpp"
#include "Regina/ReginaPizza.hpp"
#include "Fantasia/FantasiaPizza.hpp"
#include "Margarita/MargaritaPizza.hpp"
#include "Americana/AmericanaPizza.hpp"

Kitchen::Kitchen(std::size_t cookNumber, int regenerateTime, int cookTime, std::atomic<bool>& isRunning,
                 KitchenPipe& toKitchenPipe, KitchenPipe& toReceptionPipe)
    : _regeneratorThread(regenerator, std::ref(_stock), regenerateTime, std::ref(_stockMutex), std::ref(isRunning)),
      _sem(std::counting_semaphore<>(0)), _toKitchenPipe(toKitchenPipe), _toReceptionPipe(toReceptionPipe)
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

    _availableCookNumber = cookNumber;
    _baseCookNumber = cookNumber;
    for (std::size_t i = 0; i < cookNumber; i++)
        _cookThreads.push_back(std::thread(letMeCook, i, std::ref(_stock), cookTime, std::ref(_sem),
                                           std::ref(_pizzaQueue), std::ref(_stockMutex), std::ref(_availableCookNumber),
                                           std::ref(isRunning)));
    std::string command;
    std::chrono::steady_clock::time_point chrono = std::chrono::steady_clock::now();
    while (command != "exit")
    {
        command.clear();
        toKitchenPipe >> command;
        auto wordArray = Utils::strToWordArray(command, " \t\n");
        if (!wordArray.empty() && wordArray[0] == "add")
        {
            std::string type = wordArray[1];
            std::string size = wordArray[2];
            int nb = std::stoi(wordArray[3]);
            for (int i = 0; i < nb; i++)
            {
                auto pizza = _pizzaNameList[type](size);
                this->addInQueue(pizza);
            }
        }
        if (!this->_pizzaQueue.empty())
            chrono = std::chrono::steady_clock::now();
        if (!wordArray.empty() && wordArray[0] == "time")
        {
            toReceptionPipe << std::to_string(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - chrono).count());
        }
        if (!wordArray.empty() && wordArray[0] == "close")
        {
            InfoLog("Kitchen " + toKitchenPipe._path.substr(toKitchenPipe._path.find_last_of('_')) + " closed");
            exit(0);
        }
        if (!wordArray.empty() && wordArray[0] == "ingredients")
        {
            this->printIngredient();
        }
        if (!wordArray.empty() && wordArray[0] == "getAvailable")
        {
            this->getAvailableCookNumber();
        }
    }
}

Kitchen::~Kitchen()
{
    _regeneratorThread.join();
    for (auto& elt : _cookThreads)
        elt.join();
}

void Kitchen::regenerator(Stock& stock, int regenerateTime, std::mutex& stockMutex, std::atomic<bool>& isRunning)
{
    while (isRunning)
    {
        auto end = std::chrono::steady_clock::now() + std::chrono::milliseconds(regenerateTime);
        while (std::chrono::steady_clock::now() < end)
            if (!isRunning)
                return;
        stockMutex.lock();
        stock.IncrementAll();
        stockMutex.unlock();
    }
}

void Kitchen::letMeCook(int id, Stock& stock, int cookTime, std::counting_semaphore<2147483647>& sem,
                        std::queue<std::shared_ptr<IPizza>>& pizzaQueue, std::mutex& stockMutex,
                        int& availableCookNumber, std::atomic<bool>& isRunning)
{
    while (isRunning)
    {
        if (!sem.try_acquire_for(std::chrono::milliseconds(100)))
            continue;
        availableCookNumber--;
        stockMutex.lock();
        auto pizza = pizzaQueue.front();
        std::string tmp(
            "cook " + std::to_string(id) + " starts to cook : " + pizza->getName() + ", " + pizza->getSize());
        // std::cout << tmp << std::flush;
        InfoLog(tmp);
        pizza->cook(stock);
        pizzaQueue.pop();
        stockMutex.unlock();
        auto end = std::chrono::steady_clock::now() + std::chrono::milliseconds(cookTime * pizza->getCookTime());
        while (std::chrono::steady_clock::now() < end)
            if (!isRunning)
                return;
        std::this_thread::sleep_for(std::chrono::milliseconds(cookTime * pizza->getCookTime()));
        stockMutex.lock();
        tmp = "cook " + std::to_string(id) + " have finished cooking : " + pizza->getName() + ", " + pizza->getSize();
        // std::cout << tmp << "\n> " << std::flush;
        Debug::InfoLog(tmp);
        availableCookNumber++;
        stockMutex.unlock();
    }
}

Stock& Kitchen::getStock()
{
    return _stock;
}

void Kitchen::addInQueue(std::shared_ptr<IPizza>& pizza)
{
    _pizzaQueue.push(pizza);
    _sem.release();
}

void Kitchen::printIngredient()
{
    std::string tmp;
    for (auto elt : _stock.getIngredients())
        tmp.append(elt.first + " : " + std::to_string(elt.second) + "\n");
    _toReceptionPipe << tmp;
}

void Kitchen::getAvailableCookNumber() const
{
    _toReceptionPipe << std::to_string(_availableCookNumber + _baseCookNumber - _pizzaQueue.size());
}
