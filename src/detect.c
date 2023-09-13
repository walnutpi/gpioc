
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

int detect()
{
    FILE *fp;
    char buffer[1024];
    char *compatible;
    int i;

    fp = fopen("/proc/device-tree/compatible", "r");
    if (fp == NULL)
    {
        printf("Failed to open /proc/device-tree/compatible \n");
        return -1;
    }

    fgets(buffer, 100, fp);
    fclose(fp);

    compatible = strtok(buffer, "\n");

    for (i = 0; i < (int)sizeof(chips_compatible); i++)
    {
        if (strcmp(compatible, chips_compatible[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}