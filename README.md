
# Description

**A simple calculator with GUI, that calculates the minimum ammount of denominations in USD**

---
# Prerequisites
- ## Linux (gcc, g++, glfw3)
  ***Alternativly you can use the noGUI branch which only requires gcc and g++***
  - ### Install Script
    **Installs all necesary components for building the binary**

    ```bash
    chmod +x install.sh #only neccesary if running ./install.sh gives permission denied error
    ./install.sh
    ``` 

  - ### Debian/Ubuntu
    ```bash
    sudo apt-get update
    sudo apt install build-essential
    sudo apt-get install libglfw3-dev #Note this is only neccesary if you wish to recompile the program
    sudo apt-get install libglfw3 #Contains the .so file for the program
    ```

  - ### Fedora/REHL
    ```bash
    sudo dnf update
    sudo dnf groupinstall "Development Tools"
    sudo dnf install glfw
    sudo dnf install glfw-devel
    ```

---

# Build 
**Note binary comes prebuilt in repository. However it is built with glibc 2.38, if your version is older then this you must rebuild the binary.**
 - ## Linux
    - Run "make" to build binary
    - Run "make clean" to clean up build files
    - Run "make memtestNoGUI" to run the built binary with no gui with valgrind

---

# Usage
- ## Run with command line arguments (\<dollarInput> / -g)
  ```bash
  ./changeMachine <dollarInput>
  ```
  - Runs the program a single time with given command line argument
    - "dollarInput" should be in the form "*.XX"
      - Where 
        - '*' is any integer [0-9] any amount of times
        - '.' is the "decimal place" delimiter
        - 'XX' is any integer [0-99]  
  
  ```bash
  ./changeMachine -g
  ```
  - Runs the program with a gui
    - Interactive input, output updates dynamically
- ## Run without command line arguments
  ```bash
  ./changeMachine
  ```
  - Program will prompt the user for input (Same as with command line arguments).
  - Program will run indefinitly (Maybe), until user decides to exit.
---