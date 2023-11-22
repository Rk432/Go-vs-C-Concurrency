# Go-vs-C-Concurrency

Stock Price Analysis using concurrency approach

## Group - 10

- Rohit Kodam - 2020B3A71141G
- Anshul Bharti - 2020B3A71262G
- Anish Kamath - 2020B3A71085G
- Abhinav Setia - 2020B3A71784G

## Table of Contents

- [How to run code](#how-to-run-code)
- [Problem Statement](#problem-statement)
- [Software Architecture](#software-architecture)
- [POPL Aspects](#popl-aspects)
- [Results](#results)
- [Potential for future work](#potential-for-future-work)

## How to run code

### Prerequisites

- Linux machine as the code uses pthreads library
- gcc for C code compilation
- go runtime install by following docs at [go.dev/doc/install](https://go.dev/doc/install)

### C code

- C project directory
  
  ```bash
  cd ./code-orig/stock-analysis-c
  ```

- Compilation to Executable

  ```bash
  make
  ```

- Run

  ```bash
  ./a.out
  ```

### Go code

- Go project directory
  
  ```bash
  cd ./code-orig/stock-analysis-go
  ```

- Plotting Libraries Installation

  ```bash
  go get gonum.org/v1/plot/...
  ```

- Compilation to Executable

  ```bash
  go build
  ```

- Run

  ```bash
  ./stock-analysis-go
  ```

### To generate new csv data file

- Run the python file at root dir

  ```bash
  cd ./code-external
  
  python3 generate_stock_data.py
  ```

## Problem Statement

We are trying to compare Multithreading of Software vs Hardware threads. Ofcourse this is in use from before traditionally in servers Go is used for faster calculation intensive tasks using its Goroutines(threads) for less latency in realtime apis (like stock data metrics, graphs etc). So in use developers prefer Go (Golang) over Python(Flask/Django frramework) for server. And this was the motivation to explore Go via this project. As we wanted to compare similar things , multithreading vs single threaded languages was not the choice so we thought of comparing the traditional C in linux which has pthreads for multithreading with Go's Goroutines.

And Go has its own aspects which makes it more important to explore, as it has its ecosystem of frameworks and community and use in realtime servers. Go also has easy to understand syntax. Go is founded by Google developers which consisted of the legendary Ken Thompson who is the inventer of language B which is the predecessor of C language.

## Software Architecture

This is meant to be as a server side code of a realtime stock analysis product. And we tried to implement some computation aspects of it in out project , we did not implement the server/api aspect as it was not our project aim.
The whole code was written by us we just refered to some Go systax to implement the Go part of the project. MACD (moving average convergence divergence) an economic metric of stocks its formula was used by us in this project.
We are basically doing a computation intensive task using threads and comparing the time / memory usage by varing the number of threads we use and draw conclusions based on that.

Following is a difference between Golang's Gorutines vs Threads from [Geeks For Geeks](https://www.geeksforgeeks.org/golang-goroutine-vs-thread/)

![image](https://github.com/Rohitkk432/Go-vs-C-Concurrency/assets/74586376/1e164c41-ab34-491b-ba3e-e5c72ebf010e)

## Popl Aspects

- **Concurrency**: In Go, concurrency is a first-class citizen, supported by goroutines (lightweight threads) and channels, offering a clean and straightforward syntax for managing concurrent tasks. On the other hand, C lacks built-in support for concurrency, and on platforms like Linux, developers typically resort to using libraries such as pthreads to achieve concurrent execution.

- **Memory Management**: Go simplifies memory management with a garbage collector, automating memory handling to reduce the likelihood of memory leaks. In contrast, C relies on manual memory management, granting developers direct control over allocation and deallocation for more fine-grained control but requiring careful attention to avoid memory-related issues.

   Difficulties faced  - In C it is difficult to figure out exactly where the memory should be deallocated/freed or clashes / null reference will occur. Where as in Go we didnt need to think about the memory.
   example : line 91 of [main.c](https://github.com/Rohitkk432/Go-vs-C-Concurrency/blob/main/code-orig/stock-analysis-c/main.c)

- **Static Typing**: Go is statically typed with some type inference, necessitating variable type declarations at compile time but maintaining a cleaner syntax. Meanwhile, C is also statically typed, requiring explicit type declarations for each variable at compile time.

  Difficulty faced  - In C the threads argument passing to runner function and retrieving the return value is a pain to deal with for new adopters. where as in Go it was pretty straitforward to understand.
  example : In C line 25,44,47 for runner function and line 80 thread creation with arguments , line 88 retrieving return value in [main.c](https://github.com/Rohitkk432/Go-vs-C-Concurrency/blob/main/code-orig/stock-analysis-c/main.c)
  where as in Go Line 60 arguement passing was just line a function and we just add go at start of the function call [main.go](https://github.com/Rohitkk432/Go-vs-C-Concurrency/blob/main/code-orig/stock-analysis-go/main.go)

- **Error Handling**: Go takes a distinctive approach to error handling, using multiple return values, with the second often reserved for error information. In C, error handling typically involves return codes or global variables.

  example line 84 in [main.go](https://github.com/Rohitkk432/Go-vs-C-Concurrency/blob/main/code-orig/stock-analysis-go/main.go) where we are doing a systemcall to get memory usage info.
  
- **Syntax and Readability**: Go is designed for simplicity and readability, featuring a clean syntax and a minimalistic approach to language features. Conversely, C has a relatively simple syntax but allows low-level manipulation, potentially sacrificing readability for more complex tasks.

- **Package Management**: Go includes a built-in dependency management system called "go modules," streamlining the process of managing external dependencies. In contrast, C lacks a built-in package manager, necessitating manual downloading and linking of libraries.

- **Tooling**: Go provides a comprehensive set of tools, including a built-in formatter (gofmt), a testing framework, and a package manager. In contrast, C has a more minimalistic toolset, often relying on external tools and libraries for development.

- **Portability**: Go is designed for high portability, enabling code to be compiled and run on different platforms with ease. In comparison, while C code can be portable, ensuring compatibility across different platforms may require additional effort.

## Results

### Outputs

- Getting MACD for 400 days for 5 companies
- One thread finds MACD for a day for all 5 companies
- Therefore we are running 400 threads

### Execution Time Comparison -

#### C program

```
Average thread execution time: 0.000008092 seconds
Total Main execution time: 0.017068000 seconds
```

#### Go program

```
Average thread execution time: 0.000210678 seconds
Total Main execution time: 0.003490984 seconds
```

- This C is better in terms of avg thread execution time as it does not have a garbage collector like Go.
- But in terms of the execution of main function where threads are created --> main function waits --> threads joined Go is Faster.
- Because Goroutines are part of Go runtime and not bounded by kernel / hardware (software threads) , whereas in C threads are created by kernel and are hardware threads.
- Hence Goroutines have faster startup and destroy times compared to C pthreads.
- This Pretty much remains same across different number of threads

### Variation in Number of Threads -

| Threads     | C Main (in miliseconds) | Go Main (in miliseconds) | C pthreads Avg time (in miliseconds) | Go Goroutines Avg time (in miliseconds) |
| ----------- | ----------------------- | ------------------------ | --------------------------- | ------------------------------ |
| 20          | 1.210000                | 0.245596                 | 0.033600                    | 0.021921                       |
| 50          | 2.739000                | 0.468968                 | 0.029140                    | 0.022892                       |
| 100         | 6.879000                | 0.657984                 | 0.014810                    | 0.023142                       |
| 200         | 11.591000               | 3.473497                 | 0.012870                    | 0.048333                       |
| 400         | 17.068000               | 3.490984                 | 0.008092                    | 0.210678                       |

Total Main Thread Exec time Comparison             |  Avg Thread Exec time Comparison
:-------------------------:|:-------------------------:
![image](https://github.com/Rohitkk432/Go-vs-C-Concurrency/assets/74586376/6fc877d5-dfb5-43d7-ba92-6394fbb392ab) | ![image](https://github.com/Rohitkk432/Go-vs-C-Concurrency/assets/74586376/494594fa-35d6-4d56-b890-dc5efa570a64)

- From above result we can see that Go Main Execution time is pretty stable compared to C where it increases with increasing number of threads.
- Whereas C Avg Thread Execution time is more or less same where as it increases in case of Go with increasing number of threads.

### Memory Usage -

- There aren't any easy ways to find the thread memory usage in C.
- And in Go as well as Goroutines are not bounded by kernel they dont have anything like PID.
- So we decided to find the whole program memory usage using the PID of the program/process.
- We used pmap to find the memory usage (output stored in file memory.txt)

#### C Program Memory Usage

```
Address           Kbytes     RSS   Dirty
-----------------------------------------
[  refer to memory.txt for whole data   ]
-----------------------------------------
total kB          232488    3320    1260
```

#### Go program Memory Usage

```
Address           Kbytes     RSS   Dirty
-----------------------------------------
[  refer to memory.txt for whole data   ]
-----------------------------------------
total kB         1235816   12572    6808
```

#### Similar trend with varying number of threads

```
Memory Usage
 
============== 400 Threads ==============

Address           Kbytes     RSS   Dirty
-----------------------------------------
[  refer to memory.txt for whole data   ]
-----------------------------------------
# C program :
total kB          232488    3320    1260 
# Go program :
total kB         1235816   12572    6808
 
============== 200 Threads ==============

Address           Kbytes     RSS   Dirty
-----------------------------------------
[  refer to memory.txt for whole data   ]
-----------------------------------------
# C program :
total kB          232488    2820     764
# Go program :
total kB         1234728    9892    4128
 
============== 100  Threads ==============

Address           Kbytes     RSS   Dirty
-----------------------------------------
[  refer to memory.txt for whole data   ]
-----------------------------------------
# C program :
total kB          232356    2580     540
# Go program :
total kB         1234984    8572    2808
 
============== 50 Threads ==============

Address           Kbytes     RSS   Dirty
-----------------------------------------
[  refer to memory.txt for whole data   ]
-----------------------------------------
# C program :
total kB          232356    2468     408
# Go program :
total kB         1234728    8080    2316
  
============== 20 Threads ==============

Address           Kbytes     RSS   Dirty
-----------------------------------------
[  refer to memory.txt for whole data   ]
-----------------------------------------
# C program :
total kB          297892    2400     340 
# Go program :
total kB         1234728    7796    2032
```

- In this case C has better results as it is not garbage collected.
- Go makes Multithreading faster but it needs to have some overhead in terms of memory to achieve that.
- Hence Go runtime ends up using more memory to run a Go program.

## Potential for future work

- In terms for the topic we want to include few more economic matrics, and find buy sell signals at any given moment.
- In terms of more exploration of Go , channels can be explored in go which helps in easy communication between threads.
- Memory utilization could not be found for each thread , goroutine as there is no easy or known method to find the same.
