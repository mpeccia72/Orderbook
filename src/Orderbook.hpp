
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

        Orderbook();


        void addOrder(OrderPointer);
        

        void printOrderBook();



    private:

        struct OrderInfo {
            OrderPointer order_ {nullptr};
            OrderPointers::iterator location_;
        };

        // bids map is sorted in ascending order so that the highest bid is quick access
        std::map<Dollars, OrderPointers, std::greater<Dollars>> bids_; 

        // asks map is sorted in descending order so the lowest ask is quick access
        std::map<Dollars, OrderPointers, std::less<Dollars>> asks_;

        // quick order lookup, critical for order modifying features
        std::unordered_map<OrderId, OrderInfo> orders_;

   


        




        bool canMatch();

};