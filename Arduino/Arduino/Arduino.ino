#include <Servo.h>
#include <Keypad.h>

Servo myServo;  
const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const String PASSWORD = "1234"; 
const int MAX_TRIES = 3; 
int tries = 0; 
const int buzzerPin = 10; 
const int ledPin = 11; 

void setup() {
    Serial.begin(115200); 
    myServo.attach(13);  
    pinMode(buzzerPin, OUTPUT); 
    pinMode(ledPin, OUTPUT); 

}

void loop() {
    if (Serial.available() > 0) {
        String data = Serial.readStringUntil('\n'); 
        
        if (data.equalsIgnoreCase("lock")) {
            playBuzzer(1000);
            myServo.write(0);
        }
        else if (data.equalsIgnoreCase("open")) {
            playBuzzer(1000);
            myServo.write(180);
        }
        else if (data.equalsIgnoreCase("on")) {
            digitalWrite(ledPin, HIGH);
        }
        else if (data.equalsIgnoreCase("off")) {
            digitalWrite(ledPin, LOW);
        }

    }
    epMode();
}





void playBuzzer(int duration) {
    tone(buzzerPin, 1000); 
    delay(duration); 
    noTone(buzzerPin); 
}

void epMode(){
  char key = keypad.getKey();
  
  if (key != NO_KEY) {
    static String enteredPassword = ""; 
    
    if (key == 'A') {
      playBuzzer(200);
      Serial.println("Letter-A pressed"); 
    }
    else if (key == 'B') {
      playBuzzer(200);
      Serial.println("Letter-B pressed"); 
    }
    else if (key == 'C') {
      playBuzzer(200);
      Serial.println("Letter-C pressed"); 
    }
    else if (key == 'D') {
      playBuzzer(200);
      Serial.println("Letter-D pressed"); 
    }
    else if (key != '#') {
      playBuzzer(100);
      enteredPassword += key; 
      Serial.println(enteredPassword); 
    }


     else {
      
      if (enteredPassword == PASSWORD) {
        playBuzzer(200);
        delay(100);
        playBuzzer(100);
        myServo.write(180);
        Serial.println("Correct!");
        delay(1000);
        Serial.println("Welcome to MRS - Final Project");
        delay(2000);
        delay(4000); 
        Serial.println("");        
        myServo.write(0);
        tries = 0; 
      } else {
        playBuzzer(1000);
        tries++; 
        Serial.print("Attempts remaining: ");
        Serial.println(MAX_TRIES - tries);
        delay(2000);
        if (tries < MAX_TRIES) {
          Serial.println("Enter Pass Again");
        } else {
          Serial.println("Max reached");
          delay(3000);
          Serial.println("Contact Owner/State your purpose"); 
          delay(2000);
          Serial.println("CHOOSE LETTER A - B - C - D"); 
          delay(2000);
          Serial.println("A: SHOPEE DELIVERY"); 
          delay(2000);
          Serial.println("B: Maningils Utang"); 
          delay(2000);
          Serial.println("C: Naabot na ko"); 
          delay(2000);
          Serial.println("D: Doorbell"); 
          tries = 0; 
        }
      }
      
      enteredPassword = "";
    }
  }

}
