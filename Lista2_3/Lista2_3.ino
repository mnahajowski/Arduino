/*Napisz program, który będzie wczytywał polecenia z terminala UART. Akceptowane polecenia:

    LED ON – włącza diodę LED
    LED OFF – wyłącza diodę LED
    LED BLINK <czas_ms> – miga diodą LED z prędkością wyczytaną z liczby <czas_ms>
    LED BLINK – miga diodą LED z ostatnio użytą prędkością

Program ma wyświetlać odpowiednie komunikaty o przyjęciu polecenia lub przyczynie jego odrzucenia na terminalu. 
Sprawdź przy jakiej najmniejszej częstotliwości będziesz zauważał miganie diody.*/

#define DEFAULT_TIME 200
#define DIODA_PIN 5
String wiadomosc = "";
String my_seconds;
int seconds;
int time;
bool flag = false;
void setup() {
  
  Serial.begin(9600);
  Serial.println("Podaj komende: ");
  time = DEFAULT_TIME;
}

void loop() {

  if(flag == true) {
     dioda_blink(time);
  }
  
  if(Serial.available() > 0) {
    wiadomosc = Serial.readStringUntil('\n');

    if(wiadomosc.equals("LED ON")) {
      Serial.println("Polecenie LED ON");
      digitalWrite(DIODA_PIN, HIGH);
      flag = false;
      
    } else if (wiadomosc.equals("LED OFF")) {
      Serial.println("Polecenie LED OFF");
      digitalWrite(DIODA_PIN, LOW);
      flag = false;
      
    } else if(wiadomosc.startsWith("LED BLINK ")) {
      Serial.println("Polecenie LED BLINK WITH TIME");
      flag = true;
      my_seconds = wiadomosc.substring(10);
      seconds = my_seconds.toInt();
      time = seconds;
      
    } else if(wiadomosc.equals("LED BLINK")) {
      Serial.println("Polecenie LED BLINK");  
      flag = true;
      time = DEFAULT_TIME;  
        
    } else {
      Serial.println("Bledna komenda");
    }
  }  
}

void dioda_blink(int time) {
     digitalWrite(DIODA_PIN, LOW);
     delay(time);
     digitalWrite(DIODA_PIN, HIGH);
     delay(time);
}
