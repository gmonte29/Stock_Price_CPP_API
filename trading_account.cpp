//Trading account class
#include<vector>
#include<utility>
#include<iostream>
#include <thread>
#include "market.cpp"
using namespace std;
 
// Class created for binding
// all account details together
class Account {

    // Basic Variables declared
    int deposit, withdraw, balance;
 
    // Vector declared
    vector<pair<string, int> > transactions;

    thread th;
 
public:
    //constructor
    Account(int bal=50000, market& m): balance(bal), withdraw(0), deposit(0){
    }
    
    // Deposit Cash
    bool Deposit(int money)
    {
        deposit += money;
        balance += money;
        transactions.push_back({"Deposit:", money});
        return true;
    }
 
    // Get account Details
    void Get_account_information()
    {
        cout << "Money Details:\n";
        cout << "Bank Balance:" << balance << endl;
    }
 
    // Withdraw Cash
    bool Withdraw(int money)
    {
        if (money > balance) {
            return false;
        }
 
        withdraw += money;
        balance -= money;
        transactions.push_back({ "Withdraw:", money });
        return true;
    }
 
    // Checking All Transactions
    void History()
    {
        cout << "Displaying All transactions\n";
        for (auto it : transactions) {
            cout << it.first << " " << it.second << endl;
        }
 
        char temp;
        cout << "Clear all transactions?";
        cin >> temp;
 
        int no = transactions.size();
 
        // Clearing All transactions
        if (temp == 'Y') {
            transactions.clear();
            cout << "Total transactions cleared:" << no
                 << endl;
        }
        else {
            cout << "Total transaction:" << no << endl;
        }
    }
};
 