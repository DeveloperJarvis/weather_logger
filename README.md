# 🌤 **weather_logger**

**weather_logger** is a simple C console application that **simulates temperature, humidity, and wind-speed logs for each hour of a day**, stores them in memory, and saves the results to a file.

It is lightweight, portable, and fully open-source under the **GPL-3.0-or-later** license.

---

## 📌 Features

- Simulates **24 hourly weather readings**

  - Temperature
  - Humidity
  - Wind speed

- Stores logs in structured in-memory objects
- Saves results to a text file (ex: `weather_log.txt`)
- Displays logs in a clean table format
- Supports statistics

  - Daily minimum temperature
  - Daily maximum temperature
  - Average temperature

- Pure C (C89/C99 compatible)
- Cross-platform (Linux / macOS / Windows)

---

## 📁 Project Structure

```
weather_logger/
│
├── src/
│   ├── weather_logger.c        # Main program
│   ├── weather_logger.h        # Header (data structures & prototypes)
│   ├── simulation.c            # Random weather simulation module
│   ├── file_io.c               # File saving module
│   └── utils.c                 # Date, RNG, helpers
│
├── README.md
└── LICENSE (GPL-3.0-or-later)
```

> The structure above is suggested; your actual repo may differ.

---

## 🏗 Build Instructions

### **Linux / macOS**

```
gcc -o weather_logger weather_logger.c
```

### **Windows (MinGW)**

```
gcc -o weather_logger weather_logger.c
```

Or using MSVC:

```
cl weather_logger.c
```

---

## ▶ Running the Program

```
./weather_logger
```

If logs are saved successfully, you will see a file like:

```
weather_log_2025-12-05.txt
```

---

## 📄 Example Log Output

```
Date: 2025-12-06
----------------------------------------------
Hour | Temp (°C) | Humidity (%) | Wind (m/s)
----------------------------------------------
00   | 21.5      | 60           | 5.2
01   | 20.9      | 58           | 4.8
...
23   | 18.2      | 62           | 3.5

Daily Average Temperature: 19.7 °C
Min Temperature: 15.1 °C
Max Temperature: 23.8 °C
==============================================
```

---

## ⚙ Command-Line Options (Optional Feature)

```
weather_logger [options]

Options:
  -h, --help        Show help screen
  -o FILE           Output weather logs to custom filename
  -n DAYS           Simulate multiple days
  -v, --version     Show program version
```

---

## 🔧 How Weather Simulation Works

Each hour generates:

- **Temperature** using pseudo-random generator
- **Humidity** (%)
- **Wind speed** (m/s)

You may adjust ranges in the simulation module, e.g.:

- day/night temperature variation
- seasonal temperature profiles
- random spikes

---

## 🚀 Future Enhancements

- CSV / JSON output
- Real sensor integration (IoT)
- Multi-day logging dashboard
- Graph generation (ASCII or exportable)
- Configurable simulation parameters

---

## 👤 Author

**Developer Jarvis** (Pen Name)
GitHub: [https://github.com/DeveloperJarvis](https://github.com/DeveloperJarvis)

---

## 📜 License

This project is licensed under the **GNU GPL-3.0-or-later** license.
See `LICENSE` for details.
