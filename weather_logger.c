// --------------------------------------------------
// -*- C -*- Compatibility Header
//
// Copyright (C) 2023 Developer Jarvis (Pen Name)
//
// This file is part of the weather_logger Library. This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// SPDX-License-Identifier: GPL-3.0-or-later
//
// weather_logger - Simulate temperature logs for each hour and save results
//
// Author: Developer Jarvis (Pen Name)
// Contact: https://github.com/DeveloperJarvis
//
// --------------------------------------------------

// --------------------------------------------------
// header files
// --------------------------------------------------
#include <stdio.h>  // for printf()
#include <string.h> // for strcmp()
#include <stdlib.h> // for atoi()

#include "weather_logger.h"

// --------------------------------------------------
// function prototypes (internal)
// --------------------------------------------------
static void run_single_day(const char *outfile);
static void run_multiple_days(int days, const char *outfile);

// --------------------------------------------------
// Main function (argument parsing)
// --------------------------------------------------
int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        // default: simulate 1 day, print to console only
        weather_logger(argc, NULL);
    }
    else if (argc == 2)
    {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
            display_help(argv[0]);
        else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)
            display_version(argv[0]);
        else
        {
            // unknown -> default behaviour
            weather_logger(argc, NULL);
        }
    }
    else if (argc == 3)
    {
        // option -o FILE -> write logs to output file
        if (strcmp(argv[1], "-o") == 0)
        {
            weather_logger(argc, argv[2]);
        }
        // option -n DAYS -> simulate multiple days
        else if (strcmp(argv[1], "-n") == 0)
        {
            int days = atoi(argv[2]);
            if (days < 1 || days > MAX_DAYS)
            {
                printf("Invalid DAYS value. Must be 1-%d\n", MAX_DAYS);
                return 1;
            }
            run_multiple_days(argc, NULL);
        }
    }
    else if (argc == 5)
    {
        if (strcmp(argv[1], "-n") == 0 && strcmp(argv[3], "-o") == 0)
        {
            // example:   -n 3 -o output.txt
            int days = atoi(argv[2]);
            if (days < 1 || days > MAX_DAYS)
            {
                printf("Invalid DAYS value. Must be 1-%d\n", MAX_DAYS);
                return 1;
            }
            run_multiple_days(argc, argv[4]);
        }
        else
        {
            printf("Invalid input.\n");
            display_help(argv[0]);
        }
    }
    else
    {
        printf("Invalid input.\n");
        display_help(argv[0]);
    }
    return 0;
}

// --------------------------------------------------
// weather_logger(): main option handler for simple calls
// --------------------------------------------------
void weather_logger(int option, const char *outfile)
{
    if (option == 1 || option == 2)
    {
        // simulate 1 day only
        run_single_day(outfile);
    }
    else if (option == 3)
    {
        run_single_day(outfile);
    }
}

// --------------------------------------------------
// Run simulation for ONE day
// --------------------------------------------------
static void run_single_day(const char *outfile)
{
    WeatherSystem weather_system;
    init_weather_system(&weather_system, 1);

    DailyWeatherLog daily;
    init_daily_log(&daily);
    simulate_daily_weather(&daily); // generates 24-hour logs

    add_daily_log(&weather_system, &daily);

    // print to console
    print_daily_log(&daily);

    // optional file output
    if (outfile != NULL)
    {
        printf("Saving log to file: %s\n", outfile);
        save_daily_log_to_file(&daily, outfile);
        append_summary(&daily, outfile);
    }
    destroy_weather_system(&weather_system);
}

// --------------------------------------------------
// Run simulation for MULTIPLE day
// --------------------------------------------------
static void run_multiple_days(int days, const char *outfile)
{
    WeatherSystem weather_system;
    init_weather_system(&weather_system, days);

    for (int i = 0; i < days; i++)
    {
        DailyWeatherLog daily;
        init_daily_log(&daily);
        simulate_daily_weather(&daily); // generates 24-hour logs

        add_daily_log(&weather_system, &daily);
    }

    // print all
    print_system_summary(&weather_system);

    // optional file output
    if (outfile != NULL)
    {
        printf("Saving log to file: %s\n", outfile);
        save_system_logs(&weather_system, outfile);

        for (int i = 0; i < weather_system.days_logged; i++)
            append_summary(&weather_system.logs[i], outfile);
    }

    destroy_weather_system(&weather_system);
}
