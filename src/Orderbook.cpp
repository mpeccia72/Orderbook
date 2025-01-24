
#include "Orderbook.hpp"

Orderbook::Orderbook(SecurityId securityId) : 
    securityId_{securityId}
    {}

// adds order to the book
void Orderbook::addOrder(OrderPointer order) {

    // stores if limit or market order
    auto orderAction = order->getOrderAction();
    
    // limit Order
    if(orderAction == OrderAction::Limit)
        addLimitOrder(order);



    // MARKET ORDER
    else {
        return;
    }

    matchOrder();

}

// adds limit order
void Orderbook::addLimitOrder(OrderPointer order) {

    // fetching basic information
    auto orderType = order->getOrderType();
    auto side = order->getSide();

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

// order matching engine
void Orderbook::matchOrder() {
    
    // matches orders while there in an inverted spread
    while(bids_.begin()->first >= asks_.begin()->first) {

        // catches empty lists and returns
        if(bids_.empty() || asks_.empty()) 
            return;

        // structured binding to capture data related to lowest ask and highest bid
        auto& [bidPrice, bidOrderList] = *bids_.begin();
        auto& [askPrice, askOrderList] = *asks_.begin();

        // bid and ask orders respectively next in queue at their levels
        auto bidOrder = bidOrderList.begin();
        auto askOrder = askOrderList.begin();

        // read only
        const auto& bidQuantity = (*bidOrder)->getRemainingQuantity();
        const auto& askQuantity = (*askOrder)->getRemainingQuantity();

        // min value of both
        int min = std::min(bidQuantity, askQuantity);
        
        // fill matching
        (*bidOrder)->fill(min);
        (*askOrder)->fill(min);

        if(min == bidQuantity) {

            // bid order is wiped if completely filled
            bidOrderList.erase(bidOrder);

            if(bidOrderList.empty()) {

                // erases entire bid level if no more orders
                bids_.erase(bids_.begin());

                // new ask level is created if bid is eaten up
                OrderPointers level;
                level.push_back(*askOrder);
                asks_.insert({(*askOrder)->getPrice(), level});
            }

        }

        if(min == askQuantity) {

            // ask order is wiped if completely filled
            askOrderList.erase(askOrder);

            if(askOrderList.empty()) {

                // erases entire ask level if no more orders
                asks_.erase(asks_.begin());
                
                // new bid level is created if ask is eaten up
                OrderPointers level;
                level.push_back(*bidOrder);
                bids_.insert({(*bidOrder)->getPrice(), level});
            }

        }
      
    }

}


// prints orderbook to console
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