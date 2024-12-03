#ifndef MICAS_ACTUATORS_H
#define MICAS_ACTUATORS_H

class Actuators{
public:
    Actuators();
    void begin();
    void writeWPs(bool WaterPump);
    void writeEV(bool Electrovalve);
};

#endif