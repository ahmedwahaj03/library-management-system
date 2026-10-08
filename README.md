# Library Management System

A console-based Library Management System written in C++ using object-oriented programming concepts.

## Features
- Add books
- Display all books
- Search by title or author
- Update book information
- Issue and return books
- Delete books
- Input validation for common invalid entries

## Technologies
- C++
- Object-Oriented Programming
- STL `vector` and `string`

## How to Run

### Using g++
```bash
g++ -std=c++17 -Wall -Wextra -o library_management main.cpp
./library_management
```

On Windows:
```bash
g++ -std=c++17 -Wall -Wextra -o library_management.exe main.cpp
library_management.exe
```

## Note
This version stores data in memory while the program is running. Data is not persisted after the program closes.
