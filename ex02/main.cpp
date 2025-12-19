#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include "PmergeMe.hpp"

int checkInput(std::string input)
{
    for (size_t i = 0; i < input.length(); i++)
    {
        if (!isdigit(input[i]) && input[i] != ' ')
        {
            std::cerr << "Error: Invalid character '" << input[i] << "' found in input." << std::endl;
            return 1;
        }
        if (input[i] == ' ')
        {
            i++;
        }
        if (input[i] < '0' || input[i] > '9')
        {
            std::cerr << "Error: Input must be a positive integer." << std::endl;
            return 1;
        }
    }
    return 0;
}

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        std::cerr << "Error: No input provided." << std::endl;
        return 1;
    }

    std::string strInput;

    for (int i = 1; i < argc; i++)
    {
        strInput += argv[i];
        if (i < argc - 1)
        {
            strInput += " ";
        }
    }

    if (checkInput(strInput.c_str()) != 0)
    {
        return 1;
    }

    std::cout << "Before: ";
    for (int i = 1; i < argc; i++)
    {
        std::cout << argv[i];
        if (i < argc - 1)
        {
            std::cout << " ";
        }
    }
    std::cout << std::endl;

    PmergeMe nums(strInput);

    clock_t start = clock();
    nums.vectorSort();
    clock_t end = clock();
    double vec_duration = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;

    start = clock();
    nums.dequeSort();
    end = clock();
    double deq_duration = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
    std::cout << std::endl;
    std::cout << "After: ";
    std::vector<int> sorted = nums.getVec();
    for (size_t i = 0; i < sorted.size(); i++)
    {
        std::cout << sorted[i];
        if (i < sorted.size() - 1)
        {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    std::deque<int> sortedDeq = nums.getDeq();
    // test sorted output
    // for (size_t i = 0; i < sorted.size(); i++)
    // {
    //     if (i > 0 && sorted[i] < sorted[i - 1])
    //     {
    //         std::cerr << "\nError: Vector is not sorted correctly." << std::endl;
    //         return 1;
    //     }
    //     if (i == sorted.size() - 1)
    //     {
    //         std::cout << " \nVector is sorted correctly." << std::endl;
    //     }
    // }
    // for (size_t i = 0; i < sortedDeq.size(); i++)
    // {
    //     if (i > 0 && sortedDeq[i] < sortedDeq[i - 1])
    //     {
    //         std::cerr << "\nError: Vector is not sorted correctly." << std::endl;
    //         return 1;
    //     }
    //     if (i == sortedDeq.size() - 1)
    //     {
    //         std::cout << " \nDeque is sorted correctly." << std::endl;
    //     }
    // }
    // std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << sorted.size()
              << " elements with std::vector : "
              << vec_duration << " us" << std::endl;

    std::cout << "Time to process a range of " << sorted.size()
              << " elements with std::deque : "
              << deq_duration << " us" << std::endl;

    return 0;
}