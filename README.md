# Card Shop Management System in C++

This repository contains a C++ implementation of a Card Shop Management System for Yu-Gi-Oh! (YGO) cards. The `CardShop` class is built using a doubly linked list of YGO card pointers and provides functionalities to manage, sort, and display cards.

## Overview

The Card Shop Management System allows you to create a shop with YGO cards, manage them through various sorting algorithms, and perform actions like displaying card names and details.

### Dependencies

- **DoublyLinkedList**: Base class for the `CardShop`.
- **YGOCard**: Represents individual Yu-Gi-Oh! cards.

## CardShop Class

### Constructors

- **Default Constructor**: Initializes an empty shop.
- **Parameterized Constructor**: Reads from a CSV file and adds pointers to YGOCard objects to the shop.

### Methods

- **`display()`**: Displays information of all cards in the shop.
- **`displayName(int startRange, int endRange)`**: Displays names of all cards within a specific range.
- **`clear()`**: Removes all cards from the shop.
- **Equality Operator (`==`)**: Compares two `CardShop` objects for equality.

### Sorting Algorithms

- **`quickSort(Comparator comp, std::string key)`**: Implements Quick Sort.
- **`mergeSort(Comparator comp, std::string key)`**: Implements Merge Sort.
- **`bubbleSort(Comparator comp, std::string key)`**: Implements Bubble Sort.
- **`insertionSort(Comparator comp, std::string key)`**: Implements Insertion Sort.

## Usage

Include the `CardShop.hpp` class and related dependencies in your project. You can create a `CardShop` object to manage and manipulate YGO cards.

```cpp
#include "CardShop.hpp"

int main() {
    CardShop shop("cards.csv");
    shop.display();
    shop.quickSort(MyComparator(), "name");
    shop.displayName(0, 10);
    return 0;
}
```
# Example Files

- `Node.cpp`: Implementation for the doubly linked list node.
- `YGOCard.cpp`: Implementation for representing individual YGO cards.
- `cards.csv`: Sample test file for initializing the card shop.

# Contact
- For more details, feel free to reach out

# License
This project is open-source and available under the MIT License.
