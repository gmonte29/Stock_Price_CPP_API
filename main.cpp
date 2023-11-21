
#include "trading_account.cpp"
#include<iostream>

using namespace std;

//methods
//deposit(int) - add to cash value
//withdraw(int) - remove from cash value
//history() - prints history of transactions
 
int main(){
    auto ts = Account();
    ts.Deposit(50);
    ts.Withdraw(25); 

    ts.History();

    return 0;
}