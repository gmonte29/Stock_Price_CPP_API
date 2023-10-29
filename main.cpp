
#include "trading_account.cpp"
#include<iostream>

using namespace std;

int main(){
    auto ts = Account();
    ts.Get_account_information();

    cout << endl;

    ts.Withdraw(50);
    ts.Get_account_information();

    return 0;
}