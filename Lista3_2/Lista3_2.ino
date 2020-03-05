#define ADC_PIN A3
#define BUTTON_PIN 4
#define converter 0,0049
//Biblioteka do komunikacji I2C
#include<Wire.h> 
//Biblioteka do obsługi wyświetlacza LCD
#include<LiquidCrystal_I2C.h>   
int analogValue = 0;
bool lastBtnState = HIGH;
bool flag = true;
double volts = 0;
char[100] buffer;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Adres wyświetlacza LCD 0x27.
 
void setup() {
  lcd.begin(16, 2);         //konfiguracja lcd, 2 linie 16 znakowe
  lcd.setCursor(0,0);       //ustawienie kursora
  lcd.print("Miernik "); //wyswietlenie napisu
  lcd.print(ADC_PIN);
  lcd.setCursor(0,1);
}
 
void loop() {
  bool currentBtnState = digitalRead(BUTTON_PIN);
  if(currentBtnState != lastBtnState && flag == true) {
    lcd.noBacklight();
    flag = false;
  } else if (currentBtnState != lastBtnState && flag == false) {
    lcd.backlight();
    flag = true;
  }
  lastBtnState = currentBtnState;

  
  analogValue = analogRead(ADC_PIN);
  volts = toVolt(analogValue);
  lcd.sprintf(buffer, "V=%-6fADC=%4f", volts, analogValue);
  Serial.print(volts);
  Serial.print("\t");
  Serial.print(analogValue);
  Serial.println("");
  lcd.setCursor(0,1);
  delay(50);
} 

double toVolt(int value) {
  return value * converter;
}
