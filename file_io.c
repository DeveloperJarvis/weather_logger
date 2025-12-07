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
// File Persistence Module
// --------------------------------------------------
/*
 * Responsibilties:
 * - Save logs to text files.
 * - Append daily summaries.
 * - Read logs (optional).
 *
 * Functions:
 * - save_daily_log_to_file(DailyWeatherLog*, const char* filename)
 * - save_system_logs(WeatherSystem*, const char *filename)
 * - append_summary(DailyWeatherLog*, const char *filename)
 */
// --------------------------------------------------
// header files
// --------------------------------------------------
#include <stdio.h> // for printf()
// #include <stdlib.h> // for rand(), srand(), RAND_MAX macro

#include "weather_logger.h"

// --------------------------------------------------
// File functions
// --------------------------------------------------

// save daily logs to text file
void save_daily_log_to_file(DailyWeatherLog *daily_log, const char *filename)
{
    // TODO: write 24 entries
    FILE *fptr;
    FOPEN(fptr, filename, "a");
    if (fptr == NULL)
    {
        printf("ERROR: Could not open file '%s' for writing.\n", filename);
        return;
    }

    fprintf(fptr, "==============================================\n");
    fprintf(fptr, "Date: %s\n", daily_log->date_str); // 2025-12-06
    fprintf(fptr, "--------------------------------------\n");
    fprintf(fptr, " Hour\t| Temperature(C)\t| Humidity(%%)\t| Wind(m/s)\n");
    fprintf(fptr, "--------------------------------------\n");
    for (int i = 0; i < DAILY_LOG; i++)
    {
        TemperatureLog *t = &daily_log->entries[i];
        fprintf(fptr, " %02d\t| %.1f C\t| %.1f %%\t| %.1f m/s\n",
                t->hour, t->temperature, t->humidity, t->wind_speed);
    }
    fprintf(fptr, "--------------------------------------\n");
    fprintf(fptr, "Daily Average Temperature: %.1f °C\n", daily_log->avg_temperature); // 19.1
    fprintf(fptr, "Min Temperature: %.1f °C\n", daily_log->min_temperature);           // 15.1
    fprintf(fptr, "Max Temperature: %.1f °C\n", daily_log->max_temperature);           // 23.8
    fprintf(fptr, "==============================================\n");

    fclose(fptr);
}

// save system logs to text file for multiple days
void save_system_logs(WeatherSystem *weather_system, const char *filename)
{
    // TODO: loop and save
    FILE *fptr;
    FOPEN(fptr, filename, "a");
    if (fptr == NULL)
    {
        printf("ERROR: Could not open file '%s'.\n", filename);
        return;
    }
    fprintf(fptr, "WEATHER SYSTEM LOG EXPORT\n");
    fprintf(fptr, "Days Recorded: %d\n\n", weather_system->days_logged);
    fclose(fptr);

    // Now appending each daily log
    for (int i = 0; i < weather_system->days_logged; i++)
    {
        save_daily_log_to_file(&weather_system->logs[i], filename);
    }
}

// append summary to text file (stats only)
void append_summary(DailyWeatherLog *daily_log, const char *filename)
{
    // TODO: append stats
    FILE *fptr;
    FOPEN(fptr, filename, "a");
    if (fptr == NULL)
    {
        printf("ERROR: Could not append weather_system to '%s'.\n", filename);
        return;
    }
    fprintf(fptr, "SUMMARY for %s\n", daily_log->date_str);
    fprintf(fptr, "Avg Temp: %.2f\n", daily_log->avg_temperature);
    fprintf(fptr, "Min Temp: %.2f\n", daily_log->min_temperature);
    fprintf(fptr, "Max Temp: %.2f\n", daily_log->max_temperature);

    fclose(fptr);
}
