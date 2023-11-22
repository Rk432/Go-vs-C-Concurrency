package macdcalculator

import (
	"stock-analysis-go/stockdata"
)

// CalculateMACDForDay calculates MACD for a specific day using the given stock data and MACD results array.
func CalculateMACDForDay(company []stockdata.StockData) float64 {

	ema12 := calculateEMA(company, 12)
	ema26 := calculateEMA(company, 26)

	return ema12 - ema26
}

// extractLast26Records extracts the last 26 records before the given day index for all companies.
func ExtractLast26Records(day int, company []stockdata.StockData) []stockdata.StockData {
	var extractedData []stockdata.StockData

	for i := day - 26; i < day; i++ {
		// Handle out-of-bounds index
		if i >= 0 {
			extractedData = append(extractedData, company[i])
		}
	}

	return extractedData
}

// calculateEMA calculates the Exponential Moving Average for the given stock data and period.
func calculateEMA(prices []stockdata.StockData, period int) float64 {
	if len(prices) < period {
		return 0.0
	}

	multiplier := 2.0 / float64(period+1)
	ema := prices[25].Price

	for i := 24 ; i >= 26 - period ; i-- {
		ema = (prices[i].Price-ema)*multiplier + ema
	}

	return ema
}
