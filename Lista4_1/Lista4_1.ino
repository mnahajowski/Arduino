#define BUTTON_PIN_RED 2
#define BUTTON_PIN_GREEN 4
#define RED 6
#define GREEN 5
#define BLUE 3
#define DEFAULT_DELAY 200
#define STANDARD_DELAY 20
#define ADC_PIN A3

int analogValue = 0;
bool lastBtnState_red = HIGH;
bool lastBtnState_green = HIGH;
bool led_state = LOW;
int my_delay = 0;
long time_start = 0;
long time_end = 0;
int last = BLUE;


void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON_PIN_RED, INPUT_PULLUP);
  pinMode(BUTTON_PIN_GREEN, INPUT_PULLUP);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  my_delay = DEFAULT_DELAY;
}

void loop() {

  time_end = millis();

  if(time_end - time_start > my_delay) {
    time_start = time_end;

    if(last == BLUE) {
      digitalWrite(BLUE, LOW);
      digitalWrite(RED, HIGH);
      last = RED;
    } else if(last == RED) {
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      last = GREEN;
    } else if(last == GREEN) {
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, HIGH);
      last = BLUE;
    }
  }
  analogs();
  
  bool currentBtnState_red = digitalRead(BUTTON_PIN_RED); // obecny stan pierwszego buttona
  bool currentBtnState_green = digitalRead(BUTTON_PIN_GREEN); // obecny stan drugiego buttona

  if(currentBtnState_red != lastBtnState_red) {
    delay(STANDARD_DELAY);
    currentBtnState_red = digitalRead(BUTTON_PIN_RED);
    if(currentBtnState_red != lastBtnState_red) {
      my_delay += 50;
    }
  }
  if(currentBtnState_green != lastBtnState_green) {
    delay(STANDARD_DELAY);
    currentBtnState_green = digitalRead(BUTTON_PIN_GREEN);
    if(currentBtnState_green != lastBtnState_green) {
      my_delay -= 50;
      if(my_delay <= 0) {
        my_delay = 0;
        digitalWrite(RED, HIGH);  // miganie ustaje, stale swiatlo
      }
    }
  }
}

void analogs() {
  analogValue = analogRead(ADC_PIN);
  int power = map(analogValue, 0, 1023, 0, 255);
  analogWrite(last, power);
}
