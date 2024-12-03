#include "MICAS_Sensors.h"
#include "MICAS_Config.h"
#include "DHT.h"

Sensors::Sensors(){};   // Constructor definition
uint8_t NPK_VALUES[11];
HardwareSerial MAX485(2);
DHT dht11(DHT11_PIN, DHTTYPE);

void Sensors::begin(){
    pinMode(FC28_PIN, INPUT);
    pinMode(TEMP_PIN, INPUT);
    pinMode(RE_PIN, OUTPUT);    // NPK
    MAX485.begin(9600, SERIAL_8N1, RO_PIN, DI_PIN);
    pinMode(LDR_PIN,INPUT);
    pinMode(LVL_PIN, INPUT);
    dht11.begin();
}

float Sensors::readFC28(){
    float SoilHum = analogRead(FC28_PIN)/10.23;
    return SoilHum; // %H
}

float Sensors::readTemp(){
    float SoilTempRaw = 0.0;  // Raw analog value from thermistor
    float resistance = 0.0;  // Thermistor resistance
    float SoilTemp = 0.0;  // Temperature in Celsius
    SoilTempRaw = analogRead(TEMP_PIN);
    float voltage = SoilTempRaw * 5.0 / 1023.0;
    resistance = RESISTOR * (5.0 / voltage - 1.0);
    SoilTemp = 1.0 / (log(resistance / NOMINALRES) / BCOEFF + 1.0 / (NOMINALTEMP + 273.15)) - 273.15;
    return SoilTemp; // °C
}

float* Sensors::readNPK(){
    static float soilNutrients[3]; // To store N, P, and K values (use static to persist across function calls)

    // Read Nitrogen
    digitalWrite(RE_PIN, HIGH);
    if (MAX485.write(NITRO, 8) == 8) {
      digitalWrite(RE_PIN, LOW);
      for (byte i = 0; i < 7; i++) {
        NPK_VALUES[i] = MAX485.read();
      }
      soilNutrients[0] = NPK_VALUES[4];
    }

    // Read Phosphorus
    digitalWrite(RE_PIN, HIGH);
    if (MAX485.write(PHOS, 8) == 8) {
      digitalWrite(RE_PIN, LOW);
      for (byte i = 0; i < 7; i++) {
        NPK_VALUES[i] = MAX485.read();
      }
      soilNutrients[1] = NPK_VALUES[4];
    }

    // Read Potassium
    digitalWrite(RE_PIN, HIGH);
    if (MAX485.write(POTA, 8) == 8) {
      digitalWrite(RE_PIN, LOW);
      for (byte i = 0; i < 7; i++) {
        NPK_VALUES[i] = MAX485.read();
      }
      soilNutrients[2] = NPK_VALUES[4];
    }

    return soilNutrients;  // Return the array pointer
}

float Sensors::readLDR(){
    float LDR_Value = analogRead(LDR_PIN);
    return LDR_Value;
}

float Sensors::readLVL(){
    float LVL_Value = analogRead(LVL_PIN);
    return LVL_Value;
}

float* Sensors::readDHT11() {
    static float AmbientVals[2];
    
    float AmbHum = dht11.readHumidity();
    float AmbTemp = dht11.readTemperature();

    // Check for valid readings (e.g., not NaN)
    if (isnan(AmbHum) || isnan(AmbTemp)) {
        AmbientVals[0] = 0.0f;
        AmbientVals[1] = 0.0f;
    } else {
        AmbientVals[0] = AmbHum;
        AmbientVals[1] = AmbTemp;
    }
    
    return AmbientVals;
}