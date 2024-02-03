//Trading account class
#include <vector>
#include <utility>
#include <iostream>
#include <unordered_map>
#include <odb/core.hxx> // odb header for allowing various odb functions
#include "stock_price_access.cpp"
#include "buy_node.cpp"
using namespace std;

#pragma db object //pragma indiciates the class creates persistent objects
class Account {
    int balance;

    #pragma db id auto//odb unique id declaration for mapping persistent opbjects to database
    string username;

    unordered_map<string, buy_node*> holdings;
    unordered_map<string, int> holdings_quantity;

    friend class odb::access; // makes class available to database support code

public:
    //constructor
    Account(int bal=50000, string user): balance(bal), username(user){
    }

    //method for getting stock price
    void display_price(string ticker){
        float p = get_price(ticker);
        cout << ticker << " price: " << p << endl;
    }

    //adds a buy_node to the ticker linkedList
    void buy_stock(string ticker, int quantity){
        float current_val;
        try{
            current_val = get_price(ticker);
        }
        catch(exception& e) {
            cout << "purchase not executed, exception found: " << e.what() << endl;
            return;
        }
        if(current_val * quantity > balance){
            cout << "Insufficient funds to make purchase, please deposity more funds\n";
            return;
        }
        if(holdings.count(ticker) == 0){
            holdings[ticker] = new buy_node();
            holdings_quantity[ticker] = 0;
        }

        buy_node* current = holdings[ticker];
        while(current->next != nullptr) current = current->next;

        current->next = new buy_node(ticker, current_val, quantity);
        holdings_quantity[ticker]+=quantity;
    }

    //Sell stock method, uses FIFO methodology for determining recognized gain/loss
    void sell_stock(string ticker, int quantity){
        if(holdings.count(ticker)==0 || holdings_quantity[ticker] < quantity){
            cout << "Insufficient shares for sale\n";
            return;
        }
        float recognizedGL{0};
        float current_val = get_price(ticker);

        buy_node* front = holdings[ticker];
        buy_node* current = front->next;

        while(current!= nullptr && quantity > 0){
            int current_node_quant = min(current->quantity, quantity);

            float originalVal = current_node_quant * current->val;
            float currentVal = current_node_quant * current_val;
            recognizedGL += currentVal-originalVal;
            holdings_quantity[ticker] -= current_node_quant;

            if(quantity < current->quantity){
                current->quantity -= quantity;
            }
            else current = current ->next;

            quantity -= current->quantity;
        }

        front->next = current;
        if(holdings_quantity[ticker] == 0){
            holdings.erase(ticker); 
            holdings_quantity.erase(ticker);
        }

        cout << "recognized gain/loss on sale of " << ticker << ": " << recognizedGL << endl;
    }

    //method to display performance for each ticker then total holdings performance
    //want to include annualized returns at some point
    void performance_summary(){
        cout << "Unrealized Gain/Loss Display\n";
        
        float originalTotal{0};
        float newTotal{0};

        for(auto& item : holdings){
            float current_ticker_price = get_price(item.first);

            float newVal{0};
            float originalVal{0};
            
            buy_node* current = item.second->next;

            while(current != nullptr){
                originalVal+= current->quantity * current->val;
                newVal += current->quantity * current_ticker_price;
                current = current->next;
            }
            originalTotal += originalVal;
            newTotal += newVal;

            cout << item.first << "Fair Market Value: "<< newVal << ", ticker returns: " << newVal-originalVal << ", ticker performance: " << (newVal/originalVal-1) << endl;
        }

        cout << "Fair Market Value: " << newTotal << ", total returns: " << newTotal-originalTotal << ", total performance: " << (newTotal/originalTotal-1) << endl;
    }
    
    // Deposit Cash
    bool Deposit(int money){
        balance += money;
        return true;
    }
 
    // Withdraw Cash
    bool Withdraw(int money){
        if (money > balance) {
            cout << "Insufficient funds to withdrawel\n";
            return false;
        }
        balance -= money;
        return true;
    }
 
};
 