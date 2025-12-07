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
// Display Module
// --------------------------------------------------
/*
 * Responsibilties:
 * - Display hourly logs
 * - Display statistics
 * - Pretty print for terminal use
 *
 * Functions:
 * - print_hour_entry(temperatureLog*)
 * - print_daily_log(DailyWeatherLog*)
 * - print_system_summary(WeatherSystem*)
 */

// --------------------------------------------------
// header files
// --------------------------------------------------
#include <stdio.h>  // for printf()
#include <string.h> // for strcmp()

#include "weather_logger.h"

// --------------------------------------------------
// display function
// --------------------------------------------------

// prints a single hour weather record
void print_hour_entry(TemperatureLog *temp_log)
{
    // TODO: pretty terminal print
    printf(" %02d\t| %.1f C\t| %.1f %%\t| %.1f m/s\n",
           temp_log->hour,        // 00
           temp_log->temperature, // 21.5 C
           temp_log->humidity,    // 60 %
           temp_log->wind_speed); // 5.2 m/s
}

// prints full daily weather log with statistics
void print_daily_log(DailyWeatherLog *daily_log)
{
    // TODO: iterate 24 hours + stats
    printf("Date: %s\n", daily_log->date_str); // 2025-12-06
    printf("--------------------------------------\n");
    printf(" Hour\t| Temperature\t| Humidity\t| Wind\n");
    printf("--------------------------------------\n");
    for (int i = 0; i < DAILY_LOG; i++)
    {
        print_hour_entry(&daily_log->entries[i]);
    }
    printf("--------------------------------------\n");
    printf("Daily Average Temperature: %.1f °C\n", daily_log->avg_temperature); // 19.1
    printf("Min Temperature: %.1f °C\n", daily_log->min_temperature);           // 15.1
    printf("Max Temperature: %.1f °C\n", daily_log->max_temperature);           // 23.8
    printf("==============================================\n");
}

// print summary of all system logs
void print_system_summary(WeatherSystem *weather_system)
{
    // TODO: loop weather_system -> logs
    printf("==============================================\n");
    printf("SYSTEM LOGS: \n");
    printf("Days logged: %d / %d\n", weather_system->days_logged,
           weather_system->max_days);
    printf("==============================================\n");
    for (int i = 0; i < weather_system->days_logged; i++)
    {
        print_daily_log(&weather_system->logs[i]);
    }
}
