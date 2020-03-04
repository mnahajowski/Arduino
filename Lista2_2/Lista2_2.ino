/*Napisz program, który będzie mierzy czas przez jaki przycisk był w stanie wciśniętym. Po zwolnieniu przycisku na terminalu powinien pojawić się komunikat o długości wciśnięcia przycisku. Wynik ma zostać przedstawiony w milisekundach oraz w formacie zegarowym H:MM:SS.z. Przykładowo może to wyglądać tak:

Przycisk wcisniety przez: 344 -> 0:00:00.344
Przycisk wcisniety przez: 1412 -> 0:00:01.412
Przycisk wcisniety przez: 4359 -> 0:00:04.359
*/

#define BUTTON_PIN 2
#define MINUTES_IN_HOUR 60
#define SECONDS_IN_MINUTE 60
#define MILIS_IN_SECOND 1000
char buffer[50];
int time_start = 0;
int time_end = 0;
int hours = 0;
int minutes = 0;
int seconds = 0;
int milis = 0;
bool lastBtnState = HIGH;

void setup() {

  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.println("Wcisnij przycisk!");
}

void loop() {
  bool currentBtnState = digitalRead(BUTTON_PIN);
 
  if(currentBtnState != lastBtnState) {
    if(currentBtnState == LOW) {
      time_start = millis();
    } else {
      time_end = millis();
      convert(time_end - time_start);
      sprintf(buffer, "Przycisk wcisniety przez: %d -> %02d:%02d:%02d:%03d",time_end - time_start, hours, minutes, seconds, milis);
      Serial.println(buffer);
    }
  }
  lastBtnState = currentBtnState;
}

void convert(int time) {
  milis = time%MILIS_IN_SECOND;
  time = time/MILIS_IN_SECOND;
  seconds = time%SECONDS_IN_MINUTE;
  time = time/SECONDS_IN_MINUTE;
  minutes = time%MINUTES_IN_HOUR;
  time = time/MINUTES_IN_HOUR;
  hours = time;
}
