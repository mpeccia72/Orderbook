
#include <iostream>
#include <fstream>
#include "Orderbook.hpp"

using namespace std;

int main() {



    Orderbook orderbook;

    std::cout << "hello world\n";

    OrderId id{};
    while(id++ < 10) {

        

        Side side;
        int side1;
        Quantity quantity;
        Dollars price;

        cout << "Are you buying or selling?";
        cin >> side1;
        side = static_cast<Side>(side1);
        cout << endl;

        cout << "Price?";
        cin >> price;
        cout << endl;

        cout << "Quantity?";
        cin >> quantity;
        cout << endl;

        shared_ptr<Order> order = make_shared<LimitOrder>(id, quantity, side, price, OrderType::StopLoss);

        orderbook.addOrder(order);

        orderbook.printOrderBook();

    }







    return 0;
}