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
// Random weather simulation module
// --------------------------------------------------
/*
 *   Responsibilities:
 *   - Generate random temperature values of an hour.
 *   - Produce humidity, wind speed (optional)
 *   - Populate a temperatureLog entry
 *
 *   Functions:
 *   - simulate_temperature(hour)
 *   - simulate_humidity(hour)
 *   - simulate_wind_speed(hour)
 *   - simulate_hour_record(DailyWeatherLog*, hour)
 *   - simulate_daily_weather(DailyWeatherLog*)
 */

// --------------------------------------------------
// header files
// --------------------------------------------------
#include <stdio.h> // for printf()

#include "weather_logger.h"

// --------------------------------------------------
// simulation functions
// --------------------------------------------------

// simulate temperature at any hour
float simulate_temperature(int hour)
{
    // TODO: returns random temperature based on hour
    // Morning (0-6): colder
    if (hour < 6)
        return get_random_float(10.0f, 16.0f);
    // Daytime (6-12): warmer
    if (hour < 12)
        return get_random_float(15.0f, 22.0f);
    // Afternoon (12-18): hottest
    if (hour < 18)
        return get_random_float(20.0f, 28.0f);
    // Evening/ Night (18-23): pleasent
    return get_random_float(14.0f, 20.0f);
}

// simulate humidity at any hour
float simulate_humidity(int hour)
{
    // TODO: return humidity %
    // Early morning high humidity
    if (hour < 6)
        return get_random_float(60.0f, 90.0f);
    // Daytime lower humidity
    if (hour < 18)
        return get_random_float(30.0f, 55.0f);
    // Evening rises again slightly
    return get_random_float(50.0f, 80.0f);
}

// simulate wind speed at any hour
float simulate_wind_speed(int hour)
{
    // TODO: return wind speed
    // Calm at night
    if (hour < 6)
        return get_random_float(0.5f, 2.0f);
    // Breezy mid-day
    if (hour < 18)
        return get_random_float(2.0f, 7.0f);
    // Evening moderate wind
    return get_random_float(1.0f, 4.0f);
}

// simulate weather log for an hour
void simulate_hour_record(DailyWeatherLog *daily_log, int hour)
{
    // TODO: fill log->entries[hour]
    TemperatureLog *entry = &daily_log->entries[hour];

    entry->hour = hour;
    entry->temperature = simulate_temperature(hour);
    entry->humidity = simulate_humidity(hour);
    entry->wind_speed = simulate_wind_speed(hour);
}

// simulate weather log for the day
void simulate_daily_weather(DailyWeatherLog *daily_log)
{
    // TODO: loop hour= 0->23
    for (int hour = 0; hour < DAILY_LOG; hour++)
    {
        simulate_hour_record(daily_log, hour);
    }

    // After simulation, compute min/max/avg
    compute_statistics(daily_log);
}