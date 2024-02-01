#ifndef STOCK_PRICE_ACCESS_H
#define STOCK_PRICE_ACCESS_H

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <mutex>
#include <nlohmann/json.hpp> // Include the JSON library
using namespace std;

float get_price(const string& ticker);

#endif

