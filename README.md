# README

## Introduction

Welcome to **SLOC++**, a command-line tool for analyzing C/C++ source files. This application counts lines of code (LOC), comments, and blank lines, providing insights into software complexity and documentation practices. It supports single files and entire directories, offering flexible sorting options for results.

## Features
- Processes **C/C++ source files** (`.c`, `.cpp`, `.h`, `.hpp`)
- Supports **directory input** (including recursive search `-r`)
- **Sorting options** by filename, file type, comments, blank lines, SLOC, or total lines
- **Percentage breakdown** of each category
- Handles **nested comments and string literals** correctly
- Provides **detailed error messages** for unsupported files or incorrect usage

## Usage
```
$ ./sloc [options] file/directory
Options:
  -h/--help       Display usage information.
  -r              Look for files recursively in directories.
  -s f/t/c/b/s/a  Sort in ascending order by filename, file type, comments, blank lines, SLOC, or total lines.
  -S f/t/c/b/s/a  Sort in descending order.
```

### Example Output
```
$ ./sloc src/main.cpp
Files processed: 1
-----------------------------------------------------------------------------------------
Filename            Language        Comments        Blank           Code            All
-----------------------------------------------------------------------------------------
src/main.cpp        C++             140 (29.9%)     43 (9.2%)       320 (68.4%)     468
-----------------------------------------------------------------------------------------
```

## Compilation & Execution

### Requirements
- **CMake** (for build automation)
- **C++ Compiler** supporting C++17 or later

### Steps
1. Clone the repository: `git clone <repo-url>`
2. Navigate to the project directory: `cd <repo-name>`
3. Create a build directory: `mkdir build && cd build`
4. Generate build files: `cmake ..`
5. Compile the project: `cmake --build .`
6. Run the program: `./sloc <file/directory>`

## Error Handling
The program detects and handles the following errors gracefully:
- **Nonexistent file or directory:**
  ```
  $ ./sloc file.cpp
  Sorry, unable to read "file.cpp".
  ```
- **Unsupported file type:**
  ```
  $ ./sloc file.tex
  Sorry, ".tex" files are not supported at this time.
  ```
- **Empty directory (no valid files):**
  ```
  $ ./sloc src
  Sorry, unable to find any supported source file inside directory "src".
  ```
- **Invalid sorting options or arguments**

## Author(s)
- **Bianca Maciel Medeiros** (*bianca.medeiros.701@ufrn.edu.br*)
- **Marina Medeiros Araujo Leite** (*marinamaleite@gmail.com*)

&copy; DIMAp/UFRN 2024

