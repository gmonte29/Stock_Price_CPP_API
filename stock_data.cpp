#include <iostream>
#include <cstdlib>

int main() {
    const char* pythonScript = "stock_data.py";

    // Replace "AAPL" with the desired stock symbol
    const char* stockSymbol = "AAPL";

    // Run the Python script using subprocess
    std::string command = "python " + std::string(pythonScript) + " " + std::string(stockSymbol);
    int result = std::system(command.c_str());

    if (result == 0) {
        std::cout << "C++ program successfully ran Python script." << std::endl;
    } else {
        std::cerr << "Error running Python script." << std::endl;
    }

    return 0;
}