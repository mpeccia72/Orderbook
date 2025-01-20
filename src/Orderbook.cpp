
#include "Orderbook.hpp"

Orderbook::Orderbook() {

}

// adds order to the book
void Orderbook::addOrder(OrderPointer order) {

    auto orderAction = order->getOrderAction();
    auto orderType = order->getOrderType();
    auto side = order->getSide();
    
    // LIMIT ORDER
    if(orderAction == OrderAction::Limit) {
        
        // order listing price
        auto price = order->getPrice();

        // if listing an ask
        if(side == Side::Sell) {

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

    matchOrder();

}

void Orderbook::matchOrder() {

    
    // matches trades
    while(bids_.begin()->first >= asks_.begin()->first) {

        // catches empty lists and returns
        if(bids_.empty() || asks_.empty()) 
            return;



        auto& [bidPrice, bidOrderList] = *bids_.begin();
        auto& [askPrice, askOrderList] = *asks_.begin();

        auto bidOrder = bidOrderList.begin();
        auto askOrder = askOrderList.begin();

        // we want copies
        auto bidQuantity = (*bidOrder)->getRemainingQuantity();
        auto askQuantity = (*askOrder)->getRemainingQuantity();

        // min value of both
        int min = std::min(bidQuantity, askQuantity);
        
        (*bidOrder)->fill(min);
        (*askOrder)->fill(min);
 
        if(min == bidQuantity) {
            bidOrderList.erase(bidOrder);

            if(bidOrderList.empty()) {
                bids_.erase(bids_.begin());
            }

        }

        if(min == askQuantity) {
            askOrderList.erase(askOrder);

            if(askOrderList.empty()) {
                asks_.erase(asks_.begin());
            }
        }
      
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