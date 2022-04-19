#include <Servo.h>

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define BOMBA_LED 13
#define ALARME_MIN 9
#define ALARME_MAX 8
#define ALARME_FEED 10
#define POT A2
#define BOTAO 6

Servo servo_pin_3;
int BT=A0;
long int tempo;

void setup(){ 
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Pets");

  pinMode(BOMBA_LED, OUTPUT);	
  pinMode(ALARME_MAX, OUTPUT); // declara que a variável Alarme_MAX é uma saída
  pinMode(ALARME_MIN, OUTPUT); // declara que a variável Alarme_MIN é uma saída
  pinMode(POT, INPUT);
  
  pinMode(ALARME_FEED, OUTPUT);
  
  servo_pin_3.attach(6);
  pinMode(BT,INPUT_PULLUP);
  
}


void loop() {
 	
  int nivel = analogRead (POT);
  
  if(digitalRead(BT) == HIGH){
    tone (ALARME_FEED,1000, 500);
    servo_pin_3.write(90);
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print("Alimentando");
	delay(1000);
  }else{
    servo_pin_3.write(0);
	noTone (ALARME_FEED);
    delay(1000);
  }
 
  
 
  lcd.setCursor(0,0);
  lcd.print("Agua...");
  lcd.print("          ");
  
  if(nivel >= 100){
  	lcd.setCursor(7,16);
    lcd.print(nivel);
    lcd.print(" ml");
  }
  
  if((nivel >=100) || (nivel <=500) )
    digitalWrite (BOMBA_LED, HIGH);
  
   
  if ((nivel <= 400) && (nivel >= 1)) { // Se o nível do reservatório for <= a 400 "E" >= 1 o alarme mínimo aciona
    tone (ALARME_MIN, 400);
    tone (ALARME_FEED, 200);
  }
  else if (nivel >= 450) { // Se não o nível do reservatório for >= a 450 o alarme mínimo desliga
    noTone (ALARME_MIN); 
   
  }
  
  if((nivel>=700))
     digitalWrite (BOMBA_LED, LOW);
  
  if(nivel>=900){
     tone (ALARME_MAX, 400);
    lcd.setCursor(0,0);
    
    lcd.print("Tanque cheio");
  }
 
  if(nivel>=900)
     noTone (ALARME_MAX);
  
}

 