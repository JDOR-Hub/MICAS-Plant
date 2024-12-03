#ifndef MICAS_CONFIG_H
#define MICAS_CONFIG_H

#include <Arduino.h>

// Pin definitions
#define FC28_PIN 27        // Soil moisture sensor
#define TEMP_PIN 26        // Soil Temperature sensor
#define MOSI_PIN 23        // SD MOSI
#define RE_PIN 22          // MAX485 RE
#define LDR_PIN 21         // Light-dependent resistor
#define MISO_PIN 19        // SD MISO
#define SCK_PIN 18         // SD Clock
#define DI_PIN 17          // MAX485 DI
#define RO_PIN 16          // MAX485 RO
#define EV_PIN 15          // Electrovalve control
#define WP_PIN 14          // Water pump control
#define LVL_PIN 13         // Level sensor
#define CS_PIN 5           // SD SPI Chip Select
#define DHT11_PIN 4        // DHT11 humidity & temperature sensor

// Sensor definitions
#define DHTTYPE DHT11      // Sensor type for DHT11

// Thresholds (CALIBRATE!!)
// These values define the acceptable limits for various sensors
#define SOILHUM_THRES 800.0       // Soil moisture threshold (raw value)
#define SOILTEMP_MIN_THRES 5.0    // Min soil temperature in °C
#define SOILTEMP_MAX_THRES 50.0   // Max soil temperature in °C
#define NITRO_THRES 20.0          // Nitrogen level (mg/kg)
#define PHOS_TRESH 8.0            // Phosphorus level (mg/kg)
#define POTA_TRESH 100.0          // Potassium level (mg/kg)
#define LDR_TRESH 2047.0          // Light sensor threshold (raw value)
#define LVL_TRESH 1000.0          // Level sensor threshold (raw value)
#define AMBTEMP_MIN_THRES 5.0     // Min ambient temperature in °C
#define AMBTEMP_MAX_THRES 50.0    // Max ambient temperature in °C
#define AMBHUM_MIN_THRES 30.0     // Min ambient humidity in %RH
#define AMBHUM_MAX_THRES 80.0     // Max ambient humidity in %RH

// Thermistor constants
const float NOMINALRES = 100000.0; // Nominal resistance at 25°C
const float NOMINALTEMP = 25.0;    // Nominal temperature (°C)
const float BCOEFF = 3950.0;       // B coefficient (thermistor)
const float RESISTOR = 10000.0;    // Pull-up resistor value (10k)

// NPK sensor communication constants (example values)
const uint8_t NITRO[] = {0x01,0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const uint8_t PHOS[] = {0x01,0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const uint8_t POTA[] = {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};

// Timing constants
#define ACT_DURATION 5000      // Duration of each action in milliseconds
#define LOOP_DELAY 1000        // Delay between each loop iteration in milliseconds

#endif // MICAS_CONFIG_H
