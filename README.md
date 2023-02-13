### Project 1: A Few Unix Systems Utilities

#### Project Statement: 
Develop a few Unix systems utilities for process and filesystem management

#### Project Objectives: 
Practicing Unix system calls, understanding Unix process and filesystem management

#### Steps to execute
- run `make clean` before executing the c code
- ##### mytree.c: 
    - This program prints out similar to Unix command tree in a <b>sorted</b> order.
    - run `make mytree` to comiple.
    - run `./mytree.x [dir]` to view the output, [dir] is optional.

- ##### mytime.c:
    - This program works similar to time command in Unix.
    - run `make mytime` to compile.
    - run `./mytime.x cmd [args]`, cmd and [args] are optional.

- ##### mymtimes.c:
    - This program prints the total count of all files modified in last 24 hours.
    - run `make mymtimes` to compile.
    - run `./mymtimes.x [dir]`, [dir] is optional.

- Run `make clean` to remove all the binary files.


