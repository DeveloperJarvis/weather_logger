# 🌤 **LLD — Weather Logger (C Application)**

### _Simulate temperature logs for each hour and save results_

---

# 1. **Core Responsibilities**

1. **Simulate temperature values** for each hour of a day (0–23).
2. **Store logs in memory** in a structured format.
3. **Persist logs to a file** (e.g., `weather_log.txt`).
4. **Display logs** on screen.
5. **Support multiple days of logs** (if required).

---

# 2. **Data Structures**

### **2.1 TemperatureLog**

Stores a single hour's simulated weather information.

| Field         | Type    | Description                         |
| ------------- | ------- | ----------------------------------- |
| `hour`        | `int`   | Hour of the day (0–23)              |
| `temperature` | `float` | Simulated temperature value (°C/°F) |
| `humidity`    | `float` | Optional: humidity percentage       |
| `wind_speed`  | `float` | Optional: wind speed                |

---

### **2.2 DailyWeatherLog**

Stores a full day's weather data (24 hourly entries).

| Field             | Type               | Description                    |
| ----------------- | ------------------ | ------------------------------ |
| `date_str`        | `char[20]`         | Example: `"2025-12-05"`        |
| `entries[24]`     | `TemperatureLog[]` | Array of hourly logs           |
| `avg_temperature` | `float`            | Computed daily average         |
| `min_temperature` | `float`            | Minimum temperature of the day |
| `max_temperature` | `float`            | Maximum temperature of the day |

---

### **2.3 WeatherSystem**

High-level application manager.

| Field                   | Type          | Description            |
| ----------------------- | ------------- | ---------------------- |
| `DailyWeatherLog* logs` | dynamic array | Stores multiple days   |
| `int days_logged`       | integer       | Count of days recorded |
| `int max_days`          | integer       | Max storage limit      |

---

# 3. **Modules / Components**

---

## **3.1 Simulation Module**

### _Responsibilities_

- Generate random temperature values for an hour.
- Produce humidity, wind speed (optional).
- Populate a `TemperatureLog` entry.

### _Functions_

- `simulate_temperature(hour)`
- `simulate_humidity(hour)`
- `simulate_wind_speed(hour)`
- `simulate_hour_record(DailyWeatherLog*, hour)`
- `simulate_daily_weather(DailyWeatherLog*)`

---

## **3.2 Log In-Memory Storage Module**

### _Responsibilities_

- Initialize log structures.
- Store hourly and daily logs.
- Compute min, max, and average values.

### _Functions_

- `init_daily_log(DailyWeatherLog*)`
- `compute_statistics(DailyWeatherLog*)`
- `add_daily_log(WeatherSystem*, DailyWeatherLog*)`
- `init_weather_system(WeatherSystem*, max_days)`

---

## **3.3 File Persistence Module**

### _Responsibilities_

- Save logs to text files.
- Append daily summaries.
- Read logs (optional).

### _Functions_

- `save_daily_log_to_file(DailyWeatherLog*, const char* filename)`
- `save_system_logs(WeatherSystem*, const char* filename)`
- `append_summary(DailyWeatherLog*, const char* filename)`

---

## **3.4 Display Module**

### _Responsibilities_

- Display hourly logs.
- Display statistics.
- Pretty print for terminal use.

### _Functions_

- `print_hour_entry(TemperatureLog*)`
- `print_daily_log(DailyWeatherLog*)`
- `print_system_summary(WeatherSystem*)`

---

## **3.5 Date/Utility Module**

### _Responsibilities_

- Get current date.
- Format as string.
- Provide random value helpers.

### _Functions_

- `get_today_date_str(char* buffer)`
- `get_random_float(min, max)`
- `seed_rng()` (seed `rand()`)

---

# 4. **Application Workflow**

### **Step 1 — Initialize System**

- Seed RNG.
- Create a `WeatherSystem` with max days.

### **Step 2 — Start Weather Simulation**

1. Create a new `DailyWeatherLog`.
2. Assign today's date.
3. For each hour (0–23):

   - Call simulation module to fill a `TemperatureLog`.

4. Compute statistics.

### **Step 3 — Store Data**

- Add daily log to the WeatherSystem.

### **Step 4 — Output Results**

- Print logs to terminal.
- Save logs to file.

### **Step 5 — Repeat (if needed)**

- User chooses to log another day.

---

# 5. **File Output Format**

### Example: `weather_log.txt`

```
Date: 2025-12-06
--------------------------------------
Hour | Temperature | Humidity | Wind
--------------------------------------
00   | 21.5 C      | 60 %     | 5.2 m/s
01   | 20.9 C      | 58 %     | 4.8 m/s
...
23   | 18.2 C      | 62 %     | 3.5 m/s

Daily Average Temperature: 19.7 C
Min Temperature: 15.1 C
Max Temperature: 23.8 C
======================================
```

---

# 6. **Error Handling**

- File open/write failure.
- Memory allocation failure.
- Invalid hour index.
- System full (max days reached).

---

# 7. **Extensibility Options**

- Support real sensor input (instead of simulation).
- Network sync to a server (IoT support).
- Record rainfall, pressure, UV index.
- Multi-format export: JSON, CSV.
- Graph generation (ASCII or GUI).

---

# 8. **High-Level Sequence Diagram (Textual)**

```
main()
 ├── init_weather_system()
 ├── seed_rng()
 ├── init_daily_log()
 │      ├── simulate_daily_weather()
 │      ├── compute_statistics()
 ├── add_daily_log()
 ├── print_daily_log()
 ├── save_daily_log_to_file()
 └── exit
```
