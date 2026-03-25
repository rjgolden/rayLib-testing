#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

int main () {

    std::ifstream file ("test.csv");

    std::string line;
    std::vector<std::vector<std::string>> values;
    while(std::getline(file, line)){

        std::string line_value;
        std::vector<std::string> line_values;
        std::stringstream ss(line);
        while(std::getline(ss, line_value, ',')) line_values.push_back(line_value);
        values.emplace_back(line_values);
    }

    std::vector<int> numValues;
    for(std::vector<std::string>& printValues : values){
        for(std::string& num : printValues){
            std::cout << num << " ";
            numValues.push_back(stoi(num));

        }
        std::cout << "\n";
    }

    std::cout << "\n";
    for(int num : numValues){
        std::cout << num << " ";
    }

    return 0;

}
