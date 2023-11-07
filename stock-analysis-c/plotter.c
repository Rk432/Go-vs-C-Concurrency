#include "plotter.h"
#include <stdio.h>
#include <stdlib.h>

void createLineChart(double *data, int num_records, const char *filename)
{
    FILE *gp = popen("gnuplot -persist", "w");
    if (gp == NULL)
    {
        fprintf(stderr, "Error: Could not open gnuplot.\n");
        return;
    }

    fprintf(gp, "set terminal pngcairo enhanced font 'arial,10' size 800,600\n");
    fprintf(gp, "set output '%s'\n", filename);
    fprintf(gp, "plot '-' with lines title 'Data'\n");

    for (int i = 0; i < num_records; ++i)
    {
        fprintf(gp, "%d %f\n", i + 1, data[i]);
    }
    fprintf(gp, "e\n");

    fflush(gp);
    pclose(gp);
}