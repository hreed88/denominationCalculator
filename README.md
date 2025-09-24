
---
# Prerequisites
- ## Linux (gcc)
  
  - ### Debian/Ubuntu
    ```console
    $ sudo apt-get update
    $ sudo apt install build-essential
    $ sudo apt-get install libglfw3-dev
    ```

  - ### Fedora/REHL
    ```console
    $ sudo dnf update
    $ sudo dnf groupinstall "Development Tools"
    ```

- ## Windows (Clang)
  - <a href="https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022">Download and Run Build Tools for Visual Studio </a>
  - Select Desktop Development with C++
  - Ensure under the "Optional" tab, Clang is selected

---

# Build
 - ## Linux
    - Run "make" to build binary
    - Run "make clean" to remove built binary
    - Run "make memtest" to run the built binary with valgrind
 - ## Windows
    - Run build.bat to build .exe

---

# Usage
- ## Run with command line arguments (\<dollarInput> / -g)
  ```console
  $ ./changeMachine <dollarInput>
  ```
  - Runs the program a single time with given command line argument
    - "dollarInput" should be in the form "*.XX"
      - Where 
        - '*' is any integer [0-9] any amount of times
        - '.' is the "decimal place" delimiter
        - 'XX' is any integer [0-99]  
  
  ```console
  $ ./changeMachine -g
  ```
  - Runs the program with a gui
    - Interactive input, output updates dynamically
- ## Run without command line arguments
  ```console
  $ ./changeMachine
  ```
  - Program will prompt the user for input (Same as with command line arguments).
  - Program will run indefinitly (Maybe), until user decides to exit.
---