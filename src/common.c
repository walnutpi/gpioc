#include <stdio.h>
#include <string.h>
#include "common.h"

static char *chips_compatible[] = {
    "占位符",
    "sun50i-h616"};

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

    // printf("compatible=\t%s\r\n",buffer);
    compatible = strtok(buffer, "\n");

    for (i = 0; i < (int)sizeof(chips_compatible)/(int)sizeof(char *); i++)
    {
        // printf("[%d]=%s\r\n", i, chips_compatible[i]);
        if (strstr(compatible, chips_compatible[i]) != NULL)
        {
            return i;
        }
    }
    return -1;
}