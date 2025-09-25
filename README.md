# Description

**A simple calculator that calculates the minimum amount of USD denominations.**

---

# Prerequisites

- ## Linux (gcc, g++)
  - ### Install Script
    Installs all necessary components for building the binary:

    ```bash
    chmod +x install.sh   # Only necessary if running ./install.sh gives "permission denied"
    ./install.sh
    # OR
    bash install.sh
    ```

  - ### Debian/Ubuntu
    ```bash
    sudo apt-get update
    sudo apt install build-essential
    ```

  - ### Fedora/RHEL
    ```bash
    sudo dnf update
    sudo dnf groupinstall "Development Tools"
    ```

---

# Build

- ## Linux
  - Run `make` to build the binary
  - Run `make clean` to clean up build files
  - Run `make memtestNoGUI` to run the binary with Valgrind

---

# Usage

- ## Run with command line arguments
  ```bash
  ./changeMachine <dollarInput>
  ```
    - Runs the program a single time with given command line argument
    - "dollarInput" should be in the form "*.XX"
      - Where 
        - '*' is any integer [0-9] any amount of times
        - '.' is the "decimal place" delimiter
        - 'XX' is any integer [0-99]
       
- ## Run without command line arguments
  ```bash
  ./changeMachine
  ```
  - Program will prompt the user for input (Same as with command line arguments).
  - Program will run indefinitly (Maybe), until user decides to exit.
---
