#define ARRAY_SIZE 20
#define BUTTON_PIN 4
#define BUTTON_PIN2 2
#define MINIMUM 0
#define LCD_SIZE 16
#include<Wire.h>
#include<LiquidCrystal_I2C.h> 
String whole_text[ARRAY_SIZE];  // tablica stringow, kolejne zdania
String wiadomosc = "";
bool lastBtnState = HIGH;
bool lastBtnState2 = HIGH;
int i = 0;
int current = 0;
// potrzebna flaga ze wlasnie cos przyszlo
bool has_came = false;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2); // konfiguracja lcd
  lcd.setCursor(0,0); // ustawienie kursora
  Serial.println("Podaj zdanie lub uzywaj przyciskow");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(has_came == true) {
    lcd.setCursor(0,0);
    lcd.println(whole_text[i-1]);
    current = i - 1;
    // to sprawdzic
    if(i >= ARRAY_SIZE) {
      i = MINIMUM;
    }
  }

  if(whole_text[current].length() > LCD_SIZE) {
    for(int j = 0; j < (whole_text[current].length() - LCD_SIZE); j++) {
      lcd.scrollDisplayRight();
      delay(150);
    }
    for(int j = 0; j < (whole_text[current].length() - LCD_SIZE); j++) {
      lcd.scrollDisplayLeft();
      delay(150);
    }
  }
  
  bool currentBtnState = digitalRead(BUTTON_PIN); // obecny stan pierwszego buttona
  bool currentBtnState2 = digitalRead(BUTTON_PIN2); // obecny stan drugiego buttona
  if(currentBtnState != lastBtnState) { //jesli wcisniety pierwszy idz w lewo
    delay(50);  // upewnienie sie
    if(currentBtnState != lastBtnState) {
      current--;
      if(current < MINIMUM) {
        current = ARRAY_SIZE;
      }
      lcd.println(whole_text[current]);
    }
  } else if (currentBtnState2 != lastBtnState2) { // jesli wcisniety drugi idz w prawo
    delay(50);  // upewnienie sie
    if(currentBtnState2 != lastBtnState2) {
      current++;
      if(current >= ARRAY_SIZE) {
        current = MINIMUM;
      }
      lcd.println(whole_text[current]);
    }
  }

  if(Serial.available() > 0) {
    wiadomosc = Serial.readStringUntil('\n');
    whole_text[i] = wiadomosc;
    i++;
    has_came = true;
  }
}
