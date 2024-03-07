#include <iostream>
#include "stock_price_access.cpp"
using namespace std;


int main(){
    float price = REST::get_price("QQQ"); //enter ticker to receive price
    cout << price << endl;
    return 0;
}
