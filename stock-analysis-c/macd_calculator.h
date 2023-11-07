#ifndef MACD_CALCULATOR_H
#define MACD_CALCULATOR_H

#include "csv_parser.h"

double calculate_macd_for_day(StockData *data);

StockData *
extract_last_26_records(StockData *source_data, int num_records, int start_index);

#endif // MACD_CALCULATOR_H
