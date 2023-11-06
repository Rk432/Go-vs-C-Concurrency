#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include "analysis/movingaverage.h"

// Declare global variables for shared data
StockData *stockData;
int dataSize;
int threadCount = 100; // Number of threads for concurrent processing

typedef struct
{
    StockData *data;
    int dataSize;
    int threadId;
    int windowSize;
    double threadExecutionTime;
} ThreadData;

void *calculateMovingAverageThread(void *arg)
{
    ThreadData *threadData = (ThreadData *)arg;
    int startIdx = threadData->threadId * (threadData->dataSize / threadCount);
    int endIdx = (threadData->threadId == threadCount - 1) ? threadData->dataSize : startIdx + (threadData->dataSize / threadCount);

    // Measure the execution time of the thread
    struct timeval threadStart, threadEnd;
    gettimeofday(&threadStart, NULL);

    // Perform moving average analysis within the specified window size for the thread's portion of the data
    for (int i = startIdx; i < endIdx; ++i)
    {
        double movingAverage = calculateMovingAverage(threadData->data, threadData->dataSize, i, threadData->windowSize);
        // printf("Thread %d - Date: %s, Symbol: %s, Price: %.2f, Moving Average: %.2f\n",
        //        threadData->threadId, threadData->data[i].date, threadData->data[i].symbol, threadData->data[i].price, movingAverage);
    }

    gettimeofday(&threadEnd, NULL);
    threadData->threadExecutionTime = (threadEnd.tv_sec - threadStart.tv_sec) + (threadEnd.tv_usec - threadStart.tv_usec) / 1e6;

    pthread_exit(NULL);
}

int main()
{
    // Open and read stock data from CSV file
    FILE *file = fopen("data/stock_data_large.csv", "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open CSV file\n");
        exit(EXIT_FAILURE);
    }

    // Count the number of lines in the CSV file
    int lines = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        lines++;
    }
    rewind(file);

    // Allocate memory for stockData
    stockData = malloc(lines * sizeof(StockData));
    if (stockData == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Read data from CSV file into stockData array
    int index = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        sscanf(buffer, "%[^,],%[^,],%lf", stockData[index].date, stockData[index].symbol, &stockData[index].price);
        index++;
    }
    dataSize = lines;

    fclose(file);

    struct timeval start, end; // Added variables to measure total execution time
    gettimeofday(&start, NULL);

    // Create threads for concurrent moving average calculations
    double totalThreadExecutionTime = 0.0;
    pthread_t threads[threadCount];
    ThreadData threadData[threadCount];

    for (int i = 0; i < threadCount; ++i)
    {
        threadData[i].data = stockData;
        threadData[i].dataSize = dataSize;
        threadData[i].threadId = i;
        threadData[i].windowSize = 40; // Example window size

        int result = pthread_create(&threads[i], NULL, calculateMovingAverageThread, (void *)&threadData[i]);
        if (result != 0)
        {
            fprintf(stderr, "Error: Failed to create thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // Wait for threads to complete
    for (int i = 0; i < threadCount; ++i)
    {
        pthread_join(threads[i], NULL);
        printf("Thread %d execution time: %.6f seconds\n", i, threadData[i].threadExecutionTime);
        totalThreadExecutionTime += threadData[i].threadExecutionTime;
    }

    // Calculate average thread execution time
    double avgThreadExecutionTime = totalThreadExecutionTime / threadCount;

    printf("Average thread execution time: %.6f seconds\n", avgThreadExecutionTime);

    gettimeofday(&end, NULL);
    double executionTime = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;

    printf("Total Thread execution time: %.6f seconds\n", totalThreadExecutionTime);
    printf("Total Main execution time: %.6f seconds\n", executionTime);

    // Free allocated memory and perform cleanup
    free(stockData);

    return 0;
}
