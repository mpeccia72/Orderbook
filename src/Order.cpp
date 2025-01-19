
#include "Order.hpp"

// order base class constructor
Order::Order(OrderId orderId, Side side, OrderType orderType, Quantity quantity) : 
    orderId_{orderId},
    side_{side},
    orderType_{orderType},
    initialQuantity_{quantity},
    remainingQuantity_{quantity}
    {}


Quantity Order::getInitialQuantity() const {
    return initialQuantity_;
}

Quantity Order::getRemainingQuantity() const {
    return remainingQuantity_;
}

Quantity Order::getFilledQuantity() const {
    return getInitialQuantity() - getFilledQuantity();
}

Side Order::getSide() const {
    return side_;
}

OrderType Order::getOrderType() const {
    return orderType_;
}

// returns limit or buy order
OrderAction Order::getOrderAction() const {
    return orderAction_;
}

Slippage Order::getSlippage() const {
    return 0;
}

Dollars Order::getPrice() const {
    return 0;
}



// market order constructor
MarketOrder::MarketOrder(OrderId orderId, Quantity quantity, Side side, Slippage slippage, OrderType orderType) : 
    Order(orderId, side, orderType, quantity),
    slippage_{slippage}

    {
        orderAction_ = OrderAction::Market;
    }

Slippage MarketOrder::getSlippage() const{
    return slippage_;
}



// limit order constructor
LimitOrder::LimitOrder(OrderId orderId, Quantity quantity, Side side, Dollars price, OrderType orderType) : 
    Order(orderId, side, orderType, quantity),
    price_{price}
    {
        orderAction_ = OrderAction::Limit;
    }

Dollars LimitOrder::getPrice() const {
    return price_;
}
