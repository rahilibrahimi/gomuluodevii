#include <LiquidCrystal.h>
#include <Servo.h>  // Servo kütüphanesini projeme ekledim.

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


Servo servoM;  // Servo nesnemizi oluşturduk, ismini servoM yaptık.
int pos = 0;    // pos değişkenini oluşturup 0’a eşitledik.
  

#define buzzerPin A5
#define LED_KIRMIZI A0
#define LED_YESIL A1

// Hook up HC-SR04 with Trig to Arduino Pin 9, Echo to Arduino pin 10
const int TriggerPin = A4;
const int EchoPin = A3;

const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;

int counter = 0; //bir sayaç olarak counter ve başlangıç değeri olarak 0 kullandim ve belirli bir duruma bağlı olarak bu sayaç arttırılabilir veya azaltılabilir.
int topdur = 0; // Programın akışını yönlendirmek veya belirli bir durumu izlemek için bu değişken kullanıyorum

void setup(){   
  pinMode(buzzerPin, OUTPUT); 
  servoM.attach(ServoPin);

  pinMode(LED_KIRMIZI, OUTPUT);
  pinMode(LED_YESIL, OUTPUT);

  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  lcd.begin(16, 2);
  
  lcd.setCursor(3, 0);
  lcd.print("181906127");
  lcd.setCursor(1, 1);
  lcd.print("Rahil Ibrahimi");

  servoM.write(10);

  Serial.begin(9600);
}

void loop()
{
  lcd.clear();
  topdur = 0;

  unsigned long duration;
  int mesafe;

  digitalWrite(TriggerPin, LOW);
  delayMicroseconds(2); // Trigger pinini 10 saniye için high olarak ayarlıyorum ve 5 V gerilim uyguluyorum.
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);
  // echoPini okur ve ses dalgası mikrosaniye olarak döndürür.
  duration = pulseIn(EchoPin, HIGH); 
  mesafe = duration * 0.034 / 2;

  Serial.print("Mesafe: ");
  Serial.println(mesafe);

  lcd.setCursor(0, 0);
  lcd.print("M:");
  lcd.setCursor(2, 0);
  lcd.print(mesafe);
  lcd.setCursor(6, 0);
  lcd.print("181906127");
  lcd.setCursor(1, 1);
  lcd.print("Rahil Ibrahimi");

  delay(250);

  if (mesafe > 20) {
    digitalWrite(LED_KIRMIZI, LOW);
    lcd.setCursor(6, 0);
    lcd.print("181906127");
    lcd.setCursor(1, 1);
    lcd.print("Rahil Ibrahimi");
  }else{
    digitalWrite(LED_KIRMIZI, HIGH);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Donem Odevi");
    lcd.setCursor(3, 1);
    lcd.print("Bahar/2023");
    process();
  }
}

void process(){

  AtarGider();
  firstSection();
  AtarGider();
  secondSection();

  //Varyant 1
  beep(f, 250);
  beep(gS, 500);
  beep(f, 350);
  beep(a, 125);
  beep(cH, 500);
  beep(a, 375);
  beep(cH, 125);
  beep(eH, 650);

  AtarGider();
  delay(500);
  
  //2.tekrar
  secondSection();
  
  //Varyant 2
  beep(f, 250);
  beep(gS, 500);
  beep(f, 375);
  beep(cH, 125);
  beep(a, 500);
  beep(f, 375);
  beep(cH, 125);
  beep(a, 650);

  AtarGider();
  delay(500);
  AtarGider();
  delay(650);
}
void beep(int note, int duration)
{
//buzzerpin üzerinden melodi çalma
tone(buzzerPin, note, duration);

//ledlerin notalara göre yanma sönme işlemi olacak 
if(counter % 2 == 0)
{
digitalWrite(LED_KIRMIZI, HIGH);
delay(duration);
digitalWrite(LED_KIRMIZI, LOW);
}else
{
digitalWrite(LED_YESIL, HIGH);
delay(duration);
digitalWrite(LED_YESIL, LOW);
}

//buzzerı kapatma
noTone(buzzerPin);

delay(50);

topdur = topdur + duration; 
counter++;

//lcd.setCursor(10, 1);
int a = (topdur % 7000);
int spos = a / 78;

if (spos<=45){
  servoM.write(spos);
}else{
  servoM.write(90-spos);
}

//lcd.print(spos);
}

void firstSection()
{
beep(a, 500);
beep(a, 500);
beep(a, 500);
beep(f, 350);
beep(cH, 150);
beep(a, 500);
beep(f, 350);
beep(cH, 150);
beep(a, 650);

delay(500);

beep(eH, 500);
beep(eH, 500);
beep(eH, 500);
beep(fH, 350);
beep(cH, 150);
beep(gS, 500);
beep(f, 350);
beep(cH, 150);
beep(a, 650);

delay(500);
}

void secondSection()
{
beep(aH, 500);
beep(a, 300);
beep(a, 150);
beep(aH, 500);
beep(gSH, 325);
beep(gH, 175);
beep(fSH, 125);
beep(fH, 125);
beep(fSH, 250);

delay(325);

beep(aS, 250);
beep(dSH, 500);
beep(dH, 325);
beep(cSH, 175);
beep(cH, 125);
beep(b, 125);
beep(cH, 250);

delay(350);
}

void AtarGider(){
  servoM.write(180);
  delay(200);
  servoM.write(10);
  delay(200);
}
