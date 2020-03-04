/*Napisz program, który wykorzysta oba przyciski do zwiększania/zmniejszania licznika.

    Program rozpoczyna pracę z licznikiem ustawionym na 0.
    Wciśnięcie prawego (zielonego) przycisku powoduje zwiększenie licznika o jeden i wyświetlenie aktualnego stanu na Serial Monitor.
    Wciśnięcie lewego (czerwonego) przycisku powoduje zmniejszenie licznika o jeden i wyświetlenie aktualnego stanu na Serial Monitor.
    Program powinien także wykrywać sytuację gdy oba przyciski są wciśnięte jednocześnie i w tej sytuacji dioda LED ma błysnąć tyle razy ile wynosi wartość licznika. Dodatkowo odpowiedni komunikat powinien wyświetlić się na terminalu UART.
    Zadbaj o to, aby pozbyć się dowolną metodą drgań na przyciskach.
*/

#define BUTTON_PIN 2
#define BUTTON_PIN2 4
#define DIODA_PIN 5
#define DEFAULT_DELAY 200
//licznik wcisniecia przycisku
int counter = 0;
bool lastBtnState = HIGH;
bool lastBtnState2 = HIGH;
 
void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP); //przycisk jako wejście
  pinMode(BUTTON_PIN2, INPUT_PULLUP);
  pinMode(DIODA_PIN, OUTPUT);
  Serial.println("Wcisnij przycisk!");
}
 
void loop() {
  bool currentBtnState = digitalRead(BUTTON_PIN);
  bool currentBtnState2 = digitalRead(BUTTON_PIN2);
 
  if(lastBtnState != currentBtnState || lastBtnState2 != currentBtnState2){    //wykrywamy zbocze
    delay(50);
   
    currentBtnState = digitalRead(BUTTON_PIN);
    currentBtnState2 = digitalRead(BUTTON_PIN2);

    if (currentBtnState == LOW && currentBtnState2 == LOW) {

      dioda_flash(counter);
      Serial.println("Oba wcisniete!");
       
    } else if((currentBtnState == LOW || currentBtnState2 == LOW)){ //przycisk wcisniety
     
      delay(50);
      currentBtnState = digitalRead(BUTTON_PIN);
      currentBtnState2 = digitalRead(BUTTON_PIN2);
     
      if(currentBtnState == LOW){ //przycisk wcisniety
        delay(50);
        counter++;
        Serial.print("Liczba nacisniec: ");
        Serial.println(counter);
       
      } else if(currentBtnState2 == LOW) {
        delay(50);
        counter--;
        Serial.print("Liczba nacisniec: ");
        Serial.println(counter);
      }
    }
   
  }
  lastBtnState = currentBtnState;
  lastBtnState2 = currentBtnState2;
}

void dioda_flash(int counter) {
  for(int i = 0; i < counter; i++) {
        digitalWrite(DIODA_PIN, HIGH);
        delay(DEFAULT_DELAY);
        digitalWrite(DIODA_PIN, LOW);
        delay(DEFAULT_DELAY);
   }
}
