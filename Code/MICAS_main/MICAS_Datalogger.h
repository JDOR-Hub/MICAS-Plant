#ifndef MICAS_DATALOGGER_H
#define MICAS_DATALOGGER_H

#include <Arduino.h>

class Datalogger{
public:
    Datalogger();
    bool begin(const char *filename);
    bool appendCSVRow(const char *filename, 
                    float soilhum, float soiltemp, float soilnutN, float soilnutP, float soilnutK,
                    float ldr_val, float lvl_val, float ambhum, float ambtemp, 
                    bool wp1_status, bool wp2_status, bool ev_status);
    void readFile(const char *filename);
};

#endif //MICAS_DATALOGGER_H