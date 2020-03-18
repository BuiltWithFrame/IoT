const byte batteryPin = A13;
const float criticalBatteryLevel = 3.4;
float batteryAnalogReading;
float batteryVoltageReading;

void setup() {
  Serial.begin(115200);
}

void loop() {
  is_battery_critical();
  Serial.println(get_battery_voltage());
  delay(1000);
}

bool is_battery_critical() {
  if (get_battery_voltage() > criticalBatteryLevel) {
    Serial.println("Battery good.");
    return true;
  } else {
    Serial.println("Battery low.");
    return false;
  }
}

float get_battery_voltage() {
  batteryAnalogReading = analogRead(batteryPin);
  batteryVoltageReading = ((batteryAnalogReading * 2) / 4098) * 3.3;
  return batteryVoltageReading;
}
