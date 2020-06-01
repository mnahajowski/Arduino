// najchetniej bym wykorzystal lise dwukierunkowa struktur, zawierajaca tablice tego co ma, pointer na poprzedni, i pointer na siebie

#define ENCODER_A 0
#define ENCODER_B 13
#define BUTTON_PIN_RED 2
#define BUTTON_PIN_GREEN 4
#define STANDARD_DELAY 20
#define MAIN_MENU_SIZE 6
#define PHONE_BOOK_SIZE 3
#define MESSAGES_SIZE 4
#define SETTINGS_SIZE 3
#define CLOCK_SIZE 5
#include<Wire.h> 
#include<LiquidCrystal.h>  
int current_main_index = 0;
LiquidCrystal lcd(7,8,9,10,11,12);
String main_menu[MAIN_MENU_SIZE] = {"1.MAKE CALL", "2.PHONE BOOK", "3.MESSAGES", "4.SETTINGS", "5.CLOCK", "6.CALCULATOR"};
String phone_book[PHONE_BOOK_SIZE] = {"1.SEARCH", "2.ADD", "3.REMOVE"};
String messages[MESSAGES_SIZE] = {"1.WRITE", "2.INBOX", "3.OUTBOX", "4.TEMPLATES"};
String settings[SETTINGS_SIZE] = {"1.TONES", "2.AUTO ANSWER", "3.LANGUAGE"};
String clock_array[CLOCK_SIZE] = {"1.ALARM CLOCK", "2.CLOCK SETTINGS", "3.DATE SETTINGS", "4.STOPWATCH", "5.COUNTDOWN TIMER"};
bool lastBtnState_red = HIGH;
bool lastBtnState_green = HIGH;
String *working_at_array;
int max_size;
int aLastState;
int aState;
int current_index = -1;
byte customChar1[] = {
  B00000,
  B01000,
  B01110,
  B01000,
  B01000,
  B01000,
  B01000,
  B00000
};

byte customChar2[] = {
  B00000,
  B00100,
  B01010,
  B11111,
  B10001,
  B10001,
  B11111,
  B00000
};

byte customChar3[] = {
  B10001,
  B01010,
  B00100,
  B01010,
  B10001,
  B00000,
  B00000,
  B00000
};
void setup() {  // komunikat powitalny
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print(main_menu[0]);
  working_at_array = main_menu;
  //printing(working_at_array);
  pinMode (ENCODER_A,INPUT_PULLUP);     //konfiguracja wyjść enkodera
  pinMode (ENCODER_B,INPUT_PULLUP);
  aLastState = digitalRead(ENCODER_A);
  lcd.createChar(0, customChar1);
  lcd.createChar(1, customChar2);
  lcd.createChar(2, customChar3);
}

void loop() {

  bool currentBtnState_red = digitalRead(BUTTON_PIN_RED); // obecny stan pierwszego buttona
  bool currentBtnState_green = digitalRead(BUTTON_PIN_GREEN);

  if(currentBtnState_red != lastBtnState_red) { // w lewo
    delay(STANDARD_DELAY);
    currentBtnState_red = digitalRead(BUTTON_PIN_RED);
    if(currentBtnState_red == LOW) {
      if(working_at_array == main_menu) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("JESTES NA GORNYM");
        lcd.setCursor(0,1);
        lcd.print("POZIOMIE");
      } else {
        max_size = MAIN_MENU_SIZE;
        working_at_array = main_menu; // jeszcze blad wyjscia z menu
        current_index = -1;
        printing(working_at_array, current_main_index);
      }     
    } // WYBRALES OPCJE SEARCH
  }
  if(currentBtnState_green != lastBtnState_green) {
    delay(STANDARD_DELAY);
    currentBtnState_green = digitalRead(BUTTON_PIN_GREEN);
    if(currentBtnState_green != lastBtnState_green) {
      
      if(working_at_array == main_menu) {
        //lcd.setCursor(0,15);
        //lcd.print(current_main_index);
        if(current_main_index == 0) {
          print_communicate(working_at_array, current_main_index);
          
        } else if(current_main_index == 1) {
            working_at_array = phone_book;
            current_index = 0;
            max_size = PHONE_BOOK_SIZE;
            printing(working_at_array, current_index);
        } else if(current_main_index == 2) {
            working_at_array = messages;
            current_index = 0;
            max_size = MESSAGES_SIZE;
            printing(working_at_array, current_index);
        } else if(current_main_index == 3) {
          //lcd.print("dvgdsfas");
            working_at_array = settings;
            max_size = SETTINGS_SIZE;
            current_index = 0;
            printing(working_at_array, current_index);
        } else if(current_main_index == 4) {
            working_at_array = clock_array;
            max_size = CLOCK_SIZE;
            current_index = 0;
            printing(working_at_array, current_index);
        } else if(current_main_index == 5) {
            print_communicate(working_at_array, current_main_index);
        }
        
      
       else {
          print_communicate(working_at_array, current_index);
       }
      } else {
        print_communicate(working_at_array, current_index);
        //encoder_function(&current_index, max_size);
      }
    }
  }
  lastBtnState_green = currentBtnState_green;
  lastBtnState_red = currentBtnState_red;

  if(working_at_array == main_menu) {
    encoder_function(&current_main_index, MAIN_MENU_SIZE);
  } else {
    encoder_function(&current_index, max_size);
  }
}

void printing(String *my_array, int index) {
  //Serial.println(my_array[index]);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(my_array[index]);
  lcd.setCursor(1,14);
  lcd.write(byte(0));
  lcd.setCursor(1,15);
  lcd.write(byte(1));
}

void print_communicate(String *my_array, int index) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WYBRALES OPCJE");
  lcd.setCursor(0,1);
  lcd.print(my_array[index]);
  lcd.setCursor(1,15);
  lcd.write(byte(2));
}



void encoder_function(int *index, int max_current) {
  aState = digitalRead(ENCODER_A);
  //lastBtnState_green = digitalRead(ENCODER_A);
  if (aState != aLastState && aState == LOW){
    if (digitalRead(ENCODER_B) != aState) { // to zwiekszamy
      (*index)++;
      if(*index > max_current-1) {
        *index = 0;
      }
    }
   else {
     (*index)--;
     if(*index < 0) {
      *index = max_current;
     }
    }
    printing(working_at_array, *index);
  }
  aLastState = aState;
 
}
