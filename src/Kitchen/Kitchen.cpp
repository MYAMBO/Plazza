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

Kitchen::Kitchen(std::size_t cookNumber, int regenerateTime, int cookTime, std::atomic<bool>& isRunning)
    :_regeneratorThread(regenerator, std::ref(_stock), regenerateTime, std::ref(_stockMutex), std::ref(isRunning)), _sem(std::counting_semaphore<>(0))
{
    _availableCookNumber = cookNumber;
    for (std::size_t i = 0; i < cookNumber; i++)
        _cookThreads.push_back(std::thread(letMeCook, i, std::ref(_stock), cookTime, std::ref(_sem), std::ref(_pizzaQueue), std::ref(_stockMutex), std::ref(_availableCookNumber), std::ref(isRunning)));
}

Kitchen::~Kitchen()
{
    _regeneratorThread.join();
    for (auto& elt : _cookThreads)
        elt.join();
}

void Kitchen::regenerator(Stock& stock, int regenerateTime, std::mutex& stockMutex, std::atomic<bool>& isRunning)
{
    while (isRunning) {
        auto end = std::chrono::steady_clock::now() + std::chrono::milliseconds(regenerateTime);
        while (std::chrono::steady_clock::now() < end)
            if (!isRunning)
                return;
        stockMutex.lock();
        stock.IncrementAll();
        stockMutex.unlock();
    }
}

void Kitchen::letMeCook(int id, Stock& stock, int cookTime, std::counting_semaphore<2147483647>& sem, std::queue<std::shared_ptr<IPizza>>& pizzaQueue, std::mutex& stockMutex, int& availableCookNumber, std::atomic<bool>& isRunning)
{
    while (isRunning) {
        if (!sem.try_acquire_for(std::chrono::milliseconds(100)))
            continue;
        availableCookNumber--;
        stockMutex.lock();
        auto pizza = pizzaQueue.front();
        std::string tmp("cook " + std::to_string(id) + " starts to cook : " + pizza->getName() + ", " + pizza->getSize() + "\n> ");
        std::cout << tmp << std::flush;
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
        std::cout << tmp << "\n> " << std::flush;
        Debug::InfoLog(tmp, File, true);
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
    for (auto elt : _stock.getIngredients())
        std::cout << elt.first << " : " << elt.second << "\n";
}

int Kitchen::getAvailableCookNumber() const
{
    return _availableCookNumber;
}
