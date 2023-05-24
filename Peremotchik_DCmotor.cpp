#include <LiquidCrystal.h>
#include <EncButton.h>

EncButton<EB_TICK, 5> BUTTON_FORWARD;
EncButton<EB_TICK, 6> BUTTON_REVERSE;

#define EB_DEB 50
#define EB_CLICK 400

#define BIG_DIR_1 3
#define BIG_DIR_2 9
#define SMALL_DIR_1 8
#define SMALL_DIR_2 2
//потенциометр
#define POT A0

//переменные
int small_mot_dir = 2;
int big_mot_dir = 2;
int dir_sec = 0;
int speed_1;
//экран
constexpr uint8_t PIN_RS = 10;
constexpr uint8_t PIN_EN = 11;
constexpr uint8_t PIN_DB4 = 12;
constexpr uint8_t PIN_DB5 = 13;
constexpr uint8_t PIN_DB6 = 7;
constexpr uint8_t PIN_DB7 = 4;
LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_DB4, PIN_DB5, PIN_DB6, PIN_DB7);
void setup(){
  lcd.begin(16, 2);
  
  lcd.setCursor(0, 0);
  

  
  BUTTON_FORWARD.setButtonLevel(LOW);     
  BUTTON_FORWARD.setHoldTimeout(1000);     
  BUTTON_FORWARD.setStepTimeout(500);

  BUTTON_REVERSE.setButtonLevel(LOW);     
  BUTTON_REVERSE.setHoldTimeout(1000);     
  BUTTON_REVERSE.setStepTimeout(500);
 
  pinMode(BIG_DIR_1, OUTPUT);
  pinMode(BIG_DIR_2, OUTPUT);
  pinMode(SMALL_DIR_1, OUTPUT);
  pinMode(SMALL_DIR_2, OUTPUT);
 
  
}

  void loop(){
     
    BUTTON_FORWARD.tick();
    BUTTON_REVERSE.tick();
    if(BUTTON_FORWARD.click()){
      Serial.println("clicked");
       big_mot_dir = 1;
       small_mot_dir = 1;
    }
    if(BUTTON_REVERSE.click()){
      Serial.println("clicked_rev");
      big_mot_dir = 0;
      small_mot_dir = 1;
    }
    if(big_mot_dir == 1 && small_mot_dir == 1){
      speed_1 = analogRead(POT) / 4;
      lcd.command(0b101010);
      lcd.clear();
      lcd.print("C""\xEA""o""p""o""c""\xF2""\xFC"":");
      lcd.print(round(speed_1/2.55));
      lcd.print("%");
      Serial.println(speed_1);
      Serial.println("Slychai 1");
      analogWrite(BIG_DIR_1, speed_1);
      digitalWrite(BIG_DIR_2, LOW);
      digitalWrite(SMALL_DIR_1,HIGH);
      digitalWrite(SMALL_DIR_2,LOW);
      delay(10);
      dir_sec = dir_sec + 10;
    }
    else if(big_mot_dir == 1 && small_mot_dir == 0){
      speed_1 = analogRead(POT) / 4;
      lcd.command(0b101010);
      lcd.clear();
      lcd.print("C""\xEA""o""p""o""c""\xF2""\xFC"":");
      lcd.print(round(speed_1/2.55));
      lcd.print("%");
      Serial.println(speed_1);
      Serial.println("Slychai 1.1");
      analogWrite(BIG_DIR_1, speed_1);
      digitalWrite(BIG_DIR_2, LOW);
      digitalWrite(SMALL_DIR_1,LOW);
      digitalWrite(SMALL_DIR_2,HIGH);
      delay(10);
      dir_sec = dir_sec + 10;
    }
    if(big_mot_dir == 0 && small_mot_dir == 1 ){
      speed_1 = analogRead(POT) / 4;
      lcd.command(0b101010);
      lcd.clear();
      lcd.print("C""\xEA""o""p""o""c""\xF2""\xFC"":");
      lcd.print(round(speed_1/2.55));
      lcd.print("%");
      Serial.println(speed_1);
      Serial.println("Slychai 2");
      digitalWrite(BIG_DIR_1, LOW);
      analogWrite(BIG_DIR_2, speed_1);
      digitalWrite(SMALL_DIR_1,HIGH);
      digitalWrite(SMALL_DIR_2,LOW);
      delay(10);
      dir_sec = dir_sec + 10;
    }
    else if(big_mot_dir == 0 && small_mot_dir == 0){
      speed_1 = analogRead(POT) / 4;
      lcd.command(0b101010);
      lcd.clear();
      lcd.print("C""\xEA""o""p""o""c""\xF2""\xFC"":");
      lcd.print(round(speed_1/2.55));
      lcd.print("%");
      Serial.println(speed_1);
      Serial.println("Slychai 2.1");
      digitalWrite(BIG_DIR_1, LOW);
      analogWrite(BIG_DIR_2, speed_1);
      digitalWrite(SMALL_DIR_1,LOW);
      digitalWrite(SMALL_DIR_2,HIGH);
      delay(10);
      dir_sec = dir_sec + 10;
    }
    
   if(dir_sec == 1000){
    dir_sec = 0;
      if (small_mot_dir == 1){
        small_mot_dir = 0;
       }
      else if(small_mot_dir == 0){
       small_mot_dir = 1;
       }
       BUTTON_FORWARD.tick();
       BUTTON_REVERSE.tick();
   }
   else{
    BUTTON_FORWARD.tick();
    BUTTON_REVERSE.tick();
   }
  }