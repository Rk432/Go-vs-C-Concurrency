package csvparser

import (
	"encoding/csv"
	"os"
	"stock-analysis-go/stockdata"
	"strconv"
)

func ReadCSV(filePath string, numRecords int) []stockdata.StockData {
	file, err := os.Open(filePath)
	if err != nil {
		panic(err)
	}
	defer file.Close()

	reader := csv.NewReader(file)
	records, err := reader.ReadAll()
	if err != nil {
		panic(err)
	}

	var data []stockdata.StockData
	for i := 1; i <= numRecords; i++ {
		price, _ := strconv.ParseFloat(records[i][1], 64)
		data = append(data, stockdata.StockData{
			Date:  records[i][0],
			Price: price,
		})
	}

	return data
}
