#include <LiquidCrystal.h>
#define BUTTON_PIN1 7 //levi taster ili taster 1 je na pin-u 7 na Arduinu
#define BUTTON_PIN2 6 //desni taster ili taster 2 je na pin-u 6 na Arduinu
#define VODA 8 // Relej koji aktivira pumpu za vodu je na pin-u 8 na Arduinu
#define SOK 9 // Relej koji aktivira pumpu za sok je na pin-u 9 na Arduinu
const int trigPin = 13; //trigger senzora je na pin-u 13
const int echoPin = 10; //echo senzora je na pin-u 10
long duration;
int distance;
int stanje = 0; //početno stanje bez pritiska na taster

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; // Inicijalizacija pinova LCD displeja
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  
  lcd.begin(16, 2); // Postavljamo broj kolona i redova LCD displeja
  
  pinMode(BUTTON_PIN1, INPUT); //Postavljanje pina za levi taster kao INPUT
  pinMode(BUTTON_PIN2, INPUT); //Postavljanje pina za desni taster kao INPUT
  pinMode(VODA, OUTPUT); //Postavljanje pina releja za vodu kao OUTPUT
  pinMode(SOK, OUTPUT); //Postavljanje pina releja za sok kao OUTPUT
  digitalWrite(VODA, HIGH); //početno stanje releja za vodu
  digitalWrite(SOK, HIGH); //početno stanje releja za sok
  pinMode(trigPin, OUTPUT); // Postavljanje trigger pina kao OUTPUT
  pinMode(echoPin, INPUT); // Postavljanje echo pina kao INPUT
// Ispisivanje početne poruke na LCD displeju prilikom uključivanja uređaja
  lcd.print("Izaberite pice");
  lcd.setCursor(0, 1);
  lcd.print("1)voda 2)sok");
}

void loop() {

 // Clears the trigPin
  digitalWrite(trigPin, LOW); //Ovde se postavlja pin (trigPin) na nisku vrednost kako bi se osiguralo da je pin isključen.
  delayMicroseconds(2); //pauza 2 mikrosekunde
  digitalWrite(trigPin, HIGH); //trigPin se postavlja na visoku vrednost, čime se šalje ultrazvučni talas.
  delayMicroseconds(10); //pauza 10 mikrosekundi
  digitalWrite(trigPin, LOW); // Ovim se zatvara impuls ultrazvučnog talasa - trigPin se ponovo postavlja na nisku vrednost.
  duration = pulseIn(echoPin, HIGH); //funkcija pulseIn() meri vreme koje je prošlo od slanja ultrazvučnog impulsa do njegovog prijema.
 //Ova vrednost se smešta u promenljivu duration.
  distance = duration * 0.034 / 2; //Udaljenost se izračunava množenjem vremena trajanja impulsa sa brzinom zvuka (0.034 cm/μs)
  //i deljenjem sa 2 (jer je vreme koje je mereno odnosi se na put u jednom smeru, a potrebno je udvostručiti ga
  // kako bi se dobila ukupna udaljenost). Rezultat se smešta u promenljivu distance, koja sada sadrži merenu udaljenost u centimetrima.

if (digitalRead(BUTTON_PIN1) == HIGH) {
  stanje =1;
}
if (digitalRead(BUTTON_PIN2) == HIGH) {
  stanje =2;
}
  lcd.setCursor(0, 0);
if (stanje==1) {
   lcd.clear();
   lcd.print("  Izabrali ste");  
   lcd.setCursor(0, 1);
   lcd.print("      vodu");

   if(distance<10)
   {
   digitalWrite(VODA, LOW);
   digitalWrite(SOK, HIGH);
   }
    else
   {
      digitalWrite(VODA, HIGH);
   }
  }
if (stanje==2) {
   lcd.clear();
   lcd.print("  Izabrali ste");  
   lcd.setCursor(0, 1);
   lcd.print("       sok");
     if(distance<10)
   {
   digitalWrite(SOK, LOW);
    digitalWrite(VODA, HIGH);
   }
   else
   {
      digitalWrite(SOK, HIGH);
   }
  }
 
}