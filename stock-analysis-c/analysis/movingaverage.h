#ifndef MOVINGAVERAGE_H
#define MOVINGAVERAGE_H

typedef struct
{
    char date[20];
    char symbol[10];
    double price;
} StockData;

double calculateMovingAverage(StockData *data, int dataSize, int currentIndex, int windowSize);

#endif // MOVINGAVERAGE_H
