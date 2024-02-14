//ho incluso sia la libreria che l'oggetto del display
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

//ho dichiarato/collocato i vari componenti e i loro valori
int puls_avanti=13;
int puls_indietro=12;
int puls_start=11;
int led=10;
int statopuls1=LOW;
int statopuls2=LOW;
int statopuls3=LOW;
int numero;

void setup() {
 //ho inizializzato sia la comunicazione seriale e la comunicazione col display, ho configurato i vari componenti come segue:
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(puls_avanti,INPUT);
  pinMode(puls_indietro,INPUT);
  pinMode(puls_start,INPUT);
  pinMode(led,OUTPUT);
}

void loop() {
 //in questa parte sto memorizzando i valori letti dei componenti alle varibili, e sto stampando nel monitor seriale i valori della variabile "numero"
  statopuls1=digitalRead(puls_avanti);
  statopuls2=digitalRead(puls_indietro);
  statopuls3=digitalRead(puls_start);
  Serial.println(numero);
  delay(100);

//in questa parte ho usato due pulsanti, dove, il primo se premuto, mi incrementa il numero 
  if(statopuls1==HIGH){
    numero++;
    delay(10);
  }

//invece quì, il secondo se premuto, mi decrementerà il numero 
  if(statopuls2==HIGH){
    numero--;
    delay(10);
  }

//in questa parte ho usato una struttura di controllo ingrado di gestire più scelte/condizioni
  switch(numero){

   //nel primo caso, quando la variabile "numero" avrà valore 0, mi andrà a stampare nel display come segue:
    case 0:
    lcd.setCursor(0,0);
    lcd.print("> led spento...");
    lcd.setCursor(0,1);
    lcd.print("  led acceso...");

    //all'interno di una struttura di controllo si può aggiungere altre strutture di controllo e in questo caso si è usato l'if
     //quando il pulsante è premuto, il led dovrà rimanere spento
      if(statopuls3==HIGH){
        digitalWrite(led,LOW);
      }
      break;

// nel secondo caso, quando la variabile avrà il valore 1, mi andrà a stampare nel display come segue:
    case 1:
      lcd.setCursor(0,0);
      lcd.print("  led spento...");
      lcd.setCursor(0,1);
      lcd.print("> led acceso...");
    //se il pulsante è premuto il led si accenderà
      if(statopuls3==HIGH){
        digitalWrite(led,HIGH);
      }
      //altrimenti il led si spegnerà
      else{
        digitalWrite(led,LOW);
      }
      break;

//nel terzo caso, mi andrà a stampare nel display come segue:
    case 2:
    lcd.setCursor(0,0);
    lcd.print("  led acceso...");
    lcd.setCursor(0,1);
    lcd.print("> led che lamp");

    //se il pulsante è premuto, mi farà lampeggiare il led usando un ciclo for
      if(statopuls3==HIGH){
        for(int i=0;i<5;i++){
          digitalWrite(led,HIGH);
          delay(1000);
          digitalWrite(led,LOW);
          delay(1000);
        }
      }
      break;

//in tutti gli altri casi, mi andrà a stampare nel display come segue:
    default:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("> nessuna cond.");
    delay(100);
  }

}
