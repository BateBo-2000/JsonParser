# JSON Parser Console Application

## Overview

This project implements a console application that works with JSON format files. JSON (JavaScript Object Notation) is a popular text format for data interchange, derived from JavaScript's object literal syntax.

The application allows reading and manipulating JSON files, performing various operations on the loaded JSON object in memory. It adheres to the following specifications:

- **No External Libraries**: The project does not utilize external libraries for JSON handling, focusing instead on implementing data representation and operations internally.
- **CPP vesrion**: ISO C++20 Standard (/std:c++20). Go to JsonParser> Properties> Configurational Properties> General> C++ Language Standart to change.
- **Input Simplifications**: Certain simplifications are not allowed in input handling. Maybe coming soon...

## Features

### Supported Operations

1. **validate**
   - Validates the syntax of the opened JSON file and provides clear error messages if any issues are detected.

2. **print**
   - Displays the contents of the JSON object in a human-readable format.

3. **search \<key\>**
   - Searches the JSON object for data stored under the specified key. Returns an array of all occurrences of the key as JSON objects. Works with wildCard '*'.

4. **contains \<value\>**
   - Checks if the JSON object contains a value that matches the provided string. Handles data types appropriately. Works with wildCard '*' as well.

5. **set \<path\> \<string\>**
   - Updates the value of the specified element in the JSON object with the provided string, following JSON syntax rules.

6. **create \<path\> \<string\>**
   - Adds a new element to the JSON object at the specified path and assigns it the provided value. Handles validity checks.

7. **delete \<path\>**
   - Deletes the element at the specified path in the JSON object if it exists, or notifies the user of any errors. Works with wildCard '*'.

8. **move \<from\> \<to\>**
   - Moves all elements located at the specified path \<from\> to the path \<to\>.

9. **save [\<path\>]**
   - Saves the current JSON object to the specified path or the default file path if no path is provided.

10. **saveAs \<file\> [\<path\>]**
    - Saves the current JSON object to the specified file name and path.

11. **help**
    - Provides an explanation of the commands and examples of their use.

## Usage

To use the application, follow these steps:

1. **Compile and Run**
   - Compile the project using your preferred method (Visual Studio, command line, etc.).
   - Run the executable or launch from Visual Studio.

2. **Command Line Interface**
   - Enter commands in the console to perform operations on JSON files.
   - Use `help` to display available commands and their usage.

3. **Example Usage**
 - validate organization.json
 - print
 - search "employee"
 - set "employees[0].name" "John Doe"
 - save organization-updated.json
