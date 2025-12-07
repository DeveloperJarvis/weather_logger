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
#ifndef WEATHER_LOGGER_H
#define WEATHER_LOGGER_H

// --------------------------------------------------
// constants and macros
// --------------------------------------------------
#define DATE_LEN 16 // "YYYY-MM-DD" = 10 chars + NULL -> 11
// increased buffer of DATE_LEN for compiler so that snprintf does not warn
// has plenty of space for formatting
#define DAILY_LOG 24 // Hours of the day (0 - 23)
#define MAX_DAYS 5   // Max storage limit

#if defined(_MSC_VER)
#define FOPEN(fptr, filepath, mode) fopen_s(fptr, filepath, mode)
#else
#define FOPEN(fptr, filepath, mode) (fptr = fopen(filepath, mode))
#endif

typedef struct TemperatureLog
{
    int hour;          // Hour of the day (0 - 23)
    float temperature; // Simulated temperature value (C/ F)
    float humidity;    // Optional: humidity percentage
    float wind_speed;  // Optional: wind speed
} TemperatureLog;

typedef struct DailyWeatherLog
{
    char date_str[DATE_LEN];           // Example "2025-12-05"
    TemperatureLog entries[DAILY_LOG]; // Array if hourly logs
    float avg_temperature;             // Computed daily average
    float min_temperature;             // Minimum temperature of the day
    float max_temperature;             // Maximum temperature of the day
} DailyWeatherLog;

typedef struct WeatherSystem
{
    DailyWeatherLog *logs; // Stores multiple days
                           // malloc log pointer in init_weather_system()
                           // to avoid any segmentation error
    int days_logged;       // Count of days recorded
    int max_days;          // Max storage limit
} WeatherSystem;

// --------------------------------------------------
// forward function declarations/ prototypes
// --------------------------------------------------

// Date/ Utility, RNG, helpers Module
void display_help(const char *s);
void display_version(const char *s);
void get_random_date_str(char *buffer);
float get_random_float(float min, float max);
void seed_rnd();

// Log In-Memory Storage Module
void weather_logger(int option, const char *outfile);
void init_daily_log(DailyWeatherLog *daily_log);
void compute_statistics(DailyWeatherLog *daily_log);
void add_daily_log(WeatherSystem *weather_system, DailyWeatherLog *daily_log);
void init_weather_system(WeatherSystem *weather_system, int max_days);
void destroy_weather_system(WeatherSystem *weather_system);

// Display Module
void print_hour_entry(TemperatureLog *temp_log);
void print_daily_log(DailyWeatherLog *daily_log);
void print_system_summary(WeatherSystem *system);

// Random weather simulation module
float simulate_temperature(int hour);
float simulate_humidity(int hour);
float simulate_wind_speed(int hour);
void simulate_hour_record(DailyWeatherLog *daily_log, int hour);
void simulate_daily_weather(DailyWeatherLog *daily_log);

// File Persistence Module
void save_daily_log_to_file(DailyWeatherLog *daily_log, const char *filename);
void save_system_logs(WeatherSystem *system, const char *filename);
void append_summary(DailyWeatherLog *daily_log, const char *filename);
#endif // WEATHER_LOGGER_H
