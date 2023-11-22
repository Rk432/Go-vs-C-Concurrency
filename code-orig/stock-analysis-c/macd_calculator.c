#include "macd_calculator.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

StockData *
extract_last_26_records(StockData *source_data, int num_records, int start_index)
{
    int records_to_extract = 26;
    int extraction_start_index = (start_index - records_to_extract >= 0) ? (start_index - records_to_extract) : 0;

    StockData *extracted_data = malloc(records_to_extract * sizeof(StockData));
    if (extracted_data == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < records_to_extract; ++i)
    {
        extracted_data[i].date = source_data[extraction_start_index + i].date;
        extracted_data[i].price = source_data[extraction_start_index + i].price;
    }

    return extracted_data;
}

static double calculate_ema(StockData *prices, int period)
{
    double multiplier = 2.0 / (period + 1);
    double ema = prices[25].price; // Initial EMA is the closing price of the last day

    for (int i = 24; i >= 26 - period; --i)
    {
        ema = (prices[i].price - ema) * multiplier + ema;
    }

    return ema;
}

double calculate_macd_for_day(StockData *data)
{
    // Calculate 12-period and 26-period EMAs
    double ema12 = calculate_ema(data, 12);
    double ema26 = calculate_ema(data, 26);

    // Calculate MACD for the specific day
    double macd = ema12 - ema26;

    // Print the calculated MACD for the day
    // printf("MACD for the day: %.2f\n", macd);
    return macd;
}
