
// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;  // the number of the pushbutton pin
const int ledPin = 1;     // the number of the LED pin
const int resetPin = 3;
// Variables will change:
int ledState = HIGH;  // the current state of the output pin
int resetState = HIGH;
int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the input pin
int resetStartFlag = LOW;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long lastResetTime = 0;     // the last time the output pin was toggled
unsigned long debounceDelay = 50;   // the debounce time; increase if the output flickers
unsigned long resetDelay = 199;


void setup() {
  pinMode(buttonPin, INPUT);
  //pinMode(ledPin, OUTPUT);
  pinMode(resetPin, OUTPUT);


  // set initial LED state
  //digitalWrite(ledPin, ledState);
  digitalWrite(resetPin, resetState);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);


  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    delay(50);
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {


    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        if (resetStartFlag == LOW) {
          resetStartFlag = HIGH;
          lastResetTime = millis();
        }
      }
    }
  }

  if (resetStartFlag == HIGH) {

    digitalWrite(resetPin, LOW);
    // delay(200);
    // digitalWrite(resetPin, HIGH);
    //  resetStartFlag = LOW;
    if ((millis() - lastResetTime) > resetDelay) {


      digitalWrite(resetPin, HIGH);
      resetStartFlag = LOW;
    }
  }

  // set the LED:
  // digitalWrite(ledPin, ledState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
