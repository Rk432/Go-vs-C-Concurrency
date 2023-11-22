#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include <stdio.h>

typedef struct
{
    char *date;
    double price;
} StockData;

void read_csv(const char *file_path, StockData *data);

#endif // CSV_PARSER_H
