#include <iostream>
#include "stock_price_access.cpp"
using namespace std;


int main(){
    string ticker;
    cin >> ticker;

    float price = REST::get_price(ticker); //enter ticker to receive price
    cout << price << endl;
    return 0;
}
