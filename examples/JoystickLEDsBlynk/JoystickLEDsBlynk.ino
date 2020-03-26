#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <NeoPixelBus.h>
#define BLYNK_PRINT Serial

char auth[] = "#########################";
char ssid[] = "########";
char pass[] = "########";
const uint16_t PixelCount = 16;
const uint16_t PixelPin = 32;
int xCenter, yCenter, xReading, yReading, pixelNumber, oldPixelNumber;

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

void setup() {
  xCenter = 512;
  yCenter = 512;
  xReading = 512;
  yReading = 512;
  pixelNumber = -1;
  oldPixelNumber = pixelNumber;
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  strip.Begin();
  strip.Show();
}

void loop() {
  Blynk.run();
  strip.Show();
}

BLYNK_WRITE(V0) {
  xReading = param[0].asInt();
  yReading = param[1].asInt();
  Serial.print(xReading);
  Serial.print(", ");
  Serial.println(yReading);
  double joystickRadians;
  double joystickDegrees;
  joystickDegrees = getDegrees(xReading, yReading);
  pixelNumber = map(joystickDegrees, 0, 330, 0, 15);
  pixelNumber = constrain(pixelNumber, 0, 15);
  if (oldPixelNumber != pixelNumber) {
    strip.SetPixelColor(pixelNumber, RgbColor(50, 50, 50));
    strip.SetPixelColor(oldPixelNumber, RgbColor(0, 0, 0));
  }
  if (xReading == 512 && yReading == 512) {
    strip.SetPixelColor(pixelNumber, RgbColor(0, 0, 0));
    strip.SetPixelColor(oldPixelNumber, RgbColor(0, 0, 0));
  }
  oldPixelNumber = pixelNumber;
}

double getDegrees(int x, int y) {
  int xCalibrated = x - xCenter;
  int yCalibrated = y - yCenter;
  xCalibrated = -xCalibrated;
  yCalibrated = -yCalibrated;
  double calculation = atan2(yCalibrated, xCalibrated) * 180 / PI;
  if (calculation < 0) {
    calculation += 360;
  }
  return calculation;
}
