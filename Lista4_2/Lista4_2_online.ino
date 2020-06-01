#define ENCODER_A 0
#define ENCODER_B 13
#define BUTTON_PIN_RED 2
#define BUTTON_PIN_GREEN 4
#define STANDARD_DELAY 20
#define RED 6
#define GREEN 5
#define BLUE 3
#define DEFAULT_POWER 0
#include<Wire.h> 
#include<LiquidCrystal.h>  
int aState;
int rightLastState;
int leftLastState;
int current = RED;
int red_power = DEFAULT_POWER;
int green_power = DEFAULT_POWER;
int blue_power = DEFAULT_POWER;
LiquidCrystal lcd(7,8,9,10,11,12);
bool lastBtnState_red = HIGH;
bool lastBtnState_green = HIGH;

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print(" RED GREEN BLUE");

  pinMode (ENCODER_A,INPUT_PULLUP);     //konfiguracja wyjść enkodera
  pinMode (ENCODER_B,INPUT_PULLUP);
  pinMode(BUTTON_PIN_RED, INPUT_PULLUP);
  pinMode(BUTTON_PIN_GREEN, INPUT_PULLUP);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  analogWrite(GREEN, green_power);
  analogWrite(RED, red_power);
  analogWrite(BLUE, blue_power);
  lcd.setCursor(0,1);
  lcd.print(">");
  lcd.setCursor(1,1);
  lcd.print(red_power);
  lcd.setCursor(5,1);
  lcd.print(green_power);
  lcd.setCursor(11,1);
  lcd.print(blue_power);
  //aLastState = digitalRead(ENCODER_A);
}

void loop() {
  color_changer();
  power_changer();
}

void color_changer() {  // przyciski
  bool currentBtnState_red = digitalRead(BUTTON_PIN_RED); // obecny stan pierwszego buttona
  bool currentBtnState_green = digitalRead(BUTTON_PIN_GREEN);
  if(currentBtnState_red != lastBtnState_red) { // w lewo
    delay(STANDARD_DELAY);
    currentBtnState_red = digitalRead(BUTTON_PIN_RED);
    if(currentBtnState_red != lastBtnState_red) {
      if(current == RED) {
        printer(0,10);
        current = BLUE;
      } else if(current == GREEN) {
        printer(4,0);
        current = RED;
      } else if(current == BLUE) {
        printer(10,4);
        current = GREEN;
      }
    }
  } else if(currentBtnState_green != lastBtnState_green) {
    delay(STANDARD_DELAY);
    currentBtnState_green = digitalRead(BUTTON_PIN_GREEN);
    if(currentBtnState_green != lastBtnState_green) {
      if(current == RED) {
        printer(0,4);
        current = GREEN;
      } else if(current == GREEN) {
        printer(4,10);
        current = BLUE;
      } else if(current == BLUE) {
        printer(10,0);
        current = RED;
      }
    }
  }  
}

void printer(int index1, int index2) {
  lcd.setCursor(index1, 1);
  lcd.print(" ");
  lcd.setCursor(index2, 1);
  lcd.print(">");
}

void power_changer() {  // enkoder
  bool left = digitalRead(ENCODER_A);
  bool right = digitalRead(ENCODER_B);

  if (rightLastState != right){
    delay(20);
    if(right == LOW) {
      if(current == RED) {
        change_value_up(RED, 1, &red_power);
      } else if(current == GREEN) {
        change_value_up(GREEN, 5, &green_power);
      } else if(current == BLUE) {
        change_value_up(BLUE, 11, &blue_power);
      }
    }
  }
  if(leftLastState != left) {
    delay(20);
    if(left == LOW) {
      if(current == RED) {
        change_value_down(RED, 1, &red_power);
      } else if(current == GREEN) {
        change_value_down(GREEN, 5, &green_power);
      } else if(current == BLUE) {
        change_value_down(BLUE, 11, &blue_power);
      }
    }
  }
  leftLastState = left;
  rightLastState = right;
}


void change_value_up(int color, int index, int *value) {
  *value += 5;
  if(*value > 255) {
    *value = 255;
  }
  lcd.setCursor(index, 1);
  lcd.print("   ");
  lcd.setCursor(index, 1);
  lcd.print(*value);
  analogWrite(color, *value);
}

void change_value_down(int color, int index, int *value) {
  *value -= 5;
  if(*value < 0) {
    *value = 0;
  }
  lcd.setCursor(index, 1);
  lcd.print("   ");
  lcd.setCursor(index, 1);
  lcd.print(*value);
  analogWrite(color, *value);
}
