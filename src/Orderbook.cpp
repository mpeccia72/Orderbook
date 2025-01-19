
#include "Orderbook.hpp"

Orderbook::Orderbook() {

}


void Orderbook::addOrder(OrderPointer order) {

    auto orderAction = order->getOrderAction();
    auto orderType = order->getOrderType();
    auto side = order->getSide();
    


    // LIMIT ORDER
    if(orderAction == OrderAction::Limit) {
        
        // order listing price
        auto price = order->getPrice();

        // if listing an ask
        if(side == Side::Buy) {

            auto it = asks_.find(price);

            // price level already exists of current price in asks
            if(it != asks_.end()) {
                (it->second).push_back(order);
            }

            // price level doesn't exist yet in asks
            else {
                OrderPointers level;
                level.push_back(order);
                asks_.insert({price, level});
            }

        }

        // if listing a bid
        else {
            
            auto it = bids_.find(price);

            // price level already exists of current price in bids
            if(it != bids_.end()) {
                (it->second).push_back(order);
            }

            // price level doesn't exist yet in bids
            else {
                OrderPointers level;
                level.push_back(order);
                bids_.insert({price, level});
            }

        }

    }



    // MARKET ORDER
    else {
        return;
    }

}

void Orderbook::printOrderBook() {

    std::cout << "ASKS\n" << "--------\n";

    // reverse iterator
    for(auto it = asks_.rbegin(); it != asks_.rend(); it++) { 

        const auto& [price, orderList] = *it;
        std::cout << std::fixed << std::setprecision(2) << "Price: " << static_cast<double>(price) / 100 << "   ";
        int sum{};
        for(const auto& order : orderList) {
            sum += order->getRemainingQuantity();
        }

        std::cout << "Quantity: " << sum << std::endl;

    }

    std::cout << std::endl << std::endl;

    std::cout << "BIDS\n" << "--------\n";

    // iterator
    for(auto it = bids_.begin(); it != bids_.end(); it++) { 

        const auto& [price, orderList] = *it;
        std::cout << std::fixed << std::setprecision(2) << "Price: " << static_cast<double>(price) / 100 << "   ";
        int sum{};
        for(const auto& order : orderList) {
            sum += order->getRemainingQuantity();
        }

        std::cout << "Quantity: " << sum << std::endl;

    }

}