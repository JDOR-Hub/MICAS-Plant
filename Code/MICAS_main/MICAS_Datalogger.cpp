#include "MICAS_Datalogger.h"
#include "MICAS_Config.h"
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <ctime>

Datalogger::Datalogger(){};

bool Datalogger::begin(const char *filename){
    if (!SD.begin(CS_PIN)) {
    Serial.println("SD Card initialization failed!");
    while (true); // Stop the program if the SD card fails to initialize
    }

    Serial.println("SD Card initialized successfully.");

    File file = SD.open(filename, FILE_WRITE);

    if (!file) {
        Serial.print("Failed to open file for writing: ");
        Serial.println(filename);
        return false;
    }

    // Write the header row
    file.println("UTC;SOILHUM;SOILTEMP;SOILN;SOILP;SOILK;LDRVAL;LVLVAL;AMBHUM;AMBTEMP;WP1ST;WP2ST;EVST;");
    file.close();
    return true;
}

bool Datalogger::appendCSVRow(const char *filename, 
                    float soilhum, float soiltemp, float soilnutN, float soilnutP, float soilnutK,
                    float ldr_val, float lvl_val, float ambhum, float ambtemp, 
                    bool wp1_status, bool wp2_status, bool ev_status){

    // Get current time
    time_t now = time(nullptr);
    struct tm *timeInfo = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    String timestamp = String(buffer);

    // Open the file for appending
    File file = SD.open(filename, FILE_APPEND);

    if (!file) {
        Serial.print("Failed to open file for appending: ");
        Serial.println(filename);
        return false;
    }

    // Append the row with timestamp and sensor data
    file.print(timestamp);
    file.print(";");
    file.print(soilhum);
    file.print(";");
    file.print(soiltemp);
    file.print(";");
    file.println(soilnutN);
    file.print(";");
    file.println(soilnutP);
    file.print(";");
    file.println(soilnutK);
    file.print(";");
    file.println(ldr_val);
    file.print(";");
    file.println(lvl_val);
    file.print(";");
    file.println(ambhum);
    file.print(";");
    file.println(ambtemp);
    file.print(";");
    file.println(ldr_val);
    file.print(";");
    file.println(wp1_status);
    file.print(";");
    file.println(wp2_status);
    file.print(";");
    file.println(ev_status);
    file.print(";");

    file.close();

    return true;
}

void Datalogger::readFile(const char *filename){
    File file = SD.open(filename);

    if (!file) {
        Serial.print("Failed to open file for reading: ");
        Serial.println(filename);
        return;
    }

    Serial.println("File content:");

    while (file.available()) {
        Serial.write(file.read());
    }

    file.close();
}