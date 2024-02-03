#include <iostream>
#include <string>
#include <curl/curl.h>
#include <mutex>
#include <nlohmann/json.hpp> // Include the JSON library
using namespace std;

mutex m;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

float get_price(const string& ticker){
    lock_guard<mutex> lg(m);
    string api = "4CFM0T26CVJY8437";
    string url = "https://www.alphavantage.co/query?function=GLOBAL_QUOTE&symbol=" + ticker + "&apikey=" + api;

    CURL *curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    auto data = nlohmann::json::parse(readBuffer);

    float return_val = stof(string(data["Global Quote"]["05. price"]));
    
    return return_val;
}
