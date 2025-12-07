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
// Log In-Memory Storage Module
// --------------------------------------------------
/*
 * Responsibilties:
 * - Initialize log structure
 * - Store hourly and daily logs
 * - Compute min, max and average values
 *
 * Functions:
 * - init_daily_log(DailyWeatherLog*)
 * - compute_statistics(DailyWeatherLog*)
 * - add_daily_log(WeatherSystem*, DailyWeatherLog*)
 * - init_weather_system(WeatherSystem*, max_days)
 */

// --------------------------------------------------
// header files
// --------------------------------------------------
#include <stdio.h>  // for printf()
#include <string.h> // for strcmp()
#include <stdlib.h> // for atoi()

#include "weather_logger.h"

// --------------------------------------------------
// Initialize a new DailyWeatherLog
// --------------------------------------------------
void init_daily_log(DailyWeatherLog *daily_log)
{
    if (!daily_log)
        return;

    // generate random date into string
    get_random_date_str(daily_log->date_str);

    // initialize stats
    daily_log->avg_temperature = 0.0f;
    daily_log->min_temperature = 9999.0f;
    daily_log->max_temperature = -9999.0f;

    // initialize entries
    for (int i = 0; i < DAILY_LOG; i++)
    {
        daily_log->entries[i].hour = i;
        daily_log->entries[i].temperature = 0.0f;
        daily_log->entries[i].humidity = 0.0f;
        daily_log->entries[i].wind_speed = 0.0f;
    }
}

// --------------------------------------------------
// Compute min, max and average temperature for the day
// --------------------------------------------------
void compute_statistics(DailyWeatherLog *daily_log)
{
    if (!daily_log)
        return;

    float sum = 0.0f;
    float min = 9999.0f;
    float max = -9999.0f;

    for (int i = 0; i < DAILY_LOG; i++)
    {
        float temp = daily_log->entries[i].temperature;
        sum += temp;

        if (temp < min)
            min = temp;
        if (temp > max)
            max = temp;
    }

    daily_log->avg_temperature = sum / DAILY_LOG;
    daily_log->min_temperature = min;
    daily_log->max_temperature = max;
}

// --------------------------------------------------
// Add a daily log to the WeatherSystem
// --------------------------------------------------
void add_daily_log(WeatherSystem *weather_system, DailyWeatherLog *daily_log)
{
    if (!weather_system || !daily_log)
        return;

    if (weather_system->days_logged >= weather_system->max_days)
    {
        printf("WARNING: WeatherSystem storage full. Cannot add more logs.\n");
        return;
    }

    // Copy the log into weather_system.logs array
    weather_system->logs[weather_system->days_logged] = *daily_log;
    weather_system->days_logged++;
}

// --------------------------------------------------
// Initialize WeatherSystem (allocate logs array)
// --------------------------------------------------
void init_weather_system(WeatherSystem *weather_system, int max_days)
{
    if (!weather_system)
        return;

    if (max_days <= 0)
        max_days = MAX_DAYS;

    // allocate memory
    weather_system->logs = (DailyWeatherLog *)malloc(sizeof(DailyWeatherLog) * max_days);

    if (!weather_system->logs)
    {
        printf("ERROR: Failed to allocate WeatherSystem storage.\n");
        weather_system->days_logged = 0;
        weather_system->max_days = 0;
        return;
    }

    // initialize metadata
    weather_system->days_logged = 0;
    weather_system->max_days = max_days;
}

void destroy_weather_system(WeatherSystem *weather_system)
{
    if (!weather_system)
        return;
    if (weather_system->logs)
        free(weather_system->logs);
    weather_system->logs = NULL;
    weather_system->days_logged = 0;
    weather_system->max_days = 0;
}