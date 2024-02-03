#include <iostream>
#include "stock_price_access.cpp"
using namespace std;

//methods
//deposit(int) - add to cash value
//withdraw(int) - remove from cash value
//history() - prints history of transactions
int main(){
    float price = get_price("QQQ");
    cout << price << endl;
    return 0;
}
