#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>

#define RST_PIN         9          
#define SS_PIN          10   
#define BUZZER_PIN      4   // Buzzer on digital pin 4
Servo myservo;
int pos = 0;
int i;
byte accessUID[4] = {0xF5, 0xB2, 0xEA, 0x6A};
MFRC522 mfrc522(SS_PIN, RST_PIN);  
LiquidCrystal_I2C lcd(0x27, 16,2);



void setup() {
  Serial.begin(9600);    
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("GateGuard");
  lcd.setCursor(2,1);
  lcd.print("Initializing...");
  SPI.begin();      
  mfrc522.PCD_Init();    
  delay(3000);        
  Serial.println(F("Scanning for available tags in the field...."));
  delay(1000);
  lcd.clear();
  myservo.attach(3);
  myservo.write(0);
  pinMode(BUZZER_PIN, OUTPUT); // Set buzzer pin as output 
}


// Buzz function: buzzes the buzzer given number of times
void buzz(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);
  }
}

void longbuzz(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(700);                 // Increase ON time
    digitalWrite(BUZZER_PIN, LOW);
    delay(300);                 // Optional: adjust pause between buzzes
  }
}


void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Please Tap your");
  lcd.setCursor(3, 1);  // Adjusted to center 9-character text on 16-char display
  lcd.print("Key Card");



  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  if (mfrc522.uid.uidByte[0] == accessUID[0] &&
      mfrc522.uid.uidByte[1] == accessUID[1] &&
      mfrc522.uid.uidByte[2] == accessUID[2] &&
      mfrc522.uid.uidByte[3] == accessUID[3]) {
   
    buzz(2); //Buzz 2 times for access granted
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Granted!");
    lcd.setCursor(0, 1);
    lcd.print("UID: ");
    for (byte j = 0; j < 4; j++) {
      lcd.print(mfrc522.uid.uidByte[j], HEX);
      if (j < 3) lcd.print(":");
    }

    delay(2000);  // Display UID for 2 seconds

    // Open gate
    for (pos = 0; pos <= 90; pos += 1) {
      myservo.write(pos);
      delay(15);
    }

    // Countdown to lock
    for (i = 10; i >= 0; i--) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Access Granted!");
      lcd.setCursor(0, 1);
      lcd.print("Locking in: ");
      lcd.print(i);
      delay(1000);
    }

    myservo.write(0);
  } else {
    longbuzz(1); //Buzz 1 time for access denied
    lcd.clear();

    for (i = 5; i >= 0; i--) {
      lcd.setCursor(0, 0);
      lcd.print("Access Denied!");
      lcd.setCursor(0, 1);
      lcd.print("Try again in: ");
      lcd.print(i);
      delay(800);
      lcd.clear();
    }

    lcd.clear();
  }

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
