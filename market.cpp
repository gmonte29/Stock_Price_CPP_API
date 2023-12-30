#include <unordered_map>
#include <string>
#include <iostream>
#include <mutex>
using namespace std;

class instrument{
    string ticker;
    int shares;
    float val;

public:
    instrument(string t, int s, float v): ticker(t), shares(s), val(v){} 
    friend market;
};



class market{
    unordered_map<string, instrument> investments;
    int total_shares{0};

public:
    //function for creating new stock investment;
    void ipo(string ticker, int shares, int val){
        try{
            if(investments.count(ticker)!=0) throw exception();
            instrument i = instrument(ticker, shares, val);
            investments[ticker] = i;
            total_shares+=shares;
        }
        catch(exception& e){
            cout << "exception " << e.what() << " found, ipo failed" << endl;
        }
    
    }

    //method for buying/selling stock
    void stock_change(string ticker, int shares, bool buy){

        if(!buy) {
            stock_change(ticker, shares*-1, true);
            return;
        }

        investments[ticker].shares+=shares;
        total_shares+=shares;

        int current_shares = investments[ticker].shares;
        investments[ticker].val *=  investments[ticker].shares / total_shares;
    }

    //method for viewing stock info
    void view(string ticker){

        cout << "stock name: "<< ticker << endl;
        cout << "stock price: "<< investments[ticker].val << endl;
        cout << "shares outstanding: "<< investments[ticker].shares << endl;
    }
};