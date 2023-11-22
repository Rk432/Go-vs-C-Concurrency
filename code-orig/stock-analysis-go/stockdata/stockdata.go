package stockdata

// StockData represents the structure for stock data, including date and price.
type StockData struct {
	Date  string
	Price float64
}

// ExtractLastNRecords extracts the last N records from the given stock data slice starting from the specified index.
func ExtractLastNRecords(startIndex, numRecords int, data []StockData) []StockData {
	endIndex := startIndex + numRecords
	if endIndex > len(data) {
		endIndex = len(data)
	}

	return data[startIndex:endIndex]
}