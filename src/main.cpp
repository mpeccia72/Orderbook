
#include <iostream>
#include <fstream>
#include "Orderbook.hpp"

using namespace std;

// loads orders from data file into order book for testing
void loadFileToBook(ifstream&, Orderbook&);

int main() {

    // orderbook instantiation
    Orderbook orderbook;

    // "input.dat" file
    ifstream input("input.dat");

    // loads order book with orders from file
    loadFileToBook(input, orderbook);

    cout << "\nWelcome to Michaelinator's Order Book Version 1:\n" << "--------------------------------------------------\n\n";
    
    orderbook.printOrderBook();

    cout << endl;

    OrderId id{};

    while(true) {

        Side side;
        Quantity quantity;
        Dollars price;
        int in;

        cout << "Type 0 to Buy and 1 to Sell: ";
        cin >> in;
        side = static_cast<Side>(in);
        cout << endl;

        cout << "Enter Price: ";
        cin >> in;
        price = static_cast<Dollars>(in);
        cout << endl;

        cout << "Enter Quantity: ";
        cin >> in;
        quantity = static_cast<Quantity>(in);
        cout << endl;

        // creates orders and adds to book
        shared_ptr<Order> order = make_shared<LimitOrder>(id, quantity, side, price, OrderType::StopLoss);
        orderbook.addOrder(order);

        // prints book
        orderbook.printOrderBook();
        cout << endl;

    }

    return 0;
}


void loadFileToBook(ifstream& input, Orderbook& orderbook) {

    // if error opening file
    if(!input) {
        cerr << "File not found!\n";
        return;
    }

    // counts lines
    int lineCount{};
    string line;
    while (getline(input, line)) {
        ++lineCount; 
    }

    // resets to line 0
    input.clear();         
    input.seekg(0);

    // 3 lines makes up one block of data
    int partitions = lineCount/3;
    for(int i = 0; i < partitions; i++) {

        getline(input, line);
        Side side = static_cast<Side>(stoi(line));
        getline(input, line);
        Dollars price = static_cast<Dollars>(stoi(line));
        getline(input, line);
        Quantity quantity = static_cast<Quantity>(stoi(line));
        
        // create and add order to the book
        shared_ptr<Order> order = make_shared<LimitOrder>(i, quantity, side, price, OrderType::StopLoss);
        orderbook.addOrder(order);

    }

    // close file
    input.close();
  
}