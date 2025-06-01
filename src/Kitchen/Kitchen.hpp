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
    #include <functional>

    #include "IPizza.hpp"
    #include "KitchenPipe.hpp"

class Kitchen {
    public:
        Kitchen(std::size_t cookNumber, int regenerateTime, int cookTime, std::atomic<bool>& isRunning, KitchenPipe& toKitchenPipe, KitchenPipe& toReceptionPipe);
        ~Kitchen();

        Stock& getStock();
        void printIngredient();
        void getAvailableCookNumber() const;
        void addInQueue(std::shared_ptr<IPizza>& pizza);
    private:
        static void regenerator(Stock& stock, int regenerateTime, std::mutex& stockMutex, std::atomic<bool>& isRunning);
        static void letMeCook(int id, Stock& stock, int cookTime, std::counting_semaphore<2147483647>& sem, std::queue<std::shared_ptr<IPizza>>& pizzaQueue, std::mutex& stockMutex, int& availableCookNumber, std::atomic<bool>& isRunning);

        Stock _stock;
        std::mutex _stockMutex;
        int _availableCookNumber;
        int _baseCookNumber;
        std::thread _regeneratorThread;
        std::counting_semaphore<> _sem;
        std::vector<std::thread> _cookThreads;
        std::queue<std::shared_ptr<IPizza>> _pizzaQueue;
        KitchenPipe &_toKitchenPipe;
        KitchenPipe &_toReceptionPipe;
        std::unordered_map<std::string, PizzaSize> _pizzaSizeList;
        std::unordered_map<std::string, std::function<std::shared_ptr<IPizza>(std::string)>> _pizzaNameList;
};

#endif
