#include <iostream>
#include <string>
#include "PmergeMe.hpp"

int checkInput(std::string input) {
    for (size_t i = 0; i < input.length(); i++) {
        if (!isdigit(input[i])) {
            std::cerr << "Error: Invalid character '" << input[i] << "' found in input." << std::endl;
            return 1;
        }
        if (input[i] < '0' || input[i] > '9') {
            std::cerr << "Error: Input must be a positive integer." << std::endl;
            return 1;
        }
    }
    return 0;
   
}



int main(int argc, char** argv) {

     if (argc != 2) {
        std::cerr << "Error: Sequence of numbers required." << std::endl;
        return 1;
    }
    std::string strInput(argv[1]);
    if (checkInput(strInput.c_str()) != 0) {
        return 1;
    }

    PmergeMe nums(strInput);
    nums.vectorSort();
    nums.dequeSort();
    return 0;
}