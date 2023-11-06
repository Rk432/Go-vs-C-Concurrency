#include "movingaverage.h"

double calculateMovingAverage(StockData *data, int dataSize, int currentIndex, int windowSize)
{
    double sum = 0;
    int count = 0;

    // Calculate moving average within the specified window size
    for (int i = currentIndex - windowSize + 1; i <= currentIndex; ++i)
    {
        if (i >= 0 && i < dataSize)
        {
            sum += data[i].price;
            count++;
        }
    }

    if (count > 0)
    {
        return sum / count;
    }
    else
    {
        return 0; // No valid data points within the window
    }
}
