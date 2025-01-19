
#include <cstdint>

// strict defintitions
using Quantity = uint32_t;
using OrderId = uint64_t;
using Dollars = uint32_t; // ex: value of 100 = $1.00 (penny-based order book)
using Slippage = uint32_t; // ex: value of 10 = 1%


enum class Side {
    Buy, 
    Sell,
};

enum class OrderType {
    GoodTillCancel,
    FillAndKill,
    StopLoss
};

enum class OrderAction {
    Limit, 
    Market
};



// Order (generalizaiton)
class Order {

    public:
        // constructor
        Order(OrderId, Side, OrderType, Quantity);

        // API
        Quantity getInitialQuantity() const;
        Quantity getRemainingQuantity() const;
        Quantity getFilledQuantity() const;
        Side getSide() const;
        Dollars getAverageCost() const;
        OrderType getOrderType() const;
        OrderAction getOrderAction() const;

        virtual Slippage getSlippage() const;
        virtual Dollars getPrice() const;
        

    protected:
        Quantity initialQuantity_, remainingQuantity_;
        Side side_; // buy or sell side
        OrderId orderId_;
        Dollars averageCost_{};
        OrderType orderType_;
        OrderAction orderAction_;

};



// Market Order (includes slippage) (specialized order)
class MarketOrder : public Order {

    // constructor
    MarketOrder(OrderId, Quantity, Side, Slippage, OrderType);

    // API
    Slippage getSlippage() const override;

    private:
        Slippage slippage_;
        
};



// Limit Order (includes price) (specialized order)
class LimitOrder : public Order{

    public:

        // constructor
        LimitOrder(OrderId, Quantity, Side, Dollars, OrderType);

        // API
        Dollars getPrice() const override;

    private:
        Dollars price_;

};