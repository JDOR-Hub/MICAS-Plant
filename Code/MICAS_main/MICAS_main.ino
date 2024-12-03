#include "MICAS_Config.h"
#include "MICAS_Sensors.h"
#include "MICAS_Actuators.h"
#include "MICAS_Datalogger.h"

// Declare sensor, actuator, and datalogger objects
Sensors MySensors;
Actuators MyActuators;
Datalogger MyDatalogger;

// Declare states for actuators
bool WPsState = false;
bool EVState = false;

// Declare sensor readings globally
float SOILHUM, SOILTEMP, SOILN, SOILP, SOILK, LDR_VALUE, LVL_VALUE, AMBHUM, AMBTEMP;

void setup() {
  // Initialize serial communication and hardware components
  Serial.begin(9600);
  MySensors.begin();
  MyActuators.begin();
  MyDatalogger.begin("datalog.csv");
}

void loop() {
  // Read sensor values
  SOILHUM = MySensors.readFC28();   // Soil humidity (%)
  SOILTEMP = MySensors.readTemp();  // Soil temperature (°C)
  float* NPKVALS = MySensors.readNPK();   // Soil NPK values (mg/kg)
  SOILN = NPKVALS[0];               // Nitrogen (mg/kg)
  SOILP = NPKVALS[1];               // Phosphorus (mg/kg)
  SOILK = NPKVALS[2];               // Potassium (mg/kg)
  LDR_VALUE = MySensors.readLDR();  // Light level (float)
  LVL_VALUE = MySensors.readLVL();  // Water level (float)
  float* DHT11VALS = MySensors.readDHT11(); // Ambient humidity and temperature
  AMBHUM = DHT11VALS[0];           // Ambient humidity (%)
  AMBTEMP = DHT11VALS[1];          // Ambient temperature (°C)

  // Log sensor data
  logSensorData();

  // Watering system logic
  if (SOILHUM < SOILHUM_THRES) {
    WPsState = true;
    MyActuators.writeWPs(WPsState);
    delay(ACT_DURATION);
    MyActuators.writeWPs(false);
  } else {
    WPsState = false;
    MyActuators.writeWPs(WPsState);
  }

  // Fertilizer system logic
  if (SOILN < NITRO_THRES || SOILP < PHOS_TRESH || SOILK < POTA_TRESH) {
    EVState = true;
    MyActuators.writeEV(EVState);
    delay(ACT_DURATION);
    MyActuators.writeEV(false);
  } else {
    EVState = false;
    MyActuators.writeEV(EVState);
  }

  // Temperature and environmental checks
  checkEnvironmentalConditions();

  // Delay before the next loop
  delay(LOOP_DELAY);
}

void logSensorData() {
  MyDatalogger.appendCSVRow("datalog.csv", SOILHUM, SOILTEMP, SOILN, SOILP, SOILK, 
                            LDR_VALUE, LVL_VALUE, AMBHUM, AMBTEMP, WPsState, WPsState, EVState);
}

void checkEnvironmentalConditions() {
  // Check soil temperature
  if (SOILTEMP < SOILTEMP_MIN_THRES) {
    Serial.println("ALERT! SOIL TEMPERATURE TOO LOW");
  } else if (SOILTEMP > SOILTEMP_MAX_THRES) {
    Serial.println("ALERT! SOIL TEMPERATURE TOO HIGH");
  }

  // Check ambient temperature
  if (AMBTEMP < AMBTEMP_MIN_THRES) {
    Serial.println("ALERT! AMBIENT TEMPERATURE TOO LOW");
  } else if (AMBTEMP > AMBTEMP_MAX_THRES) {
    Serial.println("ALERT! AMBIENT TEMPERATURE TOO HIGH");
  }

  // Check ambient humidity
  if (AMBHUM < AMBHUM_MIN_THRES) {
    Serial.println("ALERT! AMBIENT HUMIDITY TOO LOW");
  } else if (AMBHUM > AMBHUM_MAX_THRES) {
    Serial.println("ALERT! AMBIENT HUMIDITY TOO HIGH");
  }

  // Check ambient light
  if (LDR_VALUE < LDR_TRESH) {
    Serial.println("ALERT! AMBIENT LIGHT TOO DARK");
  }

  // Check water level
  if (LVL_VALUE < LVL_TRESH) {
    Serial.println("ALERT! WATER DEPOSIT TOO LOW");
  }

  // Log sensor data for environmental conditions
  logSensorData();
}