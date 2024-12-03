#include "MICAS_Actuators.h"
#include "MICAS_Config.h"

Actuators::Actuators(){};

void Actuators::begin(){
    pinMode(WP_PIN, OUTPUT);
    pinMode(EV_PIN, OUTPUT);
    digitalWrite(WP_PIN, LOW);
    digitalWrite(EV_PIN, LOW);
}

void Actuators::writeWPs(bool WaterPump){
    if (WaterPump) {
    digitalWrite(WP_PIN, HIGH);  // Activate water pump
  } else {
    digitalWrite(WP_PIN, LOW);   // Deactivate water pump
  }
}

void Actuators::writeEV(bool Electrovalve) {
    if (Electrovalve) {
        digitalWrite(EV_PIN, HIGH);  // Activate electrovalve
    } else {
        digitalWrite(EV_PIN, LOW);   // Deactivate electrovalve
    }
}