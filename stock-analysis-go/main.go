package main

import (
	"bufio"
	"encoding/csv"
	"fmt"
	"os"
	"strconv"
	"sync"
	"time"
)

const threadCount = 100

// StockData represents stock information with Date, Symbol, and Price.
type StockData struct {
	Date   string
	Symbol string
	Price  float64
}

func calculateMovingAverage(data []StockData, windowSize int, threadID int, wg *sync.WaitGroup, threadExecutionTimes chan<- time.Duration) {
	defer wg.Done()

	startIdx := threadID * (len(data) / threadCount)
	endIdx := startIdx + (len(data) / threadCount)
	if threadID == threadCount-1 {
		endIdx = len(data)
	}

	startTime := time.Now()

	for i := startIdx; i < endIdx; i++ {
		sum := 0.0
		count := 0
		for j := i - windowSize + 1; j <= i; j++ {
			if j >= 0 && j < len(data) {
				sum += data[j].Price
				count++
			}
		}
		if count > 0 {
			// movingAverage := sum / float64(count)
			// fmt.Printf("Thread %d - Date: %s, Symbol: %s, Price: %.2f, Moving Average: %.2f\n", threadID, data[i].Date, data[i].Symbol, data[i].Price, movingAverage)
		}
	}

	endTime := time.Now()
	threadExecutionTimes <- endTime.Sub(startTime)
}

func main() {
	file, err := os.Open("data/stock_data_large.csv")
	if err != nil {
		fmt.Println("Error: Could not open CSV file")
		return
	}
	defer file.Close()

	reader := csv.NewReader(bufio.NewReader(file))
	var stockData []StockData
	for {
		line, err := reader.Read()
		if err != nil {
			break
		}
		price, _ := strconv.ParseFloat(line[2], 64)
		stockData = append(stockData, StockData{Date: line[0], Symbol: line[1], Price: price})
	}

	startTime := time.Now()

	var wg sync.WaitGroup
	threadExecutionTimes := make(chan time.Duration, threadCount)

	wg.Add(threadCount)
	for i := 0; i < threadCount; i++ {
		go calculateMovingAverage(stockData, 40, i, &wg, threadExecutionTimes)
	}

	go func() {
		wg.Wait()
		close(threadExecutionTimes)
	}()

	totalExecutionTime := 0.0
	for executionTime := range threadExecutionTimes {
		fmt.Printf("Thread execution time: %.6f seconds\n", executionTime.Seconds())
		totalExecutionTime += executionTime.Seconds()
	}

	avgThreadExecutionTime := totalExecutionTime / float64(threadCount)
	fmt.Printf("Average thread execution time: %.6f seconds\n", avgThreadExecutionTime)

	endTime := time.Now()
	executionTime := endTime.Sub(startTime)
	fmt.Printf("Total Thread execution time: %.6f seconds\n", totalExecutionTime)
	fmt.Printf("Total Main execution time: %.6f seconds\n", executionTime.Seconds())
}
