/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
    #define KITCHEN_HPP_

    #include <queue>
    #include <mutex>
    #include <memory>
    #include <thread>
    #include <atomic>
    #include <semaphore>

    #include "IPizza.hpp"

class Kitchen {
    public:
        Kitchen(std::size_t cookNumber, int regenerateTime, int cookTime, std::atomic<bool>& isRunning);
        ~Kitchen();

        Stock& getStock();
        void printIngredient();
        int getAvailableCookNumber() const;
        void addInQueue(std::shared_ptr<IPizza>& pizza);
    private:
        static void regenerator(Stock& stock, int regenerateTime, std::mutex& stockMutex, std::atomic<bool>& isRunning);
        static void letMeCook(int id, Stock& stock, int cookTime, std::counting_semaphore<2147483647>& sem, std::queue<std::shared_ptr<IPizza>>& pizzaQueue, std::mutex& stockMutex, int& availableCookNumber, std::atomic<bool>& isRunning);

        Stock _stock;
        std::mutex _stockMutex;
        int _availableCookNumber;
        std::thread _regeneratorThread;
        std::counting_semaphore<> _sem;
        std::vector<std::thread> _cookThreads;
        std::queue<std::shared_ptr<IPizza>> _pizzaQueue;

};

#endif
