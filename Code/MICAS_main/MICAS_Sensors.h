#ifndef MICAS_SENSORS_H
#define MICAS_SENSORS_H

class Sensors{
public:
    Sensors();
    void begin();
    float readFC28();
    float readTemp();
    float* readNPK();
    float readLDR();
    float readLVL();
    float* readDHT11();
};

#endif //MICAS_SENSORS_H