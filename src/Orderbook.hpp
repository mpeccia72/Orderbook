
#include "Order.hpp"
#include <map>
#include <memory>
#include <list>
#include <unordered_map>
#include <iostream>
#include <iomanip>

using OrderPointer = std::shared_ptr<Order>;
using OrderPointers = std::list<OrderPointer>;


class Orderbook {

    public:

        // connstructor
        Orderbook();

        // API
        void addOrder(OrderPointer);
        void printOrderBook();

    private:


        // bids map is sorted in ascending order so that the highest bid is quick access
        std::map<Dollars, OrderPointers, std::greater<Dollars>> bids_; 

        // asks map is sorted in descending order so the lowest ask is quick access
        std::map<Dollars, OrderPointers, std::less<Dollars>> asks_;

        // helper
        void matchOrder();
        void addLimitOrder(); // add in future
        void addMarketOrder(); // add in future

};