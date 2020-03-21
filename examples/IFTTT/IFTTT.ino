#include <WiFi.h>
#include <HTTPClient.h>
#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>

const char* ssid ="********";
const char* password = "********";
const int buttonPin = 16;
int buttonPressDuration;
const int PixelCount = 16;
const int PixelPin = 32;
const int AnimCount = 1;
const int TailLength = 6;
const float MaxLightness = 0.2f;

NeoGamma<NeoGammaTableMethod> colorGamma;
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);
NeoPixelAnimator animations(AnimCount);


void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  strip.Begin();
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}

void loop() {
  animations.UpdateAnimations();
  strip.Show();
  if (is_button_pressed(100000)) {
    DrawTailPixels();
    animations.StartAnimation(0, 100, LoopAnimUpdate); 
    if(WiFi.status()== WL_CONNECTED) {
      HTTPClient http;   
      http.begin("https://maker.ifttt.com/trigger/{your_action}/with/key/{your_key}");
      http.addHeader("Content-Type", "text/plain");
      int httpResponseCode = http.POST("Test");
      if (httpResponseCode>0) {
        String response = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(response);
      } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    } else {
      Serial.println("Error in WiFi connection");   
    }
  }
}

bool is_button_pressed(int buttonPressRequirement) {
  if (digitalRead(buttonPin) == LOW) {
    buttonPressDuration++;
    if (buttonPressDuration >= buttonPressRequirement) {
      buttonPressDuration = 0;
      Serial.println("Furry paw detected!");
      return true;
    } else {
      return false;
    }
  } else {
    buttonPressDuration = 0;
    return false;  
  }
}

void LoopAnimUpdate(const AnimationParam& param) {
  if (param.state == AnimationState_Completed){
    animations.RestartAnimation(param.index);
    strip.RotateRight(1);
  }
}

void DrawTailPixels() {
  float hue = 100 / 360.0f;
  for (uint16_t index = 0; index < strip.PixelCount() && index <= TailLength; index++) {
    float lightness = index * MaxLightness / TailLength;
    RgbColor color = HslColor(hue, 1.0f, lightness);
    strip.SetPixelColor(index, colorGamma.Correct(color));
  }
}
