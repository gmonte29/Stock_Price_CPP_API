#include <string>
using namespace std;

//node class that holds information for each stock purchase
class buy_node{
    buy_node* next{nullptr};
    string ticker;
    float val;
    int quantity;
    time_t day;

public:
    buy_node(string t, float v, int q): ticker(t), val(v), quantity(q){
        day = time(0) / (60*60*24);
    }
    buy_node(){}
    friend class Account;
};