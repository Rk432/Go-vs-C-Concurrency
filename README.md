# Go-vs-C-Concurrency
Stock Price Analysis using concurrency approach

# How to run code
### Prerequisites
- Linux machine as the code uses pthreads library
- gcc for C code compilation
- go runtime install by following docs at [go.dev/doc/install](https://go.dev/doc/install)

### C code
- C project directory
  
  ```bash
  cd stock-analysis-c
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
  cd stock-analysis-go
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
  python3 generate_stock_data.py
  ```

## Outputs

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

#### Variation in Number of Threads

| Threads     | C Main (in miliseconds) | Go Main (in miliseconds) | C pthreads Avg time (in miliseconds) | Go Goroutines Avg time (in miliseconds) |
| ----------- | ----------------------- | ------------------------ | --------------------------- | ------------------------------ |
| 20          | 1.210000                | 0.245596                 | 0.033600                    | 0.021921                       |
| 50          | 2.739000                | 0.468968                 | 0.029140                    | 0.022892                       |
| 100         | 6.879000                | 0.657984                 | 0.014810                    | 0.023142                       |
| 200         | 11.591000               | 3.473497                 | 0.012870                    | 0.048333                       |
| 400         | 17.068000               | 3.490984                 | 0.008092                    | 0.210678                       |

![image](https://github.com/Rohitkk432/Go-vs-C-Concurrency/assets/74586376/9d536b7a-eb55-4a4d-abf4-be4ab919249d)

![image](https://github.com/Rohitkk432/Go-vs-C-Concurrency/assets/74586376/4132b8fd-c0ac-4f24-9cbc-299e49d2e1c6)

- From above result we can see that Go Main Execution time is pretty stable compared to C where it increases with increasing number of threads.
- Whereas C Avg Thread Execution time is more or less same where as it increases in case of Go with increasing number of threads.

### Memory Usage

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

- In this case C has better results as it is not garbage collected.
- Go makes Multithreading faster but it needs to have some overhead in terms of memory to achieve that.
- Hence Go runtime ends up using more memory to run a Go program.
