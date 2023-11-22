#include "csv_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *get_field(char *line, int num)
{
    const char *tok, *tok2;

    if (num == 1)
    {
        tok = strtok(line, ",");
        return tok;
    }
    else
    {
        tok2 = strtok(NULL, ",\n");
        return tok2;
    }
}

void read_csv(const char *file_path, StockData *data)
{
    FILE *file = fopen(file_path, "r");
    if (!file)
    {
        fprintf(stderr, "Error: Unable to open file %s\n", file_path);
        exit(EXIT_FAILURE);
    }

    // Determine the number of records (lines) in the CSV file
    int num_records = 0;
    char line[1024];
    while (fgets(line, 1024, file) != NULL)
    {
        num_records++;
    }
    rewind(file);

    fgets(line, 1024, file);
    // Read data from CSV file and populate StockData array
    for (int i = 0; i < num_records - 1; i++)
    {
        fgets(line, 1024, file);
        char *date = strdup(get_field(line, 1));
        double price = atof(get_field(line, 2));
        // break;
        data[i].date = date;
        data[i].price = price;
    }

    fclose(file);
}
