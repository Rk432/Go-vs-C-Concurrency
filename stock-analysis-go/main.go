package main

import (
	"fmt"
	"stock-analysis-go/csvparser"
	"stock-analysis-go/macdcalculator"
	"stock-analysis-go/stockdata"
	"stock-analysis-go/plotchart"
	"sync"
	"time"
	"os"
	"os/exec"
)

const numRecords = 400

func calculateMACDAndStore(day int, companyA, companyB, companyC, companyD, companyE []stockdata.StockData, macdResults [][]float64, wg *sync.WaitGroup, threadTimes chan float64) {
	defer wg.Done()

	start := time.Now()

	dataNeeded := make([][]stockdata.StockData, 5);
	dataNeeded[0] = macdcalculator.ExtractLast26Records(day, companyA);
	dataNeeded[1] = macdcalculator.ExtractLast26Records(day, companyB);
	dataNeeded[2] = macdcalculator.ExtractLast26Records(day, companyC);
	dataNeeded[3] = macdcalculator.ExtractLast26Records(day, companyD);
	dataNeeded[4] = macdcalculator.ExtractLast26Records(day, companyE);

	for i := range macdResults {
		macdResults[i][day] = macdcalculator.CalculateMACDForDay(dataNeeded[i])
	}

	end := time.Now()
	threadTime := end.Sub(start).Seconds()

	threadTimes <- threadTime
}

func main() {
	var wg sync.WaitGroup
	threadTimes := make(chan float64, numRecords)

	companyAData := csvparser.ReadCSV("../stock_data/CompanyA_stock_prices.csv", 450)
	companyBData := csvparser.ReadCSV("../stock_data/CompanyB_stock_prices.csv", 450)
	companyCData := csvparser.ReadCSV("../stock_data/CompanyC_stock_prices.csv", 450)
	companyDData := csvparser.ReadCSV("../stock_data/CompanyD_stock_prices.csv", 450)
	companyEData := csvparser.ReadCSV("../stock_data/CompanyE_stock_prices.csv", 450)

	macdResults := make([][]float64, 5)
	for i := range macdResults {
		macdResults[i] = make([]float64, 450)
	}

	var totalThreadTime float64

	startMain := time.Now()

	for day := 26; day < 26 + numRecords; day++ {
		wg.Add(1)
		go calculateMACDAndStore(day, companyAData, companyBData, companyCData, companyDData, companyEData, macdResults, &wg, threadTimes)
	}

	go func() {
		wg.Wait()
		close(threadTimes)
	}()

	for threadTime := range threadTimes {
		fmt.Printf("Thread execution time: %.9f seconds\n", threadTime)
		totalThreadTime += threadTime
	}

	averageThreadTime := totalThreadTime / float64(numRecords)
	fmt.Printf("Average thread execution time: %.9f seconds\n", averageThreadTime)

	endMain := time.Now()
	mainExecutionTime := endMain.Sub(startMain).Seconds()

	fmt.Printf("Total Main execution time: %.9f seconds\n", mainExecutionTime)

	command := fmt.Sprintf("pmap -x %d > memory.txt", os.Getpid())
	cmd := exec.Command("bash","-c",command);

	_, err := cmd.CombinedOutput()
	if err != nil {
		fmt.Println("Error running pmap command:", err)
		return
	}

	err = plotchart.PlotMACDChart(macdResults[0], "CompanyA_MACD.png")
	if err != nil {
		fmt.Println("Error plotting MACD chart:", err)
	}
	err = plotchart.PlotMACDChart(macdResults[1], "CompanyB_MACD.png")
	if err != nil {
		fmt.Println("Error plotting MACD chart:", err)
	}
	err = plotchart.PlotMACDChart(macdResults[2], "CompanyC_MACD.png")
	if err != nil {
		fmt.Println("Error plotting MACD chart:", err)
	}
	err = plotchart.PlotMACDChart(macdResults[3], "CompanyD_MACD.png")
	if err != nil {
		fmt.Println("Error plotting MACD chart:", err)
	}
	err = plotchart.PlotMACDChart(macdResults[4], "CompanyE_MACD.png")
	if err != nil {
		fmt.Println("Error plotting MACD chart:", err)
	}

}
