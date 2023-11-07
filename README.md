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
  gcc -o myprogram main.c csv_parser.c macd_calculator.c plotter.c -lpthread -lm
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
 
### C program

```
Average thread execution time: 0.000008092 seconds
Total Main execution time: 0.017068000 seconds
```

### Go program

```
Average thread execution time: 0.000210678 seconds
Total Main execution time: 0.003490984 seconds
```
