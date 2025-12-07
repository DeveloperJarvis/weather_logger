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
// Date/ Utility, RNG, helpers Module
// --------------------------------------------------
/*
 * Responsibilties:
 * - Get current date.
 * - Format as string.
 * - Provide random value helpers.
 *
 * Functions:
 * - get_random_date_str(char *buffer)
 * - get_random_float(min, max)
 * - seed_rnd() (seed rand())
 */

// --------------------------------------------------
// header files
// --------------------------------------------------
#include <stdio.h>  // for printf()
#include <stdlib.h> // for rand(), srand(), RAND_MAX macro
#include <time.h>   // for time()

#include "weather_logger.h"

// --------------------------------------------------
// helper functions
// --------------------------------------------------

// display help screen
void display_help(const char *s)
{
    printf("Usage: %s [options]\n", s);
    printf(" -h --help\tShow help screen\n");
    printf(" -v --version\tShow program version\n");
    printf(" -n DAYS\tSimulate multiple days\n");
    printf(" -o FILE\tOutput weather logs to custom filename\n");
}

// display program version
void display_version(const char *s)
{
    printf("%s version: 1.0.0\n", s);
}

// --------------------------------------------------
// Date/ Utility functions
// --------------------------------------------------

// generate random date and convert it to string
void get_random_date_str(char *buffer)
{
    // TODO: generate YYYY-MM-DD
    // Pick a random year between 2000 and 2030
    int year = 2000 + rand() % 31;
    // Month 1-12
    int month = 1 + rand() % 12;

    // Leap year rule
    int is_leap = (year % 400 == 0) ||
                  ((year % 4 == 0) && (year % 100 != 0));
    // Days per month
    int days_in_month;
    switch (month)
    {
    case 2:
        days_in_month = is_leap ? 29 : 28;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        days_in_month = 30;
        break;
    default:
        days_in_month = 31;
        break;
    }

    int day = 1 + rand() % days_in_month;

    // Format strictly as YYYY-MM-DD
    snprintf(buffer, DATE_LEN, "%04d-%02d-%02d", year, month, day);
}

// generate random float value
float get_random_float(float min, float max)
{
    // TODO: uniform random
    // Generates float between 0.0 and 1.0
    // RAND_MAX is a macro defined in stdlib.h
    float scale = rand() / (float)RAND_MAX;
    // Scale and shift to desired range
    return min + scale * (max - min);
}

// calls srand to Seed the random number generator
void seed_rnd()
{
    srand(time(NULL));
}