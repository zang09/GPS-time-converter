#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>

// Define GPS leap seconds
int leaps[18] = {46828800, 78364801, 109900802, 173059203, 252028804, 315187205, 346723206, 393984007, 425520008, 457056009, 504489610, 551750411, 599184012, 820108813, 914803214, 1025136015, 1119744016, 1167264017};

// Test to see if a GPS second is a leap second
bool isleap(int gpsTime)
{
    bool isLeap = false;
    int lenLeaps = sizeof(leaps);

    for (int i = 0; i < lenLeaps; i++)
    {
        if (gpsTime == leaps[i])
        {
            isLeap = true;
        }
    }

    return isLeap;
}

// Count number of leap seconds that have passed
int countleaps(int gpsTime, const char* dirFlag)
{
    int lenLeaps = sizeof(leaps);

    int nleaps = 0;  // number of leap seconds prior to gpsTime

    for (int i = 0; i < lenLeaps; i++)
    {
        if (!strcmp("unix2gps", dirFlag))
        {
            if (gpsTime >= leaps[i] - i)
            {
                nleaps++;
            }
        }
        else if (!strcmp("gps2unix", dirFlag))
        {
            if (gpsTime >= leaps[i])
            {
                nleaps++;
            }
        }
        else
        {
            printf("ERROR Invalid Flag!");
        }
    }

    return nleaps;
}

// Convert Unix Time to GPS Time
int unix2gps(int unixTime)
{
    bool isLeap;

    // Add offset in seconds
    if (fmod(unixTime, 1) != 0)
    {
        unixTime = unixTime - 0.5;
        isLeap = true;
    }
    else
    {
        isLeap = false;
    }

    int gpsTime = unixTime - 315964800;
    int nleaps = countleaps(gpsTime, "unix2gps");

    gpsTime += nleaps + isLeap;

    return gpsTime;
}


// Convert GPS Time to Unix Time
int gps2unix(int gpsTime)
{
    // Add offset in seconds
    int unixTime = gpsTime + 315964800;
    int nleaps = countleaps(gpsTime, "gps2unix");

    unixTime -= nleaps;

    if (isleap(gpsTime))
    {
        unixTime = unixTime + 0.5;
    }

    return unixTime;
}


int main()
{
    int time = unix2gps(1611130000);
    int time2 = gps2unix(time);
    printf("time: %d, time2: %d\n", time, time2);

    return 0;
}
