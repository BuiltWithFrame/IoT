const int buttonPin = 16;
int buttonPressDuration;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  if (is_button_pressed(250000)) {
    Serial.println("The button is pressed!");
  }
}

bool is_button_pressed(int buttonPressRequirement) {
  if (digitalRead(buttonPin) == LOW) {
    buttonPressDuration++;
    if (buttonPressDuration >= buttonPressRequirement) {
      buttonPressDuration = 0;
      return true;
    } else {
      return false;
    }
  } else {
    buttonPressDuration = 0;
    return false;  
  }
}
