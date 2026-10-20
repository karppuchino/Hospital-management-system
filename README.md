# Hospital Management System

A command-line hospital management application developed in C++ as a university course project. The program models patients, hospital staff, care periods, medication records, and date-based hospital operations.

The project focuses on object-oriented programming, class relationships, STL containers, pointer-based object references, and structured command processing.

## Features

- Recruit and list hospital staff
- Admit patients and create new care periods
- Discharge patients and close active care periods
- Assign staff members to patient care periods
- Add and remove patient medications
- Display active patients and hospital staff
- View a patient's care history, assigned staff, and medications
- Display medications currently used in the hospital
- Manage operations using a simulated system date
- Execute commands interactively or read them from a file
- Use command aliases and built-in help for available commands

## Project Structure

```text
.
├── main.cpp
├── hospital.cpp
├── hospital.hh
├── person.cpp
├── person.hh
├── careperiod.cpp
├── careperiod.hh
├── cli.cpp
├── cli.hh
├── date.cpp
├── date.hh
├── utils.cpp
└── utils.hh
```

The exact file set may vary depending on the course project package included in this repository.

## Main Components

### `Hospital`

Contains the core application logic and coordinates patients, staff, care periods, medications, and date-related operations.

### `Person`

Represents people in the system. Person objects are used for both patients and staff members and store identifying and medication-related information.

### `CarePeriod`

Represents a patient's period of care. A care period stores its start date, an optional end date, the patient, and the staff members assigned to the period. A care period remains active until an end date is set.

### `Cli`

Implements the command-line interface. It parses user input, resolves command aliases, validates the number of parameters, displays command help, and dispatches commands to the hospital system. Commands can also be read from an input file.

### `Date`

Provides date handling for the simulated hospital timeline, including care-period start and end dates.

### `utils`

Provides input-processing helper functions. These include splitting command strings while preserving quoted values and validating numeric input.

## Technical Highlights

- Object-oriented C++ design
- Separation of responsibilities between classes
- STL containers such as `std::vector` and `std::map`
- References between related objects using pointers
- Pointer-to-member functions for command dispatch
- Command aliases and parameter validation
- File stream handling and command-file execution
- Input parsing with support for quoted parameters
- Tracking active and completed care periods

## Building the Project

Compile all implementation files with a C++17-compatible compiler. For example:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic *.cpp -o hospital
```

Run the compiled program:

```bash
./hospital
```

If the project contains a provided build configuration, such as a Qt Creator project file or Makefile, it can be used instead.

## Using the Application

The program is operated through a text-based command-line interface. Available commands and their aliases are defined in the CLI component.

To display the available commands, use:

```text
HELP
```

To view more information about a specific command, use:

```text
HELP <command>
```

The application also supports reading a sequence of commands from a file through its `Read` command. The exact command names and required parameters are shown by the program's built-in help.

## Learning Outcomes

This project provided practical experience in:

- Designing a multi-class C++ application
- Modelling relationships between real-world entities
- Managing object references and lifetimes
- Using STL containers to organise program data
- Implementing a command-line interface
- Parsing and validating user input
- Processing commands from interactive and file-based input
- Maintaining state across hospital operations

## Background

This repository contains a university course project created to practise C++ programming and object-oriented software design. It is presented as a demonstration of coursework and technical learning rather than as a production-ready healthcare system.
