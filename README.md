# Weather Data Analysis System

A comprehensive C-based system for analyzing weather data, generating statistical reports, and identifying weather patterns.

## Features

- Load and parse weather data from CSV files
- Calculate comprehensive statistics for multiple weather parameters
- Generate detailed analysis reports
- Export processed data with derived metrics
- Analyze weather trends and patterns
- Calculate heat index and other derived weather metrics

## Technical Details

### Data Parameters Analyzed

- Temperature (°C)
- Humidity (%)
- Atmospheric Pressure (hPa)
- Wind Speed (km/h)
- Rainfall (mm)

### Statistical Analysis

- Minimum and maximum values
- Averages
- Standard deviations
- Trend analysis
- Pattern recognition

## Getting Started

### Prerequisites

- GCC compiler (version 7.0 or higher)
- Make build system
- Math library (libm)
- POSIX-compliant operating system

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/weather-analysis.git
   cd weather-analysis
   ```

2. Build the project:
   ```bash
   make
   ```

3. Generate sample data:
   ```bash
   make sample-data
   ```

4. Run the analyzer:
   ```bash
   make run
   ```

### Input Data Format

The system expects CSV files with the following format:
```csv
Date,Temperature,Humidity,Pressure,WindSpeed,Rainfall
2024-01-01,20.5,65.0,1013.2,12.5,0.0
2024-01-02,22.0,70.0,1012.8,10.2,5.2
```

## Usage

### Basic Usage

```bash
./bin/weather_analyzer input_file.csv
```

### Output Files

1. `weather_report.txt`: Detailed statistical analysis
2. `processed_weather_data.csv`: Processed data with

### License
This project is licensed under the GNU General Public License v3.0 . Take a look at [License](https://github.com/stephenombuya/Weather-Data-Analysis-System/blob/main/LICENSE)
