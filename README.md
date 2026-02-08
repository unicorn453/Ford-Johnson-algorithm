# Ford-Johnson Algorithm Project

A comprehensive C++ project demonstrating three distinct algorithmic challenges: Bitcoin exchange rate computation, Reverse Polish Notation (RPN) evaluation, and the Ford-Johnson sorting algorithm (merge-insertion sort). This project is part of the 42 School curriculum.

## Project Overview

This workspace contains three independent exercises (`ex00`, `ex01`, `ex02`), each implementing a complete C++ solution with proper class design, error handling, and main entry points.

---

## Exercise 00: Bitcoin Exchange

### Description
A Bitcoin exchange rate calculator that reads historical exchange data and computes the equivalent value of Bitcoin at specific dates.

### Functionality
- **Data Loading**: Parses a CSV file (`data.csv`) containing historical Bitcoin exchange rates in the format: `date,rate`
- **Input Processing**: Reads an input file with date-amount pairs separated by pipes (`|`)
- **Exchange Calculation**: Looks up the closest available exchange rate for a given date and computes the equivalent value
- **Error Handling**: Validates dates and amounts, provides informative error messages

### Key Classes and Methods

#### BitcoinExchange Class
```cpp
class BitcoinExchange
{
    // Core Methods
    void readInputFile(const std::string &filename);
    double computeValue(const std::string &date, double amount) const;
    
    // Private Helper Methods
    void loadData(const std::string &filename);
    std::map<std::string, double>::const_iterator findClosestDate(const std::string &date) const;
    bool isValidDate(const std::string &date) const;
    double getExchangeRate(const std::string &date) const;
}
```

**Key Features:**
- **`loadData()`**: Reads CSV data and stores it in a `std::map` for efficient date-based lookups
- **`findClosestDate()`**: Uses `lower_bound()` to find the exchange rate for or before a given date
- **`isValidDate()`**: Validates date format (YYYY-MM-DD) and ensures dates are within the range 2008-2022
- **`computeValue()`**: Multiplies the Bitcoin amount by the exchange rate

### Usage
```bash
cd ex00
make
./btc <input_file>
```

**Input File Format:**
```
date | amount
2011-01-03 | 3
2011-01-03 | 2.1
2011-01-03 | 1500.2
```

**Output:**
```
2011-01-03 | 3 = 0.3
2011-01-03 | 2.1 = 0.21
2011-01-03 | 1500.2 = 150.02
```

### Data File Format
The `data.csv` file contains:
```
date,exchange_rate
2011-01-01,13.51
2011-01-02,13.51
2011-01-03,13.51
...
```

### Error Handling
- Invalid date formats or out-of-range dates
- Negative amounts
- Missing or empty data files
- Malformed input file entries

---

## Exercise 01: Reverse Polish Notation (RPN) Calculator

### Description
An evaluator for expressions written in Reverse Polish Notation (postfix notation), where operators follow their operands.

### Functionality
- **Expression Parsing**: Processes a string containing numbers (0-9) and operators
- **Stack-Based Evaluation**: Uses a stack to evaluate expressions efficiently
- **Supported Operations**: Addition (+), Subtraction (-), Multiplication (*), Division (/)
- **Error Handling**: Detects invalid expressions, division by zero, and malformed input

### Key Classes and Methods

#### RPN Class
```cpp
class RPN
{
public:
    int evaluate(const char* expression);
    
private:
    std::stack<int> operands;
    int performOperation(char op);
}
```

**Key Features:**
- **`evaluate()`**: Parses the input string character by character
  - Pushes digits onto the stack
  - Calls `performOperation()` when an operator is encountered
  - Returns the final result
- **`performOperation()`**: Pops two operands, applies the operation, and pushes the result

### Algorithm Logic
```
For each character in the expression:
  - If digit: push to stack
  - If operator: pop 2 values, apply operation, push result
  - If space: continue (skip)
  - Otherwise: error

Return top of stack as result
```

### Usage
```bash
cd ex01
make
./RPN "expression"
```

**Examples:**
```bash
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"      # Result: 42
./RPN "7 7 * 7 -"                       # Result: 42
./RPN "1 2 * 2 / 2 * 2 4 - +"           # Result: 0
```

### RPN Expression Examples
- `3 4 +` = 7 (3 + 4)
- `5 3 -` = 2 (5 - 3)
- `2 3 *` = 6 (2 * 3)
- `8 2 /` = 4 (8 / 2)
- `15 7 1 1 + - / 3 * 2 1 1 + + -` = 5

### Error Handling
- Invalid characters (non-digit, non-operator, non-space)
- Division by zero
- Insufficient operands for an operation
- Improperly formed expressions

---

## Exercise 02: PmergeMe - Ford-Johnson Sorting Algorithm

### Description
Implementation of the **Ford-Johnson algorithm** (merge-insertion sort), demonstrating efficient sorting using both `std::vector` and `std::deque` containers. This algorithm is known for minimizing the number of comparisons needed to sort a list.

### Functionality
- **Parallel Sorting**: Sorts the same data using both vector and deque containers
- **Performance Metrics**: Measures and displays execution time for each container type
- **Jacobsthal Sequence**: Uses the Jacobsthal sequence to optimize insertion order
- **Pair-Based Sorting**: Implements sorting through pairwise comparisons and merges

### Key Classes and Methods

#### PmergeMe Class
```cpp
class PmergeMe {
public:
    PmergeMe(std::string input);
    void vectorSort();
    void dequeSort();
    std::vector<int> getVec() const;
    std::deque<int> getDeq() const;
    
private:
    // Vector sorting methods
    void generatePairsVec(size_t pairSize);
    void mergeSortVec();
    void rearrangeBlocksByLastElementVec(size_t pairSize);
    void sortRemainingElementsVec(int valueOdd);
    void insertJacobsthalVec(size_t sizePairs);
    size_t binaryCompareVec(int value, size_t a, size_t b);
    
    // Deque sorting methods (parallel implementations)
    void generatePairsDeq(size_t pairSize);
    void mergeSortDeq();
    void rearrangeBlocksByLastElementDeq(size_t pairSize);
    void sortRemainingElementsDeq(int valueOdd);
    void insertJacobsthalDeq(size_t sizePairs);
    size_t binaryCompareDeq(int value, size_t a, size_t b, const std::deque<int>& container);
    
    std::vector<int> vec;
    std::deque<int> deq;
    std::vector<int> pend;      // Pending elements for vector
    std::vector<int> smalls;    // Smaller elements from pairs
    std::vector<int> bigs;      // Larger elements from pairs
    // Similar structures for deque...
}
```

### Ford-Johnson Algorithm Overview

The Ford-Johnson algorithm is an advanced sorting technique that minimizes the number of comparisons:

1. **Pair Generation**: Divide the list into pairs
2. **Pair Comparison**: Compare each pair and separate into "smaller" and "larger" elements
3. **Recursive Merge**: Recursively sort the "larger" elements
4. **Jacobsthal Insertion**: Insert "smaller" elements using the Jacobsthal sequence for optimal ordering

**Why This Algorithm?**
- Near-optimal number of comparisons (theoretical lower bound)
- Practical efficiency for competitive sorting scenarios
- Complex but elegant implementation

### Jacobsthal Sequence
The Jacobsthal sequence (1, 3, 5, 11, 21, 43, ...) is used to determine the optimal order for inserting pending elements. This minimizes the number of comparisons needed during the insertion phase.

### Usage
```bash
cd ex02
make
./PmergeMe <numbers>
```

**Examples:**
```bash
./PmergeMe 3 5 9 7 4          # Sorts these 5 numbers
./PmergeMe 100 89 23 1 99 2   # Sorts these 6 numbers
./PmergeMe $(seq 1 100)        # Sorts 100 numbers
```

**Output:**
```
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::vector : 0.00050 us
Time to process a range of 5 elements with std::deque : 0.00075 us
```

### Algorithm Steps (Detailed)

```
1. PAIR GENERATION
   - Divide input into pairs: (a[0], a[1]), (a[2], a[3]), ...
   - If odd number of elements, keep one unpaired

2. PAIR COMPARISON
   - Compare each pair: smaller elements → 'smalls', larger → 'bigs'

3. RECURSIVE MERGE
   - Recursively sort 'bigs' using the same algorithm

4. JACOBSTHAL INSERTION
   - Insert 'smalls' into the sorted 'bigs' using binary search
   - Follow Jacobsthal sequence for optimal insertion order
   
5. HANDLE REMAINING
   - Insert any odd element not in a pair
```

### Performance Characteristics
- **Time Complexity**: O(n log n) with optimized comparisons
- **Space Complexity**: O(n) for temporary storage
- **Comparison Count**: Near-optimal (very close to theoretical minimum)

---

## Project Structure

```
Ford-Johnson-algorithm/
├── ex00/                    # Bitcoin Exchange
│   ├── BitcoinExchange.hpp
│   ├── BitcoinExchange.cpp
│   ├── main.cpp
│   ├── Makefile
│   ├── data.csv            # Historical exchange rates
│   └── test_*.txt          # Test input files
│
├── ex01/                    # RPN Calculator
│   ├── RPN.hpp
│   ├── RPN.cpp
│   ├── main.cpp
│   └── Makefile
│
└── ex02/                    # PmergeMe Sorting
    ├── PmergeMe.hpp
    ├── PmergeMe.cpp
    ├── Deque.cpp           # Deque-specific implementations
    ├── main.cpp
    └── Makefile
```

---

## Building and Compilation

Each exercise is independent and can be built separately:

```bash
# Build all exercises
cd ex00 && make && cd ../ex01 && make && cd ../ex02 && make

# Or build individually
cd ex00 && make        # Creates ./btc
cd ex01 && make        # Creates ./RPN
cd ex02 && make        # Creates ./PmergeMe
```

### Clean Build
```bash
cd ex00 && make clean && cd ../ex01 && make clean && cd ../ex02 && make clean
```

---

## C++ Features Used

### Core Concepts
- **STL Containers**: `std::vector`, `std::deque`, `std::map`, `std::stack`
- **Memory Management**: RAII principles, proper constructors/destructors
- **Exception Handling**: Try-catch blocks with custom error messages
- **File I/O**: `std::ifstream` and `std::ofstream` for file operations
- **String Processing**: Parsing and validation using standard string methods
- **Algorithms**: Binary search, merge sort, insertion sort, recursive algorithms

### Design Patterns
- **Standard C++ Class Design**: Constructors, copy constructors, assignment operators, destructors
- **Error Handling**: Exceptions for robust error management
- **Separation of Concerns**: Clear method responsibilities
- **Container Abstraction**: Parallel implementations using different data structures

---

## Testing

### Ex00 - Bitcoin Exchange
Test files are provided:
- `test_errors.txt`: Invalid dates and amounts
- `test_edge_cases.txt`: Boundary cases
- `test1.txt`, `test2.txt`: General test cases

```bash
./btc test1.txt
./btc test_errors.txt
./btc test_edge_cases.txt
```

### Ex01 - RPN Calculator
```bash
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
./RPN "7 7 * 7 -"
./RPN "1 2 * 2 / 2 * 2 4 - +"
./RPN "(1 + 1)"  # Should error
```

### Ex02 - PmergeMe
```bash
./PmergeMe 3 5 9 7 4
./PmergeMe 100 89 23 1 99 2 34 56
./PmergeMe $(seq 1 1000)  # Test with 1000 elements
```

---

## Learning Objectives

This project demonstrates:

1. **Advanced Sorting Algorithms**: Understanding of algorithm optimization and complexity analysis
2. **Data Structure Mastery**: Effective use of STL containers for different use cases
3. **C++ Best Practices**: Proper class design, resource management, and error handling
4. **Algorithm Implementation**: Translating complex algorithms into working code
5. **Performance Analysis**: Measuring and comparing container performance
6. **File and String Processing**: Parsing and validating user input and data files

---

## Notes

- All exercises follow 42 School C++ coding standards
- No external libraries beyond the C++ Standard Library are used
- Proper memory management with no memory leaks
- Comprehensive error handling and user feedback
- Code is organized and well-structured for maintainability

---

## Author

Created as part of the 42 School C++ curriculum.

---

## References

- **Ford-Johnson Algorithm**: Merge-Insertion Sort with optimal comparison count
- **Jacobsthal Sequence**: Mathematical sequence used in optimal sorting
- **C++ Standard Library**: Official documentation for STL containers and algorithms
- **RPN (Postfix Notation)**: Classic stack-based expression evaluation technique
