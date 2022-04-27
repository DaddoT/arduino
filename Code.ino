#include <LiquidCrystal.h>   
#include <Keypad.h>
#include <Servo.h>

#define BOMBA_LED 1
#define POT A4
#define BOTAO 6

long timer, start, inicial;
						//inicial = tempo ao ligar o arduino
						//Start = tempo ao iniciar o programa
long time; //Inserida pelo usuário
String timeString;
String schedule[4];
// valor de milis em relação ao tempo
long dia = 86400000;
long hora = 3600000; 
long minuto = 60000; 
long segundo =  1000; 

int pos = 0;
Servo servo_A2;
bool locked = true;
bool active = false;

const byte rows = 4;
const byte columns = 4;
char tecla[rows][columns] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte pinRows[rows] = {7, 6, 5, 4};
byte pinColumn[columns] = {3, 2, 1, 0}; 

Keypad keypad = Keypad( makeKeymap(tecla), pinRows, pinColumn, rows, columns);
LiquidCrystal lcd(13,12,11,10, 9, 8); 

void setup(){
  servo_A2.attach(A2, 500, 2500);
  lcd.begin(16,2); 
  pinMode(A5,OUTPUT);
  pinMode(POT, INPUT);
  pinMode(A0,OUTPUT); 
  pinMode(A1,OUTPUT);
  servo_A2.write(0);
  inicial = millis();
}
void setTimer(){
  start = millis();
}
void open(){
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("aimentando...");
  digitalWrite(A1,LOW);
  digitalWrite(A0,HIGH);
  tone(A5, 1300, 500);
  delay(500);
  tone(A5, 1000, 500);
  delay(500);
  tone(A5, 700, 500);
  
    for (pos = 0; pos <= 90; pos += 1) {
        servo_A2.write(pos);//Open
        delay(15);
          }
  	locked = false;
 lcd.clear();
}
void close(){
  lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Complete...");
  
  digitalWrite(A1,HIGH);
  digitalWrite(A0,LOW);
  
	for (pos = 90; pos >= 0; pos -= 1) {
    servo_A2.write(pos);//Close
    delay(15);
  }
     	locked = true;
lcd.clear();
}

long dias, horas, minutos, segundos, milissegundos;
String stringHoras, stringMinutos, stringSegundos;
int aux = 0;

String milisParaHora(){
  dias = timer / dia ;                              
  horas = (timer % dia) / hora;                       
  minutos = ((timer % dia) % hora) / minuto ;         
  segundos = (((timer % dia) % hora) % minuto) / segundo;
  stringHoras = String(horas);
  stringMinutos = String(minutos);
  stringSegundos = String(segundos);
  
  if(stringHoras.length() == 1){
   	stringHoras = "0";
    stringHoras.concat(String(horas));
  }
  if(stringMinutos.length() == 1){
   	stringMinutos = "0";
    stringMinutos.concat(String(minutos));
  }
  if(stringSegundos.length() == 1){
   	stringSegundos = "0";
    stringSegundos.concat(String(segundos));
  }

  String milisHora = stringHoras;
  milisHora.concat(":");
  milisHora.concat(stringMinutos);
  milisHora.concat(":");
  milisHora.concat(stringSegundos);
  if(segundos == 1 && aux == 0){
  lcd.clear();
    aux = 1;
  }
  if(aux == 1 && segundos != 1){
  	aux = 0;
  }
  return milisHora;
}


 char buf[6];
 
 String timeToChar(){ 
  String Hora;
   for (int i = 0; i < 6 ; i++){
   	buf[i] = timeString.charAt(i);
   }
  Hora.concat(buf[0]);
  Hora.concat(buf[1]);
  Hora.concat(":");
  Hora.concat(buf[2]);
  Hora.concat(buf[3]);
  Hora.concat(":");
  Hora.concat(buf[4]);
  Hora.concat(buf[5]);
  return Hora;
}


void concat(int y){
  time = 10*time + y;
}

//LOOP
void loop(){
  
   int nivel = analogRead (POT);
  
  if((nivel >=100) || (nivel <=500) )
    digitalWrite (BOMBA_LED, HIGH);
  
   
  if ((nivel <= 400) && (nivel >= 1)) { // Se o nível do reservatório for <= a 400 "E" >= 1 o alarme mínimo aciona
    tone (A5, 400);
    tone (A5, 200);
  }
  else if (nivel >= 450) { // Se não o nível do reservatório for >= a 450 o alarme mínimo desliga
    noTone (A5); 
   
  }
  
  if((nivel>=700))
     digitalWrite (BOMBA_LED, LOW);
  
  if(nivel>=900){
     tone (A5, 400);
    lcd.setCursor(6,0);
    //lcd.clear();
    lcd.print(" cheio");
    //lcd.clear();
  }
 lcd.setCursor(0,0);
  if(nivel>=900)
     noTone (A5);
  
  
  timer = millis();
  long t = start + time*1000;
  char key = keypad.getKey();
  if(key){
  switch (key){
    case 'A':
    	schedule[0] = timeToChar();
    	lcd.clear();
    	lcd.setCursor(7,1),lcd.print("Time set!");
    	delay(1000);
    	lcd.clear();
    	timeString = "";
    	break;
    case 'B':
    	schedule[1] = timeToChar();
    	lcd.clear();
    	lcd.setCursor(7,1),lcd.print("Time set!");
    	delay(1000);
    	lcd.clear();
    	timeString = "";
    	break;
    case 'C':
    	schedule[2] = timeToChar();
    	lcd.clear();
    	lcd.setCursor(7,1),lcd.print("Time set!");
    	delay(1000);
    	lcd.clear();
    	timeString = "";
    	break;
    case 'D':
    	schedule[3] = timeToChar();
    	lcd.clear();
    	lcd.setCursor(7,1),lcd.print("Time set!");
    	delay(1000);
    	lcd.clear();
    	timeString = "";
    	break;
   	case '*':
    	setTimer();
    	lcd.clear();
    	lcd.setCursor(7,1),lcd.print("Time set!");
    	delay(1000);
    	lcd.clear();
    	timeString = "";
    	active = true;
    	break;
    case '#':
    	time = 0;
    	lcd.clear();
    	timeString = "";
    	break;
    case '1':
    	concat(1);
    	timeString.concat(1);
    	lcd.clear();
    	break;
    case '2':
    	concat(2);
    	timeString.concat(2);
    	lcd.clear();
    	break;
    case '3':
    	concat(3);
    	timeString.concat(3);
    	lcd.clear();
    	break;
    case '4':
    	concat(4);
    	timeString.concat(4);
    	lcd.clear();
    	break;
    case '5':
    	concat(5);
    	timeString.concat(5);
    	lcd.clear();
    	break;
    case '6':
    	concat(6);
    	timeString.concat(6);
    	lcd.clear();
    	break;
    case '7':
    	concat(7);
    	timeString.concat(7);
    	lcd.clear();
    	break;
    case '8':
    	concat(8);
    	timeString.concat(8);
    	lcd.clear();
    	break;
    case '9':
    	concat(9);
    	timeString.concat(9);
    	lcd.clear();
    	break;
    case '0':
    	concat(0);
    	timeString.concat(0);
    	lcd.clear();
    	break;
  }
  }
  
  if(timer > t && t > 0 && active == true){
    open();
    delay(1000);
    close();
    setTimer();
  }
  
  for (int i = 0; i < 4; i++){
    if(milisParaHora().equals(schedule[i]) == true){
    	open();
    	delay(1000);
    	close();
    	setTimer();
    }
  }
  
 
 if(locked == false){
   lcd.clear();
     lcd.setCursor(4,0),lcd.print("Feeding...");
   
 } else {
 	 lcd.setCursor(0,0),lcd.print(nivel);lcd.print(" ml");
     lcd.setCursor(9,1),lcd.print(timeString);
   	 lcd.setCursor(0,1),lcd.print(milisParaHora());
   	 digitalWrite(A1,HIGH);
  	 digitalWrite(A0,LOW);
 }
}