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
  gcc -o myprogram main.c analysis/movingaverage.c -lpthread -lm
  ```
- Run 

  ```bash
  ./myprogram
  ```

### Go code
- Go project directory
  
  ```bash
  cd stock-analysis-go
  ```
- Compilation to Executable

  ```bash
  go build main.go
  ```
- Run 

  ```bash
  ./main
  ```

## Outputs

With 100 Threads and 40 window MACD
 
### C program

```
Average thread execution time: 0.001935 seconds
Total Thread execution time: 0.193539 seconds
Total Main execution time: 0.028249 seconds
```

### Go program

``` 
Average thread execution time: 0.000626 seconds
Total Thread execution time: 0.062599 seconds
Total Main execution time: 0.014623 seconds
```
