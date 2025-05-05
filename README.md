# Airline Reservation and Management System

## Overview

This project is a modern C++ Airline Reservation and Management System designed for educational and demonstration purposes. It features a modular, object-oriented architecture and supports multiple user roles, robust data persistence, and extensible business logic.

## Features

- **Role-Based Access:** Supports Administrator, Booking Agent, and Passenger roles with tailored interfaces and permissions.
- **CRUD Operations:** Create, read, update, and delete flights, users, and bookings.
- **JSON Data Storage:** Uses [nlohmann/json](https://github.com/nlohmann/json) for efficient and human-readable data persistence.
- **Design Patterns:** Implements Factory, Singleton, DAO, and other patterns for maintainable and scalable code.
- **Interactive CLI:** Command-line interface for all user operations with input validation and error handling.

## Technologies Used

- **C++17**
- **nlohmann/json** for JSON serialization/deserialization
- **Standard Template Library (STL)**
- **Object-Oriented Programming**

## Project Structure

```
Airline-Reservation-and-Management-System/
├── src/
│   ├── main.cpp
│   └── manager/
│       └── FlightManager.cpp
├── header/
│   ├── manager/
│   │   ├── IManager.hpp
│   │   └── FlightManager.hpp
│   ├── flight/
│   │   └── Flight.hpp
│   └── utils/
│       └── JSONFileManager.hpp
├── include/
│   └── nlohmann/
│       └── json.hpp
└── storage/
    └── flights001.json
```

## Getting Started

### Prerequisites

- C++17 compatible compiler (e.g., g++)
- [nlohmann/json](https://github.com/nlohmann/json) single-header library

### Build Instructions

```bash
g++ -std=c++17 -I./include -o airline-reservation src/main.cpp src/manager/FlightManager.cpp
```

### Run

```bash
./airline-reservation
```

## Usage

- Follow the CLI prompts to log in as an administrator, booking agent, or passenger.
- Manage flights, users, and bookings through interactive menus.

## Contributing

Pull requests are welcome! For major changes, please open an issue first to discuss what you would like to change.

## License

This project is licensed under the MIT License.

---

**Author:** [Your Name]  
**Contact:** [your.email@example.com]