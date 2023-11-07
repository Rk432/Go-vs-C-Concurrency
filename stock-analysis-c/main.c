#include "csv_parser.h"
#include "macd_calculator.h"
#include "plotter.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int num_records = 400;
StockData companyA_data[450];
StockData companyB_data[450];
StockData companyC_data[450];
StockData companyD_data[450];
StockData companyE_data[450];
double macd_results[5][450];

// Thread function to calculate MACD for a specific day and store the result
void *calculate_macd_and_store(void *args)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);

    int dayToFind = *((int *)args);

    StockData *dataNeeded[5];
    dataNeeded[0] = extract_last_26_records(companyA_data, num_records, dayToFind);
    dataNeeded[1] = extract_last_26_records(companyB_data, num_records, dayToFind);
    dataNeeded[2] = extract_last_26_records(companyC_data, num_records, dayToFind);
    dataNeeded[3] = extract_last_26_records(companyD_data, num_records, dayToFind);
    dataNeeded[4] = extract_last_26_records(companyE_data, num_records, dayToFind);

    // Populate data_for_day array with stock data for each company on the specific day
    // Populate data_for_day array for each company
    for (int company = 0; company < 5; ++company)
    {
        macd_results[company][dayToFind] = calculate_macd_for_day(dataNeeded[company]);
    }

    free(args); // Free the allocated memory for the day copy

    gettimeofday(&end, NULL);
    double *thread_time = malloc(sizeof(double));
    *thread_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    pthread_exit((void *)thread_time);
}

int main()
{
    // Read data from CSV files for each company
    read_csv("../stock_data/CompanyA_stock_prices.csv", companyA_data);
    read_csv("../stock_data/CompanyB_stock_prices.csv", companyB_data);
    read_csv("../stock_data/CompanyC_stock_prices.csv", companyC_data);
    read_csv("../stock_data/CompanyD_stock_prices.csv", companyD_data);
    read_csv("../stock_data/CompanyE_stock_prices.csv", companyE_data);

    // Initialize threads and data for MACD calculation
    pthread_t threads[num_records];

    // Initialize all elements to 0
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < num_records; ++j)
        {
            macd_results[i][j] = 0.0;
        }
    }

    struct timeval startMain, endMain; // Added variables to measure total execution time
    gettimeofday(&startMain, NULL);

    // Create threads for each day to calculate MACD for each company
    for (int day = 26; day < 26 + num_records; ++day)
    {
        int *day_copy = malloc(sizeof(int)); // Allocate memory for the day copy
        *day_copy = day;                     // Copy the value of day to day_copy
        pthread_create(&threads[day - 26], NULL, calculate_macd_and_store, (void *)day_copy);
    }

    // Wait for all threads to complete and calculate total thread time
    double total_thread_time = 0;
    for (int day = 26; day < 26 + num_records; ++day)
    {
        double *thread_time;
        pthread_join(threads[day - 26], (void **)&thread_time);
        printf("Thread %d execution time: %.9f seconds\n", (day - 26) + 1, *thread_time);
        total_thread_time += *thread_time;
        free(thread_time);
    }

    // Calculate and print average thread time
    double average_thread_time = total_thread_time / num_records;
    printf("Average thread execution time: %.9f seconds\n", average_thread_time);

    gettimeofday(&endMain, NULL);
    double executionTime = (endMain.tv_sec - startMain.tv_sec) + (endMain.tv_usec - startMain.tv_usec) / 1e6;
    printf("Total Main execution time: %.9f seconds\n", executionTime);

    createLineChart(macd_results[0], 450, "CompanyA_MACD_C.png");
    createLineChart(macd_results[1], 450, "CompanyB_MACD_C.png");
    createLineChart(macd_results[2], 450, "CompanyC_MACD_C.png");
    createLineChart(macd_results[3], 450, "CompanyD_MACD_C.png");
    createLineChart(macd_results[4], 450, "CompanyE_MACD_C.png");

    return 0;
}
