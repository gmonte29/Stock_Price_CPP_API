#include <iostream>
#include "stock_data.cpp"
using namespace std;


//methods
//deposit(int) - add to cash value
//withdraw(int) - remove from cash value
//history() - prints history of transactions
int main(){
    cout << get_price("AAPL")<< endl;

    return 0;
}