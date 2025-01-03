#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_RECORDS 1000
#define MAX_LINE_LENGTH 256
#define DATE_LENGTH 11

typedef struct {
    char date[DATE_LENGTH];
    float temperature;
    float humidity;
    float pressure;
    float wind_speed;
    float rainfall;
} WeatherRecord;

typedef struct {
    float min;
    float max;
    float avg;
    float std_dev;
} Statistics;

// Global variables
WeatherRecord records[MAX_RECORDS];
int record_count = 0;

// Function prototypes
int load_data(const char* filename);
Statistics calculate_statistics(float* data, int count);
void generate_report(const char* output_file);
void export_csv(const char* filename);
void analyze_trends(void);
void print_monthly_summary(void);
float calculate_heat_index(float temp, float humidity);
void generate_daily_forecast(void);

// Load weather data from CSV file
int load_data(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Unable to open file %s\n", filename);
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    // Skip header line
    fgets(line, MAX_LINE_LENGTH, file);

    while (fgets(line, MAX_LINE_LENGTH, file) && record_count < MAX_RECORDS) {
        WeatherRecord* record = &records[record_count];
        if (sscanf(line, "%10[^,],%f,%f,%f,%f,%f",
                   record->date,
                   &record->temperature,
                   &record->humidity,
                   &record->pressure,
                   &record->wind_speed,
                   &record->rainfall) == 6) {
            record_count++;
        }
    }

    fclose(file);
    return record_count;
}

// Calculate basic statistics for a data series
Statistics calculate_statistics(float* data, int count) {
    Statistics stats = {0};
    if (count == 0) return stats;

    // Calculate min, max, and average
    stats.min = stats.max = data[0];
    float sum = data[0];
    float sum_sq = data[0] * data[0];

    for (int i = 1; i < count; i++) {
        if (data[i] < stats.min) stats.min = data[i];
        if (data[i] > stats.max) stats.max = data[i];
        sum += data[i];
        sum_sq += data[i] * data[i];
    }
    
    stats.avg = sum / count;

    // Calculate standard deviation
    float variance = (sum_sq / count) - (stats.avg * stats.avg);
    stats.std_dev = sqrt(variance);

    return stats;
}

// Generate comprehensive analysis report
void generate_report(const char* output_file) {
    FILE* file = fopen(output_file, "w");
    if (!file) {
        printf("Error: Unable to create report file\n");
        return;
    }

    // Prepare data arrays for statistical analysis
    float temperatures[MAX_RECORDS];
    float humidity[MAX_RECORDS];
    float pressure[MAX_RECORDS];
    float wind_speed[MAX_RECORDS];
    float rainfall[MAX_RECORDS];

    for (int i = 0; i < record_count; i++) {
        temperatures[i] = records[i].temperature;
        humidity[i] = records[i].humidity;
        pressure[i] = records[i].pressure;
        wind_speed[i] = records[i].wind_speed;
        rainfall[i] = records[i].rainfall;
    }

    // Calculate statistics for each metric
    Statistics temp_stats = calculate_statistics(temperatures, record_count);
    Statistics humidity_stats = calculate_statistics(humidity, record_count);
    Statistics pressure_stats = calculate_statistics(pressure, record_count);
    Statistics wind_stats = calculate_statistics(wind_speed, record_count);
    Statistics rain_stats = calculate_statistics(rainfall, record_count);

    // Write report
    fprintf(file, "Weather Data Analysis Report\n");
    fprintf(file, "=========================\n\n");
    fprintf(file, "Analysis Period: %s to %s\n", 
            records[0].date, records[record_count-1].date);
    fprintf(file, "Total Records Analyzed: %d\n\n", record_count);

    fprintf(file, "Temperature Statistics (°C):\n");
    fprintf(file, "  Minimum: %.2f\n  Maximum: %.2f\n  Average: %.2f\n  Std Dev: %.2f\n\n",
            temp_stats.min, temp_stats.max, temp_stats.avg, temp_stats.std_dev);

    fprintf(file, "Humidity Statistics (%%):\n");
    fprintf(file, "  Minimum: %.2f\n  Maximum: %.2f\n  Average: %.2f\n  Std Dev: %.2f\n\n",
            humidity_stats.min, humidity_stats.max, humidity_stats.avg, humidity_stats.std_dev);

    fprintf(file, "Pressure Statistics (hPa):\n");
    fprintf(file, "  Minimum: %.2f\n  Maximum: %.2f\n  Average: %.2f\n  Std Dev: %.2f\n\n",
            pressure_stats.min, pressure_stats.max, pressure_stats.avg, pressure_stats.std_dev);

    fprintf(file, "Wind Speed Statistics (km/h):\n");
    fprintf(file, "  Minimum: %.2f\n  Maximum: %.2f\n  Average: %.2f\n  Std Dev: %.2f\n\n",
            wind_stats.min, wind_stats.max, wind_stats.avg, wind_stats.std_dev);

    fprintf(file, "Rainfall Statistics (mm):\n");
    fprintf(file, "  Minimum: %.2f\n  Maximum: %.2f\n  Average: %.2f\n  Std Dev: %.2f\n",
            rain_stats.min, rain_stats.max, rain_stats.avg, rain_stats.std_dev);

    fclose(file);
}

// Export processed data to CSV
void export_csv(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Unable to create export file\n");
        return;
    }

    // Write header
    fprintf(file, "Date,Temperature,Humidity,Pressure,WindSpeed,Rainfall,HeatIndex\n");

    // Write data
    for (int i = 0; i < record_count; i++) {
        float heat_index = calculate_heat_index(records[i].temperature, 
                                              records[i].humidity);
        fprintf(file, "%s,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
                records[i].date,
                records[i].temperature,
                records[i].humidity,
                records[i].pressure,
                records[i].wind_speed,
                records[i].rainfall,
                heat_index);
    }

    fclose(file);
}

// Calculate heat index using temperature and humidity
float calculate_heat_index(float temp, float humidity) {
    // Simplified heat index calculation
    float hi = 0.5 * (temp + 61.0 + ((temp-68.0)*1.2) + (humidity*0.094));
    return hi;
}

// Analyze weather trends
void analyze_trends(void) {
    printf("\nWeather Trend Analysis\n");
    printf("=====================\n");

    // Calculate temperature trends
    float temp_change = 0;
    for (int i = 1; i < record_count; i++) {
        temp_change += records[i].temperature - records[i-1].temperature;
    }
    float avg_temp_change = temp_change / (record_count - 1);

    // Calculate precipitation patterns
    float total_rainfall = 0;
    int rainy_days = 0;
    for (int i = 0; i < record_count; i++) {
        if (records[i].rainfall > 0) {
            total_rainfall += records[i].rainfall;
            rainy_days++;
        }
    }

    printf("Temperature Trend: %.2f°C per day\n", avg_temp_change);
    printf("Average Rainfall: %.2f mm per rainy day\n", 
           rainy_days > 0 ? total_rainfall/rainy_days : 0);
    printf("Rainy Days: %d (%.1f%%)\n", rainy_days, 
           (float)rainy_days/record_count * 100);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <weather_data.csv>\n", argv[0]);
        return 1;
    }

    // Load and process data
    if (load_data(argv[1]) < 0) {
        return 1;
    }

    printf("Successfully loaded %d weather records.\n", record_count);

    // Generate analysis outputs
    generate_report("weather_report.txt");
    export_csv("processed_weather_data.csv");
    analyze_trends();

    return 0;
}
